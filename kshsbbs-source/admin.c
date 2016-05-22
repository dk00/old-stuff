/*-------------------------------------------------------*/
/* admin.c      ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : administration routines                      */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/

 #define _ADMIN_C_

#include "bbs.h"


/* ----------------------------------------------------- */
/* 設定系統檔案                                          */
/* ----------------------------------------------------- */

int
x_file()
{
  int aborted;
  char ans[4], *fpath, editfile[80];

/*
woju
  getdata(b_lines, 0, "設定 (1)歡迎畫面 (2)看板期限 (3)看板數量 (4)自由編輯 [Q]取消？", ans, 3, LCECHO, 0);
*/
  move(b_lines - 2, 0); /* Tzu */
  outs("設定 (1)歡迎畫面 (2)最新消息 (3)看板期限 (4)看板數量 (5)註冊提示畫面 ");
  getdata(b_lines - 1, 0, "     (6)新手上路需知 (7)註冊成功\信件 (8)更新系統狀態 [Q]取消？[Q] ", ans, 3, LCECHO, 0);
  switch (ans[0])
  {
  case '1':
    fpath = "etc/welcome";
    break;
  
  case '2':
    fpath = "etc/hotnews";
    break;

  case '3':
    fpath = "etc/expire.conf";
    break;

  case '4':
    fpath = "etc/note.max";
    break;
  
  case '5':
    fpath = "etc/register";
    break;

  case '6':
    fpath = "etc/newuser";
    break;
  
  case '7':
    fpath = "etc/registered";
    break;
  
  case '8':
    if (HAS_PERM(PERM_SYSOP)) {
       reload_ucache();
       reload_bcache();
       resetutmpent();
    }
    return FULLUPDATE;
/*
  case '4':
woju
    getdata(b_lines, 0, "檔案名稱:", editfile, 70, LCECHO, 0);
    if(!editfile[0]) return XEASY;
    fpath = editfile;
    break;
*/

  default:
    return FULLUPDATE;
  }
  aborted = vedit(fpath, NA);
  prints("\n\n系統檔案[%s]：%s", fpath, aborted ? "未改變" : "更新完畢");
  pressanykey();
  return FULLUPDATE;
}


/* ----------------------------------------------------- */
/* 看板管理                                              */
/* ----------------------------------------------------- */

extern int cmpbnames();

static int
invalid_brdname(brd)
  char *brd;
{
  register char ch;

  ch = *brd++;
  if (not_alnum(ch))
    return 1;
  while (ch = *brd++)
  {
    if (not_alnum(ch) && ch != '_' && ch != '-' && ch != '.')
      return 1;
  }
  return 0;
}


unsigned
setperms(pbits)
  unsigned pbits;
{
  register int i;
  char choice[4];

  move(4, 0);
  for (i = 0; i < NUMPERMS; i++)
  {
    prints("%c. %-20s %s\n", 'A' + i, permstrings[i],
      ((pbits >> i) & 1 ? "ˇ" : "Ｘ"));
  }
  clrtobot();
  while (getdata(b_lines - 1, 0, "請按 [A-O] 切換設定，按 [Return] 結束：",
      choice, 3, LCECHO, 0))
  {
    i = choice[0] - 'a';
    if (i < 0 || i >= NUMPERMS || (i == NUMPERMS -1 && !HAS_PERM(PERM_SYSOP)))
      bell();
    else
    {
      pbits ^= (1 << i);
      move(i + 4, 24);
      prints((pbits >> i) & 1 ? "ˇ" : "Ｘ");
    }
  }
  return (pbits);
}


/* -------------- */
/* 自動設立精華區 */
/* -------------- */


static void
setup_man(board)
  boardheader *board;
{
  char genbuf[200];
  FILE *fp;

  setapath(genbuf, board->brdname);
  mkdir(genbuf, 0755);
}


static void
bperm_msg(board)
  boardheader *board;
{
  prints("\n設定 [%s] 看板之(%s)權限：", board->brdname,
    board->level & PERM_POSTMASK ? "發表" : "閱\讀");
}


