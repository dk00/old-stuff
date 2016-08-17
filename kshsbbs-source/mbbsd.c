/*-------------------------------------------------------*/
/* mbbsd.c      ( NTHU CS MapleBBS Ver 3.00 )            */
/*-------------------------------------------------------*/
/* target : BBS daemon/main/login/top-menu routines      */
/* create : 95/03/29                                     */
/* update : 96/10/10                                     */
/*-------------------------------------------------------*/


#define _MAIN_C_

#include <varargs.h>
#include "bbs.h"


#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/telnet.h>
#include <syslog.h>


/* 2003/08/30 by Terry */
#undef	HAVE_CHKLOAD
#define	USE_STOPLOGIN
/*		       */
#define SOCKET_QLEN     4
#define TH_LOW          100
#define TH_HIGH         120
#define PID_FILE        "/bbs1/home/bbs/run/mbbsd.pid"

/* 2003/08/30 by Terry */
#ifdef	HAVE_CHKLOAD
#define	BANNER	"\r\n�i��������-���ӿv�ڡj�� �������� �� (bbs.kshs.kh.edu.tw)\r\nFreeBSD-jdli-2.2 [163.15.56.3]\r\n\n"
#else
#define	BANNER	"\r\n����...�A�{�b�s�V���ӿv��...����"
#endif

#ifdef	USE_STOPLOGIN
#define	FN_STOPLOGIN	"/bbs1/home/bbs/etc/stoplogin"
#endif
/*		       */


jmp_buf byebye;
char remoteusername[40] = "?";
char fromhost[40];
char genbuf[1024];
extern struct UTMPFILE *utmpshm;
static uschar enter_uflag;
int Argc;
char** Argv;
static char str_badlogin[] = "logins.bad";
int mbbsd = 1;


/* ----------------------------------------------------- */
/* operation log                                         */
/* ----------------------------------------------------- */


void
file_append(fpath, msg)
  char *fpath;
  char *msg;
{
  int fd;

  if ((fd = open(fpath, O_WRONLY | O_CREAT | O_APPEND, 0644)) > 0)
  {
    write(fd, msg, strlen(msg));
    close(fd);
  }
}


void
log_usies(mode, msg)
  char *mode, *msg;
{
  char buf[512], data[256];
  time_t now = time(0);

  if (!msg)
  {
    msg = data;
    sprintf(msg, "Stay: %d (%s@%s)",
      (now - login_start_time) / 60, remoteusername, fromhost);
  }

  sprintf(buf, "%s %s %-13s%s\n", Cdate(&now), mode, cuser.userid, msg);
  file_append(FN_USIES, buf);
}


bad_user(char* name)
{
   FILE* list;
   char buf[40];

  if (list = fopen("etc/bad_user", "r")) {
     while (fgets(buf, 40, list)) {
        buf[strlen(buf) - 1] = '\0';
        if (!strcmp(buf, name))
           return 1;
     }
     fclose(list);
  }
  return 0;
}


void
setup_utmp(mode)
  int mode;
{
  user_info uinfo;
  char buf[80];
  FILE *fp;

  memset(&uinfo, 0, sizeof(uinfo));
  uinfo.pid = currpid = getpid();
  uinfo.uid = usernum;
  uinfo.mode = currstat = mode;
  uinfo.msgcount = 0;
  uinfo.msgnum = 0;
  uinfo.userlevel = cuser.userlevel;
  uinfo.uptime = time(0);

  strcpy(uinfo.userid, cuser.userid);
  strcpy(uinfo.realname, cuser.realname);
  strcpy(uinfo.username, cuser.username);
  strncpy(uinfo.from, fromhost, 28);

  setuserfile(buf, "remoteuser");

  add_distinct(buf, getenv("RFC931"));
/* 2003/08/30 by Terry */
  mh_loginfrom(uinfo.from, uinfo.userid, fromhost);
  uinfo.from[28] = '\0';
/*		       */

  if (enter_uflag & CLOAK_FLAG)
  {
      uinfo.invisible = YEA;
    if (HAS_PERM(PERM_LOGINCLOAK))
      uinfo.invisible = YEA;
    else
      cuser.uflag ^= CLOAK_FLAG;
  }
  uinfo.pager = !(enter_uflag & PAGER_FLAG);

  getnewutmpent(&uinfo);
  friend_load();
}


void
u_exit(mode)
  char *mode;
{
  extern void auto_backup();    /* �s�边�۰ʳƥ� */
  userec xuser;
/* 2003/08/30 by Terry */
  int diff = (time(0) - login_start_time) / 60;
/*		       */

  get_record(fn_passwd, &xuser, sizeof(xuser), usernum);

  auto_backup();

  setflags(PAGER_FLAG, currutmp->pager != 1);
  if (HAS_PERM(PERM_LOGINCLOAK))
    setflags(CLOAK_FLAG, currutmp->invisible);
  purge_utmp(currutmp);
  
/* 2003/08/30 by Terry */
  if ((cuser.uflag != enter_uflag) || (currmode & MODE_DIRTY) || (diff < 1))
  {
/*		       */
    xuser.uflag = cuser.uflag;
    xuser.numposts = cuser.numposts;
    
/* 2003/08/30 by Terry */
    if (diff < 1 && cuser.numlogins)	/*�W���ɶ��֩�@�������p�W������, by Leeym */
      xuser.numlogins = --cuser.numlogins;
/*		       */

    substitute_record(fn_passwd, &xuser, sizeof(userec), usernum);
  }
  log_usies(mode, NULL);
}


