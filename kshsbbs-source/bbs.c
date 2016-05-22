/*-------------------------------------------------------*/
/* bbs.c        ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : bulletin boards' routines                    */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/

#include "bbs.h"
extern int mail_reply();
extern char currdirect[MAXPATHLEN];

time_t board_note_time;
time_t board_visit_time;

static char *brd_title;
static int continue_flag;
int local_article;

#define UPDATE_USEREC   (currmode |= MODE_DIRTY)

static int
g_board_names(fhdr)
  boardheader *fhdr;
{
  AddNameList(fhdr->brdname);
  return 0;
}


void
make_blist()
{
  CreateNameList();
  apply_boards(g_board_names);
}

static int
g_bm_names(fhdr)
  boardheader *fhdr;
{
  char buf[IDLEN * 3 + 3];
  char* uid;

  strcpy(buf, fhdr->BM);
  uid = strtok(buf, "/");
  while (uid) {
     if (!InNameList(uid) && searchuser(uid))
        AddNameList(uid);
     uid = strtok(0, "/");
  }
  return 0;
}


make_bmlist()
{
  CreateNameList();
  apply_boards(g_bm_names);
}

void
set_board()
{
  boardheader *bp;
  boardheader *getbcache();

  bp = getbcache(currboard);
  board_note_time = bp->bupdate;
  brd_title = bp->BM;
  if (brd_title[0] <= ' ')
    brd_title = "¼x¨D¤¤";
  sprintf(currBM, "ªO¥D¡G%s", brd_title);
  brd_title = (bp->bvote == 1 ? "¥»¬ÝªO¶i¦æ§ë²¼¤¤" : bp->title + 7);

  currmode = (currmode & MODE_DIRTY) | MODE_STARTED;
/* MH */
  if(bp->bmode & MH_BMODE_POST)
  {
    char buf[200];
    
    setbfile(buf, bp->brdname, MH_FN_BRD_ALLOWPOST);
    if(belong(buf, cuser.userid))
    {
      currmode |= MODE_POST;
    }
    setbfile(buf, bp->brdname, MH_FN_BRD_DENYPOST);
    if(belong(buf, cuser.userid))
    {
      currmode &= ~MODE_POST;
    }
  }
/*    */
  else if (HAS_PERM(PERM_ALLBOARD) ||  /* MH */
    (HAS_PERM(PERM_BM) && is_BM(currBM + 6)))
  {
    currmode |= (MODE_BOARD | MODE_POST);
  }
  else if (haspostperm(currboard))
    currmode |= MODE_POST;
}

/* MH */
extern int thread_title;
/*    */

static
void
readtitle()
{
  showtitle(currBM, brd_title);
  if((currmode & MODE_SELECT) && thread_title == 1)
    outs("[¡ö]Â÷¶} [¡÷]¾\\Åª [^P]µoªí¤å³¹ [b]³Æ§Ñ¿ý [d]§R°£ [z]ºëµØ°Ï [TAB]¤åºK [h]elp\n"
         "[7m  ½s¸¹ ¦ê¦C¼Æ¥Ø ¦ê¦C±Ò©l§@ªÌ ¦ê  ¦C  ¼Ð  ÃD                                   [0m");
  else
    outs("[¡ö]Â÷¶} [¡÷]¾\\Åª [^P]µoªí¤å³¹ [b]³Æ§Ñ¿ý [d]§R°£ [z]ºëµØ°Ï [TAB]¤åºK [h]elp\n"
         "[7m  ½s¸¹   ¤é ´Á  §@  ªÌ       ¤å  ³¹  ¼Ð  ÃD                                   [0m");
}

void
readdoent(num, ent)
  int num;
  fileheader *ent;
{
  int type;
  char *mark, *title, color;

  type = brc_unread(ent->filename) ? '+' : ' ';

  if ((currmode & MODE_BOARD) && (ent->filemode & FILE_DIGEST))
    type = (type == ' ') ? '*' : '#';
  else if (ent->filemode & FILE_MARKED)
    type = (type == ' ') ? 'm' : 'M';

  if (ent->filemode & FILE_TAGED)
     type = 'D';

/* MH */
  if(ent->filemode & FILE_TDED)
    type = 'd';
/*    */

  title = subject(mark = ent->title);
  if (title == mark)
  {
    color = '1';
    mark = "¡¼";
  }
  else
  {
    color = '3';
    mark = "R:";
  }

  if (title[47])
    strcpy(title + 44, " ¡K");  /* §â¦h¾lªº string ¬å±¼ */

/* MH */
  mh_delete_esc(title);
/*    */

#ifdef MH_COLORFUL_READ
  {
    struct tm date;
    char buf[7];
    int mh_color;
    
    if((currmode & MODE_SELECT) && thread_title == 1)
      mh_color = 7;
    else
    {
      strncpy(buf, ent->date, 6);
      mh_strtodate(buf, &date);
      mh_color = mh_rc[(date.tm_mday - 1) % MH_RCS];
    }
    if (strncmp(currtitle, title, 40))
      prints("%6d %c [1;3%dm%-7s[0m%-13.12s%s %s\n", num, type, mh_color,
        ent->date, ent->owner, mark, title);
    else
      prints("%6d %c [1;3%dm%-7s[0m%-13.12s[1;3%cm%s %s[0m\n", num, type, mh_color,
        ent->date, ent->owner, color, mark, title);
  }
#else
  if (strncmp(currtitle, title, 40))
    prints("%6d %c %-7s%-13.12s%s %s\n", num, type,
      ent->date, ent->owner, mark, title);
  else
    prints("%6d %c %-7s%-13.12s[1;3%cm%s %s[0m\n", num, type,
      ent->date, ent->owner, color, mark, title);
#endif
}


int
cmpbnames(bname, brec)
  char *bname;
  boardheader *brec;
{
  return (!ci_strncmp(bname, brec->brdname, sizeof(brec->brdname)));
}


int
cmpfilename(fhdr)
  fileheader *fhdr;
{
  return (!strcmp(fhdr->filename, currfile));
}


/*
woju
*/
int
cmpfmode(fhdr)
  fileheader *fhdr;
{
  return (fhdr->filemode & currfmode);
}



int
do_select(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  static char bname[20];
  char bpath[60];
  struct stat st;

  move(0, 0);
  clrtoeol();
  make_blist();
  namecomplete(MSG_SELECT_BOARD, bpath);
  if (*bpath)
     strcpy(bname, bpath);

  setbpath(bpath, bname);
  if ((*bname == '\0') || (stat(bpath, &st) == -1))
  {
    move(2, 0);
    clrtoeol();
    outs(err_bid);
/*
woju
    pressanykey();
*/
    return FULLUPDATE;
  }

/*
  board_visit_time = 0x7fffffff;
*/
  brc_initial(bname);
  set_board();
  setbdir(direct, currboard);

  move(1, 0);
  clrtoeol();
  return NEWDIRECT;
}


/* ----------------------------------------------------- */
/* §ï¨} innbbsd Âà¥X«H¥ó¡B³s½u¬å«H¤§³B²zµ{§Ç             */
/* ----------------------------------------------------- */