int
m_newbrd()
{
  boardheader newboard;
  char ans[4];
  int bid;
  char genbuf[200];
  char smsg[200];
  
  stand_title("建立新板");
  memset(&newboard, 0, sizeof(newboard));

  do
  {
    if (!getdata(3, 0, msg_bid, newboard.brdname, IDLEN + 1, DOECHO, 0))
      return -1;
  } while (invalid_brdname(newboard.brdname));

  getdata(4, 0, "看板主題：", newboard.title, BTLEN + 1, DOECHO, 0);
  setbpath(genbuf, newboard.brdname);
  if (getbnum(newboard.brdname) > 0 || mkdir(genbuf, 0755) == -1)
  {
    outs(err_bid);
    pressanykey();
    return -1;
  }

  getdata(5, 0, "板主名單：", newboard.BM, IDLEN * 3 + 3, DOECHO, 0);

  newboard.level = 0;
  getdata(6, 0, "設定讀寫權限(Y/N)？[N] ", ans, 4, LCECHO, 0);
  if (*ans == 'y')
  {
    getdata(7, 0, "限制 [R]閱\讀 (P)發表？", ans, 4, LCECHO, 0);
    if (*ans == 'p')
      newboard.level = PERM_POSTMASK;

    move(1, 0);
    clrtobot();
    bperm_msg(&newboard);

    newboard.level = setperms(newboard.level);
    clear();
  }
  if ((bid = getbnum("")) > 0)
  {
    substitute_record(fn_board, &newboard, sizeof(newboard), bid);
  }
  else if (append_record(fn_board, &newboard, sizeof(newboard)) == -1)
  {
    pressanykey();
    return -1;
  }
  setup_man(&newboard);
  touch_boards();
  outs("\n新板成立");
  log_usies("NewBoard", newboard.title);
  sprintf(smsg, "%s 建立了 %s 板。", cuser.userid, newboard.brdname);
/*  securityreport(smsg); Tzu*/
  pressanykey();
  return 0;
}

/* MH */
int
mh_board()
{
  boardheader bh, newbh;
  char bname[20];
  int bid;
  char genbuf[200];
  char smsg[200];

  stand_title("看板設定");
  make_blist();
  namecomplete(msg_bid, bname);
  if (!*bname)
    return 0;

  bid = getbnum(bname);
  if (get_record(fn_board, &bh, sizeof(bh), bid) == -1)
  {
    outs(err_bid);
    pressanykey();
    return -1;
  }

  prints("看板名稱：%s\n看板說明：%s\n板主名單：%s",
    bh.brdname, bh.title, bh.BM);

  bperm_msg(&bh);
  prints("%s設限", (bh.level & ~PERM_POSTMASK) ? "有" : "不");

  getdata(7, 0, "看板 (D)刪除 (E)設定 (Q)取消？[Q] ", genbuf, 3, LCECHO, 0);

  switch (*genbuf)
  {
  case 'd':

    getdata(9, 0, msg_sure_ny, genbuf, 3, LCECHO, 0);
    if (genbuf[0] != 'y')
    {
      outs(MSG_DEL_CANCEL);
    }
    else
    {
      strcpy(bname, bh.brdname);
      sprintf(genbuf, "/bin/rm -fr boards/%s man/boards/%s", bname, bname);
      system(genbuf);
      memset(&bh, 0, sizeof(bh));
      sprintf(bh.title, "[%s] deleted by %s", bname, cuser.userid);
      substitute_record(fn_board, &bh, sizeof(bh), bid);
      touch_boards();
      log_usies("DelBoard", bh.title);
      sprintf(smsg, "%s 刪除了 %s 板。", cuser.userid, bname);
      
      outs("刪板完畢");
    }
    break;

  case 'e':
    memcpy(&newbh, &bh, sizeof(bh));

    while (getdata(9, 0, "新看板名稱：", genbuf, IDLEN + 1, DOECHO,
       newbh.brdname))
    {
      if (strcasecmp(newbh.brdname, genbuf) && getbnum(genbuf))
      {
        move(3, 0);
        outs("錯誤! 板名雷同");
      }
      else if (!invalid_brdname(genbuf))
      {
        strcpy(newbh.brdname, genbuf);
        break;
      }
    }

    if (getdata(10, 0, "新看板說明：", genbuf, BTLEN + 1, DOECHO, newbh.title))
      strcpy(newbh.title, genbuf);

    if (getdata(11, 0, "新板主名單：", genbuf, IDLEN * 3 + 3, DOECHO, newbh.BM))
    {
      trim(genbuf);
      strcpy(newbh.BM, genbuf);
    }

    getdata(12, 0, "是否更改存取權限(Y/N)？[N] ", genbuf, 4, LCECHO, 0);
    if (*genbuf == 'y')
    {
      char ans[4];

      getdata(13, 0, "限制 (R)閱\讀 (P)發表？ ", ans, 4, LCECHO,
         newbh.level & PERM_POSTMASK ? "P" : "R");
      if (newbh.level & PERM_POSTMASK)
      {
        if (*ans == 'r')
          newbh.level &= ~PERM_POSTMASK;
      }
      else
      {
        if (*ans == 'p')
          newbh.level |= PERM_POSTMASK;
      }

      move(1, 0);
      clrtobot();
      bperm_msg(&newbh);
      newbh.level = setperms(newbh.level);
    }

    sprintf(genbuf, "是否使用Access.Read設限(Y/N)？[%c] ", (bh.bmode & MH_BMODE_READ) ? 'Y' : 'N');
    getdata(13, 0, genbuf, genbuf, 4, LCECHO, 0);
    if(*genbuf == 'y')
    {
      newbh.bmode |= MH_BMODE_READ;
    }
    else if(*genbuf == 'n')
    {
      newbh.bmode &= ~MH_BMODE_READ;
    }
    sprintf(genbuf, "是否使用Access.Post設限(Y/N)？[%c] ", (bh.bmode & MH_BMODE_POST) ? 'Y' : 'N');
    getdata(14, 0, genbuf, genbuf, 4, LCECHO, 0);
    if(*genbuf == 'y')
    {
      newbh.bmode |= MH_BMODE_POST;
    }
    else if(*genbuf == 'n')
    {
      newbh.bmode &= ~MH_BMODE_POST;
    }

    getdata(b_lines - 1, 0, msg_sure_ny, genbuf, 4, LCECHO, 0);

    if ((*genbuf == 'y') && memcmp(&newbh, &bh, sizeof(bh)))
    {
      if (strcmp(bh.brdname, newbh.brdname))
      {
        char src[60], tar[60];

        setbpath(src, bh.brdname);
        setbpath(tar, newbh.brdname);
        Rename(src, tar);

        setapath(src, bh.brdname);
        setapath(tar, newbh.brdname);
        Rename(src, tar);
      }
      setup_man(&newbh);
      substitute_record(fn_board, &newbh, sizeof(newbh), bid);
      touch_boards();
    }
  }
  return 0;
}