setflags(mask, value)
  int mask, value;
{
  if (value)
    cuser.uflag |= mask;
  else
    cuser.uflag &= ~mask;
}


login_query()
{
  char uid[IDLEN + 1], passbuf[PASSLEN];
  int attempts;
  char genbuf[200];
  extern struct UTMPFILE *utmpshm;
  extern dumb_term;
/* 2003/08/30 by Terry */
  double cpu_load[3];
/*		       */

  dumb_term = YEA;
  resolve_utmp();
  attempts = utmpshm->number;
/* 2003/08/30 by Terry */
  getloadavg(cpu_load, 3);
  
  prints("\nPowered by FreeBSD (�t�έt�� %.2f %.2f %.2f)\n\n�w����{�i[1;37;41m %s [m�j   �����H�ơi[1;33;44m %d / %d [m�j\n\n",
         cpu_load[0], cpu_load[1], cpu_load[2], BoardName, attempts, MAXACTIVE);
/*		       */

  if (attempts >= MAXACTIVE)
  {
    outs("�ѩ�H�ƤӦh�A�бz�y��A�ӡC\n");
    oflush();
/* 2003/08/30 by Terry */
    sleep(10);
/*		       */
    exit(1);
  }
  
/* 2003/08/30 by Terry */
  /* hint 
  show_hint_message();*/
  more("etc/banner", NA);
/*		       */

  attempts = 0;
  while (1)
  {
    if (attempts++ >= LOGINATTEMPTS)
    {
      more("etc/goodbye", NA);
      oflush();
      sleep(1);
      exit(1);
    }
    
/* 2003/08/30 by Terry */
    getdata(17, 10, "\n�п�J�N���A�ΥH[guest]���[�A�H[new]���U�G", uid, IDLEN + 1, DOECHO, 0);
/*		       */

    if (ci_strcmp(uid, str_new) == 0)
    {

#ifdef LOGINASNEW
      new_register();
      break;
#else
      outs("���t�Υثe�L�k�H new ���U, �Х� guest �i�J\n");
      continue;
#endif
    }
    else if (uid[0] == '\0' || !dosearchuser(uid))
    {
      outs(err_uid);
    }
    else if (strcmp(uid, "guest") && !belong("etc/anonymous", uid))
    {
      if (Argc == 1 && !strcmp("/home/woju/bbs/maple/bbs", Argv[0]))
         break;
      getdata(0, 0, MSG_PASSWD, passbuf, PASSLEN, NOECHO, 0);
      passbuf[8] = '\0';

      if (!checkpasswd(cuser.passwd, passbuf))
      {
        logattempt(cuser.userid, '-');
        outs(ERR_PASSWD);
      }
      else
      {
        /* SYSOP gets all permission bits */

        if (!ci_strcmp(cuser.userid, str_sysop))
          cuser.userlevel = ~0;
        if (0 && HAS_PERM(PERM_SYSOP) && !strncmp(getenv("RFC931"), "?@", 2)) {
           logattempt(cuser.userid, '*');
           outs("�����Х� trusted host �i�J");
           continue;
        }
        else {
           logattempt(cuser.userid, ' ');
           break;
        }
      }
    }
    else
    {                           /* guest */
      cuser.userlevel = 0;
      cuser.uflag = COLOR_FLAG | PAGER_FLAG | BRDSORT_FLAG | MOVIE_FLAG;
      break;
    }
  }
  multi_user_check();
  /* MH */
  /* bug fixed */
  if (strcmp(uid, "guest") && !belong("etc/anonymous", uid) && ci_strcmp(uid, str_new) != 0)
    dosearchuser(uid);
  /*    */
  sethomepath(genbuf, cuser.userid);
  mkdir(genbuf, 0755);
  dumb_term = NA;
}


/* 2003/08/30 by Terry */
#if 0
/*		       */
show_hint_message()
{
        struct timeval  timep;
        struct timezone timezp;
        int     i, j, msgNum;
        FILE    *hintp;
        char    msg[200];
        /* Tzu */
        char    *bureau[6] = {"�аȳB","�Щx��","�V�ɳB","�`�ȳB","���ɤ���","�åͲ�"};
        int     tzu = rand() % 6;
        /*     */

        if (!(hintp = fopen("etc/hint", "r")))
          return 0;
        fgets(msg, 200, hintp);
        msgNum = atoi(msg);
        gettimeofday(&timep, &timezp);
        i = (int) timep.tv_sec%(msgNum + 1); /* �̷s���@�g���|�[�� */
        if (i == msgNum)
          i--;
        j = 0;

        while (j < i)
        {
          fgets(msg, 200, hintp);
          msg[1] = '\0';
          if (!strcmp(msg,"#"))
            j++;
        }

        fgets(msg, 200, hintp);
        /* Tzu */
        prints("[1;34m�X�����ǨӤU�Ҫ����n [1;37m%s���i�G[40;0m\n", bureau[tzu]);
        /*     */
        prints("                   %s[0m", msg);
        fgets(msg, 200, hintp);
        prints("                   %s[0m", msg);
        fclose(hintp);
}
/* 2003/08/30 by Terry */
#endif
/*		       */


system_abort()
{
  if (currmode)
    u_exit("ABORT");

  clear();
  refresh();
  printf("���¥��{, �O�o�`�ӳ� !\n");
  sleep(1);
  exit(0);
}


