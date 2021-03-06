/****************************************************************************
 * ($) 2011 - Lab408 - NTU CSIE/GINM
 ****************************************************************************
 */

#include <xen/config.h>
#include <xen/init.h>
#include <xen/lib.h>
#include <xen/sched.h>
#include <xen/domain.h>
#include <xen/delay.h>
#include <xen/event.h>
#include <xen/time.h>
#include <xen/perfc.h>
#include <xen/sched-if.h>
#include <xen/softirq.h>
#include <asm/atomic.h>
#include <xen/errno.h>
#include <xen/trace.h>
#include <xen/cpu.h>

#if __i386__
#define PRI_stime "lld"
#else
#define PRI_stime "ld"
#endif

#define d2printk(x...)

#define TRC_CSCHED2_TICK        TRC_SCHED_CLASS + 1
#define TRC_CSCHED2_RUNQ_POS    TRC_SCHED_CLASS + 2
#define TRC_CSCHED2_CREDIT_BURN TRC_SCHED_CLASS + 3
#define TRC_CSCHED2_CREDIT_ADD  TRC_SCHED_CLASS + 4
#define TRC_CSCHED2_TICKLE_CHECK TRC_SCHED_CLASS + 5
#define TRC_CSCHED2_TICKLE       TRC_SCHED_CLASS + 6
#define TRC_CSCHED2_CREDIT_RESET TRC_SCHED_CLASS + 7
#define TRC_CSCHED2_SCHED_TASKLET TRC_SCHED_CLASS + 8
#define TRC_CSCHED2_UPDATE_LOAD   TRC_SCHED_CLASS + 9
#define TRC_CSCHED2_RUNQ_ASSIGN   TRC_SCHED_CLASS + 10
#define TRC_CSCHED2_UPDATE_VCPU_LOAD   TRC_SCHED_CLASS + 11
#define TRC_CSCHED2_UPDATE_RUNQ_LOAD   TRC_SCHED_CLASS + 12

/* Default weight: How much a new domain starts with */
#define CSCHED_DEFAULT_WEIGHT       256
/* Min timer: Minimum length a timer will be set, to
 * achieve efficiency */
#define CSCHED_MIN_TIMER            MICROSECS(500)
/* Amount of credit VMs begin with, and are reset to.
 * ATM, set so that highest-weight VMs can only run for 10ms
 * before a reset event. */
#define CSCHED_CREDIT_INIT          MILLISECS(10)
/* Carryover: How much "extra" credit may be carried over after
 * a reset. */
#define CSCHED_CARRYOVER_MAX        CSCHED_MIN_TIMER
/* Stickiness: Cross-L2 migration resistance.  Should be less than
 * MIN_TIMER. */
#define CSCHED_MIGRATE_RESIST       ((opt_migrate_resist)*MICROSECS(1))
/* How much to "compensate" a vcpu for L2 migration */
#define CSCHED_MIGRATE_COMPENSATION MICROSECS(50)
/* Reset: Value below which credit will be reset. */
#define CSCHED_CREDIT_RESET         0
/* Max timer: Maximum time a guest can be run for. */
#define CSCHED_MAX_TIMER            MILLISECS(2)


#define CSCHED_IDLE_CREDIT                 (-(1<<30))

#define __CSFLAG_scheduled 1
#define CSFLAG_scheduled (1<<__CSFLAG_scheduled)
/* CSFLAG_delayed_runq_add: Do we need to add this to the runqueue once it'd done
 * being context switched out?
 * + Set when scheduling out in csched_schedule() if prev is runnable
 * + Set in csched_vcpu_wake if it finds CSFLAG_scheduled set
 * + Read in csched_context_saved().  If set, it adds prev to the runqueue and
 *   clears the bit.
 */
#define __CSFLAG_delayed_runq_add 2
#define CSFLAG_delayed_runq_add (1<<__CSFLAG_delayed_runq_add)
/* CSFLAG_runq_migrate_request: This vcpu is being migrated as a result of a
 * credit2-initiated runq migrate request; migrate it to the runqueue indicated
 * in the svc struct. 
 */
#define __CSFLAG_runq_migrate_request 3
#define CSFLAG_runq_migrate_request (1<<__CSFLAG_runq_migrate_request)


int opt_migrate_resist=500;
integer_param("sched_credit2_migrate_resist", opt_migrate_resist);

/*
 * Useful macros
 */
#define CSCHED_PRIV(_ops)   \
    ((struct csched_private *)((_ops)->sched_data))
#define CSCHED_VCPU(_vcpu)  ((struct csched_vcpu *) (_vcpu)->sched_priv)
#define CSCHED_DOM(_dom)    ((struct csched_dom *) (_dom)->sched_priv)
#define CSCHED_CPUONLINE(_pool)    \
    (((_pool) == NULL) ? &cpupool_free_cpus : &(_pool)->cpu_valid)
/* CPU to runq_id macro */
#define c2r(_ops, _cpu)     (CSCHED_PRIV(_ops)->runq_map[(_cpu)])
/* CPU to runqueue struct macro */
#define RQD(_ops, _cpu)     (&CSCHED_PRIV(_ops)->rqd[c2r(_ops, _cpu)])

/*
 * Shifts for load average.
 * - granularity: Reduce granularity of time by a factor of 1000, so we can use 32-bit maths
 * - window shift: Given granularity shift, make the window about 1 second
 * - scale shift: Shift up load by this amount rather than using fractions; 128 corresponds 
 *   to a load of 1.
 */
