/*-------------------------------------------------------*/
/* talk.c       ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : talk/quety/friend routines                   */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/

#define _MODES_C_


#include "bbs.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#ifdef lint
#include <sys/uio.h>
#endif


#define M_INT 15                /* monitor mode update interval */
#define P_INT 20                /* interval to check for page req. in
                                 * talk/chat */

#define FRIEND_OVERRIDE 0
#define FRIEND_REJECT   1

#define IRH 1
#define HRM 2



struct talk_win
{
  int curcol, curln;
  int sline, eline;
};


typedef struct
{
  user_info *ui;
  time_t idle;
  usint friend;
}      pickup;

extern int bind( /* int,struct sockaddr *, int */ );
extern bad_user(char* name);
extern char* getuserid();
extern struct UTMPFILE *utmpshm;
extern screenline* big_picture;
#ifdef USE_MC07_WHERE
extern char *where(char *);
#endif

/* -------------------------- */
/* �O�� friend �� user number */
/* -------------------------- */

#define PICKUP_WAYS     5
int pickup_way = 0;
int friendcount;
int count_number;
int friends_number;
int override_number;
int rejected_number;
char *fcolor[7] = {"", "[1;32m", "[1;33m", "[1;36m", "[31m", "[1;35m", "[1;37m"};



char *talk_uent_buf;
char save_page_requestor[40];
char page_requestor[40];
static FILE* flog;


void friend_load();

int is_rejected(user_info *ui);

char *
modestring(uentp, simple)
  user_info *uentp;
  int simple;
{
  static char modestr[40];
  static char *notonline="���b���W";
  register int mode = uentp->mode;
  register char *word;

  word = ModeTypeTable[mode];

  if (!(PERM_HIDE(uentp) && is_rejected(uentp) & HRM && is_friend(uentp) & 2))
     if (!(HAS_PERM(PERM_SYSOP) || HAS_PERM(PERM_SEECLOAK)) &&
         (uentp->invisible ||
         (is_rejected(uentp) & HRM && !(is_friend(uentp) & 2))))
       return (notonline);
/*
woju
*/
  if (mode == EDITING) {
     sprintf(modestr, "E:%s",
         ModeTypeTable[uentp->destuid < EDITING ? uentp->destuid : EDITING]);
     word = modestr;
  }
  else if (!mode && *uentp->chatid == 1)
  {
     if (!simple)
        sprintf(modestr, "�^�� %s", getuserid(uentp->destuid));
     else
        sprintf(modestr, "�^���I�s");
  }
/* MH */
  else if (!mode && *uentp->chatid == 2)
     if (uentp->msgcount < 10)
     {
        char *cnum[10] = {"", "�@", "��", "�T", "�|", "��", "��", "�C",
                              "�K", "�E"};
        sprintf(modestr, "��%s�����y", cnum[uentp->msgcount]);
     }
     else
        sprintf(modestr, "����F @_@", uentp->msgcount);
  else if (!mode && *uentp->chatid == 3)
     sprintf(modestr, "���y�ǳƤ�");
  else if (!mode)
    return (uentp->destuid == 6) ? uentp->chatid :
      IdleTypeTable[(0 <= uentp->destuid && uentp->destuid < 6) ?
                    uentp->destuid: 0];
  else if (simple)
    return (word);

  else if (uentp->in_chat && mode == CHATING)
    sprintf(modestr, "%s (%s)", word, uentp->chatid);
  else if (mode != TALK && mode != PAGE && mode != QUERY)
    return (word);
  else
    sprintf(modestr, "%s %s", word, getuserid(uentp->destuid));

  return (modestr);
}


int
cmpuids(uid, urec)
  int uid;
  user_info *urec;
{
  return (uid == urec->uid);
}


/*
woju
*/
int
cmppids(pid, urec)
  pid_t pid;
  user_info *urec;
{
  return (pid == urec->pid);
}


static int
cmpunums(unum, up)
  int unum;
  user_info *up;
{
  if (up->pid)
    return (unum == up->destuid);
  return 0;
}


/* ------------------------------------- */
/* routines for Talk->Friend             */
/* ------------------------------------- */


static int
can_override(userid, whoasks)
  char *userid;
  char *whoasks;
{
  char buf[STRLEN];

  sethomefile(buf, userid, fn_overrides);
  return belong(buf, whoasks);
}


int
is_friend(ui)
  user_info *ui;
{
  register ushort unum, hit, *myfriends;

  /* �P�_���O�_���ڪ��B�� ? */

  unum = ui->uid;
  myfriends = currutmp->friend;
  while (hit = *myfriends++)
  {
    if (unum == hit)
    {
      hit = 1;
      if (count_number && !ui->invisible && !PERM_HIDE(ui))
         friends_number++;
      break;
    }
  }

  /* �P�_�ڬO�_����誺�B�� ? */

  myfriends = ui->friend;
  while (unum = *myfriends++)
  {
    if (unum == usernum)
    {
      if (count_number && !ui->invisible && !PERM_HIDE(ui))
         override_number++;
      hit |= 2;
      break;
    }
  }
  return hit;
}



static int
be_rejected(userid)
  char *userid;
{
  char buf[STRLEN];

  sethomefile(buf, userid, fn_reject);
  return belong(buf, cuser.userid);
}

  /* �Q�ڵ� */

int
is_rejected(ui)
  user_info *ui;
{
  register ushort unum, hit, *myrejects;

  /* �P�_���O�_���ڪ����H ? */

  unum = ui->uid;
  myrejects = currutmp->reject;
  while (hit = *myrejects++)
  {
    if (unum == hit)
    {
      hit = 1;
      if (count_number && !PERM_HIDE(ui))  /* MH */
      /* ���ΤH�����ӳQ��i�u�a�H�H�ơv */
         rejected_number++;
      break;
    }
  }

  /* �P�_�ڬO�_����誺���H ? */

  myrejects = ui->reject;
  while (unum = *myrejects++)
  {
    if (unum == usernum)
    {
      if (hit & IRH && count_number && !PERM_HIDE(ui))  /* MH */
      /* ���ΤH�����ӳQ��i�u�a�H�H�ơv */
         --rejected_number;
      hit |= 2;
      break;
    }
  }
  return hit;
}


/* ------------------------------------- */
/* �u��ʧ@                              */
/* ------------------------------------- */


static char *friend_file[2];
static char *friend_desc[2] = {"�ͽ˴y�z�G", "�c�δc���G"};
static char *friend_list[2] = {"�n�ͦW��", "�a�H�W��"};


static void
friend_add(uident, type)
  char *uident;
  int type;
{
  char fpath[80];

  setuserfile(fpath, friend_file[type]);

  if ((uident[0] > ' ') && !belong(fpath, uident))
  {
    FILE *fp;
    char buf[40];
    char t_uident[IDLEN + 1];
    strcpy(t_uident, uident);   /* Thor: avoid uident run away when get data */

    getdata(2, 0, friend_desc[type], buf, 40, DOECHO, 0);
    if (fp = fopen(fpath, "a"))
    {
      flock(fileno(fp), LOCK_EX);
      fprintf(fp, "%-13s%s\n", t_uident, buf);
      flock(fileno(fp), LOCK_UN);
      fclose(fp);
    }
  }
}


static void
friend_delete(uident, type)
  char *uident;
  int type;
{
  FILE *fp, *nfp;
  char fn[80], fnnew[80];
  char genbuf[200];

  setuserfile(fn, friend_file[type]);
  sprintf(fnnew, "%s-", fn);
  if ((fp = fopen(fn, "r")) && (nfp = fopen(fnnew, "w")))
  {
    int length = strlen(uident);

    while (fgets(genbuf, STRLEN, fp))
    {
      if ((genbuf[0] > ' ') && strncmp(genbuf, uident, length))
        fputs(genbuf, nfp);
    }
    fclose(fp);
    fclose(nfp);
    Rename(fnnew, fn);
  }
}


static void
friend_query(uident, type)
  char *uident;
  int type;
{
  char fpath[80], name[IDLEN + 2], *desc, *ptr;
  int len;
  FILE *fp;
  char genbuf[200];

  setuserfile(fpath, friend_file[type]);
  if (fp = fopen(fpath, "r"))
  {
    sprintf(name, "%s ", uident);
    len = strlen(name);
    desc = genbuf + 13;

    while (fgets(genbuf, STRLEN, fp))
    {
      if (!memcmp(genbuf, name, len))
      {
        if (ptr = strchr(desc, '\n'))
          ptr[0] = '\0';
        if (desc)
          prints("�A%s%s", friend_desc[type], desc);
        break;
      }
    }
    fclose(fp);
  }
}



/* ----------------------------------------------------- */


static void
my_kick(uentp)
  user_info *uentp;
{
  char genbuf[200];

  getdata(1, 0, msg_sure_ny, genbuf, 4, LCECHO, 0);
  clrtoeol();
  if (genbuf[0] == 'y')
  {
    sprintf(genbuf, "%s (%s)", uentp->userid, uentp->username);
    log_usies("KICK ", genbuf);
    if ((kill(uentp->pid, SIGHUP) == -1) && (errno == ESRCH))
      memset(uentp, 0, sizeof(user_info));
    /* purge_utmp(uentp); */
    outs("��X�h�o");
  }
  else
    outs(msg_cancel);
  pressanykey();
}