do_aloha()
{
   FILE* fp;
   char userid[80];
   char genbuf[200];

   setuserfile(genbuf, "aloha");
   
/* 2003/08/30 by Terry */
   if (fp = fopen(genbuf, "r"))
   {
      sprintf(genbuf + 1, "<<�W���q��>> -- �ڨӰաI�O�{��");
/*		       */
      *genbuf = 1;
      while (fgets(userid, 80, fp)) {
         user_info *uentp;
         extern cmpuids();
         int tuid;

         if ((tuid = searchuser(userid))  && tuid != usernum &&
             (uentp = (user_info *) search_ulistn(cmpuids, tuid, 1)) &&
             uentp->mode != XMODE &&
             (uentp->userlevel & PERM_SYSOP || !(is_rejected(uentp) & 1))) {
            my_write(uentp->pid, genbuf);
         }
      }
      fclose(fp);
   }
}


multi_user_check()
{
  register user_info *ui;
  register pid_t pid;
  int cmpuids();
  char genbuf[3];

#if 0  /* MH */ /* �n�\��j�a��...�ϥ��w�]�O'n' */
  if (HAS_PERM(PERM_SYSOP) || HAS_PERM(PERM_BM))
    return;                     /* don't check sysops */
#endif

  if (cuser.userlevel)
  {
    if (!(ui = (user_info *) search_ulist(cmpuids, usernum)))
      return;                   /* user isn't logged in */

    pid = ui->pid;
    if (!pid || (kill(pid, 0) == -1))
      return;                   /* stale entry in utmp file */
      
/* 2003/08/30 by Terry */
    getdata(0, 0, "�z�Q�N��L���ƪ� login ��U����(Y/N)�H[Y] ", genbuf, 3, LCECHO, 0);
    
    if (genbuf[0] != 'n')
    {
      kill(pid, SIGHUP);
      log_usies("KICK ", cuser.username);
/*		       */
    }
    else
    {
/* 2003/08/30 by Terry */
      if (count_multi() >= 2 && !(HAS_PERM(PERM_SYSOP) || HAS_PERM(PERM_BM)))
	system_abort();		/* Goodbye(); */
/*		       */
    }
  }
  else
  {
/* 2003/08/30 by Terry */
    extern struct UTMPFILE *utmpshm;
    
    /* allow multiple guest user */
    if (count_multi() > 16 ||
        utmpshm->number >= (MAXACTIVE - 50))	/* �y�p�ɶ����� guest login, by MH */
/*		       */
    {
      outs("\n��p�A�ثe�w���Ӧh guest, �еy��A�աC\n");
      pressanykey();
      oflush();
      exit(1);
    }
  }
}


dosearchuser(userid)
  char *userid;
{
  if (usernum = getuser(userid))
    memcpy(&cuser, &xuser, sizeof(cuser));
  else
    memset(&cuser, 0, sizeof(cuser));
  return usernum;
}


logattempt(uid, type)
  char *uid;
  char type;                    /* '-' login failure   ' ' success */
{
  char fname[40];
  int fd, len;
  char genbuf[200];

  sprintf(genbuf, "%c%-12s[%s] %s\n", type, uid,
    Cdate(&login_start_time), getenv("RFC931"));
  len = strlen(genbuf);
  if ((fd = open(str_badlogin, O_WRONLY | O_CREAT | O_APPEND, 0644)) > 0)
  {
    write(fd, genbuf, len);
    close(fd);
  }

  if (type == '-')
  {
    sprintf(genbuf, "[%s] %s\n", Cdate(&login_start_time), fromhost);
    len = strlen(genbuf);
    sethomefile(fname, uid, str_badlogin);
    if ((fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644)) > 0)
    {
      write(fd, genbuf, len);
      close(fd);
    }
  }
}