int mh_decloak(void)
{
  char buf[20];
  int id;
  
  stand_title("解除隱形");
  usercomplete(msg_uid, buf);
  if (*buf)
  {
    move(2, 0);
    if (id = getuser(buf))
    {
      xuser.uflag &= (~CLOAK_FLAG);
      substitute_record(fn_passwd, &xuser, sizeof(xuser), id);
    }
  }
  return 0;
}
/*    */

int
m_board()
{
  boardheader bh, newbh;
  char bname[20];
  int bid;
  char genbuf[200];
  char smsg[200];

  stand_title("看板設定");
  make_blist();
  namecomplete(msg_bid, bname);
  if (!*bname)
    return 0;

  bid = getbnum(bname);
  if (get_record(fn_board, &bh, sizeof(bh), bid) == -1)
  {
    outs(err_bid);
    pressanykey();
    return -1;
  }

  prints("看板名稱：%s\n看板說明：%s\n板主名單：%s",
    bh.brdname, bh.title, bh.BM);

  bperm_msg(&bh);
  prints("%s設限", (bh.level & ~PERM_POSTMASK) ? "有" : "不");

  getdata(7, 0, "看板 (D)刪除 (E)設定 (Q)取消？[Q] ", genbuf, 3, LCECHO, 0);

  switch (*genbuf)
  {
  case 'd':

    getdata(9, 0, msg_sure_ny, genbuf, 3, LCECHO, 0);
    if (genbuf[0] != 'y')
    {
      outs(MSG_DEL_CANCEL);
    }
    else
    {
      strcpy(bname, bh.brdname);
      sprintf(genbuf, "/bin/rm -fr boards/%s man/boards/%s", bname, bname); 
      /* bug killed by Tzu  原 man/%s -> man/boards/%s */
      system(genbuf);
      memset(&bh, 0, sizeof(bh));
      sprintf(bh.title, "[%s] deleted by %s", bname, cuser.userid);
      substitute_record(fn_board, &bh, sizeof(bh), bid);
      touch_boards();
      log_usies("DelBoard", bh.title);
      sprintf(smsg, "%s 刪除了 %s 板。", cuser.userid, bname);
/*Tzu      securityreport(smsg);*/
      
      outs("刪板完畢");
    }
    break;

  case 'e':
    memcpy(&newbh, &bh, sizeof(bh));

    while (getdata(9, 0, "新看板名稱：", genbuf, IDLEN + 1, DOECHO,
       newbh.brdname))
    {
      if (strcasecmp(newbh.brdname, genbuf) && getbnum(genbuf))
      {
        move(3, 0);
        outs("錯誤! 板名雷同");
      }
      else if (!invalid_brdname(genbuf))
      {
        strcpy(newbh.brdname, genbuf);
        break;
      }
    }

    if (getdata(10, 0, "新看板說明：", genbuf, BTLEN + 1, DOECHO, newbh.title))
      strcpy(newbh.title, genbuf);

    if (getdata(11, 0, "新板主名單：", genbuf, IDLEN * 3 + 3, DOECHO, newbh.BM))
    {
      trim(genbuf);
      strcpy(newbh.BM, genbuf);
    }

    getdata(12, 0, "是否更改存取權限(Y/N)？[N] ", genbuf, 4, LCECHO, 0);
    if (*genbuf == 'y')
    {
      char ans[4];

      getdata(13, 0, "限制 (R)閱\讀 (P)發表？ ", ans, 4, LCECHO,
         newbh.level & PERM_POSTMASK ? "P" : "R");
      if (newbh.level & PERM_POSTMASK)
      {
        if (*ans == 'r')
          newbh.level &= ~PERM_POSTMASK;
      }
      else
      {
        if (*ans == 'p')
          newbh.level |= PERM_POSTMASK;
      }

      move(1, 0);
      clrtobot();
      bperm_msg(&newbh);
      newbh.level = setperms(newbh.level);
    }

    getdata(b_lines - 1, 0, msg_sure_ny, genbuf, 4, LCECHO, 0);

    if ((*genbuf == 'y') && memcmp(&newbh, &bh, sizeof(bh)))
    {
      if (strcmp(bh.brdname, newbh.brdname))
      {
        char src[60], tar[60];

        setbpath(src, bh.brdname);
        setbpath(tar, newbh.brdname);
        Rename(src, tar);

        setapath(src, bh.brdname);
        setapath(tar, newbh.brdname);
        Rename(src, tar);
      }
      setup_man(&newbh);
      substitute_record(fn_board, &newbh, sizeof(newbh), bid);
      touch_boards();
/*
woju
*/
      log_usies("SetBoard", newbh.brdname);
      sprintf(smsg, "%s 變更了 %s 板的設定。", cuser.userid, newbh.brdname);
/*Tzu      securityreport(smsg);*/
    }
  }
  return 0;
}