my_query(uident)
  char *uident;
{
  extern char currmaildir[];
  char fpath[80];
  int tuid;
  user_info *uentp;

  if (tuid = getuser(uident))
  {
    move(1, 0);
    clrtobot();
    move(2, 0);
    setutmpmode(QUERY);
    currutmp->destuid = tuid;

    prints("%s %s(%s) �@�W�� %d ���A�o��L %d �g�峹",
      (xuser.userlevel & PERM_LOGINOK) ? "[1;32m��[m" : "[1;31m�H[m",
      xuser.userid, xuser.username, xuser.numlogins, xuser.numposts);


    prints("\n�̪�(%s)�q[%s]�W��", Cdate(&xuser.lastlogin),
      (xuser.lasthost[0] ? xuser.lasthost : "(����)"));

#if defined(REALINFO) && defined(QUERY_REALNAMES)
    if (HAS_PERM(PERM_SYSOP))
      prints("�u��m�W: %s\n", xuser.realname);
#endif

    /* Query �ɥi�P�ɬݨ�ͽ˴y�z�δc�� */

    friend_query(uident, FRIEND_OVERRIDE);
    friend_query(uident, FRIEND_REJECT);

#if 0
    prints("�q�l�l��H�c�a�}: %s \n", xuser.email);
#endif

    uentp = (user_info *) search_ulist(cmpuids, tuid);
    if (uentp && !(PERM_HIDE(currutmp) ||
       is_rejected(uentp) & HRM && is_friend(uentp) & 2)
        && PERM_HIDE(uentp))
       prints("\n[1;33m[�ثe�ʺA�G%s][m  ", "���b���W");
    else
       prints("\n[1;33m[�ثe�ʺA�G%s][m  ",
         uentp ? modestring(uentp, 0) : "���b���W");

    sethomedir(currmaildir, xuser.userid);
    outs(chkmail(1) ? "[1;36m���s�i�H���٨S��[m" : "�Ҧ��H�󳣬ݹL�F");
    sethomedir(currmaildir, cuser.userid);
    chkmail(1);

    if (can_override(xuser.userid, cuser.userid))
    {
/* MH */    
      char *sex[MAX_SEXS] = { MSG_BIG_BOY, MSG_BIG_GIRL,
                       MSG_LITTLE_BOY, MSG_LITTLE_GIRL,
                       MSG_MAN, MSG_WOMAN, MSG_PLANT, MSG_MIME, MSG_BORG, 
                       MSG_VULCAN, MSG_TRILL, MSG_KLINGON, MSG_ENTERPRISE,
                       MSG_ADA };
/*    */                       
      outs("�A�ʧO�G");
      outs(sex[xuser.sex]);
    }
    outs("\n");

    showplans(uident);
    pressanykey();
    return FULLUPDATE;
  }
  return DONOTHING;
  /* currutmp->destuid = 0; */
}

/* MH */

/* MH �Ҽg�����y�^��t�� */

#define MH_WB_NOT_REPLIED "��"
#define MH_WB_REPLIED "��"
#define MH_WB_GONE "��"

#undef USE_OUTS

extern uschar standing;

int mh_throw_water_ball(void)
{
    int a, b;
    char ch;
    char buf[200];
    user_info *uin[MAXMSGS];
    uschar msgnum;
    uschar msgstart;
    msgque msgs[MAXMSGS];
    int currstat0 = currstat;
    int mode0 = currutmp->mode;
    int c0 = currutmp->chatid[0];

    currstat = DBACK;
    currutmp->mode = 0;
    currutmp->chatid[0] = 3;
    msgnum = currutmp->msgnum;
    msgstart = currutmp->msgstart;

    if(msgnum == 0)
    /* �S�����y�A�^����H:P */
        return;

    /* �u�n�I�s�L�o�Ө禡�N�� have_wb �]�� false, ��ܤw�g�^�L�F */
    currutmp->have_wb = NA;

    if(currutmp->mode == 0 && currutmp->chatid[0] == 2 && currstat == ROWB)
    {
      my_outmsg("                                                                               ");
    }

    currstat = DBACK;

    for(a = 0, b = currutmp->msgstart;a < msgnum;a ++, b = (b + 1) % MAXMSGS)
    {
       msgs[msgnum - a - 1] = currutmp->msgs[b];
       uin[msgnum - a - 1] = (user_info*)search_ulist(cmppids, msgs[msgnum - a - 1].last_pid);
       sprintf(buf, "[1;33;46m  %s%s[37;45m %s ",
          uin[msgnum - a - 1] ? (msgs[msgnum - a - 1].replied == NA ? MH_WB_NOT_REPLIED : MH_WB_REPLIED) : MH_WB_GONE,
          msgs[msgnum - a - 1].last_userid,
          msgs[msgnum - a - 1].last_call_in);
       strncat(buf, SPACE_STRING, 80 + 18 - strlen(buf));
       strcat(buf, "[0m");
 
       my_outmsg_row(buf, (msgnum - a - 1) + 1);
    }
    
    my_outmsg_row("================================================================================", a + 1);
    my_outmsg_row("����GCtrl-U:�V�W, Ctrl-D:�V�U                                                  ", a + 2);
    my_outmsg_row("�лx�G" MH_WB_NOT_REPLIED ":�٨S���^, " MH_WB_REPLIED ":�w�g�^�L�F, " MH_WB_GONE ":���w�g���]�F, ��:�ثe�n�^�����y          ", a + 3);
    my_outmsg_row("================================================================================", a + 4);
    my_outmsg_row("                                                                                ", a + 5);
    
    a = 0;
    do
    {
#ifdef USE_OUTS
        /* �o�G��O�ΨӸѨM outs �@�}�l�N�O ANSI ����X�ɵL�k���T��Ķ�����D */
    	move(a + 1, 0);
    	outs(" ");
    	move(a + 1, 0);
    	outs("[1;33;46m��[0m");
    	refresh();
#else
        sprintf(buf, "[1;33;46m��%s%s[37;45m %s ",
           uin[a] ? (msgs[a].replied == NA ? MH_WB_NOT_REPLIED : MH_WB_REPLIED) : MH_WB_GONE,
           msgs[a].last_userid,
           msgs[a].last_call_in);
        strncat(buf, SPACE_STRING, 80 + 18 - strlen(buf));
        strcat(buf, "[0m");
    	my_outmsg_row(buf, a + 1);
#endif
        if(!uin[a])
        {
            my_outmsg("[1;33;41m�V�|! ���w���]�F(���b���W)! [37m~>_<~[m");
            ch = igetch();
#ifdef USE_OUTS
            /* �o�G��O�ΨӸѨM outs �@�}�l�N�O ANSI ����X�ɵL�k���T��Ķ�����D */
            move(a + 1, 0);
            outs(" ");
            move(a + 1, 0);
            outs("[1;33;46m  [0m");
            refresh();
#else
            sprintf(buf, "[1;33;46m  %s%s[37;45m %s ",
               uin[a] ? (msgs[a].replied == NA ? MH_WB_NOT_REPLIED : MH_WB_REPLIED) : MH_WB_GONE,
               msgs[a].last_userid,
               msgs[a].last_call_in);
            strncat(buf, SPACE_STRING, 80 + 18 - strlen(buf));
            strcat(buf, "[0m");
            my_outmsg_row(buf, a + 1);
#endif
            switch(ch)
            {
            	case Ctrl('U'):
            	    a = (a + msgnum - 1) % msgnum;
            	    break;
            	case Ctrl('D'):
            	    a = (a + 1) % msgnum;
            	    break;
            	default:
/*            	    sleep(1);*/
                    pressanykey();
                    currutmp->chatid[0] = c0;
                    currutmp->mode = mode0;
                    currstat = currstat0;
            	    return 0;
            	    break;
            }
            my_outmsg("                                                     ");
        }
        else
        {
#ifdef DIRECT_MY_WRITE
            b = my_write(msgs[a].last_pid, "���y��^�h�G");
#else
            {
              char msgbuf[70] = "";
              
              b = mh_getdata(0, 0, "���y��^�h�G", msgbuf + 1, 65, DOECHO, 0, MH_GETDATA_UD, NULL);
              if(b > 0)
              /* �u�������y�n�� */
              {
                char tmpbuf[5];
                
                sprintf(buf, "��%s���y:%.40s....?[Y] ", msgs[a].last_userid, msgbuf + 1);

                getdata(0, 0, buf, tmpbuf, 3, LCECHO, 0);

                if (tmpbuf[0] == 'n') {
                  currutmp->chatid[0] = c0;
                  currutmp->mode = mode0;
                  currstat = currstat0;
                  return 0;
                }
                b = my_write(msgs[a].last_pid, msgbuf);
              }
            }
#endif
#ifdef USE_OUTS
            /* �o�G��O�ΨӸѨM outs �@�}�l�N�O ANSI ����X�ɵL�k���T��Ķ�����D */
            move(a + 1, 0);
            outs(" ");
            move(a + 1, 0);
            outs("[1;33;46m  [0m");
            refresh();
#else
            sprintf(buf, "[1;33;46m  %s%s[37;45m %s ",
               uin[a] ? (msgs[a].replied == NA ? MH_WB_NOT_REPLIED : MH_WB_REPLIED) : MH_WB_GONE,
               msgs[a].last_userid,
               msgs[a].last_call_in);
            strncat(buf, SPACE_STRING, 80 + 18 - strlen(buf));
            strcat(buf, "[0m");
            my_outmsg_row(buf, a + 1);
#endif
            if(b == 1)
            {
              if(currutmp->msgs[(msgstart + msgnum - a - 1) % MAXMSGS].last_pid == msgs[a].last_pid
                 && strcmp(currutmp->msgs[(msgstart + msgnum - a - 1) % MAXMSGS].last_call_in, msgs[a].last_call_in) == 0)
              /* �o�Ӥ��y�O���٦b */
              {
                currutmp->msgs[(msgstart + msgnum - a - 1) % MAXMSGS].replied = YEA;
              }
              currutmp->chatid[0] = c0;
              currutmp->mode = mode0;
              currstat = currstat0;
              return 1;
            }
            else if(b == 0)
            {
                currutmp->chatid[0] = c0;
                currutmp->mode = mode0;
                currstat = currstat0;
                return 0;
            }
	    else if(b == MH_UP)
    	    	a = (a + msgnum - 1) % msgnum;
    	    else if(b == MH_DOWN)
    	    	a = (a + 1) % msgnum;
        }
    } while(1 == 1);
    currutmp->chatid[0] = c0;
    currutmp->mode = mode0;
    currstat = currstat0;
}
/*    */