#define LOADAVG_GRANULARITY_SHIFT (10)
int opt_load_window_shift=18;
#define  LOADAVG_WINDOW_SHIFT_MIN 4
integer_param("credit2_load_window_shift", opt_load_window_shift);
int opt_underload_balance_tolerance=0;
integer_param("credit2_balance_under", opt_underload_balance_tolerance);
int opt_overload_balance_tolerance=-3;
integer_param("credit2_balance_over", opt_overload_balance_tolerance);

/*
 * Per-runqueue data
 */
struct csched_runqueue_data {
    int id;

    spinlock_t lock;      /* Lock for this runqueue. */
    cpumask_t active;      /* CPUs enabled for this runqueue */

    struct list_head runq; /* Ordered list of runnable vms */
    struct list_head svc;  /* List of all vcpus assigned to this runqueue */
    int max_weight;

    cpumask_t idle,        /* Currently idle */
        tickled;           /* Another cpu in the queue is already targeted for this one */
    int load;              /* Instantaneous load: Length of queue  + num non-idle threads */
    s_time_t load_last_update;  /* Last time average was updated */
    s_time_t avgload;           /* Decaying queue load */
    s_time_t b_avgload;         /* Decaying queue load modified by balancing */
};

/*
 * System-wide private data
 */
struct csched_private {
    spinlock_t lock;
    cpumask_t initialized; /* CPU is initialized for this pool */
    
    struct list_head sdom; /* Used mostly for dump keyhandler. */

    int runq_map[NR_CPUS];
    cpumask_t active_queues; /* Queues which may have active cpus */
    struct csched_runqueue_data rqd[NR_CPUS];

    int load_window_shift;
};

/*
 * Virtual CPU
 */
struct csched_vcpu {
    struct list_head rqd_elem;  /* On the runqueue data list */
    struct list_head sdom_elem; /* On the domain vcpu list */
    struct list_head runq_elem; /* On the runqueue         */
    struct csched_runqueue_data *rqd; /* Up-pointer to the runqueue */

    /* Up-pointers */
    struct csched_dom *sdom;
    struct vcpu *vcpu;

    int weight, cap, reserve;

    int xreq;
    int credit, usage;
    s_time_t start_time; /* When we were scheduled (used for credit) */
    unsigned flags;      /* 16 bits doesn't seem to play well with clear_bit() */

    /* Individual contribution to load */
    s_time_t load_last_update;  /* Last time average was updated */
    s_time_t avgload;           /* Decaying queue load */

    struct csched_runqueue_data *migrate_rqd; /* Pre-determined rqd to which to migrate */
};

/*
 * Domain
 */
struct csched_dom {
    struct list_head vcpu;
    struct list_head sdom_elem;
    struct domain *dom;
    uint16_t weight, cap, reserve;
    uint16_t nr_vcpus;
};


/*
 * Runqueue related code
 */

static /*inline*/ int
__vcpu_on_runq(struct csched_vcpu *svc)
{
    return !list_empty(&svc->runq_elem);
}

static /*inline*/ struct csched_vcpu *
__runq_elem(struct list_head *elem)
{
    return list_entry(elem, struct csched_vcpu, runq_elem);
}

static int
__runq_insert(struct list_head *runq, struct csched_vcpu *svc)
{
    struct list_head *iter;
    int pos = 0;

    d2printk("rqi d%dv%d\n",
           svc->vcpu->domain->domain_id,
           svc->vcpu->vcpu_id);

    BUG_ON(&svc->rqd->runq != runq);
    /* Idle vcpus not allowed on the runqueue anymore */
    BUG_ON(is_idle_vcpu(svc->vcpu));
    BUG_ON(svc->vcpu->is_running);
    BUG_ON(test_bit(__CSFLAG_scheduled, &svc->flags));

    list_for_each( iter, runq ) {
        pos++;
    }

    list_add_tail(&svc->runq_elem, iter);
    return pos;
}

static void
runq_insert(const struct scheduler *ops, unsigned int cpu, struct csched_vcpu *svc)
{
    struct list_head * runq = &RQD(ops, cpu)->runq;
    int pos = 0;

    ASSERT( spin_is_locked(per_cpu(schedule_data, cpu).schedule_lock) );

    BUG_ON( __vcpu_on_runq(svc) );
    BUG_ON( c2r(ops, cpu) != c2r(ops, svc->vcpu->processor) );

    pos = __runq_insert(runq, svc);

    {
        struct {
            unsigned dom:16,vcpu:16;
            unsigned pos;
        } d;
        d.dom = svc->vcpu->domain->domain_id;
        d.vcpu = svc->vcpu->vcpu_id;
        d.pos = pos;
        trace_var(TRC_CSCHED2_RUNQ_POS, 0,
                  sizeof(d),
                  (unsigned char *)&d);
    }

    return;
}

static inline void
__runq_remove(struct csched_vcpu *svc)
{
    BUG_ON( !__vcpu_on_runq(svc) );
    list_del_init(&svc->runq_elem);
}

/* Check to see if the item on the runqueue is higher priority than what's
 * currently running; if so, wake up the processor */
static /*inline*/ void
runq_tickle(const struct scheduler *ops, unsigned int cpu, struct csched_vcpu *new, s_time_t now)
{
    int ipid=-1;
    struct csched_runqueue_data *rqd = RQD(ops, cpu);
    struct csched_vcpu * cur;

    d2printk("rqt d%dv%d cd%dv%d\n",
             new->vcpu->domain->domain_id,
             new->vcpu->vcpu_id,
             current->domain->domain_id,
             current->vcpu_id);

    BUG_ON(new->vcpu->processor != cpu);
    BUG_ON(new->rqd != rqd);

    /* Look at the cpu it's running on first */
    cur = CSCHED_VCPU(per_cpu(schedule_data, cpu).curr);

   ipid = cpu;

   BUG_ON(ipid == -1);

    /* TRACE */ {
        struct {
            unsigned cpu:8;
        } d;
        d.cpu = ipid;
        trace_var(TRC_CSCHED2_TICKLE, 0,
                  sizeof(d),
                  (unsigned char *)&d);
    }
    cpu_set(ipid, rqd->tickled);
    cpu_raise_softirq(ipid, SCHEDULE_SOFTIRQ);

    return;
}

