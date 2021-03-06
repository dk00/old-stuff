/*-------------------------------------------------------*/
/* user.c       ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* author : opus.bbs@bbs.cs.nthu.edu.tw                  */
/* target : user configurable setting routines           */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"

extern int numboards;
extern boardheader *bcache;
extern void resolve_boards();

/* MH */
char *sex[MAX_SEXS] = { MSG_BIG_BOY, MSG_BIG_GIRL, MSG_LITTLE_BOY, MSG_LITTLE_GIRL,
                 MSG_MAN, MSG_WOMAN, MSG_PLANT, MSG_MIME, MSG_BORG, MSG_VULCAN,
                 MSG_TRILL, MSG_KLINGON, MSG_ENTERPRISE, MSG_ADA };
/*    */

void
user_display(u, real)
  userec *u;
{
  int diff;
  char genbuf[200];

  clrtobot();
  prints(
    "代號        ：%s\n"
    "暱稱        ：%s\n"
    "真實姓名    ：%s\n"
    "居住住址    ：%s\n"
    "電子郵件信箱：%s\n"
    "性別        ：%s\n"
    "生日        ：%02i/%02i/%02i\n",
    u->userid,
    u->username,
    u->realname,
    u->address,
    u->email,
    sex[(u->sex < sizeof(sex) / sizeof(*sex)) ? u->sex: 0],
    u->month, u->day, u->year);

  prints(/*"終端機形態  ：%s\n"*/
    "註冊日期    ：%s",
    /*u->termtype,*/
    ctime(&u->firstlogin));

  prints("最近光臨日期：%s", ctime(&u->lastlogin));

  if (real)
    prints("最近光臨機器：%s\n", u->lasthost);

  prints("上站次數    ：%d 次\n", u->numlogins);

  prints("文章數目    ：%d 篇\n", u->numposts);

  sethomedir(genbuf, u->userid);
  prints("私人信箱    ：%d 封\n", get_num_records(genbuf, sizeof(fileheader)));

  if (real)
  {
    strcpy(genbuf, "bTCPRp#@XWBA#VS");
    for (diff = 0; diff < 15; diff++)
      if (!(u->userlevel & (1 << diff)))
        genbuf[diff] = '-';
    prints("認證資料    ：%s\n使用者權限  ：%s\n", u->justify, genbuf);
  }
  else
  {
    diff = (time(0) - login_start_time) / 60;
    prints("停留期間    ：%d 小時 %2d 分\n", diff / 60, diff % 60);
  }

  /* Thor: 想看看這個 user 是那些版的版主 */

  if (u->userlevel >= PERM_BM)
  {
    int i, len, ch;
    boardheader *bhdr;
    char *list;

    resolve_boards();

    len = strlen(u->userid);

    outs("擔任板主    ：");

    for (i = 0, bhdr = bcache; i < numboards; i++, bhdr++)
    {
      list = bhdr->BM;
      ch = list[0];
      if ((ch > ' ') && (ch < 128))
      {
        do
        {
          if (!ci_strncmp(list, u->userid, len))
          {
            ch = list[len];
            if ((ch == 0) || (ch == '/'))
            {
              outs(bhdr->brdname);
              outc(' ');
              break;
            }
          }
          while (ch = *list++)
            if (ch == '/')
              break;
        } while (ch);
      }
    }
    outc('\n');
  }

  outs((u->userlevel & PERM_LOGINOK) ?
    "\n您的註冊程序已經完成，歡迎加入本站" :
    "\n如果要提昇權限，請參考本站公佈欄辦理註冊");

#ifdef  NEWUSER_LIMIT
  if ((u->lastlogin - u->firstlogin < 3 * 86400) && !HAS_PERM(PERM_POST))
    outs("\n新手上路，三天後開放權限");
#endif
}