int
my_write(pid, hint)
  pid_t pid;
  char *hint;
{
  int a, b;
  int len;
  char msg[80];
/*struct stat st; */
  FILE *fp;
  struct tm *ptime;
  time_t now;
  char genbuf[200];
  char inputbuf[4];
  char write_id[IDLEN + 1];
  user_info *uin = (user_info*)search_ulist(cmppids, pid);

/*
woju
*/
  uschar mode0 = currutmp->mode;
  char c0 = currutmp->chatid[0];
  int currstat0 = currstat;

  if (!uin) {
     my_outmsg("[1;33;41m�V�|! ���w���]�F(���b���W)! [37m~>_<~[m");
     if (isprint2(*hint))
        sleep(1);
     return 0;
  }
  strcpy(write_id, uin->userid);

  currutmp->mode = 0;
  currutmp->chatid[0] = 3;
  currstat = XMODE;

  time(&now);
  ptime = localtime(&now);

  if (isprint2(*hint)) {
/*    char inputbuf[4];*/

    if (!(len = getdata(0, 0, hint, msg, 65, DOECHO, 0))) {
      my_outmsg("[1;33;42m��F! ��A�@��...[m");
      sleep(1);
      currutmp->chatid[0] = c0;
      currutmp->mode = mode0;
      currstat = currstat0;
      return 0;
    }

#ifdef DIRECT_MY_WRITE
/* MH */
    if(len == MH_UP || len == MH_DOWN)
    {
    	return len;
    }
/*    */
#endif

    if (!*uin->userid || strcmp(write_id, uin->userid)) {
       my_outmsg("[1;33;41m�V�|! ���w���]�F(���b���W)! [37m~>_<~[m");
       if (*hint)
          sleep(1);
       currutmp->chatid[0] = c0;
       currutmp->mode = mode0;
       currstat = currstat0;
       return 0;
    }

    sprintf(genbuf, "��%s���y:%.40s....?[Y] ", uin->userid, msg);

    getdata(0, 0, genbuf, inputbuf, 3, LCECHO, 0);
    genbuf[0] = '\0';

    if (inputbuf[0] == 'n') {
      currutmp->chatid[0] = c0;
      currutmp->mode = mode0;
      currstat = currstat0;
      return 0;
    }
    if (!*uin->userid || strcmp(write_id, uin->userid)) {
       my_outmsg("[1;33;41m�V�|! ���w���]�F(���b���W)! [37m~>_<~[m");
       if (isprint2(*hint))
          sleep(1);
       currutmp->chatid[0] = c0;
       currutmp->mode = mode0;
       currstat = currstat0;
       return 0;
    }
  }
  else {
     strcpy(msg, hint + 1);
     len = strlen(msg);
  }

   now = time(0);
   if (*hint != 1) {
      sethomefile(genbuf, uin->userid, fn_writelog);
      if (fp = fopen(genbuf, "a")) {
        fprintf(fp, "[1;33;46m�� %s %s[37;45m %s [0m[%s]\n",
          cuser.userid, (*hint == 2) ? "[33;41m�s��" : "", msg, Cdatelite(&now));
        fclose(fp);
      }
      sethomefile(genbuf, cuser.userid, fn_writelog);
      if (fp = fopen(genbuf, "a")) {
         fprintf(fp, "To %s: %s [%s]\n", uin->userid, msg, Cdatelite(&now));
         fclose(fp);
      }
   }

   if (*hint == 2 && uin->msgcount) {
      uin->destuip = currutmp;
      uin->sig = 2;
      kill(uin->pid, SIGUSR1);
   }
   else if (*hint != 1 && !HAS_PERM(PERM_SYSOP) && uin->pager == 3)
      my_outmsg("[1;33;41m�V�|! ��訾���F! [37m~>_<~[m");
   else
/* MH */
   {
      int msgc;
      
      msgc = ++ uin->msgcount;
      if(msgc > MAXMSGS)
      /* ���w�g�u����v�F */
      {
        uin->msgcount --;
        if (*hint != 1)
         my_outmsg("[1;33;41m�V�|! ��褣��F! (����Ӧh���y) [37m@_@[m");
      }
      
      {
        int i;
        msgque *msgp;

        if(uin->msgnum >= MAXMSGS)
        /* ���w�g���L MAXMSGS �ӥH�W�����y */
        {
          /* �h���@�Ӥ��y */
          uin->msgstart = (uin->msgstart + 1) % MAXMSGS;
        }
        else
        {
          uin->msgnum ++;
        }
        /* �g�J���y */
        i = (uin->msgstart + uin->msgnum - 1) % MAXMSGS;
        msgp = &uin->msgs[i];
        msgp->last_pid = currpid;
        msgp->replied = NA;
        strcpy(msgp->last_userid, cuser.userid);
        strcpy(msgp->last_call_in, msg);
        uin->have_wb = YEA;
      }
      
      if (msgc == 1 && kill(uin->pid, SIGUSR2) == -1 && *hint != 1)
         my_outmsg("[1;33;41m�V�|! �S����! [37m~>_<~[m");
      else if (msgc == 1 && *hint != 1)
         my_outmsg("[1;33;44m���y�{�L�h�F! [37m*^o^Y[m");
      else if (msgc > 1 && msgc < MAXMSGS && *hint != 1)
         my_outmsg("[1;33;44m�A�ɤW�@��! [37m*^o^Y[m");
   }
   /*    */

   if (isprint2(*hint))
      sleep(1);
      
   refresh();

   currutmp->chatid[0] = c0;
   currutmp->mode = mode0;
   currstat = currstat0;
   return 1;
}


/* Thor: for ask last call-in message */

int
t_display()
{
  char ans[4];
  char genbuf[200];

  setuserfile(genbuf, fn_writelog);
  strcpy(vetitle, "[���y�O��]");
  if (more(genbuf, YEA) != -1)
     return FULLUPDATE;
  return DONOTHING;
}


/* ----------------------------------------------------- */


static int
dotalkuent(uentp)
  user_info *uentp;
{
  char buf[STRLEN];
  char mch;

  if (HAS_PERM(PERM_SYSOP) || HAS_PERM(PERM_SEECLOAK) || !uentp->invisible)
  {
    switch (uentp->mode)
    {
    case CLASS:
      mch = 'S';
      break;
    case TALK:
      mch = 'T';
      break;
    case CHATING:
      mch = 'C';
      break;
    case READNEW:
    case READING:
      mch = 'R';
      break;
    case POSTING:
      mch = 'P';
      break;
    case SMAIL:
    case RMAIL:
    case MAIL:
      mch = 'M';
      break;
    case EDITING:
      mch = 'E';
      break;
    default:
      mch = '-';
    }
    sprintf(buf, "%s%s(%c), ",
      uentp->invisible ? "*" : "", uentp->userid, mch);
    strcpy(talk_uent_buf, buf);
    talk_uent_buf += strlen(buf);
  }
  return 0;
}


static void
do_talk_nextline(twin)
  struct talk_win *twin;
{
#if 0
   if (mbbsd) {
      register int curln;

      curln = twin->curln + 1;
      if (curln > twin->eline)
        curln = twin->sline;
      if (curln != twin->eline)
      {
        move(curln + 1, 0);
        clrtoeol();
      }
      move(curln, 0);
      clrtoeol();
      twin->curcol = 0;
      twin->curln = curln;
      return;
   }
#endif

   twin->curcol = 0;
   if (twin->curln < twin->eline)
      ++(twin->curln);
   else
      region_scroll_up(twin->sline, twin->eline);
   move(twin->curln, twin->curcol);
}


static void
do_talk_char(twin, ch)
  struct talk_win *twin;
  int ch;
{
  extern int dumb_term;
  screenline* line;
  int i;
  char ch0;
  char buf[81];

  if (isprint2(ch)) {
     ch0 = big_picture[twin->curln].data[twin->curcol + mbbsd];
     if (big_picture[twin->curln].len < 79)
        move(twin->curln, twin->curcol);
     else
        do_talk_nextline(twin);
     outc(ch);
     ++(twin->curcol);
     line =  big_picture + twin->curln;
     if (twin->curcol < line->len) {      /* insert */
        ++(line->len);
        memcpy(buf, line->data + twin->curcol + mbbsd, 80);
        save_cursor();
        do_move(twin->curcol, twin->curln);
        ochar(line->data[twin->curcol + mbbsd] = ch0);
        for (i = twin->curcol + 1; i < line->len; i++)
           ochar(line->data[i + mbbsd] = buf[i - twin->curcol - 1]);
        restore_cursor();
     }
     line->data[line->len + mbbsd] = 0;
     return;
  }

  switch (ch)
  {
  case Ctrl('H'):
  case '\177':
    if (twin->curcol == 0)
    {
      return;
    }
    line =  big_picture + twin->curln;
    --(twin->curcol);
    if (twin->curcol < line->len) {
       --(line->len);
       save_cursor();
       do_move(twin->curcol, twin->curln);
       for (i = twin->curcol; i < line->len; i++)
          ochar(line->data[i + mbbsd] = line->data[i + 1 + mbbsd]);
       line->data[i + mbbsd] = 0;
       ochar(' ');
       restore_cursor();
    }
    move(twin->curln, twin->curcol);
    return;

  case Ctrl('D'):
     line =  big_picture + twin->curln;
     if (twin->curcol < line->len) {
        --(line->len);
        save_cursor();
        do_move(twin->curcol, twin->curln);
        for (i = twin->curcol; i < line->len; i++)
           ochar(line->data[i + mbbsd] = line->data[i + 1 + mbbsd]);
        line->data[i + mbbsd] = 0;
        ochar(' ');
        restore_cursor();
     }
     return;
  case Ctrl('G'):
    bell();
    return;
  case Ctrl('b'):
     if (twin->curcol > 0) {
        --(twin->curcol);
        move(twin->curln, twin->curcol);
     }
     return;
  case Ctrl('F'):
     if (twin->curcol < 79) {
        ++(twin->curcol);
        move(twin->curln, twin->curcol);
     }
     return;
  case Ctrl('A'):
     twin->curcol = 0;
     move(twin->curln, twin->curcol);
     return;
  case Ctrl('K'):
     clrtoeol();
     return;
  case Ctrl('Y'):
     twin->curcol = 0;
     move(twin->curln, twin->curcol);
     clrtoeol();
     return;
  case Ctrl('E'):
     twin->curcol = big_picture[twin->curln].len;
     move(twin->curln, twin->curcol);
     return;
  case Ctrl('M'):
  case Ctrl('J'):
     line =  big_picture + twin->curln;
     strncpy(buf, line->data + mbbsd, line->len);
     buf[line->len] = 0;
     if (dumb_term)
       outc('\n');
     do_talk_nextline(twin);
     break;
  case Ctrl('P'):
     line =  big_picture + twin->curln;
     strncpy(buf, line->data + mbbsd, line->len);
     buf[line->len] = 0;
     if (twin->curln > twin->sline) {
        --(twin->curln);
        move(twin->curln, twin->curcol);
     }
     break;
  case Ctrl('N'):
     line =  big_picture + twin->curln;
     strncpy(buf, line->data + mbbsd, line->len);
     buf[line->len] = 0;
     if (twin->curln < twin->eline) {
        ++(twin->curln);
        move(twin->curln, twin->curcol);
     }
     break;
  }
  trim(buf);
  if (*buf)
     fprintf(flog, "%s%s: %s%s\n",
        (twin->eline == b_lines - 1) ? "[1;35m" : "",
        (twin->eline == b_lines - 1) ?
        getuserid(currutmp->destuid) : cuser.userid, buf,
        (ch == Ctrl('P')) ? "[37;45m(Up)[m" : "[m");
}


static void
do_talk_string(twin, str)
  struct talk_win *twin;
  char *str;
{
  while (*str)
  {
    do_talk_char(twin, *str++);
  }
}


static void
dotalkuserlist(twin)
  struct talk_win *twin;
{
  char bigbuf[MAXACTIVE * 20];
  int savecolumns;

