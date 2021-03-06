/*-------------------------------------------------------*/
/* xyz.c        ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : system toolbox routines                      */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


/* ----------------------------------------------------- */
/* 各種統計及相關資訊列表                                */
/* ----------------------------------------------------- */


int
x_user()
{
  strcpy(vetitle, "[泳者與閒者]");
  more("etc/topusr", YEA);
  return 0;
}


int
x_note()
{
  strcpy(vetitle, "[合作社的言論廣場]");
  more(fn_note_ans, YEA);
  return 0;
}


#if 0
int
x_note2()
{
  strcpy(vetitle, "[合作社的言論廣場]");
  more(fn_note_ans2, YEA);
  return 0;
}
#endif


int
x_issue()
{
  strcpy(vetitle, "[今日水球大賽成績]");
  more("etc/day", YEA);
  more("etc/day_classboards", YEA);
  return 0;
}


int
x_week()
{
  strcpy(vetitle, "[本週五十大熱言榜]");
  more("etc/week", YEA);
  more("etc/week_classboards", YEA);
  return 0;
}


int
x_today()
{
  strcpy(vetitle, "[今日濤客人次統計]");
  more("etc/today", YEA);
  return 0;
}


int
x_yesterday()
{
  strcpy(vetitle, "[昨日濤客人次統計]");
  more("etc/yesterday", YEA);
  return 0;
}

/* Tzu */
int
x_birthday()
{
  strcpy(vetitle, "[生日快樂！]");
  birthday(YEA);

  more("etc/birth.today", YEA);
  return 0;
}

int
x_topboardman()
{
  strcpy(vetitle, "[看板精華區評比]");
  more("etc/topboardman", YEA);
  return 0;
}
/*     */

#ifdef HAVE_INFO
x_program()
{
  strcpy(vetitle, "[本程式之版本與版權宣告]");
  more("etc/version", YEA);
  return 0;
}
#endif


#ifdef HAVE_License
x_gpl()
{
  strcpy(vetitle, "[GNU 使用執照]");
  more("etc/GPL", YEA);
  return 0;
}
#endif

/* Leeym */
int
x_showload()
{
  char genbuf[80];
  double cpu_load[3];
  int i;

  getloadavg(cpu_load, 3);
  i = cpu_load[0];

  sprintf(genbuf, "[1;36m目前系統負荷:[m %.2f  %.2f  %.2f , %s\n",
        cpu_load[0], cpu_load[1],  cpu_load[2],
        i ? ( i-1 ? "[1;31m負荷危險[m" :
        "[1;33m負荷偏高[m"):"[1;32m負荷正常[m");

  if (i) system("/usr/local/bin/killbbs &");

  move(b_lines - 1, 0);
  outs(genbuf);
  pressanykey();
  return 0;
}
/*       */

int
Welcome()
{
  strcpy(vetitle, "[歡迎畫面]");
  more("etc/welcome", NA);
  pressanykey();
  more("etc/hotnews", 2);
  return 0;
}

/* Leeym 生日快樂*/
int
birthday(int more_birth)
{
  struct tm *ptime;
  time_t now;
  time(&now);
  ptime = localtime(&now);

/* Tzu 這是沒有填生日的叫他去填，已改為一上站即填生日
  if((cuser.year==0) && (cuser.userlevel))
    more("etc/check_birthday", YEA);
  else
*/
  if ((cuser.month==ptime->tm_mon+1)&(cuser.day==ptime->tm_mday))
  {
    if (more_birth) /* Tzu: 秀出生日蛋糕 */
    {
      more("etc/birthday",NA);
      mh_pressanykey("          生日快樂!!生日快樂!!生日快樂!!生日快樂!!生日快樂!!生日快樂!!         ");
    }
    return 1;
  }
  return 0;
}


/* ----------------------------------------------------- */
/* 離開 BBS 站                                           */
/* ----------------------------------------------------- */


