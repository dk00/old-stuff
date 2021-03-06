#define VACATION
/*-------------------------------------------------------*/
/* register.c   ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : user register routines                       */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


/* ------------------- */
/* password encryption */
/* ------------------- */

char *crypt();
static char pwbuf[14];


char *
genpasswd(pw)
  char *pw;
{
  if (pw[0])
  {
    char saltc[2], c;
    int i;

    i = 9 * getpid();
    saltc[0] = i & 077;
    saltc[1] = (i >> 6) & 077;

    for (i = 0; i < 2; i++)
    {
      c = saltc[i] + '.';
      if (c > '9')
        c += 7;
      if (c > 'Z')
        c += 6;
      saltc[i] = c;
    }
    strcpy(pwbuf, pw);
    return crypt(pwbuf, saltc);
  }
  return "";
}


int
checkpasswd(passwd, test)
  char *passwd, *test;
{
  char *pw;

  strncpy(pwbuf, test, 14);
  pw = crypt(pwbuf, passwd);
  return (!strncmp(pw, passwd, 14));
}


/* ------------------ */
/* 檢查 user 註冊情況 */
/* ------------------ */


static int
bad_user_id(userid)
  char *userid;
{
  register char ch;

  if (strlen(userid) < 2)
    return 1;

  if (not_alpha(*userid))
    return 1;

  if (!ci_strcmp(userid, str_new))
    return 1;

  while (ch = *(++userid))
  {
    if (not_alnum(ch))
      return 1;
  }
  return 0;
}


/* -------------------------------- */
/* New policy for allocate new user */
/* (a) is the worst user currently  */
/* (b) is the object to be compared */
/* -------------------------------- */


static int
compute_user_value(urec, clock)
  userec *urec;
  time_t clock;
{
  int value;

  /* if (urec) has XEMPT permission, don't kick it */
  if ((urec->userid[0] == '\0') || (urec->userlevel & PERM_XEMPT))
    return 9999;

  value = (clock - urec->lastlogin) / 60;       /* minutes */

  /* new user should register in 30 mins */
/*  if (strcmp(urec->userid, str_new) == 0)
    return (30 - value);*/ /* MH */ /* 暫時刪掉 */

#ifdef  VACATION
  return 120 * 24 * 60 - value; /* 寒暑假保存帳號 120 天 */
#else
  if (!urec->numlogins)         /* 未 login 成功者，不保留 */
    return -1;
  if (urec->numlogins <= 3)     /* #login 少於三者，保留 30 天 */
    return 30 * 24 * 60 - value;

  /* 未完成註冊者，保留 45 天 */
  /* 一般情況，保留 90 天 */
  return (urec->userlevel & PERM_LOGINOK ? 90 : 45) * 24 * 60 - value;
#endif
}