outgo_post(fh, board)
  fileheader *fh;
  char *board;
{
  FILE *foo;

  if (foo = fopen("innd/out.bntp", "a"))
  {
    fprintf(foo, "%s\t%s\t%s\t%s\t%s\n", board,
      fh->filename, cuser.userid, cuser.username, fh->title);
    fclose(foo);
  }
}


void
cancelpost(fhdr, by_BM)
  fileheader *fhdr;
  int by_BM;
{
  int fd;
  char fpath[STRLEN];

  setbfile(fpath, currboard, fhdr->filename);
  if ((fd = open(fpath, O_RDONLY)) >= 0) {
#define NICK_LEN        80
    char *ptr, *left, *right, nick[NICK_LEN + 1];
    FILE *fout;
    int ch;
    fileheader postfile;
    char fn2[STRLEN], *brd, genbuf[200];

    brd = by_BM ? "deleted" : "junk";
    setbpath(fn2, brd);
    stampfile(fn2, &postfile);
    memcpy(postfile.owner, fhdr->owner, IDLEN + TTLEN + 10);
    postfile.savemode = 'D';
    sprintf(postfile.title, "%-32.32s - %s", fhdr->title, cuser.userid);

    if ((fhdr->savemode == 'S') &&/* ¥~Âà«H¥ó */
        (atoi(fhdr->filename + 2) > login_start_time - 7 * 86400)) {  /* 7 ¤Ñ¤§¤º¦³®Ä */
      ptr = nick;
      ch = read(fd, ptr, NICK_LEN);
      ptr[ch] = '\0';
      if (!strncmp(ptr, str_author1, LEN_AUTHOR1) ||
        !strncmp(ptr, str_author2, LEN_AUTHOR2))
      {
        if (left = (char *) strchr(ptr, '('))
        {
          right = NULL;
          for (ptr = ++left; ch = *ptr; ptr++)
          {
            if (ch == ')')
              right = ptr;
            else if (ch == '\n')
              break;
          }

          if (right != NULL)
          {
            *right = '\0';

            if (fout = fopen("innd/cancel.bntp", "a"))
            {
              fprintf(fout, "%s\t%s\t%s\t%s\t%s\n",
                currboard, fhdr->filename, fhdr->owner   /*  cuser.userid*/
                ,left, fhdr->title);
              fclose(fout);
            }
          }
        }
      }
    }
    close(fd);
    Rename(fpath, fn2);
    setbdir(genbuf, brd);
    append_record(genbuf, &postfile, sizeof(postfile));
#undef  NICK_LEN
  }
}


/* ----------------------------------------------------- */
/* µoªí¡B¦^À³¡B½s¿è¡BÂà¿ý¤å³¹                            */
/* ----------------------------------------------------- */


void
do_reply_title(row, title)
  int row;
  char *title;
{
  char genbuf[200];
  char genbuf2[4];

  if (ci_strncmp(title, str_reply, 4))
    sprintf(save_title, "Re: %s", title);
  else
    strcpy(save_title, title);
  save_title[TTLEN - 1] = '\0';
  sprintf(genbuf, "±Ä¥Î­ì¼ÐÃD¡m%.60s¡n¶Ü?[Y] ", str_decode(save_title));
  getdata(row, 0, genbuf, genbuf2, 4, LCECHO, 0);
  if (*genbuf2 == 'n')
    getdata(++row, 0, "¼ÐÃD¡G", save_title, TTLEN, DOECHO, save_title);
}


static void
do_reply(fhdr)
  fileheader *fhdr;
{
  char genbuf[200];
  int ent_as_flag = 0;

  if(HAVE_PERM(PERM_BASIC))
  /* by MH */
  /* ¨S¦³ PERM_BASIC ªº¤£¥i¥H¦^À³¦Ü«H½c */
  {
    getdata(b_lines - 1, 0, "¡¶ ¦^À³¦Ü (F)¬ÝªO (M)§@ªÌ«H½c (B)¤GªÌ¬Ò¬O (O)¨ä¥¦ (Q)¨ú®ø¡H[F] ", genbuf, 3, LCECHO, 0);
  }
  else
  {
    do
    {
      getdata(b_lines - 1, 0, "¡¶ ¦^À³¦Ü (F)¬ÝªO (Q)¨ú®ø¡H[F] ", genbuf, 3, LCECHO, 0);
    } while(genbuf[0] == 'o' || genbuf[0] == 'm' || genbuf[0] == 'b');
  }
  switch (genbuf[0])
  {
  case 'o':
    ent_as_flag = -1;
  case 'm':
    mail_reply(ent_as_flag, fhdr, 0);
  case 'q':
    break;

  case 'b':
    curredit = EDIT_BOTH;
  default:
    strcpy(currtitle, fhdr->title);
    strcpy(quote_user, fhdr->owner);
    quote_file[79] = fhdr->savemode;
    do_post();
  }
  *quote_file = 0;
}


/*
woju
*/
brdperm(char* brdname, char* userid)
{
   boardheader *bp;
   boardheader *getbcache();
   int uid = searchuser(userid);

   bp = getbcache(currboard);
   if (uid && bp) {
      int level = bp->level;
      char* ptr = bp->BM;
      char buf[64], manager[IDLEN + 1];
      userec xuser;

      get_record(fn_passwd, &xuser, sizeof(xuser), uid);
      if ((level & PERM_POSTMASK) || ((level)?xuser.userlevel&(level):1))
         return 1;

      if (ptr[0] <= ' ')
         return 0;

      if (userid_is_BM(userid, ptr))
         return 1;

      if ((level & 0xffff) != PERM_SYSOP)
         return 0;

      strncpy(manager, ptr, IDLEN + 1);
      if (ptr = strchr(manager, '/'))
         *ptr = 0;
      sethomefile(buf, manager, fn_overrides);
      return (belong(buf, userid));
   }
   return 0;
}

do_postnotify(char* fpath)
{
   fileheader mhdr;
   char title[128], buf1[80], buf[80];
   FILE* fp;
   char genbuf[200];

   setuserfile(genbuf, "postnotify");
   if (fp = fopen(genbuf, "r")) {
      char last_fname[80];
      boardheader *bp;
      boardheader *getbcache();

      strcpy(last_fname, fpath);
      bp = getbcache(currboard);
      while (fgets(buf, 80, fp))
         if (brdperm(currboard, buf)) {
            sethomepath(buf1, buf);
            stampfile(buf1, &mhdr);
            strcpy(mhdr.owner, cuser.userid);
            strcpy(mhdr.title, "[·s]");
            strncat(mhdr.title, save_title, TTLEN - 4);
            mhdr.savemode = 0;
            mhdr.filemode = 0;
            sethomedir(title, buf);
            append_record(title, &mhdr, sizeof(mhdr));
            unlink(buf1);
            Link(last_fname, buf1);
            strcpy(last_fname, buf1);
         }
      fclose(fp);
   }
}

