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
    "¥N¸¹        ¡G%s\n"
    "¼ÊºÙ        ¡G%s\n"
    "¯u¹ê©m¦W    ¡G%s\n"
    "©~¦í¦í§}    ¡G%s\n"
    "¹q¤l¶l¥ó«H½c¡G%s\n"
    "©Ê§O        ¡G%s\n"
    "¥Í¤é        ¡G%02i/%02i/%02i\n",
    u->userid,
    u->username,
    u->realname,
    u->address,
    u->email,
    sex[(u->sex < sizeof(sex) / sizeof(*sex)) ? u->sex: 0],
    u->month, u->day, u->year);

  prints(/*"²×ºÝ¾÷§ÎºA  ¡G%s\n"*/
    "µù¥U¤é´Á    ¡G%s",
    /*u->termtype,*/
    ctime(&u->firstlogin));

  prints("³Ìªñ¥úÁ{¤é´Á¡G%s", ctime(&u->lastlogin));

  if (real)
    prints("³Ìªñ¥úÁ{¾÷¾¹¡G%s\n", u->lasthost);

  prints("¤W¯¸¦¸¼Æ    ¡G%d ¦¸\n", u->numlogins);

  prints("¤å³¹¼Æ¥Ø    ¡G%d ½g\n", u->numposts);

  sethomedir(genbuf, u->userid);
  prints("¨p¤H«H½c    ¡G%d «Ê\n", get_num_records(genbuf, sizeof(fileheader)));

  if (real)
  {
    strcpy(genbuf, "bTCPRp#@XWBA#VS");
    for (diff = 0; diff < 15; diff++)
      if (!(u->userlevel & (1 << diff)))
        genbuf[diff] = '-';
    prints("»{ÃÒ¸ê®Æ    ¡G%s\n¨Ï¥ÎªÌÅv­­  ¡G%s\n", u->justify, genbuf);
  }
  else
  {
    diff = (time(0) - login_start_time) / 60;
    prints("°±¯d´Á¶¡    ¡G%d ¤p®É %2d ¤À\n", diff / 60, diff % 60);
  }

  /* Thor: ·Q¬Ý¬Ý³o­Ó user ¬O¨º¨Çª©ªºª©¥D */

  if (u->userlevel >= PERM_BM)
  {
    int i, len, ch;
    boardheader *bhdr;
    char *list;

    resolve_boards();

    len = strlen(u->userid);

    outs("¾á¥ôªO¥D    ¡G");

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
    "\n±zªºµù¥Uµ{§Ç¤w¸g§¹¦¨¡AÅwªï¥[¤J¥»¯¸" :
    "\n¦pªG­n´£ª@Åv­­¡A½Ð°Ñ¦Ò¥»¯¸¤½§GÄæ¿ì²zµù¥U");