static int
getnewuserid(char *newuserid)
{
  static char *fn_fresh = ".fresh";
  extern struct UCACHE *uidshm;
  userec utmp, zerorec;
  time_t clock;
  struct stat st;
  int fd, val, i;
  char genbuf[200];
  char genbuf2[200];

  memset(&zerorec, 0, sizeof(zerorec));
  clock = time(NULL);

/*
woju: reload shm before searchnewuser ("resolve"_ucache)
*/
  reload_ucache();

  /* -------------------------------------- */
  /* Lazy method : 先找尋已經清除的過期帳號 */
  /* -------------------------------------- */

  if ((i = searchnewuser(0)) == 0)
  {

    /* ------------------------------- */
    /* 每 1 個小時，清理 user 帳號一次 */
    /* ------------------------------- */

    if ((stat(fn_fresh, &st) == -1) || (st.st_mtime < clock - 3600))
    {
      if ((fd = open(fn_fresh, O_RDWR | O_CREAT, 0600)) == -1)
        return -1;
      write(fd, ctime(&clock), 25);
      close(fd);
      log_usies("CLEAN", "dated users");

      printf("尋找新帳號中, 請稍待片刻...\n\r");
      if ((fd = open(fn_passwd, O_RDWR | O_CREAT, 0600)) == -1)
        return -1;
      i = 0;
      while (i < MAXUSERS)
      {
        i++;
        if (read(fd, &utmp, sizeof(userec)) != sizeof(userec))
          break;
/*
woju
*/
        if ((val = compute_user_value(&utmp, clock)) < 0 &&
            !belong("etc/anonymous", utmp.userid)) {
           sprintf(genbuf, "#%d %-12s %15.15s %d %d %d",
             i, utmp.userid, ctime(&(utmp.lastlogin)) + 4,
             utmp.numlogins, utmp.numposts, val);
           if (val > -1 * 60 * 24 * 365)
           {
             log_usies("CLEAN", genbuf);
             sprintf(genbuf, "home/%s", utmp.userid);
             sprintf(genbuf2, "tmp/%s", utmp.userid);
             sweep(utmp.userid);
             if (dashd(genbuf) && Rename(genbuf, genbuf2))
             {
               sprintf(genbuf, "/bin/rm -fr home/%s", utmp.userid);
               system(genbuf);
             }
             if (lseek(fd, (i - 1) * sizeof(userec), SEEK_SET) != -1)
                write(fd, &zerorec, sizeof(utmp));
           }
           else
              log_usies("DATED", genbuf);
        }
      }
      close(fd);
      time(&(uidshm->touchtime));
    }
  }
  if ((fd = open(fn_passwd, O_RDWR | O_CREAT, 0600)) == -1)
    return -1;
  flock(fd, LOCK_EX);

  i = searchnewuser(1);
  if ((i <= 0) || (i > MAXUSERS))
  {
    flock(fd, LOCK_UN);
    close(fd);
    if (more("etc/user_full", NA) == -1)
      printf("抱歉，使用者帳號已經滿了，無法註冊新的帳號\n\r");
    val = (st.st_mtime - clock + 3660) / 60;
    printf("請等待 %d 分鐘後再試一次，祝你好運\n\r", val);
    sleep(2);
    exit(1);
  }

  sprintf(genbuf, "uid %d, %s", i, newuserid);
  log_usies("APPLY", genbuf);
  sprintf(genbuf, "home/%s", newuserid);
  if (stat(genbuf, &st) != -1) {
    sprintf(genbuf, "uid %d, %s", i, newuserid);
    log_usies("COLLISION", genbuf);
    exit(1);
  }

  strcpy(zerorec.userid, str_new);
  zerorec.lastlogin = clock;
  if (lseek(fd, sizeof(zerorec) * (i - 1), SEEK_SET) == -1)
  {
    flock(fd, LOCK_UN);
    close(fd);
    return -1;
  }
  write(fd, &zerorec, sizeof(zerorec));
  setuserid(i, zerorec.userid);
  flock(fd, LOCK_UN);
  close(fd);
  return i;
}



