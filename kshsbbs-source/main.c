/*-------------------------------------------------------*/
/* main.c       ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* author : opus.bbs@bbs.cs.nthu.edu.tw                  */
/* target : BBS main/login/top-menu routines             */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#define _MAIN_C_


#include "bbs.h"

jmp_buf byebye;

static uschar enter_uflag;

#ifdef SHOW_IDLE_TIME
char fromhost[STRLEN - 20] = "\0";
char tty_name[20] = "\0";
#else
char fromhost[STRLEN] = "\0";
#endif

char remoteusername[40];
int mbbsd = 0;

void check_register();
int Argc;
char** Argv;

/* ----------------------------------------------------- */
/* 離開 BBS 程式                                         */
/* ----------------------------------------------------- */

void
log_usies(mode, mesg)
  char *mode, *mesg;
{
  FILE *fp;
  char genbuf[200];

  if (fp = fopen(FN_USIES, "a+"))
  {
    time_t now = time(0);

    if (!mesg)
    {
      sprintf(genbuf, "Stay: %d (%s)",
        (now - login_start_time) / 60, cuser.username);
      mesg = genbuf;
    }

    fprintf(fp, cuser.userid[0] ? "%s %s %-12s %s\n" : "%s %s %s%s\n",
      Cdate(&now), mode, cuser.userid, mesg);
    fclose(fp);
  }
}


static void
setflags(mask, value)
  int mask, value;
{
  if (value)
    cuser.uflag |= mask;
  else
    cuser.uflag &= ~mask;
}


void
u_exit(mode)
  char *mode;
{
  extern void auto_backup();    /* 編輯器自動備份 */
  userec xuser;
  char genbuf[80], fpath[80];
/* Leeym */
/* 上站時間少於一分鐘不計上站次數 */
  int diff = (time(0) - login_start_time) / 60;
/*       */

  if (currmode & MODE_SELECT){
     sprintf(fpath, "SR.%s", cuser.userid);
     if(currstat==RMAIL)
     {
     setuserfile(genbuf, fpath);
     unlink(genbuf);
     }
     else{
     setbfile(genbuf, currboard, fpath);
     unlink(genbuf);
     }
  }

  get_record(fn_passwd, &xuser, sizeof(xuser), usernum);

  auto_backup();

  setflags(PAGER_FLAG, currutmp->pager != 1);
  if (HAS_PERM(PERM_LOGINCLOAK))
    setflags(CLOAK_FLAG, currutmp->invisible);
  purge_utmp(currutmp);

  if ((cuser.uflag != enter_uflag) || (currmode & MODE_DIRTY) || (diff < 1)) {
    xuser.uflag = cuser.uflag;
    xuser.numposts = cuser.numposts;
/* Leeym */
/* 上站時間少於一分鐘不計上站次數 */
    if(diff < 1 && cuser.numlogins)
      xuser.numlogins = -- cuser.numlogins;
/*       */
    substitute_record(fn_passwd, &xuser, sizeof(userec), usernum);
  }
  log_usies(mode, NULL);
}


void
system_abort()
{
  if (currmode)
    u_exit("ABORT");

  clear();
  refresh();
  printf("謝謝光臨, 記得常來喔 !\n");
  sleep(1);
  exit(0);
}


void
abort_bbs(int signo)  /* MH */
{
/*
  kill(xyzpid, SIGHUP);
*/
  kill(0, SIGHUP);
  signal(SIGALRM, SIG_IGN);  /* MH: 預防又遇到SIGALRM */
  switch(signo)
  {
    case SIGHUP:
      log_usies("MH ", "SIGHUP");
      break;
    case SIGBUS:
      log_usies("MH ", "SIGBUS");
      break;
    case SIGSEGV:
      log_usies("MH ", "SIGSEGV");
#ifdef MH_LET_SEGV
      /* 記錄之後把SEGV的處理函式式設回預設, 然後再丟一個SEGV給自己 */
      signal(SIGSEGV, SIG_DFL);
      kill(getpid(), SIGSEGV);
      return;
#endif
      break;
    case SIGSYS:
      log_usies("MH ", "SIGSYS");
      break;
    default:
      {
        char buf[100];
        
        sprintf(buf, "SIG: %d", signo);
        log_usies("MH ", buf);
      }
      break;
  }
#if 1
  if(currmode && (currutmp != NULL || signo != SIGSEGV))
    u_exit("AXXED");
#else
#if 1
  if(currutmp != NULL && currmode)
    u_exit("AXXED");
#else
  if ((signo != SIGSEGV || currutmp != NULL) &&
      currmode)
      /* MH: 若是currutmp == NULL造成SEGV的話就不要再u_exit */
    u_exit("AXXED");
#endif
#endif
  exit(0);
}