/* MH */
void
mh_uinfo_query(u, real, unum)
  userec *u;
{
  userec x;
  register int i, fail, mail_changed;
  char ans[4], buf[STRLEN];
  char genbuf[200];

  char *genpasswd();


  fail = mail_changed = 0;

  memcpy(&x, u, sizeof(userec));
  getdata(b_lines - 1, 0, real ?
    "(1)修改資料 (2)設定密碼 (3)設定權限 (4)清除帳號 (5)改ID [0]結束 " :
    "請選擇 (1)修改資料 (2)設定密碼 ==> [0]結束 ",
    ans, 3, DOECHO, 0);

  if (ans[0] > '2' && !real)
  {
    ans[0] = '0';
  }

  if (ans[0] == '1' || ans[0] == '3')
  {
    clear();
    i = 2;
    move(i++, 0);
    outs(msg_uid);
    outs(x.userid);
  }

  switch (ans[0])
  {
  case '1':
    move(0, 0);
    outs("請逐項修改。");

    {
      int sex;
      struct tm birthday;
      int numlogins;
      int numposts;
      struct mh_field setu_form[] =
      {{MH_FIELD_STRING, (void *)x.username, MH_FIELD_USEDEFAULT, 24, "暱稱：", 3, 0, 3, 6, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.realname, MH_FIELD_USEDEFAULT, 20, "真實姓名：", 4, 0, 4, 10, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.address, MH_FIELD_USEDEFAULT, 50, "居住地址：", 5, 0, 5, 10, "", NULL, -1},
       {MH_FIELD_CHOICE, (void *)&sex, 0, 4, "性別 (1)葛格 (2)姐接 (3)底迪 (4)美眉\n"
                                             "     (5)薯叔 (6)阿姨 (7)植物 (8)礦物 [%2d]：", 6, 0, 7, 43, "", NULL, -1},
       {MH_FIELD_DATE, (void *)&birthday, MH_FIELD_USEDEFAULT, 11, "生日：", 8, 0, 8, 6, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.email, MH_FIELD_USEDEFAULT, 50, "電子信箱(*寄認證信用*)：", 9, 0, 9, 24, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.justify, MH_FIELD_USEDEFAULT, 44, "認證資料：", 10, 0, 10, 10, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.lasthost, MH_FIELD_USEDEFAULT, 16, "最近光臨機器：", 11, 0, 11, 14, "", NULL, -1},
       {MH_FIELD_NUM, (void *)&numlogins, MH_FIELD_USEDEFAULT, 10, "上線次數：", 12, 0, 12, 10, "", NULL, -1},
       {MH_FIELD_NUM, (void *)&numposts, MH_FIELD_USEDEFAULT, 10, "文章數目：", 13, 0, 13, 10, "", NULL, -1}
      };
      
      sex = x.sex;
      birthday.tm_year = x.year;
      birthday.tm_mon = x.month - 1;
      birthday.tm_mday = x.day;
      numlogins = x.numlogins;
      numposts = x.numposts;
      mh_form(((real) ? 10 : 6), setu_form, 3);
      for(i = 0; i < 5; i ++)
      {
        move(t_lines - i - 2, 0);
        clrtoeol();
      }
      x.sex = sex;
      x.year = birthday.tm_year;
      x.month = birthday.tm_mon + 1;
      x.day = birthday.tm_mday;
      x.numlogins = numlogins;
      x.numposts = numposts;
    }

    break;

  case '2':
    i = 19;
    if (!real)
    {
      if (!getdata(i++, 0, "請輸入原密碼：", buf, PASSLEN, NOECHO, 0) ||
        !checkpasswd(u->passwd, buf))
      {
        outs("\n\n您輸入的密碼不正確\n");
        fail++;
        break;
      }
    }

    if (!getdata(i++, 0, "請設定新密碼：", buf, PASSLEN, NOECHO, 0))
    {
      outs("\n\n密碼設定取消, 繼續使用舊密碼\n");
      fail++;
      break;
    }
    strncpy(genbuf, buf, PASSLEN);

    getdata(i++, 0, "請檢查新密碼：", buf, PASSLEN, NOECHO, 0);
    if (strncmp(buf, genbuf, PASSLEN))
    {
      outs("\n\n新密碼確認失敗, 無法設定新密碼\n");
      fail++;
      break;
    }
    buf[8] = '\0';
    strncpy(x.passwd, genpasswd(buf), PASSLEN);
    break;

  case '3':
    i = setperms(x.userlevel);
    if (i == x.userlevel)
      fail++;
    else
      x.userlevel = i;
    break;

  case '4':
    i = QUIT;
    break;

  case '5':
    if (getdata(b_lines - 3, 0, "新的使用者代號：", genbuf, IDLEN + 1, DOECHO, 0))
    {
      if (searchuser(genbuf))
      {
        outs("錯誤! 已經有同樣 ID 的使用者");
        fail++;
      }
      else
      {
        strcpy(x.userid, genbuf);
      }
    }
    break;

  default:
    return;
  }

  if (fail)
  {
    pressanykey();
    return;
  }

  getdata(b_lines - 1, 0, msg_sure_ny, ans, 3, LCECHO, 0);
  if (*ans == 'y')
  {
    if (strcmp(u->userid, x.userid))
    {
      char src[STRLEN], dst[STRLEN];

      sethomepath(src, u->userid);
      sethomepath(dst, x.userid);
      sweep(u->userid);
      Rename(src, dst);
      setuserid(unum, x.userid);
    }
    memcpy(u, &x, sizeof(x));
    if (mail_changed)
    {

#ifdef  EMAIL_JUSTIFY
      x.userlevel &= ~PERM_LOGINOK;
      mail_justify(x);
#endif
    }

    if (i == QUIT)
    {
      char src[STRLEN], dst[STRLEN];

      sprintf(src, "home/%s", x.userid);
      sprintf(dst, "tmp/%s", x.userid);
      sweep(x.userid);
      if (Rename(src, dst))
      {
        sprintf(genbuf, "/bin/rm -fr %s", src);
        system(genbuf);
      }
/*
woju
*/
      log_usies("KILL", x.userid);
      x.userid[0] = '\0';
      setuserid(unum, x.userid);
    }
    else
       log_usies("SetUser", x.userid);
    substitute_record(fn_passwd, &x, sizeof(x), unum);
  }
}
/*    */