user_login()
{
  char ans[4];
  char genbuf[200];

  log_usies("ENTER", getenv("RFC931")/* fromhost */);

  /* ------------------------ */
  /* ��l�� uinfo�Bflag�Bmode */
  /* ------------------------ */

  enter_uflag = cuser.uflag;

#ifdef  INITIAL_SETUP
  if (!getbnum(DEFAULT_BOARD))
  {
    strcpy(currboard, "�|����w");
  }
  else
#endif

  {
    brc_initial(DEFAULT_BOARD);
    set_board();
  }

  setup_utmp(LOGIN);
  currmode = MODE_STARTED;
/* 2003/08/30 by Terry */
  load_userrc();
/*		       */

  /* ------------ */
  /* �e���B�z�}�l */
  /* ------------ */

  initscr();
  if (!(HAS_PERM(PERM_SYSOP) && HAS_PERM(PERM_DENYPOST)))
     do_aloha();
  more("etc/welcome", NA);

  if (cuser.userlevel)          /* not guest */
  /* if (strcmp(cuser.userid, "guest")) */
  {
    char buf[80], *ptr;

    move(t_lines - 3, 0);
    prints("     �w��z�� [1;33m%d[0;37m �׫��X�����A\
�W���z�O�q [1;33m%s[0;37m �s�������A\n\
     �ڰO�o���ѬO [1;33m%s[0;37m�C\n",
      ++cuser.numlogins, cuser.lasthost,
      Cdate(&cuser.lastlogin));

    pressanykey();

    setuserfile(genbuf, str_badlogin);
    if (more(genbuf, NA) != -1)
    {
      getdata(b_lines - 1, 0, "�z�n�R���H�W���~���ժ��O����(Y/N)?[Y]",
        ans, 3, LCECHO, 0);
      if (*ans != 'n')
        unlink(genbuf);
    }
    check_register();
    
/* 2003/08/30 by Terry */
    if (cuser.numlogins < 10)	/* �W�����Ƥp�� 10 �� newuser, by Tzu */
      more("etc/newuser", YEA);
/*		       */

    strncpy(cuser.lasthost, fromhost, 16);
    cuser.lasthost[15] = '\0';
/*
    strncpy(buf, (char *) getenv("RFC931"), 80);
    if (ptr = strchr(buf, '@'))
      *ptr = '\0';
    strncpy(cuser.remoteuser, buf, 8);
*/
    restore_backup();
  }
  else if (!strcmp(cuser.userid, STR_GUEST))
  {
/* 2003/07/05 by Terry */
    /* �������u�S��v�� guest, by Tzu */
    char *nick[16] = {"�_��", "�L�\\", "�K��", "�T��", "���~",
		      "����", "�y�c", "��ĥ", "�]��", "�P��",
		      "����", "�Ҩ�", "����", "�A�l", "�t�H",
		      "�T�U"};
    char *name[16] = {"�n�j���_��", "����", "�|�Q����", "�B�ʶ���", "���O",
		      "��", "AIR Jordon", "�K�F����", "�B�Y�Y", "�a�H���p��",
		      "�u���۫�", "�n�J", "��ꪺ�L�l", "�����S��", "�t�z�j�t�H",
		      "�ƾǷ��D"};
    char *addr[16] = {"�Ĥ��B�C�ɶ�", "�\\�U", "�X�@��", "�c���", "���ݼ�",
		      "����", "NIKE", "�G�Q�@���ִ��B���ԻX", "�q���Ы�", "��X�j��",
		      "���֯Z", "�Q�C�ճ����", "�N�O�o�ӥ�", "���t����", "���쭸�з|",
		      "�|���O�_��!"};
    int sex[16] = {6, 7, 7, 7, 7, 6, 7, 7, 4, 7, 1, 6, 7, 3, 9, 5};
    int i = time(0) % 16;
    
    currutmp->pager = 3;	/* �� guest �� pager ����, by Tzu */
    sprintf(cuser.username, "���ӿv�ڸ̪�%s", nick[i]);
/*		       */
    sprintf(currutmp->username, cuser.username);
    sprintf(cuser.realname, name[i]);
    sprintf(currutmp->realname, cuser.realname);
    sprintf(cuser.address, addr[i]);
    cuser.sex = sex[i];
    pressanykey();
  }
  else
    pressanykey();
    
/* 2003/08/30 by Terry */
  more("etc/hotnews", 2);	/* �C�ӤH���n��, guest �]�@��, by MH */
/*		       */

  if (bad_user(cuser.userid)) {
     sprintf(currutmp->username, "BAD_USER");
     cuser.userlevel = 0;
     cuser.uflag = COLOR_FLAG | PAGER_FLAG | BRDSORT_FLAG | MOVIE_FLAG;
  }

  m_init();
  while (chkmailbox())
     m_read();

  if (!PERM_HIDE(currutmp))
     cuser.lastlogin = login_start_time;
  substitute_record(fn_passwd, &cuser, sizeof(cuser), usernum);
  
/* 2003/08/30 by Terry */
#if 0
  more(fn_note_ans, 2);
/*
woju
  x_user();
*/
  x_issue();
#endif

  mh_welcome();
  birthday(YEA);
/*		       */
}


void
abort_bbs()
{
  if (currmode)
    u_exit("AXXED");
  exit(0);
}


static void
talk_request()
{
#ifdef  LINUX
  /*
   * Linux �U�s�� page ���⦸�N�i�H�����X�h�G �o�O�ѩ�Y�Ǩt�Τ@ nal
   * �i�ӴN�|�N signal handler �]�w�����w�� handler, �������O default �O�N�{
   * erminate. �ѨM��k�O�C�� signal �i�ӴN���] signal handler
   */

  signal(SIGUSR1, talk_request);
#endif
  bell();
  bell();

  if (currutmp->msgcount) {
     char buf[200];
     time_t now = time(0);

     sprintf(buf, "[33;41m��%s[34;47m [%s] %s [0m",
        (currutmp->destuip)->userid,  my_ctime(&now),
        (currutmp->sig == 2) ? "���n�����s���I(��Ctrl-U,l�d�ݼ��T�O��)" : "�I�s�B�I�s�Ať��Ц^��");
     move(0, 0);
     clrtoeol();
     outs(buf);
     refresh();
  }
  else
     scr_exec(talkreply);
}


show_last_call_in()
{
   char buf[200];
/* 2003/08/30 by Terry */
   int i;
   
   i = (currutmp->msgstart + currutmp->msgnum - currutmp->msgcount) % MAXMSGS;
   sprintf(buf, "[1;33;46m��%s[37;45m %s [0m",
           currutmp->msgs[i].last_userid, currutmp->msgs[i].last_call_in);
           
   /* �o�@��O�ΨӸѨM outs �@�}�l�N�O ANSI ����X�ɵL�k���T��Ķ�����D, by MH */
   my_outmsg(" ");
/*		       */
   my_outmsg(buf);
}


/* 2003/08/30 by Terry */
mh_show_call_in(amsg)
  msgque amsg;
{
  char buf[200];
  
  sprintf(buf, "[1;33;46m��%s[37;45m %s [0m", amsg.last_userid, amsg.last_call_in);
  
  /* �o�@��O�ΨӸѨM outs �@�}�l�N�O ANSI ����X�ɵL�k���T��Ķ�����D, by MH */
  my_outmsg(" ");
  my_outmsg(buf);
}
/*		       */