  do_talk_string(twin, "*** �W�u���� ***\n");
  savecolumns = (t_columns > STRLEN ? t_columns : 0);
  talk_uent_buf = bigbuf;
  if (apply_ulist(dotalkuent) == -1)
  {
    strcpy(bigbuf, "�S������ϥΪ̤W�u\n");
  }
  strcpy(talk_uent_buf, "\n");
  do_talk_string(twin, bigbuf);
  if (savecolumns)
    t_columns = savecolumns;
}


char *talk_help =
  "== On-line Help! ==\n"
  " ^O ���u�W�����e��  "  " ^W �z�z�z�a�� :~(\n"
  " ^U �C�X�u�W�ϥΪ�  "  " ^Y ��ϡ�I Y^o^Y\n"
  " ^P ����Pager       "  " ^A ��������... :D\n"
  " ^G ��!(�εۤF��?)  "  " ^K ��s�L�v�}~~~!\n"
  " ^C/^D �T�T�F...    "  " ^Z zzzzz.........\n";

char *talk_wawa = "��z�z�z�z�ڰڰڰڰڡ���!!!\n ~~~>_<~~~\n";
char *talk_yaya = "��Ϣ�Ϣ�ϡ���!!!\n Y*^o^*Y\n";
char *talk_haha = "�z����������......!!!\n :DDD\n";
char *talk_kick = "�ݧڦ�s�L�v�}~~~!!!\n >:D\n";
char *talk_zzz = "-_- . . z Z ��\n";

static
do_talk(fd)
int fd;
{
   struct talk_win mywin, itswin;
   char mid_line[128], data[200], ans[4];
   int i, ch, datac;
   int im_leaving = 0;
   FILE *log;
   struct tm *ptime;
   time_t now;
   FILE* fp;
   char genbuf[200], fpath[100];
   int phone_mode = 0;
   char* pstr;
   extern char* phone_char();


   time(&now);
   ptime = localtime(&now);

   sethomepath(fpath, cuser.userid);
   strcpy(fpath, tempnam(fpath, "talk_"));
   flog = fopen(fpath, "w");

   setuserfile(genbuf, fn_talklog); /* Kaede */
   if (!is_watched(cuser.userid))
     log = NULL;
   else if (log = fopen(genbuf, "a+"))
     fprintf(log, "[%d/%d %d:%02d] & %s\n",
             ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_hour, ptime->tm_min,
             save_page_requestor);

   setutmpmode(TALK);

   ch = 58 - strlen(save_page_requestor);
   sprintf(genbuf, "%s�i%s", cuser.userid, cuser.username);
   i = ch - strlen(genbuf);
   if (i >= 0)
   {
      i = (i >> 1) + 1;
   }
   else
   {
     genbuf[ch] = '\0';
     i = 1;
   }
   memset(data, ' ', i);
   data[i] = '\0';

   sprintf(mid_line, "[1;46;37m  �ͤѻ��a  [45m%s%s�j ��  %s%s[0m",
     data, genbuf, save_page_requestor,  data);

   memset(&mywin, 0, sizeof(mywin));
   memset(&itswin, 0, sizeof(itswin));

   i = b_lines >> 1;
   mywin.eline = i - 1;
   itswin.curln = itswin.sline = i + 1;
   itswin.eline = b_lines - 1;

   clear();
   move(i, 0);
   outs(mid_line);
   move(0, 0);

   add_io(fd, 0);

   while (1)
   {
     ch = igetkey();

     if (ch == I_OTHERDATA)
     {
       datac = recv(fd, data, sizeof(data), 0);
       if (datac <= 0)
         break;
       for (i = 0; i < datac; i++)
         do_talk_char(&itswin, data[i]);
     }
     else
     {
       if (ch == Ctrl('C'))
       {
         if (im_leaving)
           break;
         move(b_lines, 0);
         clrtoeol();
         outs("�A���@�� Ctrl-C �N��������͸��o�I");
         im_leaving = 1;
         continue;
       }
       if (im_leaving)
       {
         move(b_lines, 0);
         clrtoeol();
         im_leaving = 0;
       }

       if (ch == KEY_LEFT)
          ch = Ctrl('b');
       else if  (ch == KEY_RIGHT)
          ch = Ctrl('F');
       else if  (ch == KEY_UP)
          ch = Ctrl('P');
       else if  (ch == KEY_DOWN)
          ch = Ctrl('N');

       if (phone_mode && (pstr = phone_char(ch))
         || isprint2(ch) || ch == Ctrl('H') || ch == '\177'
         || ch == Ctrl('G') || ch == Ctrl('M') || ch == Ctrl('J') ||
            ch == Ctrl('F') || ch == Ctrl('b') || ch == Ctrl('D') ||
            ch == Ctrl('A') || ch == Ctrl('E') || ch == Ctrl('K') ||
            ch == Ctrl('Y') || ch == Ctrl('P') || ch == Ctrl('N'))
       {
         if (phone_mode && pstr)
            data[0] = (char)pstr[0];
         else
            data[0] = (char) ch;
         if (send(fd, data, 1, 0) != 1)
           break;
         if (log)
           fprintf(log, "%c", (ch == Ctrl('M'))? '\n' : (char) *data);
         do_talk_char(&mywin, *data);
         if (phone_mode && pstr) {
            data[0] = (char) pstr[1];
            if (send(fd, data, 1, 0) != 1)
              break;
            if (log)
              fprintf(log, "%c", (ch == Ctrl('M'))? '\n' : (char) *data);
            do_talk_char(&mywin, *data);
         }
       }
       else if (ch == KEY_ESC)
          switch (KEY_ESC_arg) {
          case 'p':
             phone_mode ^= 1;
             break;
          case 'a':
             send(fd, talk_haha, strlen(talk_haha), 0);
             do_talk_string(&mywin, talk_haha);
             break;
          case 'k':
             send(fd, talk_kick, strlen(talk_kick), 0);
             do_talk_string(&mywin, talk_kick);
             break;
          case 'w':
             send(fd, talk_wawa, strlen(talk_wawa), 0);
             do_talk_string(&mywin, talk_wawa);
             break;
          case 'y':
             send(fd, talk_yaya, strlen(talk_yaya), 0);
             do_talk_string(&mywin, talk_yaya);
             break;
          case 'z':
             send(fd, talk_zzz, strlen(talk_zzz), 0);
             do_talk_string(&mywin, talk_zzz);
             break;
          case 'c':
             capture_screen();
             break;
          case 'n': {
             add_io(0, 0);
             scr_exec(edit_note);
             add_io(fd, 0);
             }
             break;
          }
       else if (ch == Ctrl('U'))
       {
         add_io(0, 0);
         scr_exec(t_users);
         add_io(fd, 0);
       }
       else if (ch == Ctrl('I'))
       {
         add_io(0, 0);
         scr_exec(t_idle);
         add_io(fd, 0);
       }
       else if (ch == Ctrl('B'))
       {
         add_io(0, 0);
         scr_exec(m_read);
         add_io(fd, 0);
       }
/* MH */
       else if (ch == Ctrl('R')) {
         screenline* screen0 = calloc(t_lines, sizeof(screenline));
         int y, x;

         memcpy(screen0, big_picture, t_lines * sizeof(screenline));
         add_io(0, 0);
         getyx(&y, &x);
         mh_throw_water_ball();
         move(y, x);
         memcpy(big_picture, screen0, t_lines * sizeof(screenline));
         free(screen0);
         redoscr();
         add_io(fd, 0);
       }
/*    */
     }
   }
   if (log)
     fclose(log);

   add_io(0, 0);
   close(fd);

   if (flog) {
      char ans[4];
      extern uschar scr_lns;
      int i;

      time(&now);
      fprintf(flog, "\n[33;44m���O�e�� [%s] ...     [m\n", Cdatelite(&now));
      for (i = 0; i < scr_lns; i++)
         fprintf(flog, "%.*s\n", big_picture[i].len, big_picture[i].data + mbbsd);
      fclose(flog);
      more(fpath, NA);
      getdata(b_lines - 1, 0, "�M��(C) ���ܳƧѿ�(M) (C/M)?[C]",
         ans, 4, LCECHO, 0);
      if (*ans == 'm') {
         fileheader mymail;
         char title[128];

         sethomepath(genbuf, cuser.userid);
         stampfile(genbuf, &mymail);
         mymail.savemode = 'H';        /* hold-mail flag */
         mymail.filemode = FILE_READ;
         strcpy(mymail.owner, "[��.��.��]");
         sprintf(mymail.title, "��ܰO�� [1;36m(%s)[m", getuserid(currutmp->destuid));
         if(mh_memoforward(cuser.userid, fpath, &mymail, sizeof(mymail)))
         {
           sethomedir(title, cuser.userid);
           append_record(title, &mymail, sizeof(mymail));
           Rename(fpath, genbuf);
         }
      }
      else
         unlink(fpath);
      flog = 0;
   }

   setutmpmode(XINFO);
}