static void
note()
{
  static char *fn_note_tmp = "note.tmp";
  static char *fn_note_dat = "note.dat";
#if 0
  static char *fn_note_dat2 = "note.dat2";
#endif
  int total, i, collect, len;
  struct stat st;
  char buf[256], buf2[80], *p;
  int fd, fx;
  FILE *fp, *foo,*outf;

  struct notedata
  {
    time_t date;
    char userid[IDLEN + 1];
    char username[19];
    char buf[3][80];
  };
  struct notedata myitem;

  do
  {
    myitem.buf[0][0] = myitem.buf[1][0] = myitem.buf[2][0] = '\0';
    move(12, 0);
    clrtobot();
    outs("\n請留言 (至多三行)，按[Enter]結束");
    for (i = 0; (i < 3) &&
      getdata(16 + i, 0, "：", myitem.buf[i], 78, DOECHO, 0); i++);
    getdata(b_lines - 1, 0, "(S)儲存 (E)重新來過 (Q)取消？[S] ", buf, 3, LCECHO, 0);
/*
woju
*/
    if (buf[0] == 'q' || i == 0 && *buf != 'e')
      return;
  } while (buf[0] == 'e');

  strcpy(myitem.userid, cuser.userid);
  strncpy(myitem.username, cuser.username, 18);
  myitem.username[18] = '\0';
  time(&(myitem.date));

  /* begin load file */
  
#if 0
/* MH */
  if((fp = fopen(fn_note_dat2, "a")) == NULL)
    return;
  fwrite(&myitem, sizeof(myitem), 1, fp);
  fclose(fp);
/*    */
#endif

  if ((foo = fopen(".note", "a")) == NULL)
    return;

  if ((fp = fopen(fn_note_ans, "w")) == NULL)
    return;

  if ((fx = open(fn_note_tmp, O_WRONLY | O_CREAT, 0644)) <= 0)
    return;

  if ((fd = open(fn_note_dat, O_RDONLY)) == -1)
  {
    total = 1;
  }
  else if (fstat(fd, &st) != -1)
  {
    total = st.st_size / sizeof(struct notedata) + 1;
    if (total > MAX_NOTE)
      total = MAX_NOTE;
  }

  fputs("\t\t\t[37;45m ● 合 作 社 言 論 廣 場 ● \n\n", fp);
  collect = 1;

  while (total)
  {
    sprintf(buf, "[1;33;41mΦ[47;30m %s [34m(%s)",
      myitem.userid, myitem.username);
    len = strlen(buf);

    strcat(buf, " [35;45m" + (len & 1));

    for (i = len >> 1; i < 41; i++)
      strcat(buf, "▄");
    sprintf(buf2, "[44;37m %.14s [33;41mΦ[0m\n",
      Cdate(&(myitem.date)));
    strcat(buf, buf2);
    fputs(buf, fp);

    if (collect)
      fputs(buf, foo);

    sprintf(buf, "%s\n%s\n%s\n", myitem.buf[0], myitem.buf[1], myitem.buf[2]);
    fputs(buf, fp);

    if (collect)
    {
      fputs(buf, foo);
      fclose(foo);
      collect = 0;
    }

    write(fx, &myitem, sizeof(myitem));

    if (--total)
      read(fd, (char *) &myitem, sizeof(myitem));
  }
  fclose(fp);
  close(fd);
  close(fx);
  Rename(fn_note_tmp, fn_note_dat);

#if 0
/* MH */
  if ((fp = fopen(fn_note_ans2, "w")) == NULL)
    return;

  if ((fd = open(fn_note_dat2, O_RDONLY)) == -1)
    return;

  if (fstat(fd, &st) != -1)
  {
    total = st.st_size / sizeof(struct notedata);
  }
  else
    total = 0;
  
  fputs("\t\t\t[37;45m ● 合 作 社 言 論 廣 場 ● \n\n", fp);

  while (total > 0)
  {
    if(lseek(fd, (total - 1) * sizeof(myitem), SEEK_SET) == -1)
      break;
    if(read(fd, (char *) &myitem, sizeof(myitem)) != sizeof(myitem))
      break;
    
    sprintf(buf, "[1;33;41mΦ[47;30m %s [34m(%s)",
      myitem.userid, myitem.username);
    len = strlen(buf);

    strcat(buf, " [35;45m" + (len & 1));

    for (i = len >> 1; i < 41; i++)
      strcat(buf, "▄");
    sprintf(buf2, "[44;37m %.14s [33;41mΦ[0m\n",
      Cdate(&(myitem.date)));
    strcat(buf, buf2);
    fputs(buf, fp);

    sprintf(buf, "%s\n%s\n%s\n", myitem.buf[0], myitem.buf[1], myitem.buf[2]);
    fputs(buf, fp);

    total --;
  }
  fclose(fp);
  close(fd);
/*    */
#endif

  strcpy(vetitle, "[合作社的言論廣場]");
  more(fn_note_ans, YEA);
}