void
uinfo_query(u, real, unum)
  userec *u;
{
  userec x;
  register int i, fail, mail_changed;
  char ans[4], buf[STRLEN];
  char genbuf[200];

  char *genpasswd();


  fail = mail_changed = 0;

  memcpy(&x, u, sizeof(userec));
  getdata(b_lines - 1, 0, real ?
    "(1)修改資料 (2)設定密碼 (3)設定權限 (4)清除帳號 (5)改ID [0]結束 " :
    "請選擇 (1)修改資料 (2)設定密碼 ==> [0]結束 ",
    ans, 3, DOECHO, 0);

  if (ans[0] > '2' && !real)
  {
    ans[0] = '0';
  }

  if (ans[0] == '1' || ans[0] == '3')
  {
    clear();
    i = 2;
    move(i++, 0);
    outs(msg_uid);
    outs(x.userid);
  }

  switch (ans[0])
  {
  case '1':
    move(0, 0);
    outs("請逐項修改。");

    if (getdata(i++, 0, "暱稱：", buf, 24, DOECHO, u->username))
      strcpy(x.username, buf);

/* Tzu  已認證不能亂改資料 */
    if(!HAS_PERM(PERM_LOGINOK) || HAS_PERM(PERM_ACCOUNTS))
    {
      if (getdata(i++, 0, "真實姓名：", buf, 20, DOECHO, u->realname))
        strcpy(x.realname, buf);

      if (getdata(i++, 0,  "居住地址：", buf, 50, DOECHO, u->address))
        strcpy(x.address, buf);
    }
    else
    {
      outs("真實姓名： [7m若要更新本項資料，請重填註冊單！[m\n");
      outs("居住地址： [7m若要更新本項資料，請重填註冊單！[m\n");
      i += 2;
    }
/*     */

/* MH */
    if(HAS_PERM(PERM_SYSOP))
    {
      sprintf(genbuf,
        "性別 (1)葛格 (2)姐接 (3)底迪 (4)美眉 (5)薯叔 (6)阿姨 (7)植物 (8)礦物"
        "\n     (9)博格人 (10)瓦肯人 (11)楚爾人 (12)克林貢人 (13)企業號"
        "\n     (14)Ada Augusta Byron"
        "[%i]：", u->sex + 1);
    }
    else
    {
      sprintf(genbuf,
        "性別 (1)葛格 (2)姐接 (3)底迪 (4)美眉 (5)薯叔 (6)阿姨 (7)植物 (8)礦物"
        "[%i]：", u->sex + 1);
    }
    getdata(i++, 0, genbuf, buf, 3, DOECHO, 0);
    if(HAS_PERM(PERM_SYSOP))
      i += 2;
/*    if (buf[0] >= '1' && buf[0] <= '9')
      x.sex = buf[0] - '1';
    else
      x.sex = u->sex;*/
    {
      int mhtmp1;

      mhtmp1 = atoi(buf);
      if(mhtmp1 >= 1 && mhtmp1 <= MAX_SEXS)
        x.sex = mhtmp1 - 1;
      else
        x.sex = u->sex;
    }
/*    */

    while (1)
    {
      int len;

      sprintf(genbuf, "%02i/%02i/%02i",
        u->month, u->day, u->year);
      len = getdata(i, 0, "生日 月月/日日/西元：", buf, 9, DOECHO, genbuf);
      if (len && len != 8)
        continue;
      if (!len)
      {
        x.month = u->month;
        x.day   = u->day;
        x.year  = u->year;
      }
      else if (len == 8)
      {
        x.month = (buf[0] - '0') * 10 + (buf[1] - '0');
        x.day   = (buf[3] - '0') * 10 + (buf[4] - '0');
        x.year  = (buf[6] - '0') * 10 + (buf[7] - '0');
      }
      else
        continue;
      if (!real && (x.month > 12 || x.month < 1 ||
        x.day > 31 || x.day < 1 || x.year > 90 || x.year < 40))
        continue;
      i++;
      break;
    }

    getdata(i++, 0, "電子信箱(*寄認證信用*)：", buf, 50, DOECHO, u->email);
    if (*buf && strcmp(buf, u->email)) {
      strcpy(x.email, buf);
      mail_changed = 1 - real;
    }
    else
       strcpy(x.email, u->email);

/*
    sprintf(genbuf, "終端機形態 [%s]：", u->termtype);
    if (getdata(i++, 0, genbuf, buf, 8, DOECHO, u->termtype))
      strcpy(x.termtype, buf);
*/
    if (real)
    {
      if (getdata(i++, 0, "認證資料：", buf, 44, DOECHO, u->justify))
        strcpy(x.justify, buf);

      if (getdata(i++, 0, "最近光臨機器：", buf, 16, DOECHO, u->lasthost))
        strcpy(x.lasthost, buf);

      sprintf(genbuf, "%d", u->numlogins);
      if (getdata(i++, 0, "上線次數：", buf, 10, DOECHO, genbuf))
        if ((fail = atoi(buf)) >= 0)
          x.numlogins = fail;

      sprintf(genbuf, "%d", u->numposts);
      if (getdata(i++, 0, "文章數目：", buf, 10, DOECHO, genbuf))
        if ((fail = atoi(buf)) >= 0)
          x.numposts = fail;

      fail = 0;
    }
    break;

  case '2':
    i = 19;
    if (!real)
    {
      if (!getdata(i++, 0, "請輸入原密碼：", buf, PASSLEN, NOECHO, 0) ||
        !checkpasswd(u->passwd, buf))
      {
        outs("\n\n您輸入的密碼不正確\n");
        fail++;
        break;
      }
    }

    if (!getdata(i++, 0, "請設定新密碼：", buf, PASSLEN, NOECHO, 0))
    {
      outs("\n\n密碼設定取消, 繼續使用舊密碼\n");
      fail++;
      break;
    }
    strncpy(genbuf, buf, PASSLEN);

    getdata(i++, 0, "請檢查新密碼：", buf, PASSLEN, NOECHO, 0);
    if (strncmp(buf, genbuf, PASSLEN))
    {
      outs("\n\n新密碼確認失敗, 無法設定新密碼\n");
      fail++;
      break;
    }
    buf[8] = '\0';
    strncpy(x.passwd, genpasswd(buf), PASSLEN);
    break;

  case '3':
    i = setperms(x.userlevel);
    if (i == x.userlevel)
      fail++;
    else
      x.userlevel = i;
    break;

  case '4':
    i = QUIT;
    break;

  case '5':
    if (getdata(b_lines - 3, 0, "新的使用者代號：", genbuf, IDLEN + 1, DOECHO, 0))
    {
      if (searchuser(genbuf))
      {
        outs("錯誤! 已經有同樣 ID 的使用者");
        fail++;
      }
      else
      {
        strcpy(x.userid, genbuf);
      }
    }
    break;

  default:
    return;
  }

  if (fail)
  {
    pressanykey();
    return;
  }

  getdata(b_lines - 1, 0, msg_sure_ny, ans, 3, LCECHO, 0);
  if (*ans == 'y')
  {
    if (strcmp(u->userid, x.userid))
    {
      char src[STRLEN], dst[STRLEN];

      sethomepath(src, u->userid);
      sethomepath(dst, x.userid);
      sweep(u->userid);
      Rename(src, dst);
      setuserid(unum, x.userid);
    }
    memcpy(u, &x, sizeof(x));
    if (mail_changed)
    {

#ifdef  EMAIL_JUSTIFY
      x.userlevel &= ~PERM_LOGINOK;
      mail_justify(x);
#endif
    }

    if (i == QUIT)
    {
      char src[STRLEN], dst[STRLEN];

      sprintf(src, "home/%s", x.userid);
      sprintf(dst, "tmp/%s", x.userid);
      sweep(x.userid);
      if (Rename(src, dst))
      {
        sprintf(genbuf, "/bin/rm -fr %s", src);
        system(genbuf);
      }
/*
woju
*/
      log_usies("KILL", x.userid);
      x.userid[0] = '\0';
      setuserid(unum, x.userid);
    }
    else
       log_usies("SetUser", x.userid);
    substitute_record(fn_passwd, &x, sizeof(x), unum);
  }
}


