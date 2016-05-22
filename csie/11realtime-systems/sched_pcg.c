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

struct pcg_private {
    spinlock_t lock;
    cpumask_t initialized; /* CPU is initialized for this pool */
    
    struct list_head sdom; /* Used mostly for dump keyhandler. */

    int runq_map[NR_CPUS];
    cpumask_t active_queues; /* Queues which may have active cpus */
    struct pcg_runqueue_data rqd[NR_CPUS];

    int load_window_shift;
};

static struct pcg_private _pcg_priv;

struct pcg_dom {
  //List vcpu
  //List sdom_elem
  struct domain *dom;
  uint16_t weight;
  uint16_t nr_vcpus;  
}; 

static void *pcg_alloc_domdata(const struct scheduler *ops, struct domain *dom) {

}

static void *pcg_free_domdata(const struct scheduler *ops, struct domain *dom) {

}

static int pcg_dom_init(const struct scheduler *ops, struct domain *dom) {
  printk("%s: Initializing domain %d\n", __func__, dom->domain_id);
  if (is_idle_domain(dom)) return 0;

  struct pcg_dom *sdom = pcg_alloc_domdata(ops, dom);
  if (sdom == NULL) return -ENOMEM;
  dom->sched_priv = sdom;
  return 0;  
}

static void pcg_dom_destroy(const struct scheduler *ops, struct domain *dom) {
  struct pcg_dom *sdom = (struct pcg_dom *)dom->sched_priv;
  BUG_ON(!list_empty(&sdom->vcpu));
  pcg_free_domdata(ops, sdom);
}

static void pcg_vcpu_insert(const struct scheduler *ops, struct vcpu *vc) {
  printk("%s: Inserting d%d v%d\n", __func__, dom->domain_id, vc->vcpu_id);
  /* NB: On boot, idle vcpus are inserted before alloc_pdata() has
   * been called for that cpu.
   */  
  if (!is_idle_vcpu(vc)) return;

  struct csched_vcpu *svc = vc->sched_priv;
  struct domain * const dom = vc->domain;
  struct csched_dom * const sdom = svc->sdom;

  /* FIXME: Do we need the private lock here? */
  list_add_tail(&svc->sdom_elem, &svc->sdom->vcpu);
  /* Add vcpu to runqueue of initial processor */
  vcpu_schedule_lock_irq(vc);
  runq_assign(ops, vc);
  vcpu_schedule_unlock_irq(vc);
  sdom->nr_vcpus++;

  CSCHED_VCPU_CHECK(vc);
}

static void pcg_vcpu_remove(const struct scheduler *ops, struct vcpu *vc) {
  if (is_idle_vcpu(vc)) return;

  struct csched_vcpu * const svc = CSCHED_VCPU(vc);
  struct csched_dom * const sdom = svc->sdom;
  BUG_ON( sdom == NULL );
  BUG_ON( !list_empty(&svc->runq_elem) );

  /* Remove from runqueue */
  vcpu_schedule_lock_irq(vc);
  runq_deassign(ops, vc);
  vcpu_schedule_unlock_irq(vc);
  /* Remove from sdom list.  Don't need a lock for this, as it's called
   * syncronously when nothing else can happen. */
  list_del_init(&svc->sdom_elem);
  svc->sdom->nr_vcpus--;
}

static void pcg_vcpu_sleep(const struct scheduler *ops, struct vcpu *vc) {
  struct csched_vcpu * const svc = CSCHED_VCPU(vc);

  BUG_ON(is_idle_vcpu(vc));
  if (per_cpu(schedule_data, vc->processor).curr == vc)
    cpu_raise_softirq(vc->processor, SCHEDULE_SOFTIRQ);
  else if (__vcpu_on_runq(svc)) {
    BUG_ON(svc->rqd != RQD(ops, vc->processor));
    update_load(ops, svc->rqd, svc, -1, NOW());
    __runq_remove(svc);
  }
  else if (test_bit(__CSFLAG_delayed_runq_add, &svc->flags))
    clear_bit(__CSFLAG_delayed_runq_add, &svc->flags);
}

static void pcg_vcpu_wake(const struct scheduler *ops, struct vcpu *vc) {
  d2printk("w d%d v%d\n", vc->domain->domain_id, vc->vcpu_id);
  /* Schedule lock should be held at this point. */
  BUG_ON(is_idle_vcpu(vc));

  struct csched_vcpu * const svc = CSCHED_VCPU(vc);
  s_time_t now = 0;
  /* Make sure svc priority mod happens before runq check */
  if (unlikely(per_cpu(schedule_data, vc->processor).curr == vc)) {
    goto out;
  }

  if ( unlikely(__vcpu_on_runq(svc)) ) {
    /* If we've boosted someone that's already on a runqueue, prioritize
     * it and inform the cpu in question. */
    goto out;
  }

  /* If the context hasn't been saved for this vcpu yet, we can't put it on
   * another runqueue.  Instead, we set a flag so that it will be put on the runqueue
   * after the context has been saved. */
  if (unlikely(test_bit(__CSFLAG_scheduled, &svc->flags))) {
     set_bit(__CSFLAG_delayed_runq_add, &svc->flags);
     goto out;
  }

  /* Add into the new runqueue if necessary */
  if (svc->rqd == NULL) runq_assign(ops, vc);
  else BUG_ON(RQD(ops, vc->processor) != svc->rqd );

  now = NOW();
  update_load(ops, svc->rqd, svc, 1, now);        
  /* Put the VCPU on the runq */
  runq_insert(ops, vc->processor, svc);
  runq_tickle(ops, vc->processor, svc, now);

out:
  d2printk("w-\n");
  return;
}

static int pcg_dom_cntl(
    const struct scheduler *ops,
    struct domain *d,
    struct xen_domctl_scheduler_op *op) {
  return 0;
}

static int pcg_cpu_pick(const struct scheduler *ops, struct vcpu *vc)
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

#define XEN_SCHEDULER_PCG 8

const struct scheduler sched_pcg_def = {
  .name           = "Precaution Cut Greedy",
  .opt_name       = "pcg",
  .sched_id       = XEN_SCHEDULER_PCG,
  .sched_data     = &_pcg_priv,

  .init_domain    = pcg_dom_init,
  .alloc_domdata  = pcg_alloc_domdata,
  .destroy_domain = pcg_dom_destroy,    
  .free_domdata   = pcg_free_domdata,
  .init           = pcg_init,
  .deinit         = pcg_deinit,

  .alloc_pdata    = pcg_alloc_pdata,
  .free_pdata     = pcg_free_pdata,
  .alloc_vdata    = pcg_alloc_vdata,
  .free_vdata     = pcg_free_vdata,

  .insert_vcpu    = pcg_vcpu_insert,
  .remove_vcpu    = pcg_vcpu_remove,
  .sleep          = pcg_vcpu_sleep,
  .wake           = pcg_vcpu_wake,

  .dump_cpu_state = pcg_dump_pcpu,
  .dump_settings  = pcg_dump,

  .adjust         = pcg_dom_cntl,
  .pick_cpu       = pcg_cpu_pick,
  .do_schedule    = pcg_schedule,
  .context_saved  = pcg_context_saved,
};