/* Tzu */

#if 0
void
securityreport(msg)
char *msg;
{
  FILE *fp;
  fileheader fhdr;
  time_t now = time(0);
  char genbuf[200],reason[30],tmpfile[200];
  int i;
  
  sprintf(tmpfile, "etc/security.%d",getpid());
  fp = fopen(tmpfile, "w");
  now = time(NULL) - 6 * 60;
  sprintf (genbuf,"作者: [雄中報告器] 看板: SYSOPs\n");
  fputs(genbuf,fp);
  sprintf(genbuf,"標題: [報告] %s\n", msg);
  fputs (genbuf,fp);
  sprintf (genbuf,"時間: %s\n",ctime(&now));
  fputs (genbuf,fp);
  
  sprintf(genbuf, "%s", msg);
  fputs(genbuf,fp);
  /*sprintf(genbuf,"\n使用者 32m%s 的權限：\n",cuser.userid);
  fputs(genbuf,fp);
  for(i=0;i < NUMPERMS/2;i++) {
  sprintf(genbuf," %s %-12s 權限\t\t%s %-12s 權限\n", (cuser.userlevel & (1 << i))?"33m有":";31m無",permstrings[i],(cuser.userlevel & (1 << i+16))?"33m有":";31m無",permstrings[i+16]);
  fputs(genbuf,fp);
  }*/
  fclose (fp);
  sprintf(genbuf, "boards/%s", "SYSOPs");
  stampfile(genbuf, &fhdr);
  rename (tmpfile,genbuf);
  sprintf(genbuf, "[報告] %s", msg);
  strcpy(fhdr.title, genbuf);
  strcpy(fhdr.owner, "[雄中報告器]");
  sprintf(genbuf, "boards/%s/.DIR", "SYSOPs");
  append_record(genbuf, &fhdr, sizeof(fhdr));
}
#endif

/* ----------------------------------------------------- */
/* 使用者管理                                            */
/* ----------------------------------------------------- */


int
m_user()
{
  userec muser;
  int id;
  char genbuf[200];

  stand_title("使用者設定");
  usercomplete(msg_uid, genbuf);
  if (*genbuf)
  {
    move(2, 0);
    if (id = getuser(genbuf))
    {
      memcpy(&muser, &xuser, sizeof(muser));
      user_display(&muser, 1);
#ifndef MH_USEFORM
      uinfo_query(&muser, 1, id);
#else
      mh_uinfo_query(&muser, 1, id);
#endif
    }
    else
    {
      outs(err_uid);
      clrtoeol();
      pressanykey();
    }
  }
  return 0;
}


#ifdef HAVE_TIN
int
post_in_tin(username)
  char *username;
{
  char buf[256];
  FILE *fh;
  int counter = 0;

  sethomefile(buf, username, ".tin/posted");
  fh = fopen(buf, "r");
  if (fh == NULL)
    return 0;
  else
  {
    while (fgets(buf, 255, fh) != NULL)
    {
      if (buf[9] != 'd' && strncmp(&buf[11], "csie.bbs.test", 13))
        counter++;
      if (buf[9] == 'd')
        counter--;
    }
    fclose(fh);
    return counter;
  }

}
#endif


/* ----------------------------------------------------- */
/* 清除使用者信箱                                        */
/* ----------------------------------------------------- */


#ifdef  HAVE_MAILCLEAN
FILE *cleanlog;
char curruser[IDLEN + 2];
extern int delmsgs[];
extern int delcnt;

static int
domailclean(fhdrp)
  fileheader *fhdrp;
{
  static int newcnt, savecnt, deleted, idc;
  char buf[STRLEN];

  if (!fhdrp)
  {
    fprintf(cleanlog, "new = %d, saved = %d, deleted = %d\n",
      newcnt, savecnt, deleted);
    newcnt = savecnt = deleted = idc = 0;
    if (delcnt)
    {
      sethomedir(buf, curruser);
      while (delcnt--)
        delete_record(buf, sizeof(fileheader), delmsgs[delcnt]);
    }
    delcnt = 0;
    return 1;
  }
  idc++;
  if (!(fhdrp->filemode & FILE_READ))
    newcnt++;
  else if (fhdrp->filemode & FILE_MARKED)
    savecnt++;
  else
  {
    deleted++;
    sethomefile(buf, curruser, fhdrp->filename);
    unlink(buf);
    delmsgs[delcnt++] = idc;
  }
  return 0;
}