int
u_info()
{
  move(2, 0);
  user_display(&cuser, 0);
#ifndef MH_USEFORM
  uinfo_query(&cuser, 0, usernum);
#else
  mh_uinfo_query(&cuser, 0, usernum);
#endif
  strcpy(currutmp->realname, cuser.realname);
  strcpy(currutmp->username, cuser.username);
  return 0;
}


int
u_ansi()
{
  showansi ^= 1;
  cuser.uflag ^= COLOR_FLAG;
  outs(reset_color);
  return 0;
}


int
u_cloak()
{
  outs((currutmp->invisible ^= 1) ? MSG_CLOAKED : MSG_UNCLOAK);
  return XEASY;
}


int
u_lock()
{
  char genbuf[PASSLEN];

  log_usies("LOCK ", "screen");

  do
  {
    getdata(b_lines - 1, 0, "▲ 請輸入密碼，以解除螢幕鎖定：",
      genbuf, PASSLEN, NOECHO, 0);
  } while (!checkpasswd(cuser.passwd, genbuf));

  return FULLUPDATE;
}


#ifdef  HAVE_SUICIDE
int
u_kill()
{
  char genbuf[200];

  getdata(b_lines - 1, 0, "▲ 如果確定要清除您的帳號，請輸入密碼：",
    genbuf, PASSLEN, NOECHO, 0);

  if (*genbuf == '\0' || !checkpasswd(cuser.passwd, genbuf))
  {
    outmsg("您輸入的密碼不正確，帳號未清除。");
    igetch();
    return FULLUPDATE;
  }

#ifdef  HAVE_REPORT
  report("suicide");
#endif

  sprintf(genbuf, "#%d %s:%s %d %d",
    usernum, cuser.realname, cuser.username, cuser.numlogins, cuser.numposts);
  log_usies("SUCI ", genbuf);

  sprintf(genbuf, "%s %s", fromhost, Cdate(&(cuser.firstlogin)));
  log_usies("SUCI ", genbuf);

  sethomepath(genbuf, cuser.userid);
  sweep(cuser.userid);
  if (Rename(genbuf, "tmp"))
  {
/*
woju
*/
    sprintf(genbuf, "(cd home; tar cvf SUCI_%s.tar %s); /bin/rm -fr home/%s",
            cuser.userid, cuser.userid, cuser.userid);
    system(genbuf);
  }
  cuser.userid[0] = '\0';
  substitute_record(fn_passwd, &cuser, sizeof(cuser), usernum);
  setuserid(usernum, cuser.userid);
  purge_utmp(currutmp);

  clear();
  outs("親愛的朋友，青山長在，綠水長流，咱們後會有期吧！");
  pressanykey();
  sleep(1);
  reset_tty();
  exit(0);
}
#endif