#ifndef NDEBUG
static /*inline*/ void
__csched_vcpu_check(struct vcpu *vc)
{
    struct csched_vcpu * const svc = CSCHED_VCPU(vc);
    struct csched_dom * const sdom = svc->sdom;

    BUG_ON( svc->vcpu != vc );
    BUG_ON( sdom != CSCHED_DOM(vc->domain) );
    if ( sdom )
    {
        BUG_ON( is_idle_vcpu(vc) );
        BUG_ON( sdom->dom != vc->domain );
    }
    else
    {
        BUG_ON( !is_idle_vcpu(vc) );
    }
}
#define CSCHED_VCPU_CHECK(_vc)  (__csched_vcpu_check(_vc))
#else
#define CSCHED_VCPU_CHECK(_vc)
#endif

static void *
csched_alloc_vdata(const struct scheduler *ops, struct vcpu *vc, void *dd)
{
    struct csched_vcpu *svc;

    /* Allocate per-VCPU info */
    svc = xmalloc(struct csched_vcpu);
    if ( svc == NULL )
        return NULL;
    memset(svc, 0, sizeof(*svc));

    INIT_LIST_HEAD(&svc->rqd_elem);
    INIT_LIST_HEAD(&svc->sdom_elem);
    INIT_LIST_HEAD(&svc->runq_elem);

    svc->sdom = dd;
    svc->vcpu = vc;
    svc->flags = 0U;

    if ( ! is_idle_vcpu(vc) )
    {
        BUG_ON( svc->sdom == NULL );

        svc->weight = svc->sdom->weight;
        svc->reserve = 0;
        svc->cap = 100;
        /* Starting load of 50% */
        svc->avgload = 1ULL << (CSCHED_PRIV(ops)->load_window_shift - 1);
        svc->load_last_update = NOW();
    }
    else
    {
        BUG_ON( svc->sdom != NULL );
        svc->weight = 0;
    }

    return svc;
}

/* Add and remove from runqueue assignment (not active run queue) */
static void
__runq_assign(struct csched_vcpu *svc, struct csched_runqueue_data *rqd)
{

    svc->rqd = rqd;
    list_add_tail(&svc->rqd_elem, &svc->rqd->svc);


    /* Expected new load based on adding this vcpu */
    rqd->b_avgload += svc->avgload;

    /* TRACE */
    {
        struct {
            unsigned dom:16,vcpu:16;
            unsigned rqi:16;
        } d;
        d.dom = svc->vcpu->domain->domain_id;
        d.vcpu = svc->vcpu->vcpu_id;
        d.rqi=rqd->id;
        trace_var(TRC_CSCHED2_RUNQ_ASSIGN, 1,
                  sizeof(d),
                  (unsigned char *)&d);
    }

}

static void
runq_assign(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_vcpu *svc = vc->sched_priv;

    BUG_ON(svc->rqd != NULL);

    __runq_assign(svc, RQD(ops, vc->processor));
}

static void
__runq_deassign(struct csched_vcpu *svc)
{
    BUG_ON(__vcpu_on_runq(svc));

    list_del_init(&svc->rqd_elem);

    /* Expected new load based on removing this vcpu */
    svc->rqd->b_avgload -= svc->avgload;

    svc->rqd = NULL;
}

static void
runq_deassign(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_vcpu *svc = vc->sched_priv;

    BUG_ON(svc->rqd != RQD(ops, vc->processor));

    __runq_deassign(svc);
}

static void
csched_vcpu_insert(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_vcpu *svc = vc->sched_priv;
    struct domain * const dom = vc->domain;
    struct csched_dom * const sdom = svc->sdom;

    printk("%s: Inserting d%d v%d\n",
           __func__, dom->domain_id, vc->vcpu_id);

    /* NB: On boot, idle vcpus are inserted before alloc_pdata() has
     * been called for that cpu.
     */
    if ( ! is_idle_vcpu(vc) )
    {
        /* FIXME: Do we need the private lock here? */
        list_add_tail(&svc->sdom_elem, &svc->sdom->vcpu);

        /* Add vcpu to runqueue of initial processor */
        vcpu_schedule_lock_irq(vc);

        runq_assign(ops, vc);

        vcpu_schedule_unlock_irq(vc);

        sdom->nr_vcpus++;
    }

    CSCHED_VCPU_CHECK(vc);
}

static void
csched_free_vdata(const struct scheduler *ops, void *priv)
{
    struct csched_vcpu *svc = priv;

    xfree(svc);
}

static void
csched_vcpu_remove(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_vcpu * const svc = CSCHED_VCPU(vc);
    struct csched_dom * const sdom = svc->sdom;

    BUG_ON( sdom == NULL );
    BUG_ON( !list_empty(&svc->runq_elem) );

    if ( ! is_idle_vcpu(vc) )
    {
        /* Remove from runqueue */
        vcpu_schedule_lock_irq(vc);

        runq_deassign(ops, vc);

        vcpu_schedule_unlock_irq(vc);

        /* Remove from sdom list.  Don't need a lock for this, as it's called
         * syncronously when nothing else can happen. */
        list_del_init(&svc->sdom_elem);

        svc->sdom->nr_vcpus--;
    }
}