static int
cleanmail(urec)
  userec *urec;
{
  struct stat statb;
  char genbuf[200];

  if (urec->userid[0] == '\0' || !strcmp(urec->userid, str_new))
    return;
  sethomedir(genbuf, urec->userid);
  fprintf(cleanlog, "%s：", urec->userid);
  if (stat(genbuf, &statb) == -1 || statb.st_size == 0)
    fprintf(cleanlog, "no mail\n");
  else
  {
    strcpy(curruser, urec->userid);
    delcnt = 0;
    apply_record(genbuf, domailclean, sizeof(fileheader));
    domailclean(NULL);
  }
  return 0;
}


int
m_mclean()
{
  char ans[4];

  getdata(b_lines - 1, 0, msg_sure_ny, ans, 4, LCECHO, 0);
  if (ans[0] != 'y')
    return FULLUPDATE;

  cleanlog = fopen("mailclean.log", "w");
  outmsg("This is variable msg_working!");

  move(b_lines - 1, 0);
  if (apply_record(fn_passwd, cleanmail, sizeof(userec)) == -1)
  {
    outs(ERR_PASSWD_OPEN);
  }
  else
  {
    fclose(cleanlog);
    outs("清除完成! 記錄檔 mailclean.log.");
  }
  return FULLUPDATE;
}
#endif  HAVE_MAILCLEAN


/* ----------------------------------------------------- */
/* 產生追蹤記錄：建議改用 log_usies()、TRACE()           */
/* ----------------------------------------------------- */


#ifdef  HAVE_REPORT
void
report(s)
  char *s;
{
  static int disable = NA;
  int fd;

  if (disable)
    return;

  if ((fd = open("trace", O_WRONLY, 0644)) != -1)
  {
    char buf[256];
    char *thetime;
    time_t dtime;

    time(&dtime);
    thetime = Cdate(&dtime);
    flock(fd, LOCK_EX);
    lseek(fd, 0, L_XTND);
    sprintf(buf, "%s %s %s\n", cuser.userid, thetime, s);
    write(fd, buf, strlen(buf));
    flock(fd, LOCK_UN);
    close(fd);
  }
  else
    disable = YEA;
}


int
m_trace()
{
  struct stat bstatb, ostatb, cstatb;
  int btflag, otflag, ctflag, done = 0;
  char ans[2];
  char *msg;

  clear();
  move(0, 0);
  outs("Set Trace Options");
  clrtobot();
  while (!done)
  {
    move(2, 0);
    otflag = stat("trace", &ostatb);
    ctflag = stat("trace.chatd", &cstatb);
    btflag = stat("trace.bvote", &bstatb);
    outs("Current Trace Settings:\n");
    if (otflag)
      outs("Normal tracing is OFF\n");
    else
      prints("Normal tracing is ON (size = %d)\n", ostatb.st_size);
    if (ctflag)
      outs("Chatd  tracing is OFF\n");
    else
      prints("Chatd  tracing is ON (size = %d)\n", cstatb.st_size);
    if (btflag)
      outs("BVote  tracing is OFF\n");
    else
      prints("BVote  tracing is ON (size = %d)\n", bstatb.st_size);

    move(8, 0);
    outs("Enter:\n");
    prints("<1> to %s Normal tracing\n", otflag ? "enable " : "disable");
    prints("<2> to %s Chatd  tracing\n", ctflag ? "enable " : "disable");
    prints("<3> to %s BVote  tracing\n", btflag ? "enable " : "disable");
    getdata(12, 0, "Anything else to exit：", ans, 2, DOECHO, 0);

    switch (ans[0])
    {
    case '1':
      if (otflag)
      {
/*
woju
*/
        system("touch trace");
        msg = "BBS   tracing enabled.";
        report("opened report log");
      }
      else
      {
        report("closed report log");
        system("/bin/mv trace trace.old");
        msg = "BBS   tracing disabled; log is in trace.old";
      }
      break;

    case '2':
      if (ctflag)
      {
        system("touch trace.chatd");
        msg = "Chat  tracing enabled.";
        report("chatd trace log opened");
      }
      else
      {
        system("/bin/mv trace.chatd trace.chatd.old");
        msg = "Chat  tracing disabled; log is in trace.chatd.old";
        report("chatd trace log closed");
      }
      break;

    case '3':
      if (btflag)
      {
        system("touch trace.bvote");
        msg = "BVote tracing enabled.";
        report("BVote trace log opened");
      }
      else
      {
        system("/bin/mv trace.bvote trace.bvote.old");
        msg = "BVote tracing disabled; log is in trace.bvote.old";
        report("BoardVote trace log closed");
      }
      break;

    default:
      msg = NULL;
      done = 1;
    }
    move(t_lines - 2, 0);
    if (msg)
      prints("%s\n", msg);
  }
  clear();
}
#endif                          /* HAVE_REPORT */