void
showplans(uid)
  char *uid;
{
  FILE *planfile;
  int i;
  char genbuf[256];

  sethomefile(genbuf, uid, fn_plans);
  if (planfile = fopen(genbuf, "r"))
  {
    prints("%s 的名片:\n", uid);
    i = 0;
    while (i++ < MAXQUERYLINES && fgets(genbuf, 256, planfile))
    {
/* MH */
/* 用 mhsin_prints (in mhsin.c) 取代 kaede_prints */
/*      outs(kaede_prints(genbuf));*/
      outs(mhsin_prints(genbuf, 255));
/*    */
    }
    fclose(planfile);
  }
  else
    prints("%s 目前沒有名片", uid);
}


int
showsignature(fname)
  char *fname;
{
  FILE *fp;
  char buf[256];
  int i, j;
  char ch;

  clear();
  move(2, 0);
  setuserfile(fname, "sig.0");
  j = strlen(fname) - 1;

  for (ch = '1'; ch <= '9'; ch++)
  {
    fname[j] = ch;
    if (fp = fopen(fname, "r"))
    {
      prints("[36m【 簽名檔.%c 】[m\n", ch);
      for (i = 0; i++ < MAXSIGLINES && fgets(buf, 256, fp); outs(buf));
      fclose(fp);
    }
  }
  return j;
}

/* MH */
#define MH_SHOWSIG_USE_SCROLL
#undef MH_SHOWSIG_USE_SCROLL_DEBUG

int mh_showsignature(char msg[])
{
  int sig_files[MAXSIGFILES];
  int lines[MAXSIGFILES];
  int sig_file_num;
  int st, end;
  int refresh_flag;
  int i, j, k;
  int lused;
  char buf[20], fname[200];
  char bufs[MAXSIGFILES][MAXSIGLINES][256];
  char ans[4];
  FILE *fp;

  sig_file_num = 0;
  for(i = 1; i <= MAXSIGFILES; i ++)
  {
    sprintf(buf, "sig.%d", i);
    setuserfile(fname, buf);
    if((fp = fopen(fname, "r")) != NULL)
    {
      sig_files[sig_file_num] = i;
      for(j = 0; j < MAXSIGLINES && fgets(bufs[sig_file_num][j], 255, fp);)
        j ++;
      fclose(fp);
      if(j > MAXSIGLINES)
        j --;
      lines[sig_file_num] = j;
      sig_file_num ++;
    }
  }

  refresh_flag = YEA;
  st = 0;
  do
  {
    if(st >= sig_file_num)
    {
      st = sig_file_num - 1;
      refresh_flag = YEA;
    }
    if(st < 0)
      st = 0;

    if(refresh_flag)
    {
      refresh_flag = NA;
      lused = 0;
      clear();
      move(3, 0);
      for(i = st; i < sig_file_num; i ++)
      {
        j = lines[i];
#ifdef SHOW_IF_ALL_VISIBLE
        if(j + lused + 2 <= t_lines - 3)
        {
          prints("[36m【 簽名檔.%d 】[m\n", sig_files[i]);
          for(k = 0; k < MAXSIGLINES && k < j; k ++)
            outs(mhsin_prints(bufs[i][k], 255));
          lused += (j + 1);
        }
        else
          break;
#else
        prints("[36m【 簽名檔.%d 】[m\n", sig_files[i]);
        for(k = 0; k < MAXSIGLINES && k < j && k + lused + 2 <= t_lines - 3; k ++)
          outs(mhsin_prints(bufs[i][k], 255));
        if(j + lused + 2 > t_lines - 3)
          break;
        lused += (j + 1);
#endif
      }
      end = i;
#ifndef MH_SHOWSIG_USE_SCROLL_DEBUG
      my_outmsg_row("Ctrl-U: 向上捲動, Ctrl-D: 向下捲動", 1);
#else
      move(1, 0);
      prints("Ctrl-U: 向上捲動, Ctrl-D: 向下捲動 %d %d %d", st, end, lused);
#endif
    }

    i = mh_getdata(0, 0, msg, ans, 4, LCECHO, 0, MH_GETDATA_UD, NULL);
    if(i >= 0)
    {
      return ans[0];
    }
    else if(i == MH_DOWN)
    {
      if(end < sig_file_num)
      {
#ifdef MH_SHOWSIG_USE_SCROLL
        move(0, 0);
        clrtoeol();
        move(1, 0);
        clrtoeol();
        move(2, 0);
        clrtoeol();
        for(i = 0; i < lines[st] + 1; i ++)
        {
          move(i + 3, 0);
          clrtoeol();
        }
        refresh();
        for(i = 0; i < lines[st] + 1; i ++)
          scroll();
        st ++;
        lused = 0;
        for(i = st; i < end; i ++)
          lused += (lines[i] + 1);
        move(1, 0);
        prints("%d", lused);
        move(lused + 3, 0);
        for(; i < sig_file_num; i ++)
        {
          j = lines[i];
          prints("[36m【 簽名檔.%d 】[m\n", sig_files[i]);
          for(k = 0; k < MAXSIGLINES && k < j && k + lused + 2 <= t_lines - 3; k ++)
            outs(mhsin_prints(bufs[i][k], 255));
          if(j + lused + 2 > t_lines - 3)
            break;
          lused += (j + 1);
        }
        end = i;
        move(1, 0);
#ifndef MH_SHOWSIG_USE_SCROLL_DEBUG
        my_outmsg_row("Ctrl-U: 向上捲動, Ctrl-D: 向下捲動", 1);
#else
        prints("Ctrl-U: 向上捲動, Ctrl-D: 向下捲動 %d %d %d", st, end, lused);
#endif
#else
        st ++;
        refresh_flag = YEA;
#endif
      }
    }
    else if(i == MH_UP)
    {
      if(st > 0)
      {
#ifdef MH_SHOWSIG_USE_SCROLL
        move(0, 0);
        clrtoeol();
        move(1, 0);
        clrtoeol();
        move(2, 0);
        clrtoeol();
        refresh();
        for(i = 0; i < lines[st - 1] + 1; i ++)
          rscroll();
        st --;
        move(3, 0);
        prints("[36m【 簽名檔.%d 】[m\n", sig_files[st]);
        for(i = 0; i < lines[st]; i ++)
          outs(mhsin_prints(bufs[st][i], 255));
        lused = 0;
        for(i = st; i < sig_file_num; i ++)
        {
          j = lines[i];
          if(j + lused + 2 > t_lines - 3)
            break;
          lused += (j + 1);
        }
        end = i;
        move(1, 0);
#if 1
        my_outmsg_row("Ctrl-U: 向上捲動, Ctrl-D: 向下捲動", 1);
#else
        prints("Ctrl-U: 向上捲動, Ctrl-D: 向下捲動 %d %d %d", st, end, lused);
#endif
#else
        st --;
        refresh_flag = YEA;
#endif
      }
    }    
  } while(1);
  return 0;
}