do_unanonymous_post(char* fpath)
{
   fileheader mhdr;
   char title[128], buf1[80], buf[80];
   FILE* fp;
   char genbuf[200];

   setbpath(genbuf, UNANONYMOUS_BOARD);
   if (dashd(genbuf)) {
      stampfile(genbuf, &mhdr);
      unlink(genbuf);
      Link(fpath, genbuf);
      strcpy(mhdr.owner, cuser.userid);
      strcpy(mhdr.title, save_title);
      mhdr.savemode = 0;
      mhdr.filemode = 0;
      setbdir(title, UNANONYMOUS_BOARD);
      append_record(title, &mhdr, sizeof(mhdr));
   }
}


int
do_post()
{
  fileheader postfile;
  char fpath[80], buf[80];
  int aborted;
  char genbuf[200];

  clear();
  if (!(currmode & MODE_POST))
  {
    move(5, 10);
    outs("¹ï¤£°_¡A±z¥Ø«eµLªk¦b¦¹µoªí¤å³¹¡I");
    pressanykey();
    return FULLUPDATE;
  }

  more("etc/post.note", NA);
  prints("µoªí¤å³¹©ó¡i %s ¡j¬ÝªO\n\n", currboard);

  if (quote_file[0])
    do_reply_title(20, currtitle);
  else
    getdata(21, 0, "¼ÐÃD¡G", save_title, TTLEN, DOECHO, 0);

/* MH */
  mh_delete_esc(save_title);
/*    */

  if (save_title[0] == '\0')
    return FULLUPDATE;

  curredit &= ~EDIT_MAIL;
  setutmpmode(POSTING);

  /* ¥¼¨ã³Æ Internet Åv­­ªÌ¡A¥u¯à¦b¯¸¤ºµoªí¤å³¹ */

  if (HAS_PERM(PERM_INTERNET))
    local_article = 0;
  else
    local_article = 1;

  buf[0] = 0;

  aborted = vedit(buf, YEA);
  if (aborted == -1)
  {
    unlink(buf);
    pressanykey();
    return FULLUPDATE;
  }

  /* build filename */

  setbpath(fpath, currboard);
  stampfile(fpath, &postfile);
  Rename(buf, fpath);
  strcpy(postfile.owner, cuser.userid);

  /* set owner to Anonymous , for Anonymous board */

#ifdef HAVE_ANONYMOUS
  if (!strcmp(ANONYMOUS_BOARD, currboard))
    strcpy(postfile.owner, ANONYMOUS_USER);
#endif

  strcpy(postfile.title, save_title);
  if (aborted >= 1)             /* local save or too few words */ 
  {
    postfile.savemode = 'L';
    postfile.filemode = FILE_LOCAL;
  }
  else
    postfile.savemode = 'S';

  setbdir(buf, currboard);
  if (append_record(buf, &postfile, sizeof(postfile)) != -1)
  {
    if(currmode & MODE_SELECT)
      append_record(currdirect,&postfile,sizeof(postfile));
    if (aborted != 1)
      outgo_post(&postfile, currboard);

    brc_addlist(postfile.filename);
    outs("¶¶§Q¶K¥X§G§i¡A");

/* MH */
/*    if (strcmp(currboard, "Test"))
    {
      prints("³o¬O±zªº²Ä %d ½g¤å³¹¡C", ++cuser.numposts);
      UPDATE_USEREC;
    }
    else
      outs("´ú¸Õ«H¥ó¤£¦C¤J¬ö¿ý¡A·q½Ð¥]²[¡C");*/
      
    /* Tzu ¤Ó¤Ö¦r¤å³¹¤£ºâ¤å³¹¼Æ */  

    if (!belong("etc/NoCountBoards", currboard))
    /* ¦C¦b etc/NoCountBoards ¸Ìªº¬ÝªO¬Ò¤£ºâ¤å³¹¼Æ¡]Äé¤ô or ´ú¸ÕªO¡^ */
    {
      if (aborted == 2) 
        outs("\n\n\n[0;7m¤å³¹¤Óµu¤£¦C¤J¬ö¿ý¡A·q½Ð¥]²[¡C[0m\n\n\n");
      else {
        prints("³o¬O±zªº²Ä %d ½g¤å³¹¡C", ++cuser.numposts);
        UPDATE_USEREC;
      }
    }
    else if(strcmp(currboard, "Test") == 0)
      outs("´ú¸Õ¤å³¹¤£¦C¤J¬ö¿ý¡A·q½Ð¥]²[¡C");
    else
      outs("¦¹ªO¤å³¹¤£¦C¤J¬ö¿ý¡A·q½Ð¥]²[¡C");
/*    */

    /* ¦^À³¨ì­ì§@ªÌ«H½c */

    if (curredit & EDIT_BOTH)
    {
      char *str, *msg = "¦^À³¦Ü§@ªÌ«H½c";

      if (str = strchr(quote_user, '.'))
      {
        if (bbs_sendmail(fpath, save_title, str + 1) < 0)
          msg = "§@ªÌµLªk¦¬«H";
      }
      else
      {
        sethomepath(genbuf, quote_user);
        stampfile(genbuf, &postfile);
        unlink(genbuf);
        Link(fpath, genbuf);

        strcpy(postfile.owner, cuser.userid);
        strcpy(postfile.title, save_title);
        postfile.savemode = 'B';/* both-reply flag */
        sethomedir(genbuf, quote_user);
        if (append_record(genbuf, &postfile, sizeof(postfile)) == -1)
          msg = err_uid;
      }
      outs(msg);
      curredit ^= EDIT_BOTH;
    }
    if (strcmp(ANONYMOUS_BOARD, currboard))
       do_postnotify(fpath);
    else
       do_unanonymous_post(fpath);
  }
  pressanykey();
  return FULLUPDATE;
}


static int
reply_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  if (!(currmode & MODE_POST))
    return DONOTHING;

  setdirpath(quote_file, direct, fhdr->filename);
  do_reply(fhdr);
  *quote_file = 0;
  return FULLUPDATE;
}


static int
edit_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
   char fpath[80], fpath0[80];
   extern bad_user(char* name);
   char genbuf[200];
   fileheader postfile;
   int edit_mode;


   if (HAS_PERM(PERM_SYSOP) ||
       !strcmp(fhdr->owner, cuser.userid) && strcmp(cuser.userid, "guest") &&
       /* strcmp(currboard, ANONYMOUS_BOARD)  && */  !bad_user(cuser.userid))
      edit_mode = 0;
   else
      edit_mode = 2;

  setdirpath(genbuf, direct, fhdr->filename);
  local_article = fhdr->filemode & FILE_LOCAL;
  strcpy(save_title, fhdr->title);

  if (vedit(genbuf, edit_mode) != -1) {
/*
woju
     setbpath(fpath, currboard);
     stampfile(fpath, &postfile);
     unlink(fpath);
     setbfile(fpath0, currboard, fhdr->filename);
     Rename(fpath0, fpath);
     brc_addlist(postfile.filename);
     if (strcmp(currboard, ANONYMOUS_BOARD))
        do_postnotify(fpath);
     strcpy(fhdr->filename, postfile.filename);
*/
     strcpy(fhdr->title, save_title);
     substitute_record(direct, fhdr, sizeof(*fhdr), ent);
     return NEWDIRECT;
  }
  return FULLUPDATE;
}