static void
write_request()
{
  FILE *fp;
  int ch;
  char fpath[80];
/*struct stat st;*/
  struct tm *ptime;
  time_t now;


/*
Half-hour remind
*/
  if (*currmsg) {
     my_outmsg(currmsg);
     bell();
     *currmsg = 0;
     return;
  }

  time(&now);
  ptime = localtime(&now);

#ifdef  LINUX
  signal(SIGUSR2, write_request);
#endif


/* MH */
/* 2003/08/30 by Terry */
  if (currutmp->pager && cuser.userlevel && currutmp->msgcount
      && currutmp->mode != TALK && currutmp->mode != CHATING
      && currutmp->mode != PAGE && currutmp->mode != IDLE
      && currutmp->mode != MAILALL && currutmp->mode != MONITOR)
  {
    int i;
    char c0 = currutmp->chatid[0];
    int currstat0 = currstat;
    uschar mode0 = currutmp->mode;
    
    currutmp->mode = 0;
    currutmp->chatid[0] = 2;
    currstat = XMODE;
      
    do
    {
      msgque amsg;
      int msgstart, msgnum, msgcount;
      
      bell();
      msgstart = currutmp->msgstart;
      msgnum = currutmp->msgnum;
      msgcount = currutmp->msgcount;
      amsg = currutmp->msgs[(msgstart + msgnum - msgcount) % MAXMSGS];
    /*show_last_call_in();*/
      mh_show_call_in(amsg);
/*
      ch = igetch();
        
      if (ch == Ctrl('R'))
      {
	char buf[100] = "";
	
	if (getdata(b_lines, 0, "�i�c! ��^�h�G", buf + 1, 65, DOECHO, 0))
	  my_write(currutmp->msgs[0].last_pid, buf);
	else
	  my_outmsg("[1;33;42m��F! ����A�p��...[m");
      }
      
      if (ch == Ctrl('R'))
      {
	char buf[100] = "";
	
	if (getdata(b_lines, 0, "�i�c! ��^�h�G", buf + 1, 65, DOECHO, 0))
	  my_write(currutmp->msgs[0].last_pid, buf);
	else
	  my_outmsg("[1;33;42m��F! ����A�p��...[m");
      }
*/

      currutmp->msgcount--;
	
    /*for (i = 0; i < currutmp->msgcount; i++)
        currutmp->msgs[i] = currutmp->msgs[i + 1];*/
    } while (currutmp->msgcount);
    
    currutmp->chatid[0] = c0;
    currutmp->mode = mode0;
    currstat = currstat0;
  }
  else
  {
    bell();
    show_last_call_in();
    currutmp->msgcount = 0;
  }
/*		       */
}


/* ----------------------------------------------------- */
/* BBS child process �D�{��                              */
/* ----------------------------------------------------- */


/* start_client() �N�O main.c �� main()�A�����ٲ� */


static void
start_client()
{
  extern struct commands cmdlist[];

  currmode = 0;
  login_start_time = time(0);

  (void) signal(SIGHUP, abort_bbs);
  (void) signal(SIGBUS, abort_bbs);
  (void) signal(SIGSEGV, abort_bbs);
  (void) signal(SIGSYS, abort_bbs);
  (void) signal(SIGTERM, abort_bbs);

  (void) signal(SIGUSR1, talk_request);
  (void) signal(SIGUSR2, write_request);

  if (setjmp(byebye))
    abort_bbs();

  dup2(0, 1);
  login_query();
  user_login();

  if (HAVE_PERM(PERM_SYSOP | PERM_BM))
    b_closepolls();

  if (!(cuser.uflag & COLOR_FLAG))
    showansi = 0;

#ifdef DOTIMEOUT
  (void) init_alarm();
#else
  (void) signal(SIGALRM, SIG_IGN);
#endif

  if (HAS_PERM(PERM_ACCOUNTS) && belong("etc/sysop", cuser.userid)
      && dashf(fn_register)
      || belong("etc/ugly", cuser.userid) && HAS_PERM(PERM_BM)) /* for ugly old liu */
     m_register();
  (void) domenu(MMENU, "�D�\\���", (chkmail(0) ? 'M' : 'C'), cmdlist);
}


/* ----------------------------------------------------- */
/* FSA (finite state automata) for telnet protocol       */
/* ----------------------------------------------------- */


static void
telnet_init()
{
  static char svr[] = {
    IAC, DO, TELOPT_TTYPE,
    IAC, SB, TELOPT_TTYPE, TELQUAL_SEND, IAC, SE,
    IAC, WILL, TELOPT_ECHO,
    IAC, WILL, TELOPT_SGA
  };

  register int n, len;
  register char *cmd, *data;
  int rset, oset;
  struct timeval to;
  char buf[256];

  data = buf;
  sprintf(data, BANNER, genbuf);
  write(0, data, strlen(data));

  to.tv_sec = 1;
  rset = to.tv_usec = 0;
  FD_SET(0, (fd_set *) & rset);
  oset = rset;

  for (n = 0, cmd = svr; n < 4; n++)
  {
    len = (n == 1 ? 6 : 3);
    write(0, cmd, len);
    cmd += len;

    if (select(1, (fd_set *) & rset, NULL, NULL, &to) > 0)
    {
      read(0, data, sizeof(buf));
    }
    rset = oset;
  }
}


/* ----------------------------------------------- */
/* ���o remote user name �H�P�w����                */
/* ----------------------------------------------- */


/*
 * rfc931() speaks a common subset of the RFC 931, AUTH, TAP, IDENT and RFC
 * 1413 protocols. It queries an RFC 931 etc. compatible daemon on a remote
 * host to look up the owner of a connection. The information should not be
 * used for authentication purposes. This routine intercepts alarm signals.
 *
 * Author: Wietse Venema, Eindhoven University of Technology, The Netherlands.
 */

#include <setjmp.h>