static void
my_talk(uin)
  user_info *uin;
{
  int sock, msgsock, length, ch;
  struct sockaddr_in server;
  pid_t pid;
  char c;
  char genbuf[4];
  uschar mode0 = currutmp->mode;

  ch = uin->mode;
  strcpy(currauthor, uin->userid);

  if (!(pid = uin->pid) || (kill(pid, 0) == -1))
  {
    resetutmpent();
    outs(msg_usr_left);
  }
  else if (ch == EDITING || ch == TALK || ch == CHATING
      || ch == PAGE || ch == MAILALL || ch == MONITOR
      || !ch && (uin->chatid[0] == 1 || uin->chatid[0] == 3))
  {
    outs("�H�a�b����");
  }
  else if (!HAS_PERM(PERM_SYSOP) && (be_rejected(uin->userid) ||
      (!uin->pager && !can_override(uin->userid, cuser.userid))))
  {
    outs("��������I�s���F");
  }
  else if (!HAS_PERM(PERM_SYSOP) &&
           (be_rejected(uin->userid) || uin->pager == 2))
  {
    outs("���ޱ��I�s���F");
  }
  else if (!HAS_PERM(PERM_SYSOP) &&
           (be_rejected(uin->userid) || uin->pager == 3))
  {
    outs("���I�s�������F");
  }
  else
  {
    showplans(uin->userid);
    getdata(2, 0, "�T�w�n�M�L/�o�ͤѶ�(Y/N)?[N] ", genbuf, 4, LCECHO, 0);
    if (*genbuf != 'y')
      return;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
      perror("sock err");
      return;
    }
    server.sin_family = PF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 0;
    if (bind(sock, (struct sockaddr *) & server, sizeof server) < 0)
    {
      close(sock);
      perror("bind err");
      return;
    }
    length = sizeof server;
    if (getsockname(sock, (struct sockaddr *) & server, &length) < 0)
    {
      close(sock);
      perror("sock name err");
      return;
    }
    currutmp->sockactive = YEA;
    currutmp->sockaddr = server.sin_port;
    currutmp->destuid = uin->uid;
    setutmpmode(PAGE);
    uin->destuip = currutmp;
    kill(pid, SIGUSR1);
    clear();
    prints("���I�s %s.....\n��J Ctrl-D ����....", uin->userid);

    listen(sock, 1);
    add_io(sock, 5);
    while (1) {
      ch = igetch();
      if (ch == I_TIMEOUT) {
         ch = uin->mode;
         if (!ch && uin->chatid[0] == 1 && uin->destuip == currutmp) {
             bell();
             outmsg("���^����...");
             refresh();
         }
         else if (ch == EDITING || ch == TALK || ch == CHATING
             || ch == PAGE || ch == MAILALL || ch == MONITOR
             || !ch && (uin->chatid[0] == 1 || uin->chatid[0] == 3)) {
             add_io(0, 0);
             close(sock);
             currutmp->sockactive = currutmp->destuid = 0;
             outmsg("�H�a�b����");
             pressanykey();
             return;
         }
         else {
#ifdef LINUX
           add_io(sock, 20);       /* added 4 linux... achen */
#endif

           move(0, 0);
           outs("�A");
           bell();

           uin->destuip = currutmp;
           if (kill(pid, SIGUSR1) == -1)
           {

#ifdef LINUX
             add_io(sock, 20);     /* added 4 linux... achen */
#endif

             outmsg(msg_usr_left);
             refresh();
             sleep(1);
             pressanykey();
             return;
           }
           continue;
         }
      }

      if (ch == I_OTHERDATA)
        break;

      if (ch == '\004')
      {
        add_io(0, 0);
        close(sock);
        currutmp->sockactive = currutmp->destuid = 0;
        return;
      }
    }

    msgsock = accept(sock, (struct sockaddr *) 0, (int *) 0);
    if (msgsock == -1)
    {
      perror("accept");
      return;
    }
    add_io(0, 0);
    close(sock);
    currutmp->sockactive = NA;
    /* currutmp->destuid = 0 ; */
    read(msgsock, &c, sizeof c);

    if (c == 'y')
    {
      sprintf(save_page_requestor, "%s (%s)", uin->userid, uin->username);
      do_talk(msgsock);
    }
    else
    {
      move(9, 9);
      outs("�i�^���j ");
      switch (c)
      {
      case 'a':
        outs("�ڲ{�b�ܦ��A�е��@�|��A call �ڡA�n�ܡH");
        break;
      case 'b':
        outs("�藍�_�A�ڦ��Ʊ������A talk....");
        break;
      case 'd':
        outs("���A�����S���H���a�Ǥ@�˶��s�A�u�Q��....");
        break;
      case 'c':
        outs("�Ф��n�n�ڦn�ܡH");
        break;
      case 'e':
        outs("��ڦ��ƶܡH�Х��ӫH��...^_^");
        break;
/* Thor */
      case 'f':
        {
        char msgbuf[80];
        read(msgsock, msgbuf, 60);
        outs("�藍�_�A�ڲ{�b����M�Atalk�A�]��\n");
        move(10,8);
        outs(msgbuf);
        }
        break;
/*      */
      default:
        outs("�ڲ{�b���Q talk ��.....:)");
      }
      close(msgsock);
    }
  }
  currutmp->mode = mode0;
  currutmp->destuid = 0;
  pressanykey();
}


/* ------------------------------------- */
/* ��榡��Ѥ���                        */
/* ------------------------------------- */


#define US_PICKUP       1234
#define US_RESORT       1233
#define US_ACTION       1232
#define US_REDRAW       1231

static void
t_showhelp()
{
  clear();

  outs("[36m�i �A��O�ϥλ��� �j[m\n\n\
(��)(e)         �������}      (h)             �ݨϥλ���\n\
(��)/(��)(n)    �W�U����      (TAB)           �����ƧǤ覡\n\
(PgUp)(^B)      �W�����      ( )(PgDn)(^F)   �U�����\n\
(Hm)/($)(Ed)    ��/��         (s)             �ӷ�/�n�ʹy�z ����\n\
(m)             �H�H          (q)(/)          �d�ߺ���/��M����\n\
(r)             �\\Ū�H��      (l)             �ݤW�����T\n\
(f)             ����/�n�ͦC�� (�Ʀr)          ���ܸӨϥΪ�\n\
(p/N)           �Y�ɤ����I�s��/���ʺ�\n\
(a/d/o)         �n�ͦW�椧�W�[/�R��/�ק�");

  if (HAS_PERM(PERM_PAGE))
  {
    outs("\n\n[36m�i ��߱M���� �j[m\n\n\
(��)(t)(Enter)  ��L���o���\n\
(w)             ���u Call in\n\
(b)             ��n�ͼs�� (�@�w�n�b�n�ͦC��)\n\
(^R)            �Y�ɦ^�� (���H Call in �A��)");
  }

  if (HAS_PERM(PERM_SYSOP))
  {
    outs("\n\n[36m�i �����M���� �j[m\n\n");
    if (HAS_PERM(PERM_SYSOP))
      outs("(u)/(H)         �]�w�ϥΪ̸��/�������μҦ�\n");
      outs("(R)/(K)         �d�ߨϥΪ̪��u��m�W/���a�J��X�h\n");
  }
  pressanykey();
}


static int
search_pickup(num, actor, pklist)
  int num;
  int actor;
  pickup pklist[];
{
  char genbuf[IDLEN + 2];

  getdata(b_lines - 1, 0, "�п�J�ϥΪ̩m�W�G", genbuf, IDLEN + 1, DOECHO, 0);
  move(b_lines - 1, 0);
  clrtoeol();

  if (genbuf[0])
  {
    int n = (num + 1) % actor;
    str_lower(genbuf, genbuf);
    while (n != num)
    {
      if (strstr_lower(pklist[n].ui->userid, genbuf))
        return n;
      if (++n >= actor)
        n = 0;
    }
  }
  return -1;
}


static int
pickup_cmp(i, j)
  pickup *i, *j;
{
  switch (pickup_way)
  {
  case 0:
    {
      register int friend;

      if (friend = j->friend - i->friend)
        return friend;
    }
  case 1:
    return strcasecmp(i->ui->userid, j->ui->userid);
  case 2:
    return (i->ui->mode - j->ui->mode);
  case 3:
    return (i->idle - j->idle);
  case 4:
    return strcasecmp(i->ui->from, j->ui->from);
  }
}

static char *       /* Kaede show friend description */
friend_descript(uident)
  char *uident;
{
  static char *space_buf="                    ";
  static char desc_buf[80];
  char fpath[80], name[IDLEN + 2], *desc, *ptr;
  int len, flag;
  FILE *fp;
  char genbuf[200];

  setuserfile(fpath, friend_file[0]);
  if (fp = fopen(fpath, "r"))
  {
    sprintf(name, "%s ", uident);
    len = strlen(name);
    desc = genbuf + 13;

    while ((flag = (int)fgets(genbuf, STRLEN, fp)))
    {
      if (!memcmp(genbuf, name, len))
      {
        if (ptr = strchr(desc, '\n'))
          ptr[0] = '\0';
        if (desc) break;
      }
    }

    fclose(fp);

    if(desc && flag)
      strcpy(desc_buf, desc);
    else
      return space_buf;

    return desc_buf;
  }
  else
    return space_buf;
}