static void
csched_vcpu_sleep(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_vcpu * const svc = CSCHED_VCPU(vc);

    BUG_ON( is_idle_vcpu(vc) );

    if ( per_cpu(schedule_data, vc->processor).curr == vc )
        cpu_raise_softirq(vc->processor, SCHEDULE_SOFTIRQ);
    else if ( __vcpu_on_runq(svc) )
    {
        BUG_ON(svc->rqd != RQD(ops, vc->processor));
        __runq_remove(svc);
    }
    else if ( test_bit(__CSFLAG_delayed_runq_add, &svc->flags) )
        clear_bit(__CSFLAG_delayed_runq_add, &svc->flags);
}

static void
csched_vcpu_wake(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_vcpu * const svc = CSCHED_VCPU(vc);
    s_time_t now = 0;

    /* Schedule lock should be held at this point. */

    d2printk("w d%dv%d\n", vc->domain->domain_id, vc->vcpu_id);

    BUG_ON( is_idle_vcpu(vc) );

    /* Make sure svc priority mod happens before runq check */
    if ( unlikely(per_cpu(schedule_data, vc->processor).curr == vc) )
    {
        goto out;
    }

    if ( unlikely(__vcpu_on_runq(svc)) )
    {
        /* If we've boosted someone that's already on a runqueue, prioritize
         * it and inform the cpu in question. */
        goto out;
    }

    /* If the context hasn't been saved for this vcpu yet, we can't put it on
     * another runqueue.  Instead, we set a flag so that it will be put on the runqueue
     * after the context has been saved. */
    if ( unlikely (test_bit(__CSFLAG_scheduled, &svc->flags) ) )
    {
        set_bit(__CSFLAG_delayed_runq_add, &svc->flags);
        goto out;
    }

    /* Add into the new runqueue if necessary */
    if ( svc->rqd == NULL )
        runq_assign(ops, vc);
    else
        BUG_ON(RQD(ops, vc->processor) != svc->rqd );

    now = NOW();

        
    /* Put the VCPU on the runq */
    runq_insert(ops, vc->processor, svc);
    runq_tickle(ops, vc->processor, svc, now);

out:
    d2printk("w-\n");
    return;
}

static void
csched_context_saved(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_vcpu * const svc = CSCHED_VCPU(vc);
    s_time_t now = NOW();

    vcpu_schedule_lock_irq(vc);

    BUG_ON( !is_idle_vcpu(vc) && svc->rqd != RQD(ops, vc->processor));

    /* This vcpu is now eligible to be put on the runqueue again */
    clear_bit(__CSFLAG_scheduled, &svc->flags);

    /* If someone wants it on the runqueue, put it there. */
    /*
     * NB: We can get rid of CSFLAG_scheduled by checking for
     * vc->is_running and __vcpu_on_runq(svc) here.  However,
     * since we're accessing the flags cacheline anyway,
     * it seems a bit pointless; especially as we have plenty of
     * bits free.
     */
    if ( test_and_clear_bit(__CSFLAG_delayed_runq_add, &svc->flags)
         && likely(vcpu_runnable(vc)) )
    {
        BUG_ON(__vcpu_on_runq(svc));

        runq_insert(ops, vc->processor, svc);
        runq_tickle(ops, vc->processor, svc, now);
    }

    vcpu_schedule_unlock_irq(vc);
}

#define MAX_LOAD (1ULL<<60);
static int
choose_cpu(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_private *prv = CSCHED_PRIV(ops);
    int i, min_rqi = -1, new_cpu;
    struct csched_vcpu *svc = CSCHED_VCPU(vc);
    s_time_t min_avgload;

    BUG_ON(cpus_empty(prv->active_queues));

    /* Locking:
     * - vc->processor is already locked
     * - Need to grab prv lock to make sure active runqueues don't
     *   change
     * - Need to grab locks for other runqueues while checking
     *   avgload
     * Locking constraint is:
     * - Lock prv before runqueue locks
     * - Trylock between runqueue locks (no ordering)
     *
     * Since one of the runqueue locks is already held, we can't
     * just grab the prv lock.  Instead, we'll have to trylock, and
     * do something else reasonable if we fail.
     */

    if ( !spin_trylock(&prv->lock) )
    {
        if ( test_and_clear_bit(__CSFLAG_runq_migrate_request, &svc->flags) )
        {
            d2printk("d%dv%d -\n", svc->vcpu->domain->domain_id, svc->vcpu->vcpu_id);
            clear_bit(__CSFLAG_runq_migrate_request, &svc->flags);
        }
        /* Leave it where it is for now.  When we actually pay attention
         * to affinity we'll have to figure something out... */
        return vc->processor;
    }

    /* First check to see if we're here because someone else suggested a place
     * for us to move. */
    if ( test_and_clear_bit(__CSFLAG_runq_migrate_request, &svc->flags) )
    {
        if ( unlikely(svc->migrate_rqd->id < 0) )
        {
            printk("%s: Runqueue migrate aborted because target runqueue disappeared!\n",
                   __func__);
            /* Fall-through to normal cpu pick */
        }
        else
        {
            d2printk("d%dv%d +\n", svc->vcpu->domain->domain_id, svc->vcpu->vcpu_id);
            new_cpu = first_cpu(svc->migrate_rqd->active);
            goto out_up;
        }
    }

    /* FIXME: Pay attention to cpu affinity */                                                                                      

    min_avgload = MAX_LOAD;

    /* Find the runqueue with the lowest instantaneous load */
    for_each_cpu_mask(i, prv->active_queues)
    {
        struct csched_runqueue_data *rqd;
        s_time_t rqd_avgload;

        rqd = prv->rqd + i;

        /* If checking a different runqueue, grab the lock,
         * read the avg, and then release the lock.
         *
         * If on our own runqueue, don't grab or release the lock;
         * but subtract our own load from the runqueue load to simulate
         * impartiality */
        if ( rqd == svc->rqd )
        {
            rqd_avgload = rqd->b_avgload - svc->avgload;
        }
        else if ( spin_trylock(&rqd->lock) )
        {
            rqd_avgload = rqd->b_avgload;
            spin_unlock(&rqd->lock);
        }
        else
            continue;

        if ( rqd_avgload < min_avgload )
        {
            min_avgload = rqd_avgload;
            min_rqi=i;
        }
    }

    /* We didn't find anyone (most likely because of spinlock contention); leave it where it is */
    if ( min_rqi == -1 )
        new_cpu = vc->processor;
    else
    {
        BUG_ON(cpus_empty(prv->rqd[min_rqi].active));
        new_cpu = first_cpu(prv->rqd[min_rqi].active);
    }

out_up:
    spin_unlock(&prv->lock);

    return new_cpu;
}