#define STRN_CPY(d,s,l) { strncpy((d),(s),(l)); (d)[(l)-1] = 0; }
#define RFC931_TIMEOUT   10
#define RFC931_PORT     113     /* Semi-well-known port */
#define ANY_PORT        0       /* Any old port will do */


/* ------------------------- */
/* timeout - handle timeouts */
/* ------------------------- */


static void
timeout(sig)
  int sig;
{
  (void) longjmp(byebye, sig);
}


static void
getremotename(from, rhost, rname)
  struct sockaddr_in *from;
  char *rhost;
  char *rname;
{
  struct sockaddr_in our_sin;
  struct sockaddr_in rmt_sin;
  unsigned rmt_port, rmt_pt;
  unsigned our_port, our_pt;
  FILE *fp;
  char buffer[512], user[80], *cp;
  int s;
  struct hostent *hp;

  /* get remote host name */

  hp = NULL;
  if (setjmp(byebye) == 0)
  {
    (void) signal(SIGALRM, timeout);
    (void) alarm(3);
    hp = gethostbyaddr((char *) &from->sin_addr, sizeof(struct in_addr),
      from->sin_family);
    (void) alarm(0);
  }
  (void) strcpy(rhost, hp ? hp->h_name : (char *) inet_ntoa(from->sin_addr));

  /*
   * Use one unbuffered stdio stream for writing to and for reading from the
   * RFC931 etc. server. This is done because of a bug in the SunOS 4.1.x
   * stdio library. The bug may live in other stdio implementations, too.
   * When we use a single, buffered, bidirectional stdio stream ("r+" or "w+"
   * mode) we read our own output. Such behaviour would make sense with
   * resources that support random-access operations, but not with sockets.
   */

/*
woju
  *rname = '\0';
*/

  s = sizeof our_sin;
  if (getsockname(0, (struct sockaddr*)&our_sin, &s) < 0)
    return;

  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    return;
  }

  if (!(fp = fdopen(s, "r+")))
  {
    (void) close(s);
    return;
  }

  /*
   * Set up a timer so we won't get stuck while waiting for the server.
   */

  if (setjmp(byebye) == 0)
  {
    (void) signal(SIGALRM, timeout);
    (void) alarm(RFC931_TIMEOUT);

    /*
     * Bind the local and remote ends of the query socket to the same IP
     * addresses as the connection under investigation. We go through all
     * this trouble because the local or remote system might have more than
     * one network address. The RFC931 etc. client sends only port numbers;
     * the server takes the IP addresses from the query socket.
     */

    our_pt = ntohs(our_sin.sin_port);
    our_sin.sin_port = htons(ANY_PORT);

    rmt_sin = *from;
    rmt_pt = ntohs(rmt_sin.sin_port);
    rmt_sin.sin_port = htons(RFC931_PORT);

    (void) setbuf(fp, (char *) 0);
    s = fileno(fp);

    if (bind(s, (struct sockaddr *) & our_sin, sizeof(our_sin)) >= 0 &&
      connect(s, (struct sockaddr *) & rmt_sin, sizeof(rmt_sin)) >= 0)
    {
      /*
       * Send query to server. Neglect the risk that a 13-byte write would
       * have to be fragmented by the local system and cause trouble with
       * buggy System V stdio libraries.
       */

      (void) fprintf(fp, "%u,%u\r\n", rmt_pt, our_pt);
      (void) fflush(fp);

      /*
       * Read response from server. Use fgets()/sscanf() so we can work
       * around System V stdio libraries that incorrectly assume EOF when a
       * read from a socket returns less than requested.
       */

      if (fgets(buffer, sizeof(buffer), fp) && !ferror(fp) && !feof(fp)
        && sscanf(buffer, "%u , %u : USERID :%*[^:]:%79s",
          &rmt_port, &our_port, user) == 3
        && rmt_pt == rmt_port && our_pt == our_port)
      {

        /*
         * Strip trailing carriage return. It is part of the protocol, not
         * part of the data.
         */

        if (cp = (char *) strchr(user, '\r'))
          *cp = 0;
        strcpy(rname, user);
      }
    }
    (void) alarm(0);
  }
  (void) fclose(fp);
}


/* ----------------------------------- */
/* check system / memory / CPU loading */
/* ----------------------------------- */


#ifdef  HAVE_CHKLOAD
int fkmem;

static void
chkload_init()
{
#include <nlist.h>
#define VMUNIX  "/vmunix"
#define KMEM    "/dev/kmem"

  static struct nlist nlst[] = {
    {"_avenrun"},
    {0}
  };
  register int kmem;
  long offset;

  (void) nlist(VMUNIX, nlst);
  if (nlst[0].n_type == 0)
    exit(1);
  offset = (long) nlst[0].n_value;

  if ((kmem = open(KMEM, O_RDONLY)) == -1)
    exit(1);

  if (lseek(kmem, offset, L_SET) == -1)
    exit(1);

  fkmem = kmem;
}


static int
chkload(limit)
  int limit;
{
  double cpu_load[3];
  long avenrun[3];
  register int i;

  i = fkmem;

  if (read(i, (char *) avenrun, sizeof(avenrun)) == -1)
    exit(1);

  lseek(i, -(off_t) sizeof(avenrun), SEEK_CUR);

#define loaddouble(la) ((double)(la) / (1 << 8))

  for (i = 0; i < 3; i++)
    cpu_load[i] = loaddouble(avenrun[i]);

  memcpy(utmpshm->sysload, cpu_load, sizeof(cpu_load));

  i = cpu_load[0] + cpu_load[1] * 4;
  if (i < limit)
    i = 0;
  sprintf(genbuf, "�t�έt�� %.2f %.2f %.2f%s",
    cpu_load[0], cpu_load[1], cpu_load[2],
    (i ? "�A�еy��A��\n" : ""));

  return i >> 3;
}
#endif