/* ----------------------------------------------------- */
/* 處理 Register Form                                    */
/* ----------------------------------------------------- */


scan_register_form(regfile)
  char *regfile;
{
  char genbuf[200];
  static char *logfile = "register.log";
  static char *field[] = {"num", "uid", "name", "career",
  "addr", "phone", "email", NULL};
  static char *finfo[] = {"帳號位置", "申請代號", "真實姓名", "服務單位",
  "目前住址", "連絡電話", "電子郵件信箱", NULL};
  static char *reason[] = {"輸入真實姓名", "詳填學校科系與年級班級",
    "填寫完整的住址資料", "詳填連絡電話", "確實填寫註冊申請表",
  "用中文填寫申請單", NULL};

  userec muser;
  FILE *fn, *fout, *freg;
  char fdata[7][STRLEN];
  char fname[STRLEN], buf[STRLEN];
  char ans[4], *ptr, *uid;
  int n, unum;

  uid = cuser.userid;
  sprintf(fname, "%s.tmp", regfile);
  move(2, 0);
  if (dashf(fname))
  {
    outs("其他 SYSOP 也在審核註冊申請單");
    pressanykey();
    return -1;
  }
  Rename(regfile, fname);
  if ((fn = fopen(fname, "r")) == NULL)
  {
    prints("系統錯誤，無法讀取註冊資料檔: %s", fname);
    pressanykey();
    return -1;
  }

  memset(fdata, 0, sizeof(fdata));
  while (fgets(genbuf, STRLEN, fn))
  {
    if (ptr = (char *) strstr(genbuf, ": "))
    {
      *ptr = '\0';
      for (n = 0; field[n]; n++)
      {
        if (strcmp(genbuf, field[n]) == 0)
        {
          strcpy(fdata[n], ptr + 2);
          if (ptr = (char *) strchr(fdata[n], '\n'))
            *ptr = '\0';
        }
      }
    }
    else if ((unum = getuser(fdata[1])) == 0)
    {
      move(2, 0);
      clrtobot();
      outs("系統錯誤，查無此人\n\n");
      for (n = 0; field[n]; n++)
        prints("%s     : %s\n", finfo[n], fdata[n]);
      pressanykey();
    }
    else
    {
      memcpy(&muser, &xuser, sizeof(muser));
      move(1, 0);
      prints("帳號位置    ：%d\n", unum);
      user_display(&muser, 1);
      move(14, 0);
      printdash(NULL);
      for (n = 0; field[n]; n++)
        prints("%-12s：%s\n", finfo[n], fdata[n]);
      if (muser.userlevel & PERM_LOGINOK)
      {
        getdata(b_lines - 1, 0, "此帳號已經完成註冊, 更新(Y/N/Skip)？ ",
          ans, 3, LCECHO, "N");
        if (ans[0] != 'y' && ans[0] != 's')
          ans[0] = 'd';
      }
      else
      {
        getdata(b_lines - 1, 0, "是否接受此資料(Y/N/Q/Del/Skip)？ [S]",
          ans, 3, LCECHO, 0);
      }
      move(2, 0);
      clrtobot();

      switch (ans[0])
      {
      case 'y':

        prints("以下使用者資料已經更新:\n");
        muser.userlevel |= (PERM_LOGINOK | PERM_CHAT | PERM_PAGE | PERM_POST);  /* MH */
/*
woju
        muser.userlevel &= ~(PERM_LOGINOK | PERM_POST);
*/
        strcpy(muser.realname, fdata[2]);
        strcpy(muser.address, fdata[4]);
        strcpy(muser.email, fdata[6]);
        sprintf(genbuf, "%s:%s:%s", fdata[5], fdata[3], uid);
        strncpy(muser.justify, genbuf, REGLEN);
        sethomefile(buf, muser.userid, "justify");
        if (fout = fopen(buf, "a"))
        {
          fprintf(fout, "%s\n", genbuf);
          fclose(fout);
        }
        substitute_record(fn_passwd, &muser, sizeof(muser), unum);

        if (fout = fopen(logfile, "a"))
        {
          for (n = 0; field[n]; n++)
            fprintf(fout, "%s: %s\n", field[n], fdata[n]);
          n = time(NULL);
          fprintf(fout, "Date: %s\n", Cdate(&n));
          fprintf(fout, "Approved: %s\n", uid);
          fprintf(fout, "----\n");
          fclose(fout);
        }
/*
woju
*/
        {
          fileheader mhdr;
          char title[128], buf1[80];
          FILE* fp;

          sethomepath(buf1, muser.userid);
          stampfile(buf1, &mhdr);
          strcpy(mhdr.owner, cuser.userid);
          strncpy(mhdr.title, "[註冊成功\]", TTLEN);
          mhdr.savemode = 0;
          mhdr.filemode = 0;
          sethomedir(title, muser.userid);
          append_record(title, &mhdr, sizeof(mhdr));
          Link("etc/registered", buf1);
        }

/*
        mail_justify(muser);
*/
        break;

      case 'q':         /* 太累了，結束休息 */

        if (freg = fopen(regfile, "a"))
        {
          for (n = 0; field[n]; n++)
            fprintf(freg, "%s: %s\n", field[n], fdata[n]);
          fprintf(freg, "----\n");
          while (fgets(genbuf, STRLEN, fn))
            fputs(genbuf, freg);
          fclose(freg);
        }

      case 'd':
        break;

      case 'n':

        for (n = 0; field[n]; n++)
          prints("%s: %s\n", finfo[n], fdata[n]);
        move(9, 0);
        prints("請提出退回申請表原因，按 <enter> 取消\n");
        for (n = 0; reason[n]; n++)
          prints("%d) 請%s\n", n, reason[n]);

/*
woju
*/
        if (getdata(10 + n, 0, "退回原因：", buf, 60, DOECHO, 0))
        {
          int i;
          fileheader mhdr;
          char title[128], buf1[80];
          FILE* fp;

          i = buf[0] - '0';
          if (i >= 0 && i < n)
            strcpy(buf, reason[i]);
          sprintf(genbuf, "[退回原因] 請%s", buf);

          sethomepath(buf1, muser.userid);
          stampfile(buf1, &mhdr);
/*
          strcpy(mhdr.owner, cuser.userid);
*/
          strcpy(mhdr.owner, "站長");
          strncpy(mhdr.title, "[註冊失敗]", TTLEN);
          mhdr.savemode = 0;
          mhdr.filemode = 0;
          sethomedir(title, muser.userid);
          if (append_record(title, &mhdr, sizeof(mhdr)) != -1) {
             fp = fopen(buf1, "w");
             fprintf(fp, "%s\n", genbuf);
             fclose(fp);
          }
/*
          strncpy(muser.address, genbuf, NAMELEN);
          substitute_record(fn_passwd, &muser, sizeof(muser), unum);
*/
          if (fout = fopen(logfile, "a"))
          {
            for (n = 0; field[n]; n++)
              fprintf(fout, "%s: %s\n", field[n], fdata[n]);
            n = time(NULL);
            fprintf(fout, "Date: %s\n", Cdate(&n));
            fprintf(fout, "Rejected: %s [%s]\n----\n", uid, buf);
            fclose(fout);
          }
          break;
        }
        move(10, 0);
        clrtobot();
        prints("取消退回此註冊申請表");

      default:                  /* put back to regfile */

        if (freg = fopen(regfile, "a"))
        {
          for (n = 0; field[n]; n++)
            fprintf(freg, "%s: %s\n", field[n], fdata[n]);
          fprintf(freg, "----\n");
          fclose(freg);
        }
      }
    }
  }
  fclose(fn);
  unlink(fname);
  return (0);
}