static int
csched_cpu_pick(const struct scheduler *ops, struct vcpu *vc)
{
    struct csched_vcpu * const svc = CSCHED_VCPU(vc);
    int new_cpu;

    /* The scheduler interface doesn't have an explicit mechanism to
     * involve the choosable scheduler in the migrate process, so we
     * infer that a change may happen by the call to cpu_pick, and
     * remove it from the old runqueue while the lock for the old
     * runqueue is held.  It can't be actively waiting to run.  It
     * will be added to the new runqueue when it next wakes.
     *
     * If we want to be able to call pick() separately, we need to add
     * a mechansim to remove a vcpu from an old processor / runqueue
     * before releasing the lock. */
    BUG_ON(__vcpu_on_runq(svc));

    new_cpu = choose_cpu(ops, vc);
    /* If we're suggesting moving to a different runqueue, remove it
     * from the old runqueue while we have the lock.  It will be added
     * to the new one when it wakes. */
    if ( svc->rqd != NULL
         && RQD(ops, new_cpu) != svc->rqd )
        runq_deassign(ops, vc);

    return new_cpu;
}

static int
csched_dom_cntl(
    const struct scheduler *ops,
    struct domain *d,
    struct xen_domctl_scheduler_op *op)
{
    struct csched_dom * const sdom = CSCHED_DOM(d);
    struct csched_private *prv = CSCHED_PRIV(ops);
    unsigned long flags;

    if ( op->cmd == XEN_DOMCTL_SCHEDOP_getinfo )
    {
        op->u.credit2.weight = sdom->weight;
    }
    else
    {
        ASSERT(op->cmd == XEN_DOMCTL_SCHEDOP_putinfo);

        if ( op->u.credit2.weight != 0 )
        {
            struct list_head *iter;
            int old_weight;

            /* Must hold csched_priv lock to update sdom, runq lock to
             * update csvcs. */
            spin_lock_irqsave(&prv->lock, flags);

            old_weight = sdom->weight;

            sdom->weight = op->u.credit2.weight;

            /* Update weights for vcpus, and max_weight for runqueues on which they reside */
            list_for_each ( iter, &sdom->vcpu )
            {
                struct csched_vcpu *svc = list_entry(iter, struct csched_vcpu, sdom_elem);

                /* NB: Locking order is important here.  Because we grab this lock here, we
                 * must never lock csched_priv.lock if we're holding a runqueue
                 * lock. */
                vcpu_schedule_lock_irq(svc->vcpu);

                BUG_ON(svc->rqd != RQD(ops, svc->vcpu->processor));

                svc->weight = sdom->weight;

                vcpu_schedule_unlock_irq(svc->vcpu);
            }

            spin_unlock_irqrestore(&prv->lock, flags);
        }
    }

    return 0;
}

static void *
csched_alloc_domdata(const struct scheduler *ops, struct domain *dom)
{
    struct csched_dom *sdom;
    int flags;

    sdom = xmalloc(struct csched_dom);
    if ( sdom == NULL )
        return NULL;
    memset(sdom, 0, sizeof(*sdom));

    /* Initialize credit and weight */
    INIT_LIST_HEAD(&sdom->vcpu);
    INIT_LIST_HEAD(&sdom->sdom_elem);
    sdom->dom = dom;
    sdom->weight = CSCHED_DEFAULT_WEIGHT;
    sdom->nr_vcpus = 0;

    spin_lock_irqsave(&CSCHED_PRIV(ops)->lock, flags);

    list_add_tail(&sdom->sdom_elem, &CSCHED_PRIV(ops)->sdom);

    spin_unlock_irqrestore(&CSCHED_PRIV(ops)->lock, flags);

    return (void *)sdom;
}

static int
csched_dom_init(const struct scheduler *ops, struct domain *dom)
{
    struct csched_dom *sdom;

    printk("%s: Initializing domain %d\n", __func__, dom->domain_id);

    if ( is_idle_domain(dom) )
        return 0;

    sdom = csched_alloc_domdata(ops, dom);
    if ( sdom == NULL )
        return -ENOMEM;

    dom->sched_priv = sdom;

    return 0;
}

static void
csched_free_domdata(const struct scheduler *ops, void *data)
{
    int flags;
    struct csched_dom *sdom = data;

    spin_lock_irqsave(&CSCHED_PRIV(ops)->lock, flags);

    list_del_init(&sdom->sdom_elem);

    spin_unlock_irqrestore(&CSCHED_PRIV(ops)->lock, flags);

    xfree(data);
}