int mh_u_editsig(void)
{
  int i, j, k;
  FILE *fp;
  char buf[20], fname[200];
  
  i = mh_showsignature("簽名檔 (E)編輯 (D)刪除 (Q)取消？[Q] ");
  if(i == 'd' || i == 'e')
  {
    if (getdata(0, 0, "請選擇簽名檔(1-9)？[1] ", buf, 4, DOECHO, 0) >= 0)
    {
      j = atoi(buf);
      if(buf[0] == 0)
        j = 1;
      if(j >= 1 && j <= MAXSIGFILES)
      {
        sprintf(buf, "sig.%d", j);
        setuserfile(fname, buf);
        if(i == 'd')
        {
          unlink(fname);
          clrtoeol();
          outs(msg_del_ok);
        }
        else if(i == 'e')
        {
          setutmpmode(EDITSIG);
          k = vedit(fname, NA);
          if (!k)
            outs("簽名檔更新完畢");
        }
      }
    }
    pressanykey();
  }
  return 0;
}
/*    */

int
u_editsig()
{
  int aborted;
  char ans[4];
  int j;
  char genbuf[200];

  j = showsignature(genbuf);

  getdata(0, 0, "簽名檔 (E)編輯 (D)刪除 (Q)取消？[Q] ", ans, 4, LCECHO, 0);

  aborted = 0;
  if (ans[0] == 'd')
    aborted = 1;
  if (ans[0] == 'e')
    aborted = 2;

  if (aborted)
  {
    if (!getdata(1, 0, "請選擇簽名檔(1-9)？[1] ", ans, 4, DOECHO, 0))
      ans[0] = '1';
    if (ans[0] >= '1' && ans[0] <= '9')
    {
      genbuf[j] = ans[0];
      if (aborted == 1)
      {
        unlink(genbuf);
        outs(msg_del_ok);
      }
      else
      {
        setutmpmode(EDITSIG);
        aborted = vedit(genbuf, NA);
        if (!aborted)
          outs("簽名檔更新完畢");
      }
    }
    pressanykey();
  }
  return 0;
}

int
u_editplan()
{
  char genbuf[200];

  getdata(b_lines - 1, 0, "名片 (D)刪除 (E)編輯 [Q]取消？[Q] ", genbuf, 3, LCECHO, 0);

  if (genbuf[0] == 'e')
  {
    int aborted;

    setutmpmode(EDITPLAN);
    setuserfile(genbuf, fn_plans);
    aborted = vedit(genbuf, NA);
    if (!aborted)
      outs("名片更新完畢");
    pressanykey();
    return 0;
  }
  else if (genbuf[0] == 'd')
  {
    setuserfile(genbuf, fn_plans);
    unlink(genbuf);
    outmsg("名片刪除完畢");
  }
  return 0;
}