/* MH */
void
mh_note()
{
  static char *fn_note_tmp = "note.tmp";
  static char *fn_note_dat = "note.dat";
  int total, i, collect, len;
  struct stat st;
  char buf[256], buf2[80], *p;
  int fd, fx;
  FILE *fp, *foo,*outf;

  struct notedata
  {
    time_t date;
    char userid[IDLEN + 1];
    char username[19];
    char buf[3][80];
  };
  struct notedata myitem;

  do
  {
    myitem.buf[0][0] = myitem.buf[1][0] = myitem.buf[2][0] = '\0';
    move(12, 0);
    clrtobot();
    outs("\n請留言 (至多三行)，按[Enter]結束");
    strcpy(myitem.buf[0], "祝自己生日快樂^^;;");
    strcpy(myitem.buf[1], "快樂快樂^o^");
    strcpy(myitem.buf[2], "");
    buf[0] = 's';
/*
woju
*/
    if (buf[0] == 'q' || i == 0 && *buf != 'e')
      return;
  } while (buf[0] == 'e');

  strcpy(myitem.userid, cuser.userid);
  strncpy(myitem.username, cuser.username, 18);
  myitem.username[18] = '\0';
  time(&(myitem.date));

  /* begin load file */

  if ((foo = fopen(".note", "a")) == NULL)
    return;

  if ((fp = fopen(fn_note_ans, "w")) == NULL)
    return;

  if ((fx = open(fn_note_tmp, O_WRONLY | O_CREAT, 0644)) <= 0)
    return;

  if ((fd = open(fn_note_dat, O_RDONLY)) == -1)
  {
    total = 1;
  }
  else if (fstat(fd, &st) != -1)
  {
    total = st.st_size / sizeof(struct notedata) + 1;
    if (total > MAX_NOTE)
      total = MAX_NOTE;
  }

  fputs("\t\t\t[37;45m ● 合 作 社 言 論 廣 場 ● \n\n", fp);
  collect = 1;

  while (total)
  {
    sprintf(buf, "[1;33;41mΦ[47;30m %s [34m(%s)",
      myitem.userid, myitem.username);
    len = strlen(buf);

    strcat(buf, " [35;45m" + (len & 1));

    for (i = len >> 1; i < 41; i++)
      strcat(buf, "▄");
    sprintf(buf2, "[44;37m %.14s [33;41mΦ[0m\n",
      Cdate(&(myitem.date)));
    strcat(buf, buf2);
    fputs(buf, fp);

    if (collect)
      fputs(buf, foo);

    sprintf(buf, "%s\n%s\n%s\n", myitem.buf[0], myitem.buf[1], myitem.buf[2]);
    fputs(buf, fp);

    if (collect)
    {
      fputs(buf, foo);
      fclose(foo);
      collect = 0;
    }

    write(fx, &myitem, sizeof(myitem));

    if (--total)
      read(fd, (char *) &myitem, sizeof(myitem));
  }
  fclose(fp);
  close(fd);
  close(fx);
  Rename(fn_note_tmp, fn_note_dat);
  strcpy(vetitle, "[合作社的言論廣場]");
}
/*    */