static void
pickup_user()
{
  static int real_name = 0;
  static int show_friend = 0;
  static int show_uid = 0;
  static int show_tty = 0;
  static int show_pid = 0;
  static int num = 0;
  char genbuf[200];

  register user_info *uentp;
  register int state = US_PICKUP, hate, ch;
  register int actor, head, foot;
  int badman;
  int savemode = currstat;
  time_t diff, freshtime;
  pickup pklist[USHM_SIZE];

  struct stat ttystat;
  char buf[20];
  char pagerchar[4] = "* o ";
  char *msg_pickup_way[PICKUP_WAYS] =
  { "�١I�B��",
    "���ͥN��",
    "���ͰʺA",
    "�o�b�ɶ�",
    "�Ӧۦ��"
  };

  while (1)
  {
    if (state == US_PICKUP)
    {
      freshtime = 0;
    }

    if (utmpshm->uptime > freshtime)
    {
      time(&freshtime);
      friends_number = override_number = rejected_number = actor = ch = 0;

      while (ch < USHM_SIZE)
      {
        uentp = &(utmpshm->uinfo[ch++]);
        if (uentp->pid > 1)
        {
          count_number = 1;
          head = is_friend(uentp);
          if (!((badman = is_rejected(uentp)) & HRM && head & 2 &&
              PERM_HIDE(uentp))) {
             if (badman & HRM && !(head & 2)
                && !HAS_PERM(PERM_SYSOP) ||
                 (uentp->invisible && !(HAS_PERM(PERM_SYSOP) || HAS_PERM(PERM_SEECLOAK))))
               continue;           /* Thor: can't see anyone who rejects you. */

             if (!PERM_HIDE(currutmp) && PERM_HIDE(uentp))
                continue;

             if (cuser.uflag & FRIEND_FLAG && !head)
               continue;
           }
/* 2003/08/30 by Terry */
	/*count_number = 0;*/
/*		       */

#ifdef SHOW_IDLE_TIME
/*
          strcpy(buf, uentp->tty);

          if (stat(buf, &ttystat))
          {
            diff = 0;
          }
          else

          {
*/
            diff = freshtime - uentp->uptime;

#ifdef DOTIMEOUT
            /* prevent fault /dev mount from kicking out users */

            if (!(PERM_HIDE(uentp) || uentp->mode == MAILALL) &&
                (diff > IDLE_TIMEOUT) && (diff < 60 * 60 * 24 * 5))
            {
              if ((kill(uentp->pid, SIGHUP) == -1) && (errno == ESRCH))
                memset(uentp, 0, sizeof(user_info));
              continue;
            }
#endif
/*
          }
*/
          pklist[actor].idle = diff;
#endif

          pklist[actor].friend = head;
          pklist[actor].ui = uentp;
          actor++;
        }
      }
      
/* 2003/08/30 by Terry */
      count_number = 0;
/*		       */
      badman = rejected_number;

      state = US_PICKUP;

      if (!actor)
      {
        getdata(b_lines - 1, 0, "�A���B���٨S�W���A�n�ݬݤ@����Ͷ�(Y/N)�H[Y]", genbuf, 4, LCECHO, 0);
        if (genbuf[0] != 'n')
        {
          cuser.uflag &= ~FRIEND_FLAG;
          continue;
        }
        return;
      }
    }

    if (state >= US_RESORT)
    {
      qsort(pklist, actor, sizeof(pickup), pickup_cmp);
    }

    if (state >= US_ACTION)
    {
      showtitle((cuser.uflag & FRIEND_FLAG)? "�n�ͦC��": "�𶢲��", BoardName);
      prints("  �ƧǤ覡�G[%s]  �W���H�ơG%-6d[1;32m�ڪ��B�͡G%-4d[33m�P�ڬ��͡G%-4d[31m�a�H�G%-3d[0m\n"
        "[7m  %sP%c�N��         %-21s%-17s%-16s%-4s[0m\n",
        msg_pickup_way[pickup_way], actor,
        friends_number, override_number, badman,
#ifdef SHOWUID
        show_uid ? "UID" :
#endif
        "No.",
        (HAS_PERM(PERM_SEECLOAK) || HAS_PERM(PERM_SYSOP)) ? 'C' : ' ',

#ifdef REALINFO
        real_name ? "�m�W" :
#endif

        "�ʺ�", show_friend ? "�n�ʹy�z" : "�G�m",

#ifdef SHOWTTY
        show_tty ? "TTY " :
#endif
        "�ʺA",
#ifdef SHOWPID
        show_pid ? " PID" :
#endif
#ifdef SHOW_IDLE_TIME
        "���m"
#else
        ""
#endif

        );
    }
    else
    {
      move(3, 0);
      clrtobot();
    }

    if (num < 0)
      num = 0;
    else if (num >= actor)
      num = actor - 1;

    head = (num / p_lines) * p_lines;
    foot = head + p_lines;
    if (foot > actor)
      foot = actor;

    for (ch = head; ch < foot; ch++)
    {
      uentp = pklist[ch].ui;

      if (!uentp->pid)
      {
        state = US_PICKUP;
        break;
      }

#ifdef SHOW_IDLE_TIME
      diff = pklist[ch].idle;
      if (diff > 0)
        sprintf(buf, "%3d'%02d", diff / 60, diff % 60);
      else
        buf[0] = '\0';
#else
      buf[0] = '\0';
#endif

#ifdef SHOWPID
      if (show_pid)
        sprintf(buf, "%6d", uentp->pid);
#endif

      state = (currutmp == uentp) ? 6 : pklist[ch].friend;

      hate = is_rejected(uentp);
      if (PERM_HIDE(uentp)) {
         if (hate & HRM && is_friend(uentp) & 2) {
            hate = 0;
            state = 5;
         }
         else
            state = PERM_HIDE(currutmp) ? 5 : 0;
      }
      else if (is_friend(uentp) & 2)
         hate &= 1;

      if (PERM_HIDE(currutmp) && state == 3)
         state = 6;

      diff = uentp->pager & !(hate & HRM);
      prints("%5d%c%c%s%-13s%-21.20s%s%-17.16s%-14.14s%s\n",
#ifdef SHOWUID
        show_uid ? uentp->uid :
#endif
        (ch + 1),
        (hate & HRM)? 'X' : (uentp->pager == 3) ? 'W' : (uentp->pager == 2) ? '-' : pagerchar[(state & 2) | diff],
        (uentp->invisible ? ')' : ' '), 
        (hate & IRH)? fcolor[4] : fcolor[state],
        uentp->userid,

#ifdef REALINFO
        real_name ? uentp->realname :
#endif
        uentp->username, /*state*/ 1 ? "[0m" : "",
        show_friend ? friend_descript(uentp->userid) :
#ifdef USE_MC07_WHERE
        ( (uentp->pager != 2 && uentp->pager != 3 && diff || HAS_PERM(PERM_SYSOP)) ? where(uentp->from) : "@" ),
#else
        ( (uentp->pager != 2 && uentp->pager != 3 && diff || HAS_PERM(PERM_SYSOP)) ? uentp->from : "@" ),
#endif
#ifdef SHOWTTY
        show_tty ? uentp->tty :
#endif
        modestring(uentp, 0), buf);
    }
    if (state == US_PICKUP)
      continue;

    move(b_lines, 0);
/* 2003/08/30 by Terry */
    outs("[31;47m (TAB/f)[30m�Ƨ�/�n�� [31m(t)[30m��� \
[31m(a/d/o)[30m��� [31m(q)[30m�d�� [31m(w)[30m���� \
[31m(m)[30m�H�H [31m(h)[30m�u�W���U     [m");
/*		       */

    state = 0;
    while (!state)
    {
      ch = cursor_key(num + 3 - head, 0);
      if (ch == KEY_RIGHT || ch == '\n' || ch == '\r')
        ch = 't';

      switch (ch)
      {
      case KEY_LEFT:
      case 'e':
      case 'E':
        return;

      case KEY_TAB:
        if (++pickup_way >= PICKUP_WAYS)
          pickup_way = 0;
        state = US_RESORT;
        num = 0;
        break;

      case KEY_DOWN:
      case 'n':
        if (++num < actor)
        {
          if (num >= foot)
            state = US_REDRAW;
          break;
        }

      case '0':
      case KEY_HOME:
        num = 0;
        if (head)
          state = US_REDRAW;
        break;

      case 'N':
         if (HAS_PERM(PERM_BASIC)) {
            char buf[100];

            sprintf(buf, "�ʺ� [%s]�G", currutmp->username);
            if (!getdata(1, 0, buf, currutmp->username, 21, DOECHO, currutmp->username))
               strcpy(currutmp->username, cuser.username);

            state = US_PICKUP;
         }
         break;

      case 'H':
         if (HAS_PERM(PERM_SYSOP)) {
            currutmp->userlevel ^= PERM_DENYPOST;
            state = US_PICKUP;
         }
         break;

/* by MH  �o�ӥ\���ooxx, ���� */
/*      case 'C':
         if (HAS_PERM(PERM_SYSOP)) {
            char buf[100];

            sprintf(buf, "�N�� [%s]�G", currutmp->userid);
            if (!getdata(1, 0, buf, currutmp->userid, IDLEN + 1, DOECHO, currutmp->userid))
               strcpy(currutmp->userid, cuser.userid);

            state = US_PICKUP;
         }
         break;*/
      case 'F':
         if (HAS_PERM(PERM_SYSOP)) {
            char buf[100];

            sprintf(buf, "�G�m [%s]�G", currutmp->from);
            if (!getdata(1, 0, buf, currutmp->from, 17, DOECHO, currutmp->from))
               strncpy(currutmp->from, fromhost, 28);

            state = US_PICKUP;
         }
         break;

      case ' ':
      case KEY_PGDN:
      case Ctrl('F'):
        if (foot < actor)
        {
          num += p_lines;
          state = US_REDRAW;
          break;
        }
        if (head)
          num = 0;
        state = US_PICKUP;
        break;

      case KEY_UP:
        if (--num < head)
        {
          if (num < 0)
          {
            num = actor - 1;
            if (actor == foot)
              break;
          }
          state = US_REDRAW;
        }
        break;

      case KEY_PGUP:
      case Ctrl('B'):
      case 'P':
        if (head)
        {
          num -= p_lines;
          state = US_REDRAW;
          break;
        }

      case KEY_END:
      case '$':
        num = actor - 1;
        if (foot < actor)
          state = US_REDRAW;
        break;

      case '/':
        {
          int tmp;
          if ((tmp = search_pickup(num, actor, pklist)) >= 0)
            num = tmp;
          state = US_REDRAW;
        }
        break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        {                       /* Thor: �i�H���Ʀr����ӤH */
          int tmp;
          if ((tmp = search_num(ch, actor - 1)) >= 0)
            num = tmp;
          state = US_REDRAW;
        }
        break;

#ifdef  REALINFO
      case 'R':         /* ��ܯu��m�W */
        if (HAS_PERM(PERM_SYSOP))
          real_name ^= 1;
        state = US_PICKUP;
        break;
#endif
#ifdef  SHOWUID
      case 'U':
        if (HAS_PERM(PERM_SYSOP))
          show_uid ^= 1;
        state = US_PICKUP;
        break;
#endif
#ifdef  SHOWTTY
      case 'Y':
        if (HAS_PERM(PERM_SYSOP))
          show_tty ^= 1;
        state = US_PICKUP;
        break;
#endif
#ifdef  SHOWPID
      case 'I':
        if (HAS_PERM(PERM_SYSOP))
          show_pid ^= 1;
        state = US_PICKUP;
        break;
#endif

      case 'b':         /* broadcast */
        if (cuser.uflag & FRIEND_FLAG || HAS_PERM(PERM_SYSOP))
        {
          int actor_pos = actor;
          char ans[4];

          state = US_PICKUP;
          if (!getdata(0, 0, "�s���T��:", genbuf + 1, 60, DOECHO, 0))
             break;
          if (getdata(0, 0, "�T�w�s��? [Y]", ans, 4, LCECHO, 0) && *ans == 'n')
             break;
          /*genbuf[0] = HAS_PERM(PERM_SYSOP) ? 2 : 0;*/
          genbuf[0] = 2;  /* Tzu: �@��User�s���]�|���s���r�� */
          while (actor_pos)
          {
            uentp = pklist[--actor_pos].ui;
            if (uentp->pid &&
                currpid != uentp->pid &&
                kill(uentp->pid, 0) != -1 &&
                (HAS_PERM(PERM_SYSOP) || uentp->pager != 3))
                my_write(uentp->pid, genbuf);
          }
        }
        break;

      case 's':         /* ��ܦn�ʹy�z */
        show_friend ^= 1;
        state = US_PICKUP;
        break;

      case 'u':         /* �u�W�ק��� */
      case 'K':         /* ���a�J��X�h */
        if (!HAS_PERM(PERM_ACCOUNTS))
          continue;
        uentp = pklist[num].ui;
        state = US_ACTION;
        break;

      case 't':
      case 'w':
        if (!(cuser.userlevel & PERM_PAGE))
          continue;
        uentp = pklist[num].ui;
        state = US_ACTION;
        break;

      case 'a':
      case 'A':
      case 'd':
      case 'D':
      case 'o':
      case 'O':
      case 'f':
        if (!HAS_PERM(PERM_LOGINOK))    /* ���U�~�� Friend */
          break;
        if (ch == 'f')
        {
          cuser.uflag ^= FRIEND_FLAG;
          state = US_PICKUP;
          break;
        }
        uentp = pklist[num].ui;
        state = US_ACTION;
        break;

      case 'q':
      case 'm':
      case 'r':
      case 'l':
        if (bad_user(cuser.userid) || !cuser.userlevel && ch != 'q' && ch != 'l') /* guest �u�� query */
          break;
        uentp = pklist[num].ui;
      case 'h':
        state = US_ACTION;
        break;
/* MH */
        case Ctrl('R'):
         mh_throw_water_ball();
         state = US_PICKUP;
         break;
/*    */
      case 'p':
         if (HAS_PERM(PERM_BASIC)) {
            t_pager();
            state = US_PICKUP;
         }
         break;
      case KEY_ESC:
         if (KEY_ESC_arg == 'c')
            capture_screen();
         else if (KEY_ESC_arg == 'n') {
            edit_note();
            state = US_PICKUP;
         }
         break;
      /* Tzu */
      case 'Q':
         t_query();
         state = US_PICKUP;
         break;
      /*     */
      default:          /* refresh user state */
        state = US_PICKUP;
      }
    }

    if (state != US_ACTION)
      continue;

    if (ch == 'w')
    {
      if ((uentp->pid != currpid) &&
          (HAS_PERM(PERM_SYSOP) || uentp->pager != 3))
      {
        cursor_show(num + 3 - head, 0);
        my_write(uentp->pid, "���u Call-In�G");
      }
      else
        state = 0;
    }
    else if (ch == 'l')
    {                           /* Thor: �� Last call in */
      t_display();
      state = US_PICKUP;
    }
    else
    {
      switch (ch)
      {
      case 'r':
        m_read();
        break;
      case 'a':
      case 'A':
        friend_add(uentp->userid,
           (ch == 'a') ? FRIEND_OVERRIDE : FRIEND_REJECT);
        friend_load();
        state = US_PICKUP;
        break;

      case 'd':
      case 'D':
        sprintf(genbuf, "�T�w�� %s �q [%s] ������(Y/N)?[N]",
           uentp->userid, friend_list[(ch == 'd') ? 0 : 1]);
        if (getdata(1, 0, genbuf, genbuf, 4, LCECHO, 0) && *genbuf == 'y') {
          friend_delete(uentp->userid,
             (ch == 'd') ? FRIEND_OVERRIDE : FRIEND_REJECT);
          friend_load();
        }
        state = US_PICKUP;
        break;

      case 'o':
      case 'O':
        if (ch == 'o')
           t_override();
        else
           t_reject();
        state = US_PICKUP;
        break;

      case 'K':

        if (uentp->pid && (kill(uentp->pid, 0) != -1))
        {
          move(1, 0);
          clrtobot();
          move(2, 0);
          my_kick(uentp);
          state = US_PICKUP;
        }
        break;

      case 'm':
        stand_title("�H  �H");
        prints("���H�H�G%s", uentp->userid);
        my_send(uentp->userid);
        break;

      case 'q':
        strcpy(currauthor, uentp->userid);
        my_query(uentp->userid);
        break;

      case 'u':         /* Thor: �i�u�W�d�ݤέק�ϥΪ� */
        {
          int id;
          userec muser;
           strcpy(currauthor, uentp->userid);
          stand_title("�ϥΪ̳]�w");
          move(1, 0);
          if (id = getuser(uentp->userid))
          {
            memcpy(&muser, &xuser, sizeof(muser));
            user_display(&muser, 1);
#ifndef MH_USEFORM
            uinfo_query(&muser, 1, id);
#else
            mh_uinfo_query(&muser, 1, id);
#endif
          }
        }
        break;

      case 'h':         /* Thor: �� Help */
        t_showhelp();
        break;

      case 't':
        if (uentp->pid != currpid)
/*      if (uentp->uid != usernum)      */
        {
          move(1, 0);
          clrtobot();
          move(3, 0);
          my_talk(uentp);
          state = US_PICKUP;
        }
      }
    }
    setutmpmode(savemode);
  }
}