static void
csched_dom_destroy(const struct scheduler *ops, struct domain *dom)
{
    struct csched_dom *sdom = CSCHED_DOM(dom);

    BUG_ON(!list_empty(&sdom->vcpu));

    csched_free_domdata(ops, CSCHED_DOM(dom));
}

/* How long should we let this vcpu run for? */
static s_time_t
csched_runtime(const struct scheduler *ops, int cpu, struct csched_vcpu *snext)
{
    return CSCHED_MAX_TIMER;
}

void __dump_execstate(void *unused);

/*
 * Find a candidate.
 */
static struct csched_vcpu *
runq_candidate(struct csched_runqueue_data *rqd,
               struct csched_vcpu *scurr,
               int cpu, s_time_t now)
{
    struct list_head *iter;
    struct csched_vcpu *snext = NULL;

    /* Default to current if runnable, idle otherwise */
    if ( vcpu_runnable(scurr->vcpu) )
        snext = scurr;
    else
        snext = CSCHED_VCPU(idle_vcpu[cpu]);

    list_for_each( iter, &rqd->runq )
    {
        struct csched_vcpu * svc = list_entry(iter, struct csched_vcpu, runq_elem);

        snext = svc;

        /* In any case, if we got this far, break. */
        break;

    }

    return snext;
}

/*
 * This function is in the critical path. It is designed to be simple and
 * fast for the common case.
 */
static struct task_slice
csched_schedule(
    const struct scheduler *ops, s_time_t now, bool_t tasklet_work_scheduled)
{
    const int cpu = smp_processor_id();
    struct csched_runqueue_data *rqd;
    struct csched_vcpu * const scurr = CSCHED_VCPU(current);
    struct csched_vcpu *snext = NULL;
    struct task_slice ret;

    CSCHED_VCPU_CHECK(current);

    d2printk("sc p%d c d%dv%d now %"PRI_stime"\n",
             cpu,
             scurr->vcpu->domain->domain_id,
             scurr->vcpu->vcpu_id,
             now);

    BUG_ON(!cpu_isset(cpu, CSCHED_PRIV(ops)->initialized));

    rqd = RQD(ops, cpu);
    BUG_ON(!cpu_isset(cpu, rqd->active));

    /* Protected by runqueue lock */        

    BUG_ON(!is_idle_vcpu(scurr->vcpu) && scurr->rqd != rqd);

    /* Clear "tickled" bit now that we've been scheduled */
    if ( cpu_isset(cpu, rqd->tickled) )
        cpu_clear(cpu, rqd->tickled);

    /*
     * Select next runnable local VCPU (ie top of local runq).
     *
     * If the current vcpu is runnable, and has higher credit than
     * the next guy on the queue (or there is noone else), we want to
     * run him again.
     *
     * If there's tasklet work to do, we want to chose the idle vcpu
     * for this processor, and mark the current for delayed runqueue
     * add.
     *
     * If the current vcpu is runnable, and there's another runnable
     * candidate, we want to mark current for delayed runqueue add,
     * and remove the next guy from the queue.
     *
     * If the current vcpu is not runnable, we want to chose the idle
     * vcpu for this processor.
     */
    if ( tasklet_work_scheduled )
    {
        trace_var(TRC_CSCHED2_SCHED_TASKLET, 0, 0,  NULL);
        snext = CSCHED_VCPU(idle_vcpu[cpu]);
    }
    else
        snext=runq_candidate(rqd, scurr, cpu, now);

    /* If switching from a non-idle runnable vcpu, put it
     * back on the runqueue. */
    if ( snext != scurr
         && !is_idle_vcpu(scurr->vcpu)
         && vcpu_runnable(current) )
        set_bit(__CSFLAG_delayed_runq_add, &scurr->flags);

    ret.migrated = 0;

    /* Accounting for non-idle tasks */
    if ( !is_idle_vcpu(snext->vcpu) )
    {
        /* If switching, remove this from the runqueue and mark it scheduled */
        if ( snext != scurr )
        {
            BUG_ON(snext->rqd != rqd);
    
            __runq_remove(snext);
            if ( snext->vcpu->is_running )
            {
                printk("p%d: snext d%dv%d running on p%d! scurr d%dv%d\n",
                       cpu,
                       snext->vcpu->domain->domain_id, snext->vcpu->vcpu_id,
                       snext->vcpu->processor,
                       scurr->vcpu->domain->domain_id,
                       scurr->vcpu->vcpu_id);
                BUG();
            }
            set_bit(__CSFLAG_scheduled, &snext->flags);
        }

        /* Clear the idle mask if necessary */
        if ( cpu_isset(cpu, rqd->idle) )
            cpu_clear(cpu, rqd->idle);

        snext->start_time = now;

        /* Safe because lock for old processor is held */
        if ( snext->vcpu->processor != cpu )
        {
            snext->vcpu->processor = cpu;
            ret.migrated = 1;
        }
    }
    else
    {
        /* Update the idle mask if necessary */
        if ( !cpu_isset(cpu, rqd->idle) )
            cpu_set(cpu, rqd->idle);
        /* Make sure avgload gets updated periodically even
         * if there's no activity */
    }

    /*
     * Return task to run next...
     */
    ret.time = csched_runtime(ops, cpu, snext);
    ret.task = snext->vcpu;

    CSCHED_VCPU_CHECK(ret.task);
    return ret;
}