static void
mail_sysop()
{
  FILE *fp;
  char genbuf[200];

  if (fp = fopen("etc/sysop", "r"))
  {
    int i, j;
    char *ptr;

    struct SYSOPLIST
    {
      char userid[IDLEN + 1];
      char duty[40];
    }         sysoplist[9];

    j = 0;
    while (fgets(genbuf, 128, fp))
    {
      if (ptr = strchr(genbuf, '\n'))
      {
        *ptr = '\0';
        ptr = genbuf;
        while (isalnum(*ptr))
           ptr++;
        if (*ptr)
        {
          *ptr = '\0';
          do
          {
            i = *++ptr;
          } while (i == ' ' || i == '\t');
          if (i)
          {
            strcpy(sysoplist[j].userid, genbuf);
            strcpy(sysoplist[j++].duty, ptr);
          }
        }
      }
    }

    move(12, 0);
    clrtobot();
    prints("%16s   %-18s權責劃分\n\n", "編號", "站長 ID"/*, msg_seperator*/);

    for (i = 0; i < j; i++)
    {
      prints("%15d.   [1;%dm%-16s%s[0m\n",
        i + 1, 31 + i % 7, sysoplist[i].userid, sysoplist[i].duty);
    }
    prints("%-14s0.   [1;%dm離開[0m", "", 31 + j % 7);
    getdata(b_lines - 1, 0, "                   請輸入代碼[0]：", genbuf, 4, DOECHO, 0);
    i = genbuf[0] - '0' - 1;
    if (i >= 0 && i < j)
    {
      clear();
      do_send(sysoplist[i].userid, NULL);
    }
  }
}


int
m_sysop()
{
  setutmpmode(MSYSOP);
  mail_sysop();
  return 0;
}


int
Goodbye()
{
  extern void movie();
  char genbuf[200];

/*
woju
*/
  char ans[4];


  setuserfile(genbuf, fn_writelog);
  if (more(genbuf, NA) != -1) {
/* MH */
/* 檢查水球記錄容量, 避免有人「屯積」大量水球 */
     struct stat st;
     int writelog_limit;
    
     if (HAS_PERM(PERM_BM))
        writelog_limit = MH_WRITELOGLIMIT_BM;
     else if (HAS_PERM(PERM_LOGINOK))
        writelog_limit = MH_WRITELOGLIMIT_LOGINOK;
     else
        writelog_limit = MH_WRITELOGLIMIT_BASIC;
     do
     {
       char buf[80];
       
       setuserfile(buf, fn_writelog);
       stat(buf, &st);
       if(!HAVE_PERM(PERM_SYSOP) && !HAVE_PERM(PERM_MAILLIMIT) && st.st_size / 1024 > writelog_limit)
       {
         my_outmsg_row("[1;41;37m您的水球記錄已超過限定容量，無法選擇「保留」[0m", b_lines - 2);
         getdata(b_lines - 1, 0, "清除(C) 移至備忘錄(M) (C/M)?[M]",
            ans, 3, LCECHO, 0);
       }
       else
       {
         getdata(b_lines - 1, 0, "清除(C) 移至備忘錄(M) 保留(R) (C/M/R)?[R]",
            ans, 3, LCECHO, 0);
       }
       if (*ans == 'm') {
          fileheader mymail;
          char title[128], buf[80];

          sethomepath(buf, cuser.userid);
          stampfile(buf, &mymail);

          mymail.savemode = 'H';        /* hold-mail flag */
          mymail.filemode = FILE_READ;
          strcpy(mymail.owner, "[備.忘.錄]");
          strcpy(mymail.title, "熱線[37;41m記錄[m");
          if(mh_memoforward(cuser.userid, genbuf, &mymail, sizeof(mymail)))
          {
            sethomedir(title, cuser.userid);
            append_record(title, &mymail, sizeof(mymail));
            /* MH: 備忘錄加上作者標題等資訊...不然在'x'轉寄或是buildir的時候
                   會爛掉 */
#if 1
            {
              FILE *src, *dst;
              char buf2[200];
              time_t now;
              
              if((src = fopen(genbuf, "r")) == NULL)
              {
                sprintf(buf2, "errno: %d, genbuf:%s", errno, genbuf);
                log_usies("MH ", buf2);
              }
              if((dst = fopen(buf, "w")) == NULL)
              {
                sprintf(buf2, "errno: %d, buf:%s", errno, buf);
                log_usies("MH ", buf2);
                fclose(src);
              }
              now = time(NULL);
              sprintf(buf2, "作者: %s\n標題: %s\n時間: %s\n", mymail.owner, mymail.title, ctime(&now));
              fputs(buf2, dst);
              while(fgets(buf2, 199, src) != NULL)
                fputs(buf2, dst);
              fclose(src);
              fclose(dst);
              unlink(genbuf);
            }
#else
            Rename(genbuf, buf);
#endif
          }
        }
       else if (*ans == 'c') {
          char buf[80];

          setuserfile(buf, fn_writelog);
          unlink(buf);
       }
     } while(!HAVE_PERM(PERM_SYSOP) && !HAVE_PERM(PERM_MAILLIMIT) && st.st_size / 1024 > writelog_limit && *ans != 'm' && *ans != 'c');

      clear();
      move(0, 0);
      prints("[1;44;33m                             高雄中學-紅樓築夢                                [m");
      movie(0);
  }
/*    */

  getdata(b_lines - 1, 0, "您確定要離開【 " BOARDNAME " 】嗎(Y/N)？[N] ",
    genbuf, 3, LCECHO, 0);

  if (*genbuf != 'y')
    return 0;

  movie(999);
  if (cuser.userlevel)
  {
    getdata(b_lines - 1, 0, "(G)隨風而逝 (M)托夢站長 (N)合作社的言論廣場？[G] ",
      genbuf, 3, LCECHO, 0);
    if (genbuf[0] == 'm')
      mail_sysop();
    else if (genbuf[0] == 'n')
      note();
  }

  save_userrc();
#if 0
  save_mailmsg();
#endif

  clear();
  prints("[1;36m親愛的 [33m%s(%s)[36m，別忘了再度光臨[45;33m"
    " %s [40;36m！\n以下是您在站內的註冊資料:[0m\n",
    cuser.userid, cuser.username, BoardName);
  user_display(&cuser, 0);

  if (currmode)
    u_exit("EXIT ");

  pressanykey();
  sleep(1);
  reset_tty();
  exit(0);
}