/* MH */
int
mh_u_register()
{
  char rname[20], addr[50];
  char phone[20], career[40], email[50];
  char ans[3], *ptr;
  FILE *fn;
  time_t now;
  char genbuf[200];
  struct mh_field reg_form[] =
  {{MH_FIELD_STRING, (void *)rname, MH_FIELD_USEDEFAULT, 20, "真實姓名(請用中文): ", 6, 0, 6, 20, "請確實填寫真實中文姓名", NULL, -1},
   {MH_FIELD_STRING, (void *)career, MH_FIELD_USEDEFAULT, 40, "服務單位(學校系/班級或單位職稱): ", 8, 0, 8, 33, "請填寫服務單位", NULL, -1},
   {MH_FIELD_STRING, (void *)addr, MH_FIELD_USEDEFAULT, 50, "目前住址(含寢室或門牌號碼): ", 10, 0, 10, 28, "請填寫住址", NULL, -1},
   {MH_FIELD_STRING, (void *)phone, MH_FIELD_USEDEFAULT, 20, "連絡電話(包括長途撥號區域碼): ", 12, 0, 12, 30, "", NULL, -1},
   {MH_FIELD_STRING, (void *)email, MH_FIELD_USEDEFAULT, 50, "E-Mail Address(身分認證用): ", 14, 0, 14, 28, "", NULL, -1}
  };

/*  if (cuser.userlevel & PERM_LOGINOK)
  {
    outs("您的身份確認已經完成，不需填寫申請表");
     return XEASY;
  }*/

  if (fn = fopen(fn_register, "r"))
  {
    while (fgets(genbuf, STRLEN, fn))
    {
      if (ptr = strchr(genbuf, '\n'))
        *ptr = '\0';
      if (strncmp(genbuf, "uid: ", 5) == 0 &&
        strcmp(genbuf + 5, cuser.userid) == 0)
      {
        fclose(fn);
        outs("您的註冊申請單尚在處理中，請耐心等候");
        return XEASY;
      }
    }
    fclose(fn);
  }

  if (cuser.userlevel & PERM_LOGINOK)
    strcpy(genbuf, "您的身份確認已經完成，要更新資料嗎(Y/N)？[N] ");
  else
    strcpy(genbuf, "您確定要填寫註冊單嗎(Y/N)？[N] ");

  getdata(b_lines - 1, 0, genbuf, ans, 3, LCECHO, 0);
  if (ans[0] != 'y')
    return FULLUPDATE;

  move(2, 0);
  clrtobot();
  strcpy(rname, cuser.realname);
  strcpy(addr, cuser.address);
  strcpy(email, cuser.email);
  career[0] = phone[0] = '\0';
  while (1)
  {
    clear();
    move(3, 0);
    prints("%s(%s) 您好，請據實填寫以下的資料:",
      cuser.userid, cuser.username);
    mh_form(5, reg_form, 3);
    getdata(b_lines - 5 - 1, 0, "以上資料是否正確(Y/N)？(Q)取消註冊 [N] ", ans, 3, LCECHO, 0);
    if (ans[0] == 'q')
      return 0;
    if (ans[0] == 'y')
      break;
  }
  strcpy(cuser.realname, rname);
  strcpy(cuser.address, addr);
  strcpy(cuser.email, email);
  if (fn = fopen(fn_register, "a"))
  {
    now = time(NULL);
    trim(career);
    trim(addr);
    trim(phone);
    fprintf(fn, "num: %d, %s", usernum, ctime(&now));
    fprintf(fn, "uid: %s\n", cuser.userid);
    fprintf(fn, "name: %s\n", rname);
    fprintf(fn, "career: %s\n", career);
    fprintf(fn, "addr: %s\n", addr);
    fprintf(fn, "phone: %s\n", phone);
    fprintf(fn, "email: %s\n", email);
    fprintf(fn, "----\n");
    fclose(fn);
  }
  return 0;
}
/*    */

int
u_register()
{
  char rname[20], addr[50];
  char phone[20], career[40], email[50];
  char ans[3], *ptr;
  FILE *fn;
  time_t now;
  char genbuf[200];

/*  if (cuser.userlevel & PERM_LOGINOK)
  {
    outs("您的身份確認已經完成，不需填寫申請表");
     return XEASY;
  }*/

  if (fn = fopen(fn_register, "r"))
  {
    while (fgets(genbuf, STRLEN, fn))
    {
      if (ptr = strchr(genbuf, '\n'))
        *ptr = '\0';
      if (strncmp(genbuf, "uid: ", 5) == 0 &&
        strcmp(genbuf + 5, cuser.userid) == 0)
      {
        fclose(fn);
        outs("您的註冊申請單尚在處理中，請耐心等候");
        return XEASY;
      }
    }
    fclose(fn);
  }

  if (cuser.userlevel & PERM_LOGINOK)
    strcpy(genbuf, "您的身份確認已經完成，要更新資料嗎(Y/N)？[N] ");
  else
    strcpy(genbuf, "您確定要填寫註冊單嗎(Y/N)？[N] ");

  getdata(b_lines - 1, 0, genbuf, ans, 3, LCECHO, 0);
  if (ans[0] != 'y')
    return FULLUPDATE;

  move(2, 0);
  clrtobot();
  strcpy(rname, cuser.realname);
  strcpy(addr, cuser.address);
  strcpy(email, cuser.email);
  career[0] = phone[0] = '\0';
  while (1)
  {
    clear();
    move(3, 0);
    prints("%s(%s) 您好，請據實填寫以下的資料:",
      cuser.userid, cuser.username);
    getdata(6, 0, "真實姓名(請用中文): ", rname, 20, DOECHO, rname);
    getdata(8, 0, "服務單位(學校系/班級或單位職稱): ", career, 40, DOECHO, career);
    getdata(10, 0,  "目前住址(含寢室或門牌號碼): ", addr, 50, DOECHO, addr);
    getdata(12, 0, "連絡電話(包括長途撥號區域碼): ", phone, 20, DOECHO, phone);
    getdata(14, 0, "E-Mail Address(身分認證用): ", email, 50, DOECHO, email);
    getdata(b_lines - 1, 0, "以上資料是否正確(Y/N)？(Q)取消註冊 [N] ", ans, 3, LCECHO, 0);
    if (ans[0] == 'q')
      return 0;
    if (ans[0] == 'y')
      break;
  }
  strcpy(cuser.realname, rname);
  strcpy(cuser.address, addr);
  strcpy(cuser.email, email);
  if (fn = fopen(fn_register, "a"))
  {
    now = time(NULL);
    trim(career);
    trim(addr);
    trim(phone);
    fprintf(fn, "num: %d, %s", usernum, ctime(&now));
    fprintf(fn, "uid: %s\n", cuser.userid);
    fprintf(fn, "name: %s\n", rname);
    fprintf(fn, "career: %s\n", career);
    fprintf(fn, "addr: %s\n", addr);
    fprintf(fn, "phone: %s\n", phone);
    fprintf(fn, "email: %s\n", email);
    fprintf(fn, "----\n");
    fclose(fn);
  }
  return 0;
}