int
m_register()
{
  FILE *fn;
  int x, y, wid, len;
  char ans[4];
  char genbuf[200];

  if ((fn = fopen(fn_register, "r")) == NULL)
  {
    outs("目前並無新註冊資料");
    return XEASY;
  }

  stand_title("審核使用者註冊資料");
  y = 2;
  x = wid = 0;

  while (fgets(genbuf, STRLEN, fn) && x < 65)
  {
    if (strncmp(genbuf, "uid: ", 5) == 0)
    {
      move(y++, x);
      outs(genbuf + 5);
      len = strlen(genbuf + 5);
      if (len > wid)
        wid = len;
      if (y >= t_lines - 3)
      {
        y = 2;
        x += wid + 2;
      }
    }
  }
  fclose(fn);
  getdata(b_lines - 1, 0, "開始審核嗎(Y/N)？[N] ", ans, 3, LCECHO, 0);
  if (ans[0] == 'y')
    scan_register_form(fn_register);

  return 0;
}


/* MH */
#define REGISTER_TMP "register.new.tmp"
#define TMPDIR "/bbs1/home/bbs/tmp"

int m_sh_registerfile(void)
{
  char buf[512];
  char fname[256];
  FILE *fp;
  int a, b;
  int continue_flag = YEA;
  
  clear();
  strncpy(fname, tempnam(TMPDIR, "sh_r_"), 256);
  do
  {
    clear();
    if((fp = fopen(fname, "w")) == NULL)
    {
      move(19, 0);
      outs("can't open temp file, 1");
      refresh();
      pressanykey();
      return -1;
    }
    fclose(fp);
    
    sprintf(buf, "ls -lT register.* >> %s", fname);
    system(buf);
    
    if((fp = fopen(fname, "r")) == NULL)
    {
      move(19, 0);
      outs("can't open temp file, 2");
      refresh();
      pressanykey();
      return -1;
    }
    
    a = 3;
    while(fgets(buf, 512, fp) != NULL)
    {
      move(a, 0);
      outs(buf);
      a ++;
    }
    
    fclose(fp);
    
    getdata(21, 0, "(a) append register.new.tmp to register.new, (q) quit, please choose: ", buf, 3, DOECHO, 0);
    switch(buf[0])
    {
      case 'a':
        if(dashf(REGISTER_TMP))
        {
          getdata(22, 0, "are you sure ? [y/N]", buf, 3, DOECHO, 0);
          if(buf[0] == 'y')
          {
            mh_log("log/sysutil.log", "REGISTER_TMP ", "append");
            system("cat " REGISTER_TMP " >> register.new");
            unlink(REGISTER_TMP);
          }
        }
        else
        {
          move(23, 0);
          outs("file doesn't exist");
          refresh();
          pressanykey();
        }
        break;
      case 'q':
        continue_flag = NA;
        break;
      default:
        break;
    }
  } while(continue_flag);
  unlink(fname);
}