static int
cross_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char xboard[20], fname[MAXPATHLEN], xfpath[80], xtitle[80], inputbuf[10];
  fileheader xfile;
  FILE *xptr;
  int author = 0;
  char genbuf[200];
  char genbuf2[4];

  make_blist();
  move(2, 0);
  clrtoeol();
  move(3, 0);
  clrtoeol();
  move(1, 0);
  namecomplete("Âà¿ý¥»¤å³¹©ó¬ÝªO¡G", xboard);
  if (*xboard == '\0' || !haspostperm(xboard))
    return FULLUPDATE;

  ent = 1;
  if (HAS_PERM(PERM_SYSOP) || !strcmp(fhdr->owner, cuser.userid))
  {
    getdata(2, 0, "(1)­ì¤åÂà¸ü (2)ÂÂÂà¿ý®æ¦¡¡H[1] ",
      genbuf, 3, DOECHO, 0);
    if (genbuf[0] != '2')
    {
      ent = 0;
      getdata(2, 0, "«O¯d­ì§@ªÌ¦WºÙ¶Ü?[Y] ", inputbuf, 3, DOECHO, 0);
      if (inputbuf[0] != 'n' && inputbuf[0] != 'N') author = 1;
    }
  }

  if (ent)
    sprintf(xtitle, "[Âà¿ý]%.66s", fhdr->title);
  else
    strcpy(xtitle, fhdr->title);

  sprintf(genbuf, "±Ä¥Î­ì¼ÐÃD¡m%.60s¡n¶Ü?[Y] ", str_decode(xtitle));
  getdata(2, 0, genbuf, genbuf2, 4, LCECHO, 0);
  if (*genbuf2 == 'n')
  {
    if (getdata(2, 0, "¼ÐÃD¡G", genbuf, TTLEN, DOECHO, xtitle))
      strcpy(xtitle, genbuf);
  }

  getdata(2, 0, "(S)¦sÀÉ (L)¯¸¤º (Q)¨ú®ø¡H[Q] ", genbuf, 3, LCECHO, 0);
  if (genbuf[0] == 'l' || genbuf[0] == 's')
  {
    int currmode0 = currmode;

    currmode = 0;
    setbpath(xfpath, xboard);
    stampfile(xfpath, &xfile);
    if (author)
      strcpy(xfile.owner, fhdr->owner);
    else
      strcpy(xfile.owner, cuser.userid);
    strcpy(xfile.title, xtitle);
    if (genbuf[0] == 'l')
    {
      xfile.savemode = 'L';
      xfile.filemode = FILE_LOCAL;
    }
    else
      xfile.savemode = 'S';

    strcpy(fname, direct);
    strcpy(strrchr(fname, '.'), fhdr->filename);
    if (ent)
    {
      xptr = fopen(xfpath, "w");

      strcpy(save_title, xfile.title);
      strcpy(xfpath, currboard);
      strcpy(currboard, xboard);
      write_header(xptr);
      strcpy(currboard, xfpath);

      fprintf(xptr, "¡° [¥»¤åÂà¿ý¦Û %s ¬ÝªO]\n\n", currboard);

      b_suckinfile(xptr, fname);
      fclose(xptr);
    }
    else
    {
      unlink(xfpath);
      Link(fname, xfpath);
    }

    setbdir(fname, xboard);
    append_record(fname, (char *) &xfile, sizeof(xfile));
    if (!xfile.filemode)
      outgo_post(&xfile, xboard);
    cuser.numposts++;
    UPDATE_USEREC;
    outs("¤å³¹Âà¿ý§¹¦¨");
    pressanykey();
    currmode = currmode0;
  }
  return FULLUPDATE;
}


static int
read_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char genbuf[200];
  int more_result;

  if (fhdr->owner[0] == '-')
    return DONOTHING;

  setdirpath(genbuf, direct, fhdr->filename);

  strcpy(vetitle, fhdr->title);
  if ((more_result = more(genbuf, YEA)) == -1)
    return DONOTHING;

  brc_addlist(fhdr->filename);
  strncpy(currtitle, subject(fhdr->title), 40);
  strncpy(currowner, subject(fhdr->owner), IDLEN + 2);

/*
woju
*/
  switch (more_result) {
  case 1:
     return READ_PREV;
  case 2:
     return RELATE_PREV;
  case 3:
     return READ_NEXT;
  case 4:
     return RELATE_NEXT;
  case 5:
     return RELATE_FIRST;
  case 6:
     return FULLUPDATE;
  case 7:
  case 8:
    if (currmode & MODE_POST)
    {
      strcpy(quote_file, genbuf);
      do_reply(fhdr);
      *quote_file = 0;
    }
    return FULLUPDATE;
  case 9:
     return 'A';
  case 10:
     return 'a';
  case 11:
     return '/';
  case 12:
     return '?';
  }


  outmsg("[34;46m  ¾\\Åª¤å³¹  [31;47m  (R/Y)[30m¦^«H [31m"
    "(=[]<>)[30m¬ÛÃö¥DÃD [31m(¡ô¡õ)[30m¤W¤U«Ê [31m(¡ö)[30mÂ÷¶}  [0m");

  switch (igetkey())
  {
  case 'q':
  case 'Q':
  case KEY_LEFT:
    break;

  case ' ':
  case KEY_RIGHT:
  case KEY_DOWN:
  case KEY_PGDN:
  case 'n':
  case Ctrl('N'):
    return READ_NEXT;

  case KEY_UP:
  case 'p':
  case Ctrl('P'):
  case KEY_PGUP:
    return READ_PREV;

  case '=':
    return RELATE_FIRST;

  case ']':
  case 't':
    return RELATE_NEXT;

  case '[':
    return RELATE_PREV;

  case '.':
  case '>':
    return THREAD_NEXT;

  case ',':
  case '<':
    return THREAD_PREV;

/* MH */
        case Ctrl('R'):
         mh_throw_water_ball();
         return FULLUPDATE;
/*    */

  case Ctrl('U'):
    t_users();
    return FULLUPDATE;
  case Ctrl('B'):
    m_read();
    return FULLUPDATE;
  case KEY_ESC: if (KEY_ESC_arg == 'n') {
     edit_note();
     return FULLUPDATE;
     }
     return DONOTHING;
  case Ctrl('I'):
    t_idle();
    return FULLUPDATE;
  case 'y':
  case 'r':
  case 'R':
  case 'Y':
    if (currmode & MODE_POST)
    {
      strcpy(quote_file, genbuf);
      do_reply(fhdr);
      *quote_file = 0;
    }
  }
  return FULLUPDATE;
}


/* ----------------------------------------------------- */
/* ±Ä¶°ºëµØ°Ï                                            */
/* ----------------------------------------------------- */


b_man()
{
  char buf[64];

  setapath(buf, currboard);
  a_menu(currboard, buf, HAS_PERM(PERM_ALLBOARD) ? 2 :
    (currmode & MODE_BOARD ? 1 : 0));
  return FULLUPDATE;
}



static int
cite_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char fpath[256];
  char title[TTLEN+1];

  if(currstat == RMAIL)
    sethomefile(fpath, cuser.userid, fhdr->filename);
  else
    setbfile(fpath, currboard, fhdr->filename);
  strcpy(title, "¡º ");
  strncpy(title+3, fhdr->title, TTLEN-3);
  title[TTLEN] = '\0';
  a_copyitem(fpath, title, fhdr->owner);
  b_man();
  return FULLUPDATE;
}