/* ----------------------------------------------------- */
/* stand-alone daemon                                    */
/* ----------------------------------------------------- */


static int mainset;             /* read file descriptor set */
static struct sockaddr_in xsin;


static void
reapchild()
{
  int state, pid;

  while ((pid = waitpid(-1, &state, WNOHANG | WUNTRACED)) > 0);
}


static void
start_daemon()
{
  int n;
  char buf[80];

  /*
   * More idiot speed-hacking --- the first time conversion makes the C
   * library open the files containing the locale definition and time zone.
   * If this hasn't happened in the parent process, it happens in the
   * children, once per connection --- and it does add up.
   */
   
/* 2003/08/30 by Terry */
  time_t dummy;
  struct tm *dummy_time;
  struct tm *other_dummy_time;
  
  dummy = time(NULL) + 8 * 60 * 60;
  dummy_time = localtime(&dummy);
  other_dummy_time = gmtime(&dummy);
/*		       */

  (void) strftime(buf, 80, "%d/%b/%Y:%H:%M:%S", dummy_time);
/*
  (void) gethostname(myhostname, sizeof(myhostname));
*/

  n = getdtablesize();
  if (fork())
    exit(0);

  sprintf(genbuf, "%d\t%s", getpid(), buf);

  while (n)
    (void) close(--n);

  n = open("/dev/tty", O_RDWR);
  if (n > 0)
  {
    (void) ioctl(n, TIOCNOTTY, (char *) 0);
    (void) close(n);
  }

  for (n = 1; n < NSIG; n++)
    (void) signal(n, SIG_IGN);
}


static void
close_daemon()
{
  exit(0);
}


static int
bind_port(port)
  int port;
{
  int sock, on;

  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  on = 1;
  (void) setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
  (void) setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char *) &on, sizeof(on));

  on = 0;
  (void) setsockopt(sock, SOL_SOCKET, SO_LINGER, (char *) &on, sizeof(on));

  xsin.sin_port = htons(port);
  if (bind(sock, (struct sockaddr *)&xsin, sizeof xsin) < 0) {
    syslog(LOG_INFO, "bbsd bind_port can't bind to %d",port);
    exit(1);
  }

  if (listen(sock, SOCKET_QLEN) < 0) {
    syslog(LOG_INFO, "bbsd bind_port can't listen to %d",port);
    exit(1);
  }

  (void) FD_SET(sock, (fd_set *) & mainset);
  return sock;
}


/*
woju
*/
add_distinct(char* fname, char* line)
{
   FILE *fp;
   int n = 0;

   if (fp = fopen(fname, "a+")) {
      char buffer[80];
      char tmpname[100];
      FILE *fptmp;

      strcpy(tmpname, fname);
      strcat(tmpname, "_tmp");
      if (!(fptmp = fopen(tmpname, "w"))) {
         fclose(fp);
         return;
      }

      rewind(fp);
      while (fgets(buffer, 80, fp)) {
         char* p = buffer + strlen(buffer) - 1;

         if (p[-1] == '\n' || p[-1] == '\r')
            p[-1] = 0;
         if (!strcmp(buffer, line))
            break;
         sscanf(buffer + strlen(buffer) + 2, "%d", &n);
         fprintf(fptmp, "%s%c#%d\n", buffer, 0, n);
      }

      if (feof(fp))
         fprintf(fptmp, "%s%c#1\n", line, 0);
      else {
         sscanf(buffer + strlen(buffer) + 2, "%d", &n);
         fprintf(fptmp, "%s%c#%d\n", buffer, 0, n + 1);
         while (fgets(buffer, 80, fp)) {
            sscanf(buffer + strlen(buffer) + 2, "%d", &n);
            fprintf(fptmp, "%s%c#%d\n", buffer, 0, n);
         }
      }
      fclose(fp);
      fclose(fptmp);
      unlink(fname);
      rename(tmpname, fname);
   }
}


del_distinct(char* fname, char* line)
{
   FILE *fp;
   int n = 0;

   if (fp = fopen(fname, "r")) {
      char buffer[80];
      char tmpname[100];
      FILE *fptmp;

      strcpy(tmpname, fname);
      strcat(tmpname, "_tmp");
      if (!(fptmp = fopen(tmpname, "w"))) {
         fclose(fp);
         return;
      }

      rewind(fp);
      while (fgets(buffer, 80, fp)) {
         char* p = buffer + strlen(buffer) - 1;

         if (p[-1] == '\n' || p[-1] == '\r')
            p[-1] = 0;
         if (!strcmp(buffer, line))
            break;
         sscanf(buffer + strlen(buffer) + 2, "%d", &n);
         fprintf(fptmp, "%s%c#%d\n", buffer, 0, n);
      }

      if (!feof(fp))
         while (fgets(buffer, 80, fp)) {
            sscanf(buffer + strlen(buffer) + 2, "%d", &n);
            fprintf(fptmp, "%s%c#%d\n", buffer, 0, n);
         }
      fclose(fp);
      fclose(fptmp);
      unlink(fname);
      rename(tmpname, fname);
   }
}