void
new_register()
{
  userec newuser;
  char passbuf[STRLEN];
  int allocid, try;
  char genbuf[200];

#if 0
  time_t now;

  /* ------------------ */
  /* 限定星期幾不准註冊 */
  /* ------------------ */

  now = time(0);
  sprintf(genbuf, "etc/no_register_%3.3s", ctime(&now));
  if (more(genbuf, NA) != -1)
  {
    pressanykey();
    exit(1);
  }
#endif

  memset(&newuser, 0, sizeof(newuser));

  more("etc/register", NA);
  try = 0;
  while (1)
  {
    if (++try >= 6)
    {
      outs("\n您嘗試錯誤的輸入太多，請下次再來吧\n");
      refresh();

      pressanykey();
      oflush();
      exit(1);
    }
    getdata(0, 0, msg_uid, newuser.userid, IDLEN + 1, DOECHO, 0);

    if (bad_user_id(newuser.userid))
      outs("無法接受這個代號，請使用英文字母，並且不要包含空格\n");
    else if (searchuser(newuser.userid))
      outs("此代號已經有人使用\n");
    /* Prince: 系統損壞事件暫時性的處理 */
    else if (belong("etc/fixlist",newuser.userid))
    {
      char ans[4];
      outs("[警告]此ID在本次系統損壞保管名單中!!若非原所有人註冊,站方將有權刪除!!\n");
      getdata(0, 0, "確定要以此ID註冊(Y/N)[N]?", ans, 4, DOECHO, 0);
      if ( *ans == 'y' )
        break;
    }
    /* Prince: 等事件過後可將此段刪除 */
    else
      break;
  }


    try = 0;
  while (1)
  {
    if (++try >= 6)
    {
      outs("\n您嘗試錯誤的輸入太多，請下次再來吧\n");
      refresh();

      pressanykey();
      oflush();
      exit(1);

      /*
      return;
      */
/*longjmp(byebye, -1);*/
    }
    if ((getdata(0, 0, "請設定密碼：", passbuf, PASSLEN, NOECHO, 0) < 3) ||
      !strcmp(passbuf, newuser.userid))
    {
      outs("密碼太簡單，易遭入侵，至少要 4 個字，請重新輸入\n");
      continue;
    }
    strncpy(newuser.passwd, passbuf, PASSLEN);
    getdata(0, 0, "請檢查密碼：", passbuf, PASSLEN, NOECHO, 0);
    if (strncmp(passbuf, newuser.passwd, PASSLEN))
    {
      outs("密碼輸入錯誤, 請重新輸入密碼.\n");
      continue;
    }
    passbuf[8] = '\0';
    strncpy(newuser.passwd, genpasswd(passbuf), PASSLEN);
    break;
  }
/*
  getdata(0, 0, "終端機形態 [vt100]：", newuser.termtype, 8, ECHO);
  if (newuser.termtype[0] == '\0')
  strcpy(newuser.termtype, "vt100");
*/
  newuser.userlevel = PERM_DEFAULT;
  newuser.uflag = COLOR_FLAG | BRDSORT_FLAG | MOVIE_FLAG;
  newuser.firstlogin = newuser.lastlogin = time(NULL);
  newuser.year = newuser.month = newuser.day = 0;
/*  newuser.sex = 17;*/ /* Tzu */
  newuser.sex = MAX_SEXS;  /* MH */
  
  allocid = getnewuserid(newuser.userid);
  if (allocid > MAXUSERS || allocid <= 0)
  {
    fprintf(stderr, "本站人口已達飽和！\n");
    exit(1);
  }

  if (substitute_record(fn_passwd, &newuser, sizeof(newuser), allocid) == -1)
  {
    fprintf(stderr, "客滿了，再見！\n");
    exit(1);
  }
  setuserid(allocid, newuser.userid);
  if (!dosearchuser(newuser.userid))
  {
    fprintf(stderr, "無法建立帳號\n");
    exit(1);
  }
}