Cite_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char fpath[256];
  char title[TTLEN+1];

  if(currstat == RMAIL)
    sethomefile(fpath, cuser.userid, fhdr->filename);
  else
    setbfile(fpath, currboard, fhdr->filename);
  sprintf(title, "%s%.72s",
     (currutmp->pager > 1) ? "" : "¡º ", fhdr->title);
  title[TTLEN] = '\0';
  a_copyitem(fpath, title, fhdr->owner);
  load_paste();
  if (*paste_path)
     a_menu(paste_title, paste_path, paste_level);
  return FULLUPDATE;
}


Cite_posts(int ent, fileheader* fhdr, char* direct)
{
   char fpath[256];

   if(currstat == RMAIL)
     sethomefile(fpath, cuser.userid, fhdr->filename);
   else
     setbfile(fpath, currboard, fhdr->filename);
   load_paste();
   if (*paste_path && paste_level && dashf(fpath)) {
      fileheader fh;
      char newpath[MAXPATHLEN];

      strcpy(newpath, paste_path);
      stampfile(newpath, &fh);
      unlink(newpath);
      Link(fpath, newpath);
      strcpy(fh.owner, fhdr->owner);
      sprintf(fh.title, "%s%.72s",
         (currutmp->pager > 1) ? "" : "¡º ", fhdr->title);
      strcpy(strrchr(newpath, '/') + 1, ".DIR");
      append_record(newpath, &fh, sizeof(fh));
      return POS_NEXT;
   }
   bell();
   return DONOTHING;
}


Tag_posts(int ent, fileheader* fhdr, char* direct)
{
   char fpath[256];

   setbfile(fpath, currboard, fhdr->filename);
   load_paste();
   if (*paste_path && paste_level && dashf(fpath)) {
      fileheader fh;
      char newpath[MAXPATHLEN];

      strcpy(newpath, paste_path);
      stampfile(newpath, &fh);
      unlink(newpath);
      Link(fpath, newpath);
      strcpy(fh.owner, fhdr->owner);
      sprintf(fh.title, "%s%.72s",
         (currutmp->pager > 1) ? "" : "¡º ", fhdr->title);
      strcpy(strrchr(newpath, '/') + 1, ".DIR");
      append_record(newpath, &fh, sizeof(fh));
      return RELATE_NEXT;
   }
   bell();
   return DONOTHING;
}

Tag_mails(int ent, fileheader* fhdr, char* direct)
{
   char fpath[256];

   setbfile(fpath, currboard, fhdr->filename);
   if (HAS_PERM(PERM_BASIC) && dashf(fpath)) {
      fileheader fh;
      char newpath[MAXPATHLEN];

      sethomepath(newpath, cuser.userid);
      stampfile(newpath, &fh);
      unlink(newpath);
      Link(fpath, newpath);
      if (HAS_PERM(PERM_SYSOP))
         strcpy(fh.owner, fhdr->owner);
      else
         strcpy(fh.owner, cuser.userid);
      strcpy(fh.title, fhdr->title);
      strcpy(strrchr(newpath, '/') + 1, ".DIR");
      fh.savemode = 0;
      fh.filemode = FILE_READ;
      append_record(newpath, &fh, sizeof(fh));
      return RELATE_NEXT;
   }
   bell();
   return DONOTHING;
}



int
edit_title(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char genbuf[200];

  if (HAS_PERM(PERM_SYSOP))
  {
    fileheader tmpfhdr = *fhdr;
    int dirty = 0;

    if (getdata(b_lines - 1, 0, "¼ÐÃD¡G", genbuf, TTLEN, DOECHO, tmpfhdr.title))
    {
      strcpy(tmpfhdr.title, genbuf);
      dirty++;
    }

    if (getdata(b_lines - 1, 0, "§@ªÌ¡G", genbuf, IDLEN + 2, DOECHO, tmpfhdr.owner))
    {
      strcpy(tmpfhdr.owner, genbuf);
      dirty++;
    }

    if (getdata(b_lines - 1, 0, "¤é´Á¡G", genbuf, 6, DOECHO, tmpfhdr.date))
    {
      sprintf(tmpfhdr.date, "%+5s", genbuf);
      dirty++;
    }

    if (getdata(b_lines - 1, 0, "½T©w(Y/N)?[n] ", genbuf, 3, DOECHO, 0) &&
        *genbuf == 'y' && dirty) {
       *fhdr = tmpfhdr;
       substitute_record(direct, fhdr, sizeof(*fhdr), ent);
       if(currmode & MODE_SELECT)
       {
         int now;
         if(currstat == RMAIL)
           sethomedir(genbuf, cuser.userid);
         else
           setbdir(genbuf,currboard);
         now=getindex(genbuf,fhdr->filename);
         substitute_record(genbuf,fhdr,sizeof(*fhdr),now);
       }
    }
    return FULLUPDATE;
  }
  return DONOTHING;
}

/* MH */
extern int enter;
/*    */

static
post_tag(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
   if (currstat == READING && !(currmode & MODE_BOARD))
      return DONOTHING;

   fhdr->filemode ^= FILE_TAGED;
   if (currmode & MODE_SELECT) {
      int now;
      char genbuf[100];

      if(currstat == RMAIL)
        sethomedir(genbuf, cuser.userid);
      else
        setbdir(genbuf,currboard);
      now=getindex(genbuf,fhdr->filename);
      substitute_record(genbuf,fhdr,sizeof(*fhdr),now);
      if(currstat == RMAIL)
        sprintf(genbuf, "home/%s/SR.%s.%d", cuser.userid, cuser.userid, enter);
      else
        sprintf(genbuf, "boards/%s/SR.%s", currboard, cuser.userid);
      substitute_record(genbuf, fhdr, sizeof(*fhdr), ent);
   }
   else
      substitute_record(direct, fhdr, sizeof(*fhdr), ent);
   return POS_NEXT;
}

/* MH */
/* ¥Î¨Ó¼Ð°O¡u¤T¤Ñ«á§R°£¡v */
static
taged_delete(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
   if (currstat == READING && !(currmode & MODE_BOARD))
      return DONOTHING;

#if 1
   fhdr->filemode ^= FILE_TDED;
   if (currmode & MODE_SELECT) {
      int now;
      char genbuf[100];

      if(currstat == RMAIL)
        sethomedir(genbuf, cuser.userid);
      else
        setbdir(genbuf,currboard);
      now=getindex(genbuf,fhdr->filename);
      substitute_record(genbuf,fhdr,sizeof(*fhdr),now);
      if(currstat == RMAIL)
        sprintf(genbuf, "home/%s/SR.%s.%d", cuser.userid, cuser.userid, enter);
      else
        sprintf(genbuf, "boards/%s/SR.%s", currboard, cuser.userid);
      substitute_record(genbuf, fhdr, sizeof(*fhdr), ent);
   }
   else
      substitute_record(direct, fhdr, sizeof(*fhdr), ent);
#else
   fhdr->filemode ^= FILE_TDED;
   if (currmode & MODE_SELECT) {
      int now;
      char genbuf[100];

      if(currstat == RMAIL)
        sprintf(genbuf, "home/%s/SR.%s.%d", cuser.userid, cuser.userid, enter);
      else
        sprintf(genbuf, "boards/%s/SR.%s", currboard, cuser.userid);
      substitute_record(genbuf, fhdr, sizeof(*fhdr), ent);
   }
#endif
   return POS_NEXT;
}
/*    */