/* ----------------------------------------------------- */
/* 支援外掛程式 : tin、gopher、www、bbsnet、game、csh    */
/* ----------------------------------------------------- */


#ifdef HAVE_EXTERNAL
#define LOOKFIRST       (0)
#define LOOKLAST        (1)
#define QUOTEMODE       (2)
#define MAXCOMSZ        (1024)
#define MAXARGS         (40)
#define MAXENVS         (20)
#define BINDIR          "/bin/"

char *bbsenv[MAXENVS];
int numbbsenvs = 0;


int
bbssetenv(env, val)
  char *env, *val;
{
  register int i, len;
  extern char *malloc();

  if (numbbsenvs == 0)
    bbsenv[0] = NULL;
  len = strlen(env);
  for (i = 0; bbsenv[i]; i++)
    if (!ci_strncmp(env, bbsenv[i], len))
      break;
  if (i >= MAXENVS)
    return -1;
  if (bbsenv[i])
    free(bbsenv[i]);
  else
    bbsenv[++numbbsenvs] = NULL;
  bbsenv[i] = malloc(strlen(env) + strlen(val) + 2);
  strcpy(bbsenv[i], env);
  strcat(bbsenv[i], "=");
  strcat(bbsenv[i], val);
}


pid_t xyzpid;

void
xyz_idle()
{
  struct stat ttystat;

  if (currutmp->pid != currpid)
  {
    setup_utmp(XMODE);          /* 重新配置 shm */
  }

  if (stat(currutmp->tty, &ttystat))
     currutmp->uptime = time(0);
  else
     currutmp->uptime = ttystat.st_atime;

  if (!(PERM_HIDE(currutmp) || currutmp->mode == MAILALL)
      && time(0) - currutmp->uptime > IDLE_TIMEOUT)
  {
    restore_tty();
    bell();
    prints("[1;37;41m超過閒置時間！Booting...[m\r");
    refresh();
    abort_bbs();
  }
  alarm(MOVIE_INT);
}