/* --------------------------------------------- */
/* 列出所有註冊使用者                            */
/* --------------------------------------------- */


extern struct UCACHE *uidshm;
int usercounter, totalusers, showrealname;
ushort u_list_special;


static int
u_list_CB(uentp)
  userec *uentp;
{ static int i;
  char permstr[8], *ptr;
  register int level;

  if (uentp == NULL)
  {
    move(2, 0);
    clrtoeol();
    prints("[7m  使用者代號   %-25s   上站  文章  %s  最近光臨日期     [0m\n",

    showrealname ?
/*#if defined(REALINFO) && defined(ACTS_REALNAMES)*/
      "真實姓名" :
/*#else*/
      "綽號暱稱"
/*#endif*/

      ,HAS_PERM(PERM_SEEULEVELS) ? "等級" : "");
    i = 3;
    return 0;
  }
  if (uentp->userid[0] == '\0')
    return 0;
  if (uentp->userlevel < u_list_special)
    return 0;

  if (i == b_lines)
  {
    prints("[34;46m  已顯示 %d/%d 人(%d%%)  [31;47m  (Space)[30m 看下一頁  [31m(Q)[30m 離開  [0m",
      usercounter, totalusers, usercounter * 100 / totalusers);
    i = igetch();
    if (i == 'q' || i == 'Q')
      return QUIT;
    i = 3;
  }
  if (i == 3)
  {
    move(3, 0);
    clrtobot();
  }

  level = uentp->userlevel;
  strcpy(permstr, "----");
  if (level & PERM_SYSOP)
    permstr[0] = 'S';
  else if (level & PERM_ACCOUNTS)
    permstr[0] = 'A';
  else if (level & PERM_DENYPOST)
    permstr[0] = 'p';

  if (level & (PERM_BOARD))
    permstr[1] = 'B';
  else if (level & (PERM_BM))
    permstr[1] = 'b';

  if (level & (PERM_XEMPT))
    permstr[2] = 'X';
  else if (level & (PERM_LOGINOK))
    permstr[2] = 'R';

  if (level & (PERM_CLOAK | PERM_SEECLOAK))
    permstr[3] = 'C';

  ptr = (char *) Cdate(&uentp->lastlogin);
  ptr[18] = '\0';

   prints("%-14s %-27.27s%5d %5d  %s  %s\n",
    uentp->userid,
    showrealname ?    uentp->realname :    uentp->username
    ,uentp->numlogins, uentp->numposts,
    HAS_PERM(PERM_SEEULEVELS) ? permstr : "", ptr);
  usercounter++;
  i++;
  return 0;
}


int
u_list()
{
  char genbuf[3];

  setutmpmode(LAUSERS);
  showrealname = u_list_special = usercounter = 0;
  totalusers = uidshm->number;
  if (HAS_PERM(PERM_SEEULEVELS))
  {
    getdata(b_lines - 1, 0, "觀看 [1]特殊等級 (2)全部？[1] ", genbuf, 3, DOECHO, 0);
    if (genbuf[0] != '2')
      u_list_special = 32;
  }
  if (HAS_PERM(PERM_CHATROOM) || HAS_PERM(PERM_SYSOP))
  {
    getdata(b_lines - 1, 0, "顯示 [1]真實姓名 (2)暱稱？[1] ", genbuf, 3, DOECHO, 0);
    if (genbuf[0] != '2')
      showrealname = 1;
  }
  u_list_CB(NULL);
  if (apply_record(fn_passwd, u_list_CB, sizeof(userec)) == -1)
  {
    outs(msg_nobody);
    return XEASY;
  }
  move(b_lines, 0);
  clrtoeol();
  prints("[34;46m  已顯示 %d/%d 的使用者(系統容量無上限)  [31;47m  (請按任意鍵繼續)  [0m",
    usercounter, totalusers);
  igetkey();
  return 0;
}