static int
post_del_tag(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char genbuf[3];

  if ((currstat != READING) || (currmode & MODE_BOARD)) {
     getdata(1, 0, "½T©w§R°£¼Ð°O¤å³¹(Y/N)? [N]", genbuf, 3, LCECHO, 0);
     if (genbuf[0] == 'y')
     {
       char buf[STRLEN];

       currfmode = FILE_TAGED;
       if (currmode & MODE_SELECT){
         unlink(direct);
         currmode ^= MODE_SELECT;
        if(currstat == RMAIL)
          sethomedir(direct, cuser.userid);
        else
          setbdir(direct, currboard);
         delete_files(direct, cmpfmode);
       }
       if (delete_files(direct, cmpfmode))
          return DIRCHANGED;
     }
     return FULLUPDATE;
  }
  return DONOTHING;
}




static int
mark_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{

   if (!(currmode & MODE_BOARD))
      return DONOTHING;

   fhdr->filemode ^= FILE_MARKED;
   if( currmode & MODE_SELECT) {
      int now;
      char genbuf[100];

      if(currstat == RMAIL)
        sethomedir(genbuf, cuser.userid);
      else
        setbdir(genbuf,currboard);
      now = getindex(genbuf,fhdr->filename);
      substitute_record(genbuf, fhdr, sizeof(*fhdr), now);
   }
   else
      substitute_record(direct, fhdr, sizeof(*fhdr), ent);
   return PART_REDRAW;
}


int
del_range(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char num1[8], num2[8];
  int inum1, inum2;
  char genbuf[100], genbuf2[100];
  fileheader rsfh;
  FILE *fp;
  time_t now=time(0);

  if ((currstat != READING) || (currmode & MODE_BOARD))
  {
    getdata(1, 0, "[³]©w§R°£½d³ò] °_ÂI¡G", num1, 5, DOECHO, 0);
    inum1 = atoi(num1);
    if (inum1 <= 0)
    {
      outmsg("°_ÂI¦³»~");
      refresh();
      sleep(1);
      return FULLUPDATE;
    }
    getdata(1, 28, "²×ÂI¡G", num2, 5, DOECHO, 0);
    inum2 = atoi(num2);
    if (inum2 < inum1)
    {
      outmsg("²×ÂI¦³»~");
      refresh();
      sleep(1);
      return FULLUPDATE;
    }
    getdata(1, 48, msg_sure_ny, num1, 3, LCECHO, 0);
    if (*num1 == 'y')
    {
       outmsg("³B²z¤¤,½Ðµy«á...");
       refresh();
       if(currmode & MODE_SELECT)
       {
           int fd,size=sizeof(fileheader);


           int i=inum1,now;
           
           if(currstat==RMAIL) 
             sethomedir(genbuf,cuser.userid);
           else 
             setbdir(genbuf,currboard);
           if((fd=(open(direct,O_RDONLY, 0)))!=-1)
           {
             if (lseek(fd, (off_t)(size * (inum1 - 1)), SEEK_SET) != -1)
             {
               while(read(fd,&rsfh,size) == size)
               {
                  if(i>inum2)
                     break;
                   now=getindex(genbuf,rsfh.filename);
                   strcpy(currfile,rsfh.filename);
                   delete_file (genbuf, sizeof(fileheader), now, cmpfilename);
                   i++;
               }
             }
             close(fd);
           }
       }
      delete_range(direct, inum1, inum2, NULL);
      fixkeep(direct, inum1);

      /* Tzu: ²MªO°O¿ý */      
      if(currstat == READING) {
        setbfile(genbuf2, currboard, "delrange");
        if((fp = fopen(genbuf2, "w"))!=NULL) {  
          sprintf (genbuf,"§@ªÌ: %s ¬ÝªO: %s\n", cuser.userid, currboard);
          fputs(genbuf,fp);
          sprintf(genbuf,"¼ÐÃD: [²MªO³ø§i] %s\n", currboard);
          fputs (genbuf,fp);
          sprintf (genbuf,"®É¶¡: %s\n\n",ctime(&now));
          fputs (genbuf,fp);  
          sprintf (genbuf,"\n%s ¤j¤M¤@¬å, \n\n%s ªO²Ä %d ½g¨ì²Ä %d ½g\
³Q²M±o¤@°®¤G²b, µ·²@¤£¯d²ª¸ñ.\n", cuser.userid, currboard, inum1, inum2);
          fputs (genbuf,fp);          
        
          setbpath(genbuf, "junk");
          stampfile(genbuf, &rsfh);
          Rename(genbuf2, genbuf);
          sprintf(genbuf2, "[²MªO³ø§i] %s", currboard);
          strcpy(rsfh.title, genbuf2);
          strcpy(rsfh.owner, cuser.userid);
          setbdir(genbuf, "junk");
          append_record(genbuf, &rsfh, sizeof(rsfh));  
          fclose(fp);
        }  
      }
      /*      */
      
      return DIRCHANGED;
    }
    return FULLUPDATE;
  }
  return DONOTHING;
}


static void
lazy_delete(fhdr)
  fileheader *fhdr;
{
  char buf[20];

  sprintf(buf, "-%s", fhdr->owner);
  strncpy(fhdr->owner, buf, IDLEN + 1);
  strcpy(fhdr->title, "<< article deleted >>");
  fhdr->savemode = 'L';
}


void
cancelpostnotify(fhdr)
  fileheader *fhdr;
{
  char fpath[STRLEN];
  FILE *fp;

  setuserfile(fpath, "postnotify");
   if (fp = fopen(fpath, "r"))
   {
      char buf[80];
      while (fgets(buf, 80, fp))
      {
        char genbuf[STRLEN];
        int now;
        sethomedir(genbuf, buf);
        now=getindex(genbuf,fhdr->filename);
        delete_file (genbuf, sizeof(fileheader),now,cmpfilename);
      }
      fclose(fp);
   }
}