int
do_exec(com, wd)
  char *com, *wd;
{
  char genbuf[200];
  char path[MAXPATHLEN];
  char pcom[MAXCOMSZ];
  char *arglist[MAXARGS], *arglist1[MAXARGS + 1];
  char *tz;
  register int i, len;
  register int argptr;
  register char *lparse;
  int status, w;
  pid_t pid;
  int pmode;
  void (*isig) (), (*qsig) (), (*hsig)(), (*u1sig)(), (*u2sig)(), (*asig)();
  int pager0 = currutmp->pager;

  if (mbbsd)
     return;
  currutmp->pager = 3;
  strncpy(path, BINDIR, MAXPATHLEN);
  strncpy(pcom, com, MAXCOMSZ);
  len = MIN(strlen(com) + 1, MAXCOMSZ);
  pmode = LOOKFIRST;
  for (i = 0, argptr = 0; i < len; i++)
  {
    if (pcom[i] == '\0')
      break;
    if (pmode == QUOTEMODE)
    {
      if (pcom[i] == '\001')
      {
        pmode = LOOKFIRST;
        pcom[i] = '\0';
        continue;
      }
      continue;
    }
    if (pcom[i] == '\001')
    {
      pmode = QUOTEMODE;
      arglist[argptr++] = &pcom[i + 1];
      if (argptr + 1 == MAXARGS)
        break;
      continue;
    }
    if (pmode == LOOKFIRST)
      if (pcom[i] != ' ')
      {
        arglist[argptr++] = &pcom[i];
        if (argptr + 1 == MAXARGS)
          break;
        pmode = LOOKLAST;
      }
      else
        continue;
    if (pcom[i] == ' ')
    {
      pmode = LOOKFIRST;
      pcom[i] = '\0';
    }
  }
  arglist[argptr] = NULL;
  if (argptr == 0)
    return -1;
  if (*arglist[0] == '/')
    strncpy(path, arglist[0], MAXPATHLEN);
  else
    strncat(path, arglist[0], MAXPATHLEN);
  reset_tty();
/*
woju
  alarm(0);
*/
  if ((pid = vfork()) == 0)
  {
    if (wd)
      if (chdir(wd))
      {
        fprintf(stderr, "Unable to chdir to '%s'\n", wd);
        exit(-1);
      }
    bbssetenv("PATH", "/bin:.");
    bbssetenv("TERM", "vt100"/* cuser.termtype */);
    bbssetenv("USER", cuser.userid);
    bbssetenv("USERNAME", cuser.username);
    /* added for tin's HOME and EDITOR */
/*
woju
*/
    sprintf(genbuf, "/bbs1/home/bbs/home/%s", cuser.userid);
    bbssetenv("HOME", genbuf);
    bbssetenv("EDITOR", "bin/ve");
    /* end */
    /* added for tin's reply to */
    bbssetenv("REPLYTO", cuser.email);
    bbssetenv("FROMHOST", fromhost);
    /* end of insertion */
    if ((tz = getenv("TZ")) != NULL)
      bbssetenv("TZ", tz);
    if (numbbsenvs == 0)
      bbsenv[0] = NULL;

/*
    execve(path, arglist, bbsenv);
*/

    memcpy(arglist1 + 1, arglist, sizeof(arglist));
    arglist1[0] = "bin/bbsroot";
    execve("bin/bbsroot", arglist1, bbsenv);

    fprintf(stderr, "EXECV FAILED... path = '%s'\n", path);
    exit(-1);
  }
  xyzpid = pid;
  asig = signal(SIGALRM, xyz_idle);
  isig = signal(SIGINT, SIG_IGN);
  qsig = signal(SIGQUIT, SIG_IGN);
/*  hsig = signal(SIGHUP, SIG_IGN);*/
  u1sig = signal(SIGUSR1, SIG_IGN);
  u2sig = signal(SIGUSR2, SIG_IGN);
  while ((w = wait(&status)) != pid && w != 1)
     /* NULL STATEMENT */ ;
  signal(SIGALRM, asig);
  signal(SIGINT,  isig);
  signal(SIGQUIT, qsig);
/*  signal(SIGHUP,  hsig);*/
  signal(SIGUSR1, u1sig);
  signal(SIGUSR2, u2sig);
  currutmp->pager = pager0;
  currutmp->msgcount = 0;
  restore_tty();

#ifdef DOTIMEOUT
/*
woju
  alarm(IDLE_TIMEOUT);
*/
#endif

  return ((w == -1) ? w : status);
}