static int
listcuent(uentp)
  user_info *uentp;
{
  if ((uentp->uid != usernum) && (!uentp->invisible || HAS_PERM(PERM_SYSOP) || HAS_PERM(PERM_SEECLOAK)))
    AddNameList(uentp->userid);
  return 0;
}


static void
creat_list()
{
  CreateNameList();
  apply_ulist(listcuent);
}


int
t_users()
{
  int destuid0 = currutmp->destuid;
  int mode0 = currutmp->mode;
  int stat0 = currstat;
  static enter;

  currutmp->msgcount = 0;
  if (chkmailbox() || enter > 2)
     return;
  ++enter;
  setutmpmode(LUSERS);
  pickup_user();
  currutmp->mode = mode0;
  currutmp->destuid = destuid0;
  currstat = stat0;
  --enter;
  return 0;
}


int
t_pager()
{
  currutmp->pager = (currutmp->pager + 1) % 4;
  return 0;
}


int
t_idle()
{
  int destuid0 = currutmp->destuid;
  int mode0 = currutmp->mode;
  int stat0 = currstat;
  char genbuf[20];

  setutmpmode(IDLE);
  /* Tzu */
  getdata(b_lines - 1, 0, "[0]�o�b (1)���q�� (2)�V�� (3)���O�� (4)�˦� (5)ù�� (6)��L (L)��w (Q)�S��", genbuf, 3, DOECHO, 0);
/*  getdata(b_lines - 1, 0, "�z�ѡG[0]�o�b (1)���q�� (2)�V�� (3)���O�� (4)�˦� (5)ù�� (6)��L (Q)�S�ơH", genbuf, 3, DOECHO, 0);*/
  if (genbuf[0] == 'q' || genbuf[0] == 'Q') {
    currutmp->mode = mode0;
    currstat = stat0;
    return 0;
  }
  /* Tzu */
  else if (genbuf[0] == 'l' || genbuf[0] == 'L') {
    currutmp->mode = mode0;
    currstat = stat0;
    u_lock();
    return 0;    
  }
  /*      */
  else if (genbuf[0] >= '1' && genbuf[0] <= '6')
    currutmp->destuid = genbuf[0] - '0';
  else
    currutmp->destuid = 0;

  if (currutmp->destuid == 6)
    if (!cuser.userlevel || !getdata(b_lines - 1, 0, "�o�b���z�ѡG", currutmp->chatid, 11, DOECHO, 0))
      currutmp->destuid = 0;


{
  char buf[80];

  move(b_lines - 1, 0);
  clrtoeol();
  sprintf(buf, "�o�b��: %s", (currutmp->destuid != 6) ? IdleTypeTable[currutmp->destuid] : currutmp->chatid);
  outs(buf);
  refresh();
  igetch();
}
  currutmp->mode = mode0;
  currutmp->destuid = destuid0;
  currstat = stat0;

  return 0;
}


int
t_query()
{
  char uident[STRLEN];

  stand_title("�d�ߺ���");
  usercomplete(msg_uid, uident);
  if (uident[0])
    my_query(uident);
  return 0;
}


int
t_talk()
{
  char uident[16];
  int tuid, unum, ucount;
  user_info *uentp;
  char genbuf[4];

  if (count_ulist() <= 1)
  {
    outs("�ثe�u�W�u���z�@�H�A���ܽЪB�ͨӥ��{�i" BOARDNAME "�j�a�I");
    return XEASY;
  }
  stand_title("���}�ܧX�l");
  creat_list();
  namecomplete(msg_uid, uident);
  if (uident[0] == '\0')
    return 0;

  move(3, 0);
  if (!(tuid = searchuser(uident)) || tuid == usernum)
  {
    outs(err_uid);
    pressanykey();
    return 0;
  }

  /* ----------------- */
  /* multi-login check */
  /* ----------------- */

  unum = 1;
  while ((ucount = count_logins(cmpuids, tuid, 0)) > 1)
  {
    outs("(0) ���Q talk �F...\n");
    count_logins(cmpuids, tuid, 1);
    getdata(1, 33, "�п�ܤ@�Ӳ�ѹ�H [0]�G", genbuf, 4, DOECHO, 0);
    unum = atoi(genbuf);
    if (unum == 0)
      return 0;
    move(3, 0);
    clrtobot();
    if (unum > 0 && unum <= ucount)
      break;
  }

  if (uentp = (user_info *) search_ulistn(cmpuids, tuid, unum))
    my_talk(uentp);

  return 0;
}


/* ------------------------------------- */
/* ���H�Ӧ���l�F�A�^���I�s��            */
/* ------------------------------------- */


user_info *uip;

void
talkreply()
{
  int a;
  struct hostent *h;
  char hostname[STRLEN], buf[4];
  struct sockaddr_in sin;
  char genbuf[200];
  int i;

  uip = currutmp->destuip;
  sprintf(page_requestor, "%s (%s)", uip->userid, uip->username);
  currutmp->destuid = uip->uid;
  currstat = XMODE;             /* �קK�X�{�ʵe */

  clear();
  outs("\n\n\
       (Y) ���ڭ� talk �a�I     (A) �ڲ{�b�ܦ��A�е��@�|��A call ��\n\
       (N) �ڲ{�b���Q talk      (B) �藍�_�A�ڦ��Ʊ������A talk\n\
       (C) �Ф��n�n�ڦn�ܡH     (D) �A�u���ܷСA�ڹ�b���Q��A talk\n\
       (E) ���ƶܡH�Х��ӫH     (F) �ڦۤv��J�z�Ѧn�F...:P\n\n"
       );

  getuser(uip->userid);
  currutmp->msgs[0].last_pid = uip->pid;
  strcpy(currutmp->msgs[0].last_userid, uip->userid);
  strcpy(currutmp->msgs[0].last_call_in, "�I�s�B�I�s�Ať��Ц^�� (Ctrl-R)");
  prints("���Ӧ� [%s]�A�@�W�� %d ���A�峹 %d �g\n",
    uip->from, xuser.numlogins, xuser.numposts);
  showplans(uip->userid);
  show_last_call_in();
  sprintf(genbuf, "�A�Q�� %s ���ѶܡH�п��(Y/N/A/B/C/D) ", page_requestor);
  do
  {
    getdata(0, 0, genbuf, buf, 4, LCECHO, 0);
  } while(buf[0] == '\0');

  if (uip->mode != PAGE) {
     sprintf(genbuf, "%s�w����I�s�A��Enter�~��...", page_requestor);
     getdata(0, 0, genbuf, buf, 4, LCECHO, 0);
     return;
  }

  currutmp->msgcount = 0;
  strcpy(save_page_requestor, page_requestor);
  memset(page_requestor, 0, sizeof(page_requestor));
  gethostname(hostname, STRLEN);

  if (!(h = gethostbyname(hostname)))
  {
    perror("gethostbyname");
    return;
  }
  memset(&sin, 0, sizeof sin);
  sin.sin_family = h->h_addrtype;
  memcpy(&sin.sin_addr, h->h_addr, h->h_length);
  sin.sin_port = uip->sockaddr;
  a = socket(sin.sin_family, SOCK_STREAM, 0);
  if ((connect(a, (struct sockaddr *) & sin, sizeof sin)))
  {
    perror("connect err");
    return;
  }
  write(a, buf, 1);
/* Thor */  
  if(buf[0] == 'f' || buf[0] == 'F')
  {
    if (!getdata(b_lines, 0, "���� talk ����]�G", genbuf, 60, DOECHO,0))
      strcpy(genbuf, "���i�D�A�� !! ^o^");
    write(a, genbuf, 60);
  }
/*      */  
  if (buf[0] == 'y')
     do_talk(a);
  else
     close(a);
  clear();
}