void
leave_bbs()
{
   reset_tty();
}


/* ----------------------------------------------------- */
/* 登錄 BBS 程式                                         */
/* ----------------------------------------------------- */


int
dosearchuser(userid)
  char *userid;
{
  if (usernum = getuser(userid))
    memcpy(&cuser, &xuser, sizeof(cuser));
  else
    memset(&cuser, 0, sizeof(cuser));
  return usernum;
}


static void
talk_request()
{
#ifdef  LINUX
  /*
   * Linux 下連續 page 對方兩次就可以把對方踢出去： 這是由於某些系統一 nal
   * 進來就會將 signal handler 設定為內定的 handler, 不幸的是 default 是將程
   * erminate. 解決方法是每次 signal 進來就重設 signal handler
   */

  signal(SIGUSR1, talk_request);
#endif
  bell();
  bell();

  if (currutmp->msgcount) {
     char buf[200];
     time_t now = time(0);

     sprintf(buf, "[33;41m★%s[34;47m [%s] %s [0m",
        (currutmp->destuip)->userid,  my_ctime(&now),
        (currutmp->sig == 2) ? "重要消息廣播！(請Ctrl-U,l查看熱訊記錄)" : "呼叫、呼叫，聽到請回答");
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
   int i;

   /* MH */
   i = (currutmp->msgstart + currutmp->msgnum - currutmp->msgcount) % MAXMSGS;
   sprintf(buf, "[1;33;46m★%s[37;45m %s [0m",
      currutmp->msgs[i].last_userid,
      currutmp->msgs[i].last_call_in);
   /* 這一行是用來解決 outs 一開始就是 ANSI 控制碼時無法正確解譯的問題 */
   my_outmsg(" ");
   my_outmsg(buf);
}

mh_show_call_in(msgque amsg)
{
   char buf[200];

   sprintf(buf, "[1;33;46m★%s[37;45m %s [0m",
      amsg.last_userid,
      amsg.last_call_in);
   /* 這一行是用來解決 outs 一開始就是 ANSI 控制碼時無法正確解譯的問題 */
   my_outmsg(" ");
   my_outmsg(buf);
}

extern screenline* big_picture;

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
/*         show_last_call_in();*/
         mh_show_call_in(amsg);
#if 0
         ch = igetch();
         if (ch == Ctrl('R'))
         {
/*           mh_throw_water_ball();*/
            char buf[100] = "";
            int r;
#if 0

            currstat = ROWB;
            if ((r = getdata(b_lines, 0, "可惡! 丟回去：", buf + 1, 65, DOECHO, 0)) > 0)
            {
              r = my_write(amsg.last_pid, buf);              
              if(currutmp->msgs[(msgstart + msgnum - msgcount) % MAXMSGS].last_pid == amsg.last_pid
                 && strcmp(currutmp->msgs[(msgstart + msgnum - msgcount) % MAXMSGS].last_call_in, amsg.last_call_in) == 0)
              /* 這個水球記錄還在 */
              {
                currutmp->msgs[(msgstart + msgnum - msgcount) % MAXMSGS].replied = YEA;
              }
            }
#define NEW_STYLE_REPLY
#ifdef NEW_STYLE_REPLY
            else if(r == MH_CTRLR)
            {
              screenline* screen0 = calloc(t_lines, sizeof(screenline));
              int y, x;

              memcpy(screen0, big_picture, t_lines * sizeof(screenline));
              getyx(&y, &x);
              r = mh_throw_water_ball();
              move(y, x);
              memcpy(big_picture, screen0, t_lines * sizeof(screenline));
              free(screen0);
              redoscr();
            }
#endif
#else
            {
              screenline* screen0 = calloc(t_lines, sizeof(screenline));
              int y, x;

              memcpy(screen0, big_picture, t_lines * sizeof(screenline));
              getyx(&y, &x);
              r = mh_throw_water_ball();
              move(y, x);
              memcpy(big_picture, screen0, t_lines * sizeof(screenline));
              free(screen0);
              redoscr();
            }
#endif
            if(currutmp->msgcount <= 1 && r == 0)
            {
/*               my_outmsg(" ");
               my_outmsg("[1;33;42m算了! 不跟你計較...[m");*/
            }
/*            if(currutmp->msgcount > 1)
               my_outmsg("                                                                               ");*/
            currstat = XMODE;
         }
#endif
         currutmp->msgcount --;
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
/*    */
}