bad_host(char* name)
{
   FILE* list;
   char buf[40];

  if (list = fopen("etc/bad_host", "r")) {
     while (fgets(buf, 40, list)) {
        buf[strlen(buf) - 1] = '\0';
        if (!strcmp(buf, name))
           return 1;
        if (buf[strlen(buf) - 1] == '.' && !strncmp(buf, name, strlen(buf)))
           return 1;
        if (*buf == '.' && strlen(buf) < strlen(name) &&
            !strcmp(buf, name + strlen(name) - strlen(buf)))
           return 1;
     }
     fclose(list);
  }
  return 0;
}


main(argc, argv)
  int argc;
  char *argv[];
{
  extern int errno;

  register int msock, csock;    /* socket for Master and Child */
  register int nfds;            /* number of sockets */
  register int th_low, th_high, overload;
  register int *totaluser;
  register pid_t pid;
  register time_t uptime;
  int readset;
  int value;
  struct timeval tv;

  Argc = argc;
  Argv = argv;

  /* --------------------------------------------------- */
  /* setup standalone                                    */
  /* --------------------------------------------------- */

  start_daemon();

  (void) signal(SIGCHLD, reapchild);
  (void) signal(SIGTERM, close_daemon);


  /* --------------------------------------------------- */
  /* port binding                                        */
  /* --------------------------------------------------- */

  xsin.sin_family = AF_INET;

  if (argc > 1)
  {
    msock = -1;
    for (nfds = 1; nfds < argc; nfds++)
    {
      csock = atoi(argv[nfds]);
      if (csock > 0)
         msock = bind_port(csock);
      else
         break;
    }
    if (msock < 0)
      exit(1);
  }
  else
  {
/* 2004/07/04 by Terry */
    static int ports[] = {23, 3456};
/*		       */

    for (nfds = 0; nfds < sizeof(ports) / sizeof(int); nfds++)
    {
      csock = ports[nfds];
      msock = bind_port(csock);

      sprintf(genbuf + 512, "\t%d", csock);
      strcat(genbuf, genbuf + 512);
    }
  }
  nfds = msock + 1;

  /* --------------------------------------------------- */
  /* Give up root privileges: no way back from here      */
  /* --------------------------------------------------- */

  (void) setgid(BBSGID);
  (void) setuid(BBSUID);
  (void) chdir(BBSHOME);

  strcat(genbuf, "\n");
  file_append(PID_FILE, genbuf);

  /* --------------------------------------------------- */
  /* main loop                                           */
  /* --------------------------------------------------- */


/*
  th_low = (argc > 1) ? atoi(argv[1]) : TH_LOW;
  th_high = (argc > 2) ? atoi(argv[2]) : TH_HIGH;
*/

  resolve_utmp();
  totaluser = &utmpshm->number;

#ifdef  HAVE_CHKLOAD
  chkload_init();
#endif

  tv.tv_sec = 60 * 30;
  tv.tv_usec = 0;

  overload = uptime = 0;

  for (;;)
  {

#ifdef  HAVE_CHKLOAD
    pid = time(0);
    if (pid > uptime)
    {
      overload = chkload(overload ? th_low : th_high);
      uptime = pid + overload + 45;     /* �u�ɶ������A�ˬd system load */
    }
#endif

again:

    readset = mainset;
    msock = select(nfds, (fd_set *) & readset, NULL, NULL, &tv);

    if (msock < 0)
    {
      goto again;
    }
    else if (msock == 0)        /* No network traffic */
      continue;

    msock = 0;
    csock = 1;
    for (;;)
    {
      if (csock & readset)
        break;
      if (++msock >= nfds)
        goto again;
      csock <<= 1;
    }

    value = sizeof xsin;
    do
    {
      csock = accept(msock, (struct sockaddr *)&xsin, &value);
    } while (csock < 0 && errno == EINTR);

    if (csock < 0)
    {
      goto again;
    }

#ifdef  HAVE_CHKLOAD
    if (overload)
    {
      (void) write(csock, genbuf, strlen(genbuf));
      (void) close(csock);
      continue;
    }
#endif

    pid = *totaluser;
    if (pid >= MAXACTIVE)
    {
      char buf[128];

      (void) sprintf(buf, "�ثe�u�W�H�� [%d] �H�A�Ⱥ��F�A�еy��A��", pid);
      (void) write(csock, buf, strlen(buf));
      (void) close(csock);
      goto again;
    }

    pid = fork();

    if (!pid)
    {

#ifdef  HAVE_CHKLOAD
      (void) close(fkmem);
#endif

/* 2003/08/30 by Terry */
#ifdef USE_STOPLOGIN
      FILE *fp;
      int a;
      char buf[256];
      
      if ((fp = fopen(FN_STOPLOGIN, "r")) != NULL)
      {
	while (fgets(buf, 256, fp) != NULL)
	{
	  a = strlen(buf);
	  
	  if (a < 256)
	  {
	    buf[a] = 13;
	    buf[a + 1] = '\0';
	  }
	  
	  write(csock, buf, strlen(buf));
	}
	
	fclose(fp);
	sleep(3);
	exit(0);
      }
#endif
/*		       */

      while (--nfds >= 0)
        (void) close(nfds);
      (void) dup2(csock, 0);
      (void) close(csock);

      getremotename(&xsin, fromhost, remoteusername);   /* FC931 */

      /* ban �� bad host / bad user */
      if (bad_host(fromhost) && !strcmp(remoteusername, "?"))
         exit(1);

      setenv("REMOTEHOST", fromhost, 1);
      setenv("REMOTEUSERNAME", remoteusername, 1);
      {
        char RFC931[80];
        sprintf(RFC931, "%s@%s", remoteusername, fromhost);
        setenv("RFC931", RFC931, 1);
      }

      telnet_init();
      start_client();
    }

    (void) close(csock);
  }
}