static void
csched_dump_vcpu(struct csched_vcpu *svc)
{
    printk("[%i.%i] flags=%x cpu=%i",
            svc->vcpu->domain->domain_id,
            svc->vcpu->vcpu_id,
            svc->flags,
            svc->vcpu->processor);

    printk(" credit=%" PRIi32" [w=%u]", svc->credit, svc->weight);

    printk("\n");
}

static void
csched_dump_pcpu(const struct scheduler *ops, int cpu)
{
    struct list_head *runq, *iter;
    struct csched_vcpu *svc;
    int loop;
    char cpustr[100];

    /* FIXME: Do locking properly for access to runqueue structures */

    runq = &RQD(ops, cpu)->runq;

    cpumask_scnprintf(cpustr, sizeof(cpustr), per_cpu(cpu_sibling_map,cpu));
    printk(" sibling=%s, ", cpustr);
    cpumask_scnprintf(cpustr, sizeof(cpustr), per_cpu(cpu_core_map,cpu));
    printk("core=%s\n", cpustr);

    /* current VCPU */
    svc = CSCHED_VCPU(per_cpu(schedule_data, cpu).curr);
    if ( svc )
    {
        printk("\trun: ");
        csched_dump_vcpu(svc);
    }

    loop = 0;
    list_for_each( iter, runq )
    {
        svc = __runq_elem(iter);
        if ( svc )
        {
            printk("\t%3d: ", ++loop);
            csched_dump_vcpu(svc);
        }
    }
}

static void
csched_dump(const struct scheduler *ops)
{
    struct list_head *iter_sdom, *iter_svc;
    struct csched_private *prv = CSCHED_PRIV(ops);
    int i, loop;

    printk("Active queues: %d\n"
           "\tdefault-weight     = %d\n",
           cpus_weight(prv->active_queues),
           CSCHED_DEFAULT_WEIGHT);
    for_each_cpu_mask(i, prv->active_queues)
    {
        s_time_t fraction;
        
        fraction = prv->rqd[i].avgload * 100 / (1ULL<<prv->load_window_shift);

        printk("Runqueue %d:\n"
               "\tncpus              = %u\n"
               "\tmax_weight         = %d\n"
               "\tinstload           = %d\n"
               "\taveload            = %3"PRI_stime"\n",
               i,
               cpus_weight(prv->rqd[i].active),
               prv->rqd[i].max_weight,
               prv->rqd[i].load,
               fraction);

    }
    /* FIXME: Locking! */

    printk("Domain info:\n");
    loop = 0;
    list_for_each( iter_sdom, &prv->sdom )
    {
        struct csched_dom *sdom;
        sdom = list_entry(iter_sdom, struct csched_dom, sdom_elem);

       printk("\tDomain: %d w %d v %d\n\t", 
              sdom->dom->domain_id, 
              sdom->weight, 
              sdom->nr_vcpus);

        list_for_each( iter_svc, &sdom->vcpu )
        {
            struct csched_vcpu *svc;
            svc = list_entry(iter_svc, struct csched_vcpu, sdom_elem);

            printk("\t%3d: ", ++loop);
            csched_dump_vcpu(svc);
        }
    }
}

static void activate_runqueue(struct csched_private *prv, int rqi)
{
    struct csched_runqueue_data *rqd;

    rqd = prv->rqd + rqi;

    BUG_ON(!cpus_empty(rqd->active));

    rqd->max_weight = 1;
    rqd->id = rqi;
    INIT_LIST_HEAD(&rqd->svc);
    INIT_LIST_HEAD(&rqd->runq);
    spin_lock_init(&rqd->lock);

    cpu_set(rqi, prv->active_queues);
}

static void deactivate_runqueue(struct csched_private *prv, int rqi)
{
    struct csched_runqueue_data *rqd;

    rqd = prv->rqd + rqi;

    BUG_ON(!cpus_empty(rqd->active));
    
    rqd->id = -1;

    cpu_clear(rqi, prv->active_queues);
}

static void init_pcpu(const struct scheduler *ops, int cpu)
{
    int rqi, old_rqi, flags;
    struct csched_private *prv = CSCHED_PRIV(ops);
    struct csched_runqueue_data *rqd;
    spinlock_t *old_lock;

    spin_lock_irqsave(&prv->lock, flags);

    if ( cpu_isset(cpu, prv->initialized) )
    {
        printk("%s: Strange, cpu %d already initialized!\n", __func__, cpu);
        spin_unlock_irqrestore(&prv->lock, flags);
        return;
    }

    old_rqi = prv->runq_map[cpu];

    /* Figure out which runqueue to put it in */
    rqi = 0;

    /* Figure out which runqueue to put it in */
    /* NB: cpu 0 doesn't get a STARTING callback, so we hard-code it to runqueue 0. */
    if ( cpu == 0 )
        rqi = 0;
    else
        rqi = cpu_to_socket(cpu);

    if ( rqi < 0 )
    {
        printk("%s: cpu_to_socket(%d) returned %d!\n",
               __func__, cpu, rqi);
        BUG();
    }

    rqd=prv->rqd + rqi;

    printk("Adding cpu %d to runqueue %d\n", cpu, rqi);
    if ( ! cpu_isset(rqi, prv->active_queues) )
    {
        printk(" First cpu on runqueue, activating\n");
        activate_runqueue(prv, rqi);
    }
    
    /* IRQs already disabled */
    old_lock=pcpu_schedule_lock(cpu);

    /* Move spinlock to new runq lock.  */
    per_cpu(schedule_data, cpu).schedule_lock = &rqd->lock;

    /* Set the runqueue map */
    prv->runq_map[cpu]=rqi;
    
    cpu_set(cpu, rqd->idle);
    cpu_set(cpu, rqd->active);

    spin_unlock(old_lock);

    cpu_set(cpu, prv->initialized);

    spin_unlock_irqrestore(&prv->lock, flags);

    return;
}