#define XCHATD "xchatd"
#define XCHATD3 "xchatd3"

int m_sh_xchatd(void)
{
  char buf[512];
  char fname[256];
  FILE *fp;
  int a, b;
  char *sp;
  int xchatd, xchatd3;
  int continue_flag = YEA;
  
  clear();
  strncpy(fname, tempnam(TMPDIR, "sh_x_"), 256);
  do
  {
    clear();
    if((fp = fopen(fname, "w")) == NULL)
    {
      move(19, 0);
      outs("can't open temp file, 1");
      refresh();
      pressanykey();
      return -1;
    }
    fclose(fp);
    
    sprintf(buf, "ps -o command,pid,%%cpu,%%mem,stat,vsz,rss,start,time | awk '$1 == \"xchatd\" || $1 == \"bin/xchatd\"' >> %s", fname);
    system(buf);
    sprintf(buf, "ps -o command,pid,%%cpu,%%mem,stat,vsz,rss,start,time | awk '$1 == \"xchatd3\" || $1 == \"bin/xchatd3\"' >> %s", fname);
    system(buf);
    
    if((fp = fopen(fname, "r")) == NULL)
    {
      move(19, 0);
      outs("can't open temp file, 2");
      refresh();
      pressanykey();
      return -1;
    }
    
    move(2, 0);
    outs("COMMAND            PID %CPU %MEM STAT   VSZ  RSS STARTED       TIME");
    a = 3;
    xchatd = xchatd3 = -1;
    while(fgets(buf, 512, fp) != NULL)
    {
      move(a, 0);
      outs(buf);
      a ++;
      if((sp = strtok(buf, " \t\r\n")) != NULL)
      {
        if(strcmp(sp, "xchatd") == 0 || strcmp(sp, "bin/xchatd") == 0)
        {
          if((sp = strtok(NULL, " \t\r\n")) != NULL)
            xchatd = atoi(sp);
          else
            xchatd = -1;
        }
        else if(strcmp(sp, "xchatd3") == 0 || strcmp(sp, "bin/xchatd3") == 0)
        {
          if((sp = strtok(NULL, " \t\r\n")) != NULL)
            xchatd3 = atoi(sp);
          else
            xchatd3 = -1;
        }
      }
    }
    
    fclose(fp);

#if 0
    move(19, 0);
    sprintf(buf, "xchatd: %d, xchatd3: %d", xchatd, xchatd3);
    outs(buf);
#endif
    
    getdata(21, 0, "(x/3) run xchatd/3, (k/K) kill xchatd/3, (q) quit, please choose: ", buf, 3, DOECHO, 0);
    switch(buf[0])
    {
      case 'x':
        mh_log("log/sysutil.log", "XCHATD ", "run");
        system("bin/xchatd");
        break;
      case '3':
        mh_log("log/sysutil.log", "XCHATD3 ", "run");
        system("bin/xchatd3");
        break;
      case 'k':
        if(xchatd > 1)
        {
          getdata(21, 0, "are you sure? [y/N]", buf, 3, DOECHO, 0);
          if(buf[0] == 'y')
          {
            mh_log("log/sysutil.log", "XCHATD ", "kill");
            kill(xchatd, SIGKILL);
          }
        }
        else
        {
          move(22, 0);
          outs("no such process");
          refresh();
          pressanykey();
        }
        break;
      case 'K':
        if(xchatd3 > 1)
        {
          getdata(21, 0, "are you sure? [y/N]", buf, 3, DOECHO, 0);
          if(buf[0] == 'y')
          {
            mh_log("log/sysutil.log", "XCHATD3 ", "kill");
            kill(xchatd3, SIGKILL);
          }
        }
        else
        {
          move(22, 0);
          outs("no such process");
          refresh();
          pressanykey();
        }
        break;
      case 'q':
        continue_flag = NA;
        break;
      default:
        break;
    }
  } while(continue_flag);
  unlink(fname);
}
/*    */