#ifdef  NEWUSER_LIMIT
  if ((u->lastlogin - u->firstlogin < 3 * 86400) && !HAS_PERM(PERM_POST))
    outs("\n·s¤â¤W¸ô¡A¤T¤Ñ«á¶}©ñÅv­­");
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
    "(1)­×§ï¸ê®Æ (2)³]©w±K½X (3)³]©wÅv­­ (4)²M°£±b¸¹ (5)§ïID [0]µ²§ô " :
    "½Ð¿ï¾Ü (1)­×§ï¸ê®Æ (2)³]©w±K½X ==> [0]µ²§ô ",
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
    outs("½Ð³v¶µ­×§ï¡C");

    {
      int sex;
      struct tm birthday;
      int numlogins;
      int numposts;
      struct mh_field setu_form[] =
      {{MH_FIELD_STRING, (void *)x.username, MH_FIELD_USEDEFAULT, 24, "¼ÊºÙ¡G", 3, 0, 3, 6, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.realname, MH_FIELD_USEDEFAULT, 20, "¯u¹ê©m¦W¡G", 4, 0, 4, 10, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.address, MH_FIELD_USEDEFAULT, 50, "©~¦í¦a§}¡G", 5, 0, 5, 10, "", NULL, -1},
       {MH_FIELD_CHOICE, (void *)&sex, 0, 4, "©Ê§O (1)¸¯®æ (2)©j±µ (3)©³­} (4)¬ü¬Ü\n"
                                             "     (5)Á¦¨û (6)ªü«¼ (7)´Óª« (8)Äqª« [%2d]¡G", 6, 0, 7, 43, "", NULL, -1},
       {MH_FIELD_DATE, (void *)&birthday, MH_FIELD_USEDEFAULT, 11, "¥Í¤é¡G", 8, 0, 8, 6, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.email, MH_FIELD_USEDEFAULT, 50, "¹q¤l«H½c(*±H»{ÃÒ«H¥Î*)¡G", 9, 0, 9, 24, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.justify, MH_FIELD_USEDEFAULT, 44, "»{ÃÒ¸ê®Æ¡G", 10, 0, 10, 10, "", NULL, -1},
       {MH_FIELD_STRING, (void *)x.lasthost, MH_FIELD_USEDEFAULT, 16, "³Ìªñ¥úÁ{¾÷¾¹¡G", 11, 0, 11, 14, "", NULL, -1},
       {MH_FIELD_NUM, (void *)&numlogins, MH_FIELD_USEDEFAULT, 10, "¤W½u¦¸¼Æ¡G", 12, 0, 12, 10, "", NULL, -1},
       {MH_FIELD_NUM, (void *)&numposts, MH_FIELD_USEDEFAULT, 10, "¤å³¹¼Æ¥Ø¡G", 13, 0, 13, 10, "", NULL, -1}
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
      if (!getdata(i++, 0, "½Ð¿é¤J­ì±K½X¡G", buf, PASSLEN, NOECHO, 0) ||
        !checkpasswd(u->passwd, buf))
      {
        outs("\n\n±z¿é¤Jªº±K½X¤£¥¿½T\n");
        fail++;
        break;
      }
    }

    if (!getdata(i++, 0, "½Ð³]©w·s±K½X¡G", buf, PASSLEN, NOECHO, 0))
    {
      outs("\n\n±K½X³]©w¨ú®ø, Ä~Äò¨Ï¥ÎÂÂ±K½X\n");
      fail++;
      break;
    }
    strncpy(genbuf, buf, PASSLEN);

    getdata(i++, 0, "½ÐÀË¬d·s±K½X¡G", buf, PASSLEN, NOECHO, 0);
    if (strncmp(buf, genbuf, PASSLEN))
    {
      outs("\n\n·s±K½X½T»{¥¢±Ñ, µLªk³]©w·s±K½X\n");
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
    if (getdata(b_lines - 3, 0, "·sªº¨Ï¥ÎªÌ¥N¸¹¡G", genbuf, IDLEN + 1, DOECHO, 0))
    {
      if (searchuser(genbuf))
      {
        outs("¿ù»~! ¤w¸g¦³¦P¼Ë ID ªº¨Ï¥ÎªÌ");
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
    "(1)­×§ï¸ê®Æ (2)³]©w±K½X (3)³]©wÅv­­ (4)²M°£±b¸¹ (5)§ïID [0]µ²§ô " :
    "½Ð¿ï¾Ü (1)­×§ï¸ê®Æ (2)³]©w±K½X ==> [0]µ²§ô ",
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
    outs("½Ð³v¶µ­×§ï¡C");

    if (getdata(i++, 0, "¼ÊºÙ¡G", buf, 24, DOECHO, u->username))
      strcpy(x.username, buf);

/* Tzu  ¤w»{ÃÒ¤£¯à¶Ã§ï¸ê®Æ */
    if(!HAS_PERM(PERM_LOGINOK) || HAS_PERM(PERM_ACCOUNTS))
    {
      if (getdata(i++, 0, "¯u¹ê©m¦W¡G", buf, 20, DOECHO, u->realname))
        strcpy(x.realname, buf);

      if (getdata(i++, 0,  "©~¦í¦a§}¡G", buf, 50, DOECHO, u->address))
        strcpy(x.address, buf);
    }
    else
    {
      outs("¯u¹ê©m¦W¡G [7m­Y­n§ó·s¥»¶µ¸ê®Æ¡A½Ð­«¶ñµù¥U³æ¡I[m\n");
      outs("©~¦í¦a§}¡G [7m­Y­n§ó·s¥»¶µ¸ê®Æ¡A½Ð­«¶ñµù¥U³æ¡I[m\n");
      i += 2;
    }
/*     */

/* MH */
    if(HAS_PERM(PERM_SYSOP))
    {
      sprintf(genbuf,
        "©Ê§O (1)¸¯®æ (2)©j±µ (3)©³­} (4)¬ü¬Ü (5)Á¦¨û (6)ªü«¼ (7)´Óª« (8)Äqª«"
        "\n     (9)³Õ®æ¤H (10)¥ËªÖ¤H (11)·¡º¸¤H (12)§JªL°^¤H (13)¥ø·~¸¹"
        "\n     (14)Ada Augusta Byron"
        "[%i]¡G", u->sex + 1);
    }
    else
    {
      sprintf(genbuf,
        "©Ê§O (1)¸¯®æ (2)©j±µ (3)©³­} (4)¬ü¬Ü (5)Á¦¨û (6)ªü«¼ (7)´Óª« (8)Äqª«"
        "[%i]¡G", u->sex + 1);
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
      len = getdata(i, 0, "¥Í¤é ¤ë¤ë/¤é¤é/¦è¤¸¡G", buf, 9, DOECHO, genbuf);
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

    getdata(i++, 0, "¹q¤l«H½c(*±H»{ÃÒ«H¥Î*)¡G", buf, 50, DOECHO, u->email);
    if (*buf && strcmp(buf, u->email)) {
      strcpy(x.email, buf);
      mail_changed = 1 - real;
    }
    else
       strcpy(x.email, u->email);

/*
    sprintf(genbuf, "²×ºÝ¾÷§ÎºA [%s]¡G", u->termtype);
    if (getdata(i++, 0, genbuf, buf, 8, DOECHO, u->termtype))
      strcpy(x.termtype, buf);
*/
    if (real)
    {
      if (getdata(i++, 0, "»{ÃÒ¸ê®Æ¡G", buf, 44, DOECHO, u->justify))
        strcpy(x.justify, buf);

      if (getdata(i++, 0, "³Ìªñ¥úÁ{¾÷¾¹¡G", buf, 16, DOECHO, u->lasthost))
        strcpy(x.lasthost, buf);

      sprintf(genbuf, "%d", u->numlogins);
      if (getdata(i++, 0, "¤W½u¦¸¼Æ¡G", buf, 10, DOECHO, genbuf))
        if ((fail = atoi(buf)) >= 0)
          x.numlogins = fail;

      sprintf(genbuf, "%d", u->numposts);
      if (getdata(i++, 0, "¤å³¹¼Æ¥Ø¡G", buf, 10, DOECHO, genbuf))
        if ((fail = atoi(buf)) >= 0)
          x.numposts = fail;

      fail = 0;
    }
    break;

  case '2':
    i = 19;
    if (!real)
    {
      if (!getdata(i++, 0, "½Ð¿é¤J­ì±K½X¡G", buf, PASSLEN, NOECHO, 0) ||
        !checkpasswd(u->passwd, buf))
      {
        outs("\n\n±z¿é¤Jªº±K½X¤£¥¿½T\n");
        fail++;
        break;
      }
    }

    if (!getdata(i++, 0, "½Ð³]©w·s±K½X¡G", buf, PASSLEN, NOECHO, 0))
    {
      outs("\n\n±K½X³]©w¨ú®ø, Ä~Äò¨Ï¥ÎÂÂ±K½X\n");
      fail++;
      break;
    }
    strncpy(genbuf, buf, PASSLEN);

    getdata(i++, 0, "½ÐÀË¬d·s±K½X¡G", buf, PASSLEN, NOECHO, 0);
    if (strncmp(buf, genbuf, PASSLEN))
    {
      outs("\n\n·s±K½X½T»{¥¢±Ñ, µLªk³]©w·s±K½X\n");
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
    if (getdata(b_lines - 3, 0, "·sªº¨Ï¥ÎªÌ¥N¸¹¡G", genbuf, IDLEN + 1, DOECHO, 0))
    {
      if (searchuser(genbuf))
      {
        outs("¿ù»~! ¤w¸g¦³¦P¼Ë ID ªº¨Ï¥ÎªÌ");
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
    getdata(b_lines - 1, 0, "¡¶ ½Ð¿é¤J±K½X¡A¥H¸Ñ°£¿Ã¹õÂê©w¡G",
      genbuf, PASSLEN, NOECHO, 0);
  } while (!checkpasswd(cuser.passwd, genbuf));

  return FULLUPDATE;
}


#ifdef  HAVE_SUICIDE
int
u_kill()
{
  char genbuf[200];

  getdata(b_lines - 1, 0, "¡¶ ¦pªG½T©w­n²M°£±zªº±b¸¹¡A½Ð¿é¤J±K½X¡G",
    genbuf, PASSLEN, NOECHO, 0);

  if (*genbuf == '\0' || !checkpasswd(cuser.passwd, genbuf))
  {
    outmsg("±z¿é¤Jªº±K½X¤£¥¿½T¡A±b¸¹¥¼²M°£¡C");
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
  outs("¿Ë·RªºªB¤Í¡A«C¤sªø¦b¡Aºñ¤ôªø¬y¡A«¥­Ì«á·|¦³´Á§a¡I");
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
    prints("%s ªº¦W¤ù:\n", uid);
    i = 0;
    while (i++ < MAXQUERYLINES && fgets(genbuf, 256, planfile))
    {
/* MH */
/* ¥Î mhsin_prints (in mhsin.c) ¨ú¥N kaede_prints */
/*      outs(kaede_prints(genbuf));*/
      outs(mhsin_prints(genbuf, 255));
/*    */
    }
    fclose(planfile);
  }
  else
    prints("%s ¥Ø«e¨S¦³¦W¤ù", uid);
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
      prints("[36m¡i Ã±¦WÀÉ.%c ¡j[m\n", ch);
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
          prints("[36m¡i Ã±¦WÀÉ.%d ¡j[m\n", sig_files[i]);
          for(k = 0; k < MAXSIGLINES && k < j; k ++)
            outs(mhsin_prints(bufs[i][k], 255));
          lused += (j + 1);
        }
        else
          break;
#else
        prints("[36m¡i Ã±¦WÀÉ.%d ¡j[m\n", sig_files[i]);
        for(k = 0; k < MAXSIGLINES && k < j && k + lused + 2 <= t_lines - 3; k ++)
          outs(mhsin_prints(bufs[i][k], 255));
        if(j + lused + 2 > t_lines - 3)
          break;
        lused += (j + 1);
#endif
      }
      end = i;
#ifndef MH_SHOWSIG_USE_SCROLL_DEBUG
      my_outmsg_row("Ctrl-U: ¦V¤W±²°Ê, Ctrl-D: ¦V¤U±²°Ê", 1);
#else
      move(1, 0);
      prints("Ctrl-U: ¦V¤W±²°Ê, Ctrl-D: ¦V¤U±²°Ê %d %d %d", st, end, lused);
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
          prints("[36m¡i Ã±¦WÀÉ.%d ¡j[m\n", sig_files[i]);
          for(k = 0; k < MAXSIGLINES && k < j && k + lused + 2 <= t_lines - 3; k ++)
            outs(mhsin_prints(bufs[i][k], 255));
          if(j + lused + 2 > t_lines - 3)
            break;
          lused += (j + 1);
        }
        end = i;
        move(1, 0);
#ifndef MH_SHOWSIG_USE_SCROLL_DEBUG
        my_outmsg_row("Ctrl-U: ¦V¤W±²°Ê, Ctrl-D: ¦V¤U±²°Ê", 1);
#else
        prints("Ctrl-U: ¦V¤W±²°Ê, Ctrl-D: ¦V¤U±²°Ê %d %d %d", st, end, lused);
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
        prints("[36m¡i Ã±¦WÀÉ.%d ¡j[m\n", sig_files[st]);
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
        my_outmsg_row("Ctrl-U: ¦V¤W±²°Ê, Ctrl-D: ¦V¤U±²°Ê", 1);
#else
        prints("Ctrl-U: ¦V¤W±²°Ê, Ctrl-D: ¦V¤U±²°Ê %d %d %d", st, end, lused);
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
  
  i = mh_showsignature("Ã±¦WÀÉ (E)½s¿è (D)§R°£ (Q)¨ú®ø¡H[Q] ");
  if(i == 'd' || i == 'e')
  {
    if (getdata(0, 0, "½Ð¿ï¾ÜÃ±¦WÀÉ(1-9)¡H[1] ", buf, 4, DOECHO, 0) >= 0)
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
            outs("Ã±¦WÀÉ§ó·s§¹²¦");
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

  getdata(0, 0, "Ã±¦WÀÉ (E)½s¿è (D)§R°£ (Q)¨ú®ø¡H[Q] ", ans, 4, LCECHO, 0);

  aborted = 0;
  if (ans[0] == 'd')
    aborted = 1;
  if (ans[0] == 'e')
    aborted = 2;

  if (aborted)
  {
    if (!getdata(1, 0, "½Ð¿ï¾ÜÃ±¦WÀÉ(1-9)¡H[1] ", ans, 4, DOECHO, 0))
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
          outs("Ã±¦WÀÉ§ó·s§¹²¦");
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

  getdata(b_lines - 1, 0, "¦W¤ù (D)§R°£ (E)½s¿è [Q]¨ú®ø¡H[Q] ", genbuf, 3, LCECHO, 0);

  if (genbuf[0] == 'e')
  {
    int aborted;

    setutmpmode(EDITPLAN);
    setuserfile(genbuf, fn_plans);
    aborted = vedit(genbuf, NA);
    if (!aborted)
      outs("¦W¤ù§ó·s§¹²¦");
    pressanykey();
    return 0;
  }
  else if (genbuf[0] == 'd')
  {
    setuserfile(genbuf, fn_plans);
    unlink(genbuf);
    outmsg("¦W¤ù§R°£§¹²¦");
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
  {{MH_FIELD_STRING, (void *)rname, MH_FIELD_USEDEFAULT, 20, "¯u¹ê©m¦W(½Ð¥Î¤¤¤å): ", 6, 0, 6, 20, "½Ð½T¹ê¶ñ¼g¯u¹ê¤¤¤å©m¦W", NULL, -1},
   {MH_FIELD_STRING, (void *)career, MH_FIELD_USEDEFAULT, 40, "ªA°È³æ¦ì(¾Ç®Õ¨t/¯Z¯Å©Î³æ¦ìÂ¾ºÙ): ", 8, 0, 8, 33, "½Ð¶ñ¼gªA°È³æ¦ì", NULL, -1},
   {MH_FIELD_STRING, (void *)addr, MH_FIELD_USEDEFAULT, 50, "¥Ø«e¦í§}(§t¹ì«Ç©ÎªùµP¸¹½X): ", 10, 0, 10, 28, "½Ð¶ñ¼g¦í§}", NULL, -1},
   {MH_FIELD_STRING, (void *)phone, MH_FIELD_USEDEFAULT, 20, "³sµ¸¹q¸Ü(¥]¬Aªø³~¼·¸¹°Ï°ì½X): ", 12, 0, 12, 30, "", NULL, -1},
   {MH_FIELD_STRING, (void *)email, MH_FIELD_USEDEFAULT, 50, "E-Mail Address(¨­¤À»{ÃÒ¥Î): ", 14, 0, 14, 28, "", NULL, -1}
  };

/*  if (cuser.userlevel & PERM_LOGINOK)
  {
    outs("±zªº¨­¥÷½T»{¤w¸g§¹¦¨¡A¤£»Ý¶ñ¼g¥Ó½Ðªí");
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
        outs("±zªºµù¥U¥Ó½Ð³æ©|¦b³B²z¤¤¡A½Ð­@¤ßµ¥­Ô");
        return XEASY;
      }
    }
    fclose(fn);
  }

  if (cuser.userlevel & PERM_LOGINOK)
    strcpy(genbuf, "±zªº¨­¥÷½T»{¤w¸g§¹¦¨¡A­n§ó·s¸ê®Æ¶Ü(Y/N)¡H[N] ");
  else
    strcpy(genbuf, "±z½T©w­n¶ñ¼gµù¥U³æ¶Ü(Y/N)¡H[N] ");

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
    prints("%s(%s) ±z¦n¡A½Ð¾Ú¹ê¶ñ¼g¥H¤Uªº¸ê®Æ:",
      cuser.userid, cuser.username);
    mh_form(5, reg_form, 3);
    getdata(b_lines - 5 - 1, 0, "¥H¤W¸ê®Æ¬O§_¥¿½T(Y/N)¡H(Q)¨ú®øµù¥U [N] ", ans, 3, LCECHO, 0);
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
    outs("±zªº¨­¥÷½T»{¤w¸g§¹¦¨¡A¤£»Ý¶ñ¼g¥Ó½Ðªí");
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
        outs("±zªºµù¥U¥Ó½Ð³æ©|¦b³B²z¤¤¡A½Ð­@¤ßµ¥­Ô");
        return XEASY;
      }
    }
    fclose(fn);
  }

  if (cuser.userlevel & PERM_LOGINOK)
    strcpy(genbuf, "±zªº¨­¥÷½T»{¤w¸g§¹¦¨¡A­n§ó·s¸ê®Æ¶Ü(Y/N)¡H[N] ");
  else
    strcpy(genbuf, "±z½T©w­n¶ñ¼gµù¥U³æ¶Ü(Y/N)¡H[N] ");

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
    prints("%s(%s) ±z¦n¡A½Ð¾Ú¹ê¶ñ¼g¥H¤Uªº¸ê®Æ:",
      cuser.userid, cuser.username);
    getdata(6, 0, "¯u¹ê©m¦W(½Ð¥Î¤¤¤å): ", rname, 20, DOECHO, rname);
    getdata(8, 0, "ªA°È³æ¦ì(¾Ç®Õ¨t/¯Z¯Å©Î³æ¦ìÂ¾ºÙ): ", career, 40, DOECHO, career);
    getdata(10, 0,  "¥Ø«e¦í§}(§t¹ì«Ç©ÎªùµP¸¹½X): ", addr, 50, DOECHO, addr);
    getdata(12, 0, "³sµ¸¹q¸Ü(¥]¬Aªø³~¼·¸¹°Ï°ì½X): ", phone, 20, DOECHO, phone);
    getdata(14, 0, "E-Mail Address(¨­¤À»{ÃÒ¥Î): ", email, 50, DOECHO, email);
    getdata(b_lines - 1, 0, "¥H¤W¸ê®Æ¬O§_¥¿½T(Y/N)¡H(Q)¨ú®øµù¥U [N] ", ans, 3, LCECHO, 0);
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
/* ¦C¥X©Ò¦³µù¥U¨Ï¥ÎªÌ                            */
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
    prints("[7m  ¨Ï¥ÎªÌ¥N¸¹   %-25s   ¤W¯¸  ¤å³¹  %s  ³Ìªñ¥úÁ{¤é´Á     [0m\n",

    showrealname ?
/*#if defined(REALINFO) && defined(ACTS_REALNAMES)*/
      "¯u¹ê©m¦W" :
/*#else*/
      "ºï¸¹¼ÊºÙ"
/*#endif*/

      ,HAS_PERM(PERM_SEEULEVELS) ? "µ¥¯Å" : "");
    i = 3;
    return 0;
  }
  if (uentp->userid[0] == '\0')
    return 0;
  if (uentp->userlevel < u_list_special)
    return 0;

  if (i == b_lines)
  {
    prints("[34;46m  ¤wÅã¥Ü %d/%d ¤H(%d%%)  [31;47m  (Space)[30m ¬Ý¤U¤@­¶  [31m(Q)[30m Â÷¶}  [0m",
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
    getdata(b_lines - 1, 0, "Æ[¬Ý [1]¯S®íµ¥¯Å (2)¥þ³¡¡H[1] ", genbuf, 3, DOECHO, 0);
    if (genbuf[0] != '2')
      u_list_special = 32;
  }
  if (HAS_PERM(PERM_CHATROOM) || HAS_PERM(PERM_SYSOP))
  {
    getdata(b_lines - 1, 0, "Åã¥Ü [1]¯u¹ê©m¦W (2)¼ÊºÙ¡H[1] ", genbuf, 3, DOECHO, 0);
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
  prints("[34;46m  ¤wÅã¥Ü %d/%d ªº¨Ï¥ÎªÌ(¨t²Î®e¶qµL¤W­­)  [31;47m  (½Ð«ö¥ô·NÁäÄ~Äò)  [0m",
    usercounter, totalusers);
  igetkey();
  return 0;
}