void
check_register()
{
  char *ptr;
  char genbuf[200];

  stand_title("請詳細填寫個人資料");

  while (strlen(cuser.username) < 2)
    getdata(2, 0, "綽號暱稱：", cuser.username, 24, DOECHO, 0);

  for (ptr = cuser.username; *ptr; ptr++)
  {
    if (*ptr == 9)              /* TAB convert */
      *ptr == ' ';
  }

  while (strlen(cuser.realname) < 4)
    getdata(4, 0, "真實姓名：", cuser.realname, 20, DOECHO, 0);

  while (strlen(cuser.address) < 8)
    getdata(6, 0, "聯絡地址：", cuser.address, 50, DOECHO, 0);
  
  if (!strchr(cuser.email, '@'))
  {
    bell();
    move(b_lines - 4, 0);
    prints("\
※ 為了您的權益，請填寫真實的 E-mail address， 以資確認閣下身份，\n\
   格式為 [44muser@domain_name[0m 或 [44muser@\\[ip_number\\][0m。\n\n\
※ 如果您真的沒有 E-mail，請直接按 [return] 即可。");

    do
    {
      getdata(8, 0, "電子信箱：", cuser.email, 50, DOECHO, 0);
      if (!cuser.email[0])
        sprintf(cuser.email, "%s%s", cuser.userid, str_mail_address);
    } while (!strchr(cuser.email, '@'));

#ifdef  EMAIL_JUSTIFY
    mail_justify(cuser);
#endif
  }

  while (cuser.month > 12 || cuser.month < 1 ||
    cuser.day > 31 || cuser.day < 1 || cuser.year > 90 || cuser.year < 40)
  {
    int len;
    sprintf(genbuf, "%02i/%02i/%02i",
    cuser.month, cuser.day, cuser.year);
    len = getdata(10, 0, "生日 月月/日日/西元：", genbuf, 9, DOECHO, 0);
    if (len && len != 8)
      continue;
    if (!len)
      continue;
    else if (len == 8)
    {
      cuser.month = (genbuf[0] - '0') * 10 + (genbuf[1] - '0');
      cuser.day   = (genbuf[3] - '0') * 10 + (genbuf[4] - '0');
      cuser.year  = (genbuf[6] - '0') * 10 + (genbuf[7] - '0');
    }
    else
      continue;
  }
  
/* MH */
  while (cuser.sex >= MAX_SEXS){
    if(HAS_PERM(PERM_SYSOP))
    {
      strcpy(genbuf,
        "性別 (1)葛格 (2)姐接 (3)底迪 (4)美眉 (5)薯叔 (6)阿姨 (7)植物 (8)礦物"
        "\n     (9)博格人 (10)瓦肯人 (11)楚爾人 (12)克林貢人 (13)企業號"
        "\n     (14)Ada Augusta Byron"
        "[?]：");
    }
    else
    {
      strcpy(genbuf,
        "性別 (1)葛格 (2)姐接 (3)底迪 (4)美眉 (5)薯叔 (6)阿姨 (7)植物 (8)礦物"
        "[?]：");
    }
    getdata(12, 0, genbuf, genbuf, 3, DOECHO, 0);
/*    if (genbuf[0] >= '1' && genbuf[0] <= '9')
      cuser.sex = genbuf[0] - '1';*/
    {
      int mhtmp1;
      
      mhtmp1 = atoi(genbuf);
      if(mhtmp1 >= 1 && mhtmp1 <= MAX_SEXS)
        cuser.sex = mhtmp1 - 1;
    }
/*    */      
  }

  cuser.userlevel |= PERM_DEFAULT;
  if (!HAS_PERM(PERM_SYSOP) && !(cuser.userlevel & PERM_LOGINOK))
  {
    /* 回覆過身份認證信函，或曾經 E-mail post 過 */

    setuserfile(genbuf, "email");
    if (dashf(genbuf))
    {
/*
Leeym
*/
      cuser.userlevel |= ( PERM_POST | PERM_LOGINOK );
        /* 關於權限各站請依自己規定.蔽站採嚴格認證.未確認不得 post */
/*
comment out by woju (already done by mailpost)
      strcpy(cuser.justify, cuser.email);
      改進原先 emailreply 確認後確認資料仍空白
*/
      unlink(genbuf);
        /* 身份確認成功後發一封信告知已完成確認 */
        {
          fileheader mhdr;
          char title[128], buf1[80];
          FILE* fp;
          sethomepath(buf1, cuser.userid);
          stampfile(buf1, &mhdr);
          strcpy(mhdr.owner, "站長");
          strncpy(mhdr.title, "[註冊成功\]", TTLEN);
          mhdr.savemode = 0;
          mhdr.filemode = 0;
          sethomedir(title, cuser.userid);
          append_record(title, &mhdr, sizeof(mhdr));
          Link("etc/registered", buf1);
        }
    }

#ifdef  STRICT
    else
    {
      cuser.userlevel &= ~PERM_POST;
      more("etc/justify", YEA);
    }
#endif
  }

#ifdef  NEWUSER_LIMIT
  /*if (cuser.lastlogin - cuser.firstlogin < 3 * 86400 && ...)*/
  if (!(cuser.userlevel & PERM_LOGINOK) && !HAS_PERM(PERM_SYSOP))
  {
    if (cuser.lastlogin - cuser.firstlogin < 3 * 86400)
      cuser.userlevel &= ~PERM_POST;
    more("etc/newuser", YEA);
  }
#endif

  if (HAS_PERM(PERM_DENYPOST) && !HAS_PERM(PERM_SYSOP))
    cuser.userlevel &= ~PERM_POST;
}