int
exec_cmd(umode, pager, cmdfile, mesg)
  char *cmdfile, *mesg;
{
  char buf[64];
  int save_pager;

  if (!dashf(cmdfile))
  {
    move(2, 0);
    prints("很抱歉, 本站不提供 %s (%s) 功\能.", mesg, cmdfile);
    return 0;
  }
  save_pager = currutmp->pager;
  if (pager == NA)
  {
    currutmp->pager = pager;
  }
  setutmpmode(umode);
  sprintf(buf, "/bin/sh %s", cmdfile);
  reset_tty();
  do_exec(buf, NULL);
  restore_tty();
  currutmp->pager = save_pager;
  clear();
  return 0;
}


#ifdef HAVE_TIN
x_tin()
{
  return exec_cmd(XMODE, YEA, "bin/tin.sh", "TIN");
}
#endif


#ifdef HAVE_GOPHER
x_gopher()
{
  return exec_cmd(XMODE, YEA, "bin/gopher.sh", "GOPHER");
}
#endif


#ifdef HAVE_BRIDGE
x_bridge()
{
  char buf[64];
  int save_pager;

  clear();
  outs("歡迎進入 ●[31m陽光[1;33m沙灘[0m● 來玩[1;37m網路橋牌[0m\n");
  outs("[1;35mKaede[37m:[0m 玩橋牌不用賭錢,\n");
  outs("       還可以和大家連誼,多玩有益健康喔!! *^_^*\n\n");
  outs("[1;34mRaw[37m:[0m 嗯嗯..還可以預防老人癡呆症!!\n");
  outs("     (別不相信,這有根據的!!)\n\n");
  outs("p.s: 第一位上線者將自動成為 Server!\n");
  pressanykey();

  save_pager = currutmp->pager;
  currutmp->pager = NA;
  setutmpmode(BRIDGE);
  reset_tty();

  sprintf(buf, "/bbs1/home/bbs/bin/okbridge -n %s -s freebsd", cuser.userid);
  if (!mbbsd)
     do_exec(buf, NULL);

  restore_tty();
  currutmp->pager = save_pager;

  clear();
  prints("謝謝 [1;33m%s[0m 的光臨!!\n", cuser.userid);
  outs("歡迎下次再來湊四腳啊!! ^o^\n");
  pressanykey();

  clear();
  return 0;
}
#endif


#ifdef HAVE_WWW
x_www()
{
  return exec_cmd(WWW, NA, "bin/www.sh", "WWW");
}
#endif                          /* HAVE_WWW */


#ifdef HAVE_IRC
x_irc()
{
  return exec_cmd(XMODE, NA, "bin/irc.sh", "IRC");
}
#endif                          /* HAVE_IRC */


#ifdef  HAVE_ADM_SHELL
x_csh()
{
  int save_pager;

  clear();
  refresh();
  reset_tty();
  save_pager = currutmp->pager;
  currutmp->pager = NA;

#ifdef  HAVE_REPORT
  report("shell out");
#endif

#ifdef SYSV
  do_exec("sh", NULL);
#else
  do_exec("tcsh", NULL);
#endif

  restore_tty();
  currutmp->pager = save_pager;
  clear();
  return 0;
}
#endif                          /* NO_ADM_SHELL */


#ifdef BBSDOORS
x_bbsnet()                      /* Bill Schwartz */
{
  int save_pager = currutmp->pager;

  currutmp->pager = NA;

  setutmpmode(BBSNET);
  /* bbsnet.sh is a shell script that can be customized without */
  /* having to recompile anything.  If you edit it while someone */
  /* is in bbsnet they will be sent back to the xyz menu when they */
  /* leave the system they are currently in. */

  reset_tty();
  do_exec("bbsnet.sh", NULL);
  restore_tty();
  currutmp->pager = save_pager;
  clear();
  return 0;
}
#endif


#ifdef HAVE_GAME
x_game()
{
  int save_pager = currutmp->pager;

  currutmp->pager = NA;

  setutmpmode(BBSNET);
  /* bbsnet.sh is a shell script that can be customized without */
  /* having to recompile anything.  If you edit it while someone */
  /* is in bbsnet they will be sent back to the xyz menu when they */
  /* leave the system they are currently in. */

  reset_tty();
  do_exec("okbridge.sh", NULL);
  restore_tty();
  currutmp->pager = save_pager;
  clear();
  return 0;
}
#endif                          /* HAVE_GAME */

#endif                          /* HAVE_EXTERNAL */