static void *
csched_alloc_pdata(const struct scheduler *ops, int cpu)
{
    /* Check to see if the cpu is online yet */
    /* Note: cpu 0 doesn't get a STARTING callback */
    if ( cpu == 0 || cpu_to_socket(cpu) >= 0 )
        init_pcpu(ops, cpu);
    else
        printk("%s: cpu %d not online yet, deferring initializatgion\n",
               __func__, cpu);

    return (void *)1;
}

static void
csched_free_pdata(const struct scheduler *ops, void *pcpu, int cpu)
{
    unsigned long flags;
    struct csched_private *prv = CSCHED_PRIV(ops);
    struct csched_runqueue_data *rqd;
    int rqi;

    spin_lock_irqsave(&prv->lock, flags);

    BUG_ON( !cpu_isset(cpu, prv->initialized));
    
    /* Find the old runqueue and remove this cpu from it */
    rqi = prv->runq_map[cpu];

    rqd = prv->rqd + rqi;

    /* No need to save IRQs here, they're already disabled */
    spin_lock(&rqd->lock);

    BUG_ON(!cpu_isset(cpu, rqd->idle));

    printk("Removing cpu %d from runqueue %d\n", cpu, rqi);

    cpu_clear(cpu, rqd->idle);
    cpu_clear(cpu, rqd->active);

    if ( cpus_empty(rqd->active) )
    {
        printk(" No cpus left on runqueue, disabling\n");
        deactivate_runqueue(prv, rqi);
    }

    spin_unlock(&rqd->lock);

    cpu_clear(cpu, prv->initialized);

    spin_unlock_irqrestore(&prv->lock, flags);

    return;
}

static int
csched_cpu_starting(int cpu)
{
    struct scheduler *ops;

    /* Hope this is safe from cpupools switching things around. :-) */
    ops = per_cpu(scheduler, cpu);

    init_pcpu(ops, cpu);

    return NOTIFY_DONE;
}

static int cpu_credit2_callback(
    struct notifier_block *nfb, unsigned long action, void *hcpu)
{
    unsigned int cpu = (unsigned long)hcpu;
    int rc = 0;

    switch ( action )
    {
    case CPU_STARTING:
        csched_cpu_starting(cpu);
        break;
    default:
        break;
    }

    return !rc ? NOTIFY_DONE : notifier_from_errno(rc);
}

static struct notifier_block cpu_credit2_nfb = {
    .notifier_call = cpu_credit2_callback
};

static int
csched_init(struct scheduler *ops)
{
    int i;
    struct csched_private *prv;

    printk("Initializing Credit2 scheduler\n" \
           " WARNING: This is experimental software in development.\n" \
           " Use at your own risk.\n");

    printk(" load_window_shift: %d\n", opt_load_window_shift);
    printk(" underload_balance_tolerance: %d\n", opt_underload_balance_tolerance);
    printk(" overload_balance_tolerance: %d\n", opt_overload_balance_tolerance);

    if ( opt_load_window_shift < LOADAVG_WINDOW_SHIFT_MIN )
    {
        printk("%s: opt_load_window_shift %d below min %d, resetting\n",
               __func__, opt_load_window_shift, LOADAVG_WINDOW_SHIFT_MIN);
        opt_load_window_shift = LOADAVG_WINDOW_SHIFT_MIN;
    }

    /* Basically no CPU information is available at this point; just
     * set up basic structures, and a callback when the CPU info is
     * available. */

    prv = xmalloc(struct csched_private);
    if ( prv == NULL )
        return -ENOMEM;
    memset(prv, 0, sizeof(*prv));
    ops->sched_data = prv;
    spin_lock_init(&prv->lock);
    INIT_LIST_HEAD(&prv->sdom);

    register_cpu_notifier(&cpu_credit2_nfb);

    /* But un-initialize all runqueues */
    for ( i=0; i<NR_CPUS; i++)
    {
        prv->runq_map[i] = -1;
        prv->rqd[i].id = -1;
    }

    prv->load_window_shift = opt_load_window_shift;

    return 0;
}

static void
csched_deinit(const struct scheduler *ops)
{
    struct csched_private *prv;

    prv = CSCHED_PRIV(ops);
    if ( prv != NULL )
        xfree(prv);
}


static struct csched_private _csched_priv;

const struct scheduler sched_credit2_def = {
    .name           = "SMP Credit Scheduler rev2",
    .opt_name       = "credit2",
    .sched_id       = XEN_SCHEDULER_CREDIT2,
    .sched_data     = &_csched_priv,

    .init_domain    = csched_dom_init,
    .destroy_domain = csched_dom_destroy,

    .insert_vcpu    = csched_vcpu_insert,
    .remove_vcpu    = csched_vcpu_remove,

    .sleep          = csched_vcpu_sleep,
    .wake           = csched_vcpu_wake,

    .adjust         = csched_dom_cntl,

    .pick_cpu       = csched_cpu_pick,
    .do_schedule    = csched_schedule,
    .context_saved  = csched_context_saved,

    .dump_cpu_state = csched_dump_pcpu,
    .dump_settings  = csched_dump,
    .init           = csched_init,
    .deinit         = csched_deinit,
    .alloc_vdata    = csched_alloc_vdata,
    .free_vdata     = csched_free_vdata,
    .alloc_pdata    = csched_alloc_pdata,
    .free_pdata     = csched_free_pdata,
    .alloc_domdata  = csched_alloc_domdata,
    .free_domdata   = csched_free_domdata,
};