/* ------------------------------------- */
/* ���ͰʺA²��                          */
/* ------------------------------------- */


int
shortulist(uentp)
  user_info *uentp;
{
  static int lineno, fullactive, linecnt;
  static int moreactive, page, num;
  char uentry[50];
  int state;

  if (!lineno)
  {
    lineno = 3;
    page = moreactive ? (page + p_lines * 3) : 0;
    linecnt = num = moreactive = 0;
    move(1, 70);
    prints("Page: %d", page / (p_lines) / 3 + 1);
    move(lineno, 0);
  }
  if (uentp == NULL)
  {
    int finaltally;

    clrtoeol();
    move(++lineno, 0);
    clrtobot();
    finaltally = fullactive;
    lineno = fullactive = 0;
    return finaltally;
  }
  if ((!HAS_PERM(PERM_SYSOP) && !HAS_PERM(PERM_SEECLOAK) && uentp->invisible) ||
      ((is_rejected(uentp) & HRM) && !HAS_PERM(PERM_SYSOP)))
  {
    if (lineno >= b_lines)
      return 0;
    if (num++ < page)
      return 0;
    memset(uentry, ' ', 25);
    uentry[25] = '\0';
  }
  else
  {
    fullactive++;
    if (lineno >= b_lines)
    {
      moreactive = 1;
      return 0;
    }
    if (num++ < page)
      return 0;

    state = (currutmp == uentp) ? 6 : is_friend(uentp);

    if (PERM_HIDE(uentp))
       if (is_rejected(uentp) & HRM) {
          state = 5;
       }
       else
          state = (is_rejected(uentp) & HRM || PERM_HIDE(currutmp)) ? 5 : 0;

    if (PERM_HIDE(currutmp) && state == 3)
       state = 6;

    sprintf(uentry, "%s%-13s%c%-10s%s ", fcolor[state],
      uentp->userid, uentp->invisible ? '#' : ' ',
      modestring(uentp, 1), state ? "[0m" : "");
  }
  if (++linecnt < 3)
  {
    strcat(uentry, "�x");
    outs(uentry);
  }
  else
  {
    outs(uentry);
    linecnt = 0;
    clrtoeol();
    move(++lineno, 0);
  }
  return 0;
}


static void
do_list(modestr)
  char *modestr;
{
  int count;

  showtitle(modestr, BoardName);
  if (currstat == MONITOR)
    prints("�C�j %d ���s�@���A�Ы�[Ctrl-C]��[Ctrl-D]���}", M_INT);

  outc('\n');
  outs(msg_shortulist);

  friends_number = override_number = 0;
  if (apply_ulist(shortulist) == -1)
  {
    outs(msg_nobody);
  }
  else
  {
    time_t thetime = time(NULL);

    count = shortulist(NULL);
    move(b_lines, 0);
    prints("[1;37;46m  �W���`�H�ơG%-7d[32m�ڪ��B�͡G%-6d"
      "[33m�P�ڬ��͡G%-8d[30m%-23s[37;40;0m",
      count, friends_number, override_number, Cdate(&thetime));
    refresh();
  }
}


int
t_list()
{
  setutmpmode(LUSERS);
  do_list("�ϥΪ̪��A");
  igetch();
  return 0;
}


/* ------------------------------------- */
/* �ʬݨϥα���                          */
/* ------------------------------------- */

int idle_monitor_time;

static void
sig_catcher()
{
  if (currstat != MONITOR)
  {

#ifdef DOTIMEOUT
    init_alarm();
#else
    signal(SIGALRM, SIG_IGN);
#endif

    return;
  }
  if (signal(SIGALRM, sig_catcher) == SIG_ERR)
  {
    perror("signal");
    exit(1);
  }

#ifdef DOTIMEOUT
  if (!(PERM_HIDE(currutmp) || currutmp->mode == MAILALL))
     idle_monitor_time += M_INT;
  if (idle_monitor_time > MONITOR_TIMEOUT)
  {
    clear();
    fprintf(stderr, "timeout\n");
    abort_bbs();
  }
#endif

  do_list("�l�ܯ���");
  alarm(M_INT);
}


int
t_monitor()
{
  char c;
  int i;

  setutmpmode(MONITOR);
  alarm(0);
  signal(SIGALRM, sig_catcher);
  idle_monitor_time = 0;

  do_list("�l�ܯ���");
  alarm(M_INT);
  while (YEA)
  {
    i = read(0, &c, 1);
    if (!i || c == Ctrl('D') || c == Ctrl('C'))
      break;
    else if (i == -1)
    {
      if (errno != EINTR)
      {
        perror("read");
        exit(1);
      }
    }
    else
      idle_monitor_time = 0;
  }
  return 0;
}


/* ------------------------------------- */
/* �n�ͦW��B�¦W��                      */
/* ------------------------------------- */


void
friend_load()
{
  FILE *fp;
  ushort myfriends[MAX_FRIEND];
  ushort myrejects[MAX_REJECT];
  char genbuf[200];

  friend_file[0] = fn_overrides;
  friend_file[1] = fn_reject;
  memset(myfriends, 0, sizeof(myfriends));
  friendcount = 0;
  setuserfile(genbuf, fn_overrides);
  if (fp = fopen(genbuf, "r"))
  {
    ushort unum;

    while (fgets(genbuf, STRLEN, fp) && friendcount < MAX_FRIEND - 2)
    {
      if (strtok(genbuf, str_space))
      {
        if (unum = searchuser(genbuf))
        {
          myfriends[friendcount++] = (ushort) unum;
        }
      }
    }
    fclose(fp);
  }
  memcpy(currutmp->friend, myfriends, sizeof(myfriends));

  memset(myrejects, 0, sizeof(myrejects));
  rejected_number = 0;
  setuserfile(genbuf, fn_reject);
  if (fp = fopen(genbuf, "r"))
  {
    ushort unum;

    while (fgets(genbuf, STRLEN, fp) && rejected_number < MAX_REJECT - 2)
    {
      if (strtok(genbuf, str_space))
      {
        if (unum = searchuser(genbuf))
        {
          myrejects[rejected_number++] = (ushort) unum;
        }
      }
    }
    fclose(fp);
  }
  memcpy(currutmp->reject, myrejects, sizeof(myrejects));
}


void
friend_edit(type)
  int type;
{
  char fpath[80], line[80], uident[20], *msg;
  int count, column, dirty;
  FILE *fp;
  char genbuf[200];

  setuserfile(fpath, friend_file[type]);
  msg = friend_list[type];

  dirty = 0;
  while (1)
  {
    stand_title(msg);

    count = 0;
    CreateNameList();

    if (fp = fopen(fpath, "r"))
    {
      move(3, 0);
      column = 0;
      while (fgets(genbuf, STRLEN, fp))
      {
        if (genbuf[0] <= ' ')
          continue;
        strtok(genbuf, str_space);
        AddNameList(genbuf);
        prints("%-13s", genbuf);
        count++;
        if (++column > 5)
        {
          column = 0;
          outc('\n');
        }
      }
      fclose(fp);
    }
    getdata(1, 0, (count ? "(A)�W�[ (D)�R�� (L)�ԲӦC�X (E)�s�� (Q)�����H[Q] " :
        "(A)�W�[ (Q)�����H[Q] "), uident, 4, LCECHO, 0);
    if (*uident == 'a')
    {
      move(1, 0);
      usercomplete(msg_uid, uident);
      if (uident[0] && searchuser(uident) && !InNameList(uident))
      {
        friend_add(uident, type);
        dirty = 1;
      }
    }
    else if ((*uident == 'd') && count)
    {
      move(1, 0);
      namecomplete(msg_uid, uident);
      if (uident[0] && InNameList(uident))
      {
        friend_delete(uident, type);
        dirty = 1;
      }
    }
    else if ((*uident == 'l') && count)
    {
      strcpy(vetitle, "[�n�ͦW��]");
      more(fpath, YEA);
    }
    else if (*uident == 'e') {
       vedit(fpath, NA);
       dirty = 1;
    }
    else
      break;
  }
  if (dirty)
    friend_load();
}


int
t_override()
{
  friend_edit(FRIEND_OVERRIDE);
  return 0;
}


int
t_reject()
{
  friend_edit(FRIEND_REJECT);
  return 0;
}


/*
int
t_friends()
{
  if (friendcount)
  {
    setutmpmode(FRIEND);

    pickup_user();

    if (!(friends_number || override_number))
    {
      outs("�A���@�U�a�A�]�\\�L�̫ݷ|��N�W�u�F�C");
      return XEASY;
    }
    return 0;
  }
  else
  {
    outs("�ثe�٨S�]�w�n�ͦW��");
    return XEASY;
  }
}
*/


void
t_aloha()
{
   int i;
   user_info *uentp;
   pid_t pid;
   char buf[100];

   sprintf(buf + 1, "^[[1;33;44m�� %s(%s) �W���F! ^[[0m",
      cuser.userid, cuser.username);
   *buf = 0;

    /* Thor: �S�O�`�N, �ۤv�W�����|�q���ۤv... */

   for (i = 0; i < USHM_SIZE; i++) {
      uentp = &utmpshm->uinfo[i];
      if ((pid = uentp->pid) && (kill(pid, 0) != -1) &&
          uentp->pager && (is_friend(uentp) & 2) &&
          strcmp(uentp->userid, cuser.userid))
         my_write(uentp->pid, buf);
   }
}

my_outmsg(char* msg)
{
    move(b_lines, 0);
    clrtoeol();
    outs(msg);
    refresh();
}

/* MH */
/* �i�H��� row �� my_outmsg */
my_outmsg_row(char* msg, int mhrow)
{
    move(mhrow, 0);
    clrtoeol();
    outs(msg);
    refresh();
}
/*    */