static int
del_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char buf[80];
  char *t;
  int not_owned;
  char genbuf[4];

  if ((fhdr->filemode & FILE_MARKED)
      || (fhdr->filemode & FILE_DIGEST) || (fhdr->owner[0] == '-'))
    return DONOTHING;

  not_owned = strcmp(fhdr->owner, cuser.userid);

  if (!(currmode & MODE_BOARD) && not_owned || !strcmp(cuser.userid, "guest"))
    return DONOTHING;

  getdata(1, 0, msg_del_ny, genbuf, 3, LCECHO, 0);
  if (genbuf[0] == 'y')
  {
    strcpy(currfile, fhdr->filename);

/*
    if (!update_file(direct, sizeof(fileheader), ent, cmpfilename, lazy_delete))
*/
   if (!delete_file (direct, sizeof(fileheader), ent, cmpfilename)) {
      if( currmode & MODE_SELECT ){
        int now;
        char genbuf[100];
        if(currstat == RMAIL)
          sethomedir(genbuf, cuser.userid);
        else
          setbdir(genbuf,currboard);
        now=getindex(genbuf,fhdr->filename);
        delete_file (genbuf, sizeof(fileheader),now,cmpfilename);
      }
      cancelpost(fhdr, not_owned);
      cancelpostnotify(fhdr);
/* MH */
/*      if (!not_owned && strcmp(currboard, "Test"))*/
      if (!not_owned && !belong("etc/NoCountBoards", currboard))
      /* ¦pªG¬O§R°£¡u¤£ºâ¤å³¹½g¼Æ¡vªO¸Ì­±ªº¤å³¹´N¤£­n´î¤å³¹½g¼Æ */
      {
        if (cuser.numposts)
          cuser.numposts--;
        UPDATE_USEREC;
        move(b_lines - 1, 0);
        clrtoeol();
        prints("%s¡A±zªº¤å³¹´î¬° %d ½g", msg_del_ok, cuser.numposts);
        refresh();
        sleep(1);
      }
/*
      lazy_delete(fhdr);
      return FULLUPDATE;
*/
      return DIRCHANGED;
    }
  }
  return FULLUPDATE;
}


/* ----------------------------------------------------- */
/* ¨Ì§ÇÅª·s¤å³¹                                          */
/* ----------------------------------------------------- */

static int sequent_ent;


static int
sequent_messages(fptr)
  fileheader *fptr;
{
  static int idc;
  char ans[6];
  char genbuf[200];

  if (fptr == NULL)
    return (idc = 0);

  if (++idc < sequent_ent)
    return 0;

  if (!brc_unread(fptr->filename))
    return 0;

  if (continue_flag)
  {
    genbuf[0] = 'y';
  }
  else
  {
    prints("Åª¨ú¤å³¹©ó¡G[%s] §@ªÌ¡G[%s]\n¼ÐÃD¡G[%s]",
      currboard, fptr->owner, fptr->title);
    getdata(3, 0, "(Y/N/Quit) [Y]: ", genbuf, 3, LCECHO, 0);
  }

  if (genbuf[0] != 'y' && genbuf[0])
  {
    clear();
    return (genbuf[0] == 'q' ? QUIT : 0);
  }

  setbfile(genbuf, currboard, fptr->filename);
  brc_addlist(fptr->filename);

  strcpy(vetitle, fptr->title);
  if (more(genbuf, YEA) == 0)
     outmsg("[31;47m  [31m(R)[30m¦^«H  [31m(¡õ,n)[30m¤U¤@«Ê  [31m(¡ö,q)[30mÂ÷¶}  [0m");
  continue_flag = 0;

  switch (igetkey())
  {
  case KEY_LEFT:
  case 'e':
  case 'q':
  case 'Q':
    break;

  case 'y':
  case 'r':
  case 'Y':
  case 'R':
    if (currmode & MODE_POST)
    {
      strcpy(quote_file, genbuf);
      do_reply(fptr);
      *quote_file = 0;
    }
    break;

  case ' ':
  case KEY_DOWN:
  case '\n':
  case 'n':
    continue_flag = 1;
  }

  clear();
  return 0;
}


static int
sequential_read(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char buf[40];

  clear();
  sequent_messages((fileheader *) NULL);
  sequent_ent = ent;
  continue_flag = 0;
  setbdir(buf, currboard);
  apply_record(buf, sequent_messages, sizeof(fileheader));
  return FULLUPDATE;
}

save_mail(int ent, fileheader *fh, char* direct)
{
   fileheader mhdr;
   char fpath[MAXPATHLEN];
   char genbuf[MAXPATHLEN];
   char *p;

   if (ent < 0)
      strcpy(fpath, direct);
   else {
      strcpy(genbuf, direct);
      if (p = strrchr(genbuf, '/'))
         *p = '\0';
      sprintf(fpath, "%s/%s", genbuf, fh->filename);
   }
   if (!dashf(fpath) || !HAS_PERM(PERM_BASIC)) {
      bell();
      return DONOTHING;
   }
   sethomepath(genbuf, cuser.userid);
   stampfile(genbuf, &mhdr);
   unlink(genbuf);
   Link(fpath, genbuf);
   if (HAS_PERM(PERM_SYSOP))
      strcpy(mhdr.owner, fh->owner);
   else
      strcpy(mhdr.owner, cuser.userid);
   strncpy(mhdr.title, fh->title + ((currstat == ANNOUNCE) ? 3 : 0), TTLEN);
   mhdr.savemode = '\0';
   mhdr.filemode = FILE_READ;
   sethomedir(fpath, cuser.userid);
   if (append_record(fpath, &mhdr, sizeof(mhdr)) == -1) {
      bell();
      return DONOTHING;
   }
   return POS_NEXT;
}



/* ----------------------------------------------------- */
/* ¬ÝªO³Æ§Ñ¿ý¡B¤åºK¡BºëµØ°Ï                              */
/* ----------------------------------------------------- */


static int
b_notes_edit()
{
  if (currmode & MODE_BOARD)
  {
    struct stat st;
    char buf[64];
    int aborted;

    setbfile(buf, currboard, fn_notes);
    aborted = vedit(buf, NA);
    if (aborted)
    {
      clear();
      outs(msg_cancel);
      pressanykey();
    }
    else
    {
      boardheader fh;
      int pos;

      getdata(3, 0, "½Ð³]©w¦³®Ä´Á­­(0 - 9999)¤Ñ¡H", buf, 5, DOECHO, "9999");
      aborted = atol(buf);
      pos = search_record(fn_board, &fh, sizeof(fh), cmpbnames, currboard);
      fh.bupdate = aborted ? time(0) + aborted * 86400 : 0;
      substitute_record(fn_board, &fh, sizeof(fh), pos);
      touch_boards();
    }
    return FULLUPDATE;
  }
  return 0;
}

static int
b_water_edit()
{
  if (currmode & MODE_BOARD)
  {
    struct stat st;
    char buf[64];
    int aborted;

    setbfile(buf, currboard, fn_water);
    vedit(buf, NA);
    return FULLUPDATE;
  }
  return 0;
}


static int
b_notes()
{
  char buf[64];

  setbfile(buf, currboard, fn_notes);
  if (more(buf, NA) == -1)
  {
    clear();
    move(4, 20);
    outs("¥»¬ÝªO©|µL¡u³Æ§Ñ¿ý¡v¡C");
  }
  pressanykey();
  return FULLUPDATE;
}


int
board_select()
{
  char fpath[80];
  char genbuf[100];
  currmode &= ~MODE_SELECT;
  /*sprintf(fpath,"SR.%s",cuser.userid);*/
   if(currstat==RMAIL)
   {
     sprintf(genbuf, "home/%s/SR.%s.%d", cuser.userid, cuser.userid, enter);
   /*setuserfile(genbuf, fpath);*/
   unlink(genbuf);
   }
   else
   {
     sprintf(genbuf, "boards/%s/SR.%s", currboard, cuser.userid);
   /*setbfile(genbuf, currboard, fpath);*/
   unlink(genbuf);
   }
  if(currstat==RMAIL)
    sethomedir(currdirect,cuser.userid);
  else
    setbdir(currdirect, currboard);
  return NEWDIRECT;
}