static void
multi_user_check()
{
  register user_info *ui;
  register pid_t pid;
  int cmpuids();
  char genbuf[3];

#if 0  /* MH */ /* 好功能大家用...反正預設是'n' */
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

    getdata(0, 0, "您想將其他重複的 login 踢下站嗎？(Y/n) ", genbuf, 3, LCECHO, 0); 

    if (genbuf[0] != 'n') 
    {
      kill(pid, SIGHUP);
      log_usies("KICK ", cuser.username);
    }
    else
    {
      if (count_multi() >= 2 && !(HAS_PERM(PERM_SYSOP) || HAS_PERM(PERM_BM)))
        system_abort();         /* Goodbye(); */
    }
  }
  else
  {
    extern struct UTMPFILE *utmpshm;
    
    /* allow multiple guest user */
    if (count_multi() > 16 ||
        /* MH: 尖峰時間停止guest login */
        utmpshm->number >= (MAXACTIVE - 50))
    {
      outs("\n抱歉，目前已有太多 guest, 請稍後再試。\n");
      pressanykey();
      oflush();
      exit(1);
    }
  }
}

/* --------- */
/* bad login */
/* --------- */

static char str_badlogin[] = "logins.bad";


static void
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

show_hint_message()
{
        struct timeval  timep;
        struct timezone timezp;
        int     i, j, msgNum;
        FILE    *hintp;
        char    msg[200];
        /* Tzu */
        /*char    *bureau[6] = {"教務處","教官室","訓導處","總務處","輔導中心","衛生組"};
        int     tzu = rand() % 6;*/
        /*     */

        if (!(hintp = fopen("etc/hint", "r")))
          return 0;
        fgets(msg, 200, hintp);
        msgNum = atoi(msg);
        gettimeofday(&timep, &timezp);
        i = (int) timep.tv_sec%(msgNum + 1); /* 最新的一篇機會加倍 */
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
        /*prints("擴音器傳來下課的鐘聲 %s報告：\n", bureau[tzu]);*/
        /*     */
        prints("                   %s[0m", msg);
        fgets(msg, 200, hintp);
        prints("                   %s[0m", msg);
        fclose(hintp);
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

static void
login_query()
{
  char uid[IDLEN + 1], passbuf[PASSLEN];
  int attempts;
  char genbuf[200];
  extern struct UTMPFILE *utmpshm;
  
/* by Excalibur(大魔王) is84006@cis.nctu.edu.tw
   避免hacker開一堆窗停在登入畫面佔資源 */
/*  signal(SIGALRM, abort_bbs);  */

  resolve_utmp();
  attempts = utmpshm->number;
/* Tzu */

  
  /* Tzu: 提早開始處理畫面 */


  prints("\n歡迎光臨【[1;37;41m %s [0m】  站內人數【 [1;33;44m%d / %d[m 】\n\n", BoardName, attempts, MAXACTIVE);  
  
/*     */
#ifndef MH_DONT_CHECK_MAXACTIVE
/* 2003/08/30 by Terry */
  if (attempts >= (MAXACTIVE - 100))
  {
    outs("in.zbbsd 已滿，請改連 port 3456\n");
/*		       */
    oflush();
    sleep(10);
    exit(1);
  }
#endif

  /* hint */
  /*show_hint_message();
  
    Tzu: disable 20010418*/
    
  more("etc/banner", NA);
  


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

    getdata(17, 10, "\n請輸入代號，或以[guest]參觀，以[new]註冊：",
      uid, IDLEN + 1, DOECHO, 0);
    if (ci_strcmp(uid, str_new) == 0)
    {

#ifdef LOGINASNEW
      new_register();
      break;
#else
      outs("本系統目前無法以 new 註冊, 請用 guest 進入\n");
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

#ifdef NOPASSWD
      log_usies("MH ", "nopasswd @_@");
      strcpy(genbuf, "MichaelHsin");
      dosearchuser(genbuf);
      strcpy(genbuf, cuser.passwd);
      dosearchuser(uid);
      if(!checkpasswd(genbuf, passbuf))
#else
      if (!checkpasswd(cuser.passwd, passbuf))
#endif
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
           outs("站長請由 trusted host 進入");
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
  if(strcmp(uid, "guest") && !belong("etc/anonymous", uid) && ci_strcmp(uid, str_new) != 0)
    dosearchuser(uid);
  /*    */
/*
  if (!term_init(cuser.termtype))
  {
    outs("終端機型態錯誤！預設為 [vt100]\n");
    term_init("vt100");
  }
*/
  if (!term_init("vt100"))
  {
    do
    {
      getdata(0, 0, "\n終端機型態錯誤！請輸入：", genbuf, 8, DOECHO, "vt100");
    } while (!term_init(genbuf));
  }  

  sethomepath(genbuf, cuser.userid);
  mkdir(genbuf, 0755);
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

void
setup_utmp(mode)
  int mode;
{
  user_info uinfo;
  char buf[80];
  FILE *fp;
  char mhbuf1[80];
  int mhtmp1;

  memset(&uinfo, 0, sizeof(uinfo));
  uinfo.pid = currpid = getpid();
  uinfo.uid = usernum;
  uinfo.mode = currstat = mode;
  uinfo.msgcount = 0;
  uinfo.msgnum = 0;
  uinfo.msgstart = 0;
  uinfo.userlevel = cuser.userlevel;
  uinfo.uptime = time(0);

  strcpy(uinfo.userid, cuser.userid);
  strcpy(uinfo.realname, cuser.realname);
  strcpy(uinfo.username, cuser.username);
  strncpy(uinfo.from, fromhost, 28);

  setuserfile(buf, "remoteuser");

#ifdef MH_DAMN_DEBUG
  kill(getpid(), SIGHUP);
#endif

  add_distinct(buf, getenv("RFC931"));

#ifdef SHOW_IDLE_TIME
  strcpy(uinfo.tty, tty_name);
#endif

/* MH */

#if 0
/* read mailmsg file ".mailmsgrc" */
  setuserfile(buf, ".mailmsgrc");
  if(((fp = fopen(buf, "r")) == NULL) || (fgets(mhbuf1, 79, fp) == NULL))
  {
    char mhbuf1[80];
    int mhtmp1;

    log_usies("MAILMSGRC", ".mailmsgrc doesn't exist");
    log_usies("MAILMSGRC", "that's ok");
    uinfo.mailmsg_type = MAILMSG_TYPE_SEX;
    uinfo.mailmsg_num = mailmsg_num[cuser.sex];
    uinfo.mailmsg[0] = '\0';
  }
  else
  {
    switch(mhbuf1[0])
    {
      case MAILMSG_TYPE_USERDEFINE:
        uinfo.mailmsg_type = MAILMSG_TYPE_USERDEFINE;
        uinfo.mailmsg_num = mailmsg_num[cuser.sex];
        break;
      case MAILMSG_TYPE_SELECT:
        mhtmp1 = atoi(mhbuf1 + 1);
        if(mhtmp1 >= MAX_MAILMSGS)
          mhtmp1 = mailmsg_num[cuser.sex];
        uinfo.mailmsg_type = MAILMSG_TYPE_SELECT;
        uinfo.mailmsg_num = mhtmp1;
        break;
      case MAILMSG_TYPE_RANDOM:
        uinfo.mailmsg_type = MAILMSG_TYPE_RANDOM;
        uinfo.mailmsg_num = random() % MAX_MAILMSGS;
        break;
      default:
      case MAILMSG_TYPE_SEX:
        uinfo.mailmsg_type = MAILMSG_TYPE_SEX;
        uinfo.mailmsg_num = mailmsg_num[cuser.sex];
        break;
    }
    fgets(mhbuf1, MAILMSGLEN, fp);
    mh_delete_nl(mhbuf1);
    strcpy(uinfo.mailmsg, mhbuf1);
    fclose(fp);
  }
#endif

  mh_loginfrom(uinfo.from, uinfo.userid, fromhost);
  uinfo.from[28] = '\0';
/*    */

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


static void
user_login()
{
  char ans[4];
  char genbuf[200];
/*
  logfile(cuser.userid, getenv("RFC931"), "logins.last");
*/
  log_usies("ENTER", getenv("RFC931")/* fromhost */);

  /* ------------------------ */
  /* 初始化 uinfo、flag、mode */
  /* ------------------------ */

  enter_uflag = cuser.uflag;

#ifdef  INITIAL_SETUP
  if (!getbnum(DEFAULT_BOARD))
  {
    strcpy(currboard, "尚未選定");
  }
  else
#endif

  {
    brc_initial(DEFAULT_BOARD);
    set_board();
  }

  setup_utmp(LOGIN);
  currmode = MODE_STARTED;
  
  load_userrc();

  /* ------------ */
  /* 畫面處理開始 */
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
    prints("     歡迎您第 [1;33m%d[0;37m 度拜訪本站，\
上次您是從 [1;33m%s[0;37m 連往本站，\n\
     我記得那天是 [1;33m%s[0;37m。\n",
      ++cuser.numlogins, cuser.lasthost,
      Cdate(&cuser.lastlogin));

    pressanykey();

    setuserfile(genbuf, str_badlogin);
    if (more(genbuf, NA) != -1)
    {
      getdata(b_lines - 1, 0, "您要刪除以上錯誤嘗試的記錄嗎(Y/N)?[Y]",
        ans, 3, LCECHO, 0);
      if (*ans != 'n')
        unlink(genbuf);
    }
    check_register();
    if (cuser.numlogins < 10) /* 上站次小於10看newuser by Tzu */
      more("etc/newuser", YEA);
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
/*    char *nick[13] = {"椰子", "貝殼", "內衣", "寶特瓶", "翻車魚",
                      "樹葉", "浮萍", "鞋子", "潛水艇", "魔王",
                      "鐵罐", "考卷", "大美女"};
    char *name[13] = {"大王椰子", "鸚鵡螺", "比基尼", "可口可樂", "仰泳的魚",
                      "憶", "高岡屋", "AIR Jordon", "紅色十月號", "落紫液",
                      "SASAYA椰奶", "鴨蛋", "布魯克鱈魚香絲"};
    char *addr[13] = {"陽光沙灘", "大海", "陽光天體營", "美國", "綠色珊瑚礁",
                      "遠方", "原本海", "NIKE", "蘇聯", "男七420室",
                      "愛之味", "電機B 駱子逸", "藍色珊瑚礁"};
    int sex[13] = {6, 7, 7, 7, 2, 6, 0, 7, 7, 0, 7, 6, 1};*/
        /* 有雄中「特色」(?) 的 guest ,made by Tzu */
    char *nick[16] = {"榕樹", "盤餐\", "便當", "鋁罐", "光芒",
                      "落葉", "球鞋", "船艦", "魔王", "星光",
                      "音樂", "考卷", "飛碟", "蚊子", "聖人",
                      "三下"};
    char *name[16] = {"好大的榕樹", "粉圓", "四十五元", "運動飲料", "路燈",
                      "憶", "AIR Jordon", "鐵達尼號", "劉某某", "窮人的鑽石",
                      "優揚旋律", "鴨蛋", "圓圓的盤子", "雄中特產", "宇宙大聖人",
                      "化學極刑"};
    char *addr[16] = {"第六、七棟間", "餐\廳", "合作社", "販賣機", "弘毅樓",
                      "遠方", "NIKE", "二十世紀福斯、派拉蒙", "電腦教室", "綜合大樓",
                      "音樂班", "十七組陳文文", "就是這個光", "陰暗角落", "國文科飛碟會",
                      "ㄍㄚ記起來!"};
    int sex[16] = {6, 7, 7, 7, 7, 6, 7, 7, 4, 7, 1, 6, 7, 3, 9, 5};
    int i = rand() % 16;

    /* 使 guest 的 pager 防水 add by Tzu */
    currutmp->pager = 3;

    sprintf(cuser.username, "紅樓築夢裡的%s", nick[i]);
    sprintf(currutmp->username, cuser.username);
    sprintf(cuser.realname, name[i]);
    sprintf(currutmp->realname, cuser.realname);
    sprintf(cuser.address, addr[i]);
    cuser.sex = sex[i];
    pressanykey();
  }
  else
    pressanykey();
/* MH: 每個人都要看, guest也一樣 */
  more("etc/hotnews", 2); /* Tzu */ /* MH: 應該跟 welcome 一起 */

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

#if 0
  more(fn_note_ans, 2);
/*
woju
  x_user();
*/

  x_issue();
  birthday(YEA); /* Tzu */
#else
/*  if(belong("etc/MHDebug", cuser.userid))
  {
    mh_welcome();
  }
  else
  {
    more(fn_note_ans, 2);
    x_issue();
  }*/
  mh_welcome();
#endif
  birthday(YEA);
}

do_aloha()
{
   FILE* fp;
   char userid[80];
   char genbuf[200];

   setuserfile(genbuf, "aloha");
   if (fp = fopen(genbuf, "r")) {
      sprintf(genbuf + 1, "<<上站通知>> -- 我來啦！別砸我");
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

/* MH: for setting limit */
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
/*                       */

/* 2003/08/30 by Terry */
int
/*		       */
main(argc, argv)
  int argc;
  char **argv;
{
  int getin;
  FILE *fp;
  char buf[200];
  char* rfc931;

  extern struct commands cmdlist[];

  /* ----------- */
  /* system init */
  /* ----------- */
  
  /* MH: set limit */
  {
    struct rlimit rl;
    
    if(getrlimit(RLIMIT_DATA, &rl))
    {
      printf("Err @_@ getrlimit RLIMIT_DATA\n");
    }
    rl.rlim_cur = 5L * 1024 * 1024;
    if(setrlimit(RLIMIT_DATA, &rl))
    {
      printf("Err @_@ setrlimit RLIMIT_DATA\n");
    }
    
    if(getrlimit(RLIMIT_RSS, &rl))
    {
      printf("Err @_@ getrlimit RLIMIT_RSS\n");
    }
    rl.rlim_cur = 5L * 1024 * 1024;
    if(setrlimit(RLIMIT_RSS, &rl))
    {
      printf("Err @_@ getrlimit RLIMIT_RSS\n");
    }
  }
  /*               */

  setgid(BBSGID);
  setuid(BBSUID);
  chdir(BBSHOME);
  currmode = 0;
  srand(login_start_time = time(0));
  Argc = argc;
  Argv = argv;

  setenv("REMOTEHOST", strcpy(fromhost, (argc > 1) ? argv[1] : "localhost"), 1);
  strcpy(tty_name, (argc > 2) ? argv[2] : ttyname(0));
  setenv("REMOTEUSERNAME", strcpy(remoteusername, (argc > 3) ? argv[3] : "?"), 1);

  if (!(rfc931 = getenv("RFC931"))) {
     sprintf(buf, "%s@%s", remoteusername, fromhost);
     setenv("RFC931", buf, 1);
  }
  else {
     strcpy(buf, rfc931);
     setenv("REMOTEUSERNAME", strcpy(remoteusername, strtok(buf, "@")), 1);
     setenv("REMOTEHOST", strcpy(fromhost, strtok(0, " \n\r")), 1);
  }
  sprintf(buf, "if test -x %s/bin/banner; then %s/bin/banner %s; fi", BBSHOME, BBSHOME, (*tty_name) ? tty_name + 5 : 0);
  system(buf);

  atexit(leave_bbs);

  signal(SIGHUP, abort_bbs);
  signal(SIGBUS, abort_bbs);
  signal(SIGSEGV, abort_bbs);
  signal(SIGSYS, abort_bbs);

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);
  signal(SIGTERM, SIG_IGN);

  signal(SIGURG, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);

  signal(SIGUSR1, talk_request);
  signal(SIGUSR2, write_request);

  if (setjmp(byebye))
    abort_bbs(0);
  
  init_tty();
  login_query();
  user_login();

  if (HAVE_PERM(PERM_SYSOP | PERM_BM))
    b_closepolls();

  if (!(cuser.uflag & COLOR_FLAG))
    showansi = 0;

#ifdef DOTIMEOUT
  init_alarm();
#else
  signal(SIGALRM, SIG_IGN);
#endif

  if (HAS_PERM(PERM_ACCOUNTS) && belong("etc/sysop", cuser.userid)
      && dashf(fn_register)
      || belong("etc/ugly", cuser.userid) && HAS_PERM(PERM_BM)) /* for ugly old liu */
     m_register();
  domenu(MMENU, "主功\能表", (chkmail(0) ? 'M' : 'C'), cmdlist);
}