int
board_digest()
{
  if(currmode & MODE_SELECT)
    board_select();
  currmode ^= MODE_DIGEST;
  if (currmode & MODE_DIGEST)
    currmode &= ~MODE_POST;
  else if (haspostperm(currboard))
    currmode |= MODE_POST;

  if(currstat == RMAIL)
    sethomedir(currdirect, cuser.userid);
  else
    setbdir(currdirect, currboard);
  return NEWDIRECT;
}


int
board_etc()
{
  if (!HAS_PERM(PERM_SYSOP))
     return DONOTHING;
  currmode ^= MODE_ETC;
  if (currmode & MODE_ETC)
    currmode &= ~MODE_POST;
  else if (haspostperm(currboard))
    currmode |= MODE_POST;

  if(currstat == RMAIL)
    sethomedir(currdirect, cuser.userid);
  else
    setbdir(currdirect, currboard);
  return NEWDIRECT;
}


static int
good_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char genbuf[200];
  char genbuf2[200];

  if ((currmode & MODE_DIGEST) || !(currmode & MODE_BOARD))
    return DONOTHING;

  if (fhdr->filemode & FILE_DIGEST)
  {
    fhdr->filemode = (fhdr->filemode & ~FILE_DIGEST);
  }
  else
  {
    fileheader digest;
    char *ptr, buf[64];

    memcpy(&digest, fhdr, sizeof(digest));
    digest.filename[0] = 'G';
    strcpy(buf, direct);
    ptr = strrchr(buf, '/') + 1;
    ptr[0] = '\0';
    sprintf(genbuf, "%s%s", buf, digest.filename);
    if (!dashf(genbuf)) {
       digest.savemode = digest.filemode = 0;
       sprintf(genbuf2, "%s%s", buf, fhdr->filename);
       Link(genbuf2, genbuf);
       strcpy(ptr, fn_mandex);
       append_record(buf, &digest, sizeof(digest));
    }
    fhdr->filemode = (fhdr->filemode & ~FILE_MARKED) | FILE_DIGEST;
  }
  substitute_record(direct, fhdr, sizeof(*fhdr), ent);
  if( currmode & MODE_SELECT){
    int now;
    char genbuf[100];
    setbdir(genbuf,currboard);
    now=getindex(genbuf,fhdr->filename);
    substitute_record(genbuf,fhdr,sizeof(*fhdr),now);
  }
  return PART_REDRAW;
}


/* help for board reading */

static char *board_help[] =
{
  "\0¥þ¥\\¯à¬ÝªO¾Þ§@»¡©ú",
  "\01°ò¥»©R¥O",
  "(p)(¡ô)   ¤W²¾¤@½g¤å³¹          (^P)     µoªí¤å³¹",
  "(n)(¡õ)   ¤U²¾¤@½g¤å³¹          (d)      §R°£¤å³¹",
  "(P)(PgUp) ¤W²¾¤@­¶              (^S,^T)  ±N¤å³¹/¦P¥DÃD¦s¦Ü«H½c",
  "(N)(PgDn) ¤U²¾¤@­¶              (##)     ¸õ¨ì ## ¸¹¤å³¹",
  "(r)(¡÷)   ¾\\Åª¦¹½g¤å³¹          ($)      ¸õ¨ì³Ì«á¤@½g¤å³¹",
  "\01¶i¶¥©R¥O",
  "(tab)/z   ¤åºK¼Ò¦¡/ºëµØ°Ï       (a)(A)   §ä´M§@ªÌ",
  "(b)       ®iÅª³Æ§Ñ¿ý            (?)(/)   §ä´M¼ÐÃD",
  "(V,R)     §ë²¼/¬d¸ß§ë²¼µ²ªG     (=)      §ä´M­º½g¤å³¹",
  "(x)       Âà¿ý¤å³¹¨ì¨ä¥L¬ÝªO    ([]<>-+) ¥DÃD¦¡¾\\Åª",

#ifdef INTERNET_EMAIL
  "(F)       ±N¤å³¹±H¦^ Internet ¶l½c",
  "(U)       ±N¤å³¹ uuencode «á±H¦^¶l½c",
#endif
  "(Z)       Z-modem ¶ÇÀÉ",
  "(E)       ­«½s¤å³¹",

  "\01ªO¥D©R¥O",
  "(m)       «O¯d¦¹½g¤å³¹          (W/w)   ½s¿è³Æ§Ñ¿ý/¤ô±í¦W³æ",
  "(M)       Á|¦æ§ë²¼              (c/g)   ¿ï¿ýºëµØ/¤åºK",
  "(D)       §R°£¤@¬q½d³òªº¤å³¹    (T)     ­«½s¤å³¹¼ÐÃD",

  NULL
};


static int
b_help()
{
  show_help(board_help);
  return FULLUPDATE;
}


/* ----------------------------------------------------- */
/* ¬ÝªO¥\¯àªí                                            */
/* ----------------------------------------------------- */


extern int b_vote();
extern int b_results();
extern int b_vote_maintain();

struct one_key read_comms[] = {
  KEY_TAB, board_digest,
  Ctrl('E'), board_etc,
  'b', b_notes,
  'c', cite_post,
  'C', Cite_post,
  Ctrl('C'), Cite_posts,
  Ctrl('A'), Tag_posts,
  Ctrl('T'), Tag_mails,
  'r', read_post,
  'z', b_man,
  'D', del_range,
/*
woju
  'S', sequential_read,
*/
  Ctrl('S'), save_mail,
  'E', edit_post,
  'T', edit_title,
  's', do_select,
  'R', b_results,
  'V', b_vote,
  'M', b_vote_maintain,
  'W', b_notes_edit,
  't', post_tag,
  '`', taged_delete,
  'w', b_water_edit,
  Ctrl('D'), post_del_tag,
  'x', cross_post,
  'h', b_help,
  'g', good_post,
  'y', reply_post,
  'd', del_post,
  'm', mark_post,
  Ctrl('P'), do_post,

  '\0', NULL
};

ReadSelect()
{
   int mode0 = currutmp->mode;
   int stat0 = currstat;
   char genbuf[200];

   currstat = XMODE;
   if (do_select(0, 0, genbuf) == NEWDIRECT)
      Read();
   currutmp->mode = mode0;
   currstat = stat0;
}


int
Read()
{
  int mode0 = currutmp->mode;
  int stat0 = currstat;
  char buf[40];

  /* MH */
  /*    */

  setutmpmode(READING);
  set_board();
  if (board_visit_time < board_note_time)
  {
    setbfile(buf, currboard, fn_notes);
    more(buf, NA);
    pressanykey();
  }

  setbdir(buf, currboard);
  curredit &= ~EDIT_MAIL;
  i_read(READING, buf, readtitle, readdoent, read_comms);
  brc_update();
  currutmp->mode = mode0;
  currstat = stat0;
  return 0;
}


int
Select()
{
  char genbuf[200];

  setutmpmode(SELECT);
  do_select(0, NULL, genbuf);
  return 0;
}


int
Post()
{
  do_post();
  return 0;
}
