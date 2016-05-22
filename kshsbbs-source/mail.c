/*-------------------------------------------------------*/
/* mail.c       ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : local/internet mail routines                 */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


extern int del_range();
extern int cmpfmode();

char currmaildir[32];
static char msg_cc[] = "[32m[¸s²Õ¦W³æ][0m\n";
static char listfile[] = "list.0";


#ifdef INTERNET_PRIVATE_EMAIL
static int
invalidaddr(addr)
  char *addr;
{
  if (*addr == '\0')
    return 1;                   /* blank */
  while (*addr)
  {
    if (not_alnum(*addr) && !strchr("[].%!@:-_", *addr))
      return 1;
    addr++;
  }
  return 0;
}

int
m_internet()
{
  char receiver[60];

  stand_title("Internet Mail");
  getdata(1, 0, "¦¬«H¤H¡G", receiver, 60, DOECHO, 0);
  if (strchr(receiver, '@') && !invalidaddr(receiver) &&
    getdata(2, 0, "¥D  ÃD¡G", save_title, TTLEN, DOECHO, 0))
  {
    do_send(receiver, save_title);
  }
  else
  {
    move(22, 0);
    outs("¦¬«H¤H©Î¥DÃD¤£¥¿½T, ½Ð­«·s¿ï¨ú«ü¥O");
    pressanykey();
  }
  return 0;
}
#endif


void
m_init()
{
  sethomedir(currmaildir, cuser.userid);
}


int
chkmailbox(void)
{
  if (!HAVE_PERM(PERM_SYSOP) && !HAVE_PERM(PERM_MAILLIMIT))
  {
    int keep, sum;
    int sumlimit;

    if (HAS_PERM(PERM_BM))
       sumlimit = MH_MAILSUM_BM;  /* MH */
    else if (HAS_PERM(PERM_LOGINOK))
       sumlimit = MH_MAILSUM_LOGINOK;  /* MH */
    else
       sumlimit = MH_MAILSUM_BASIC;  /* MH */

    m_init();
    if ((keep = get_num_records(currmaildir, sizeof(fileheader))) > MAXKEEPMAIL)
    {
      move(b_lines, 0);
      clrtoeol();
      bell();
      prints("±z«O¦s±¡®Ñ¼Æ¥Ø %d ¶W¥X¤W­­ %d, ½Ð¾ã²z", keep, MAXKEEPMAIL);
      bell();
      refresh();
      igetch();
      return keep;
    }
    if ((sum = get_sum_records(currmaildir, sizeof(fileheader))) > sumlimit)
    {
      move(b_lines, 0);
      clrtoeol();
      bell();
      prints("±z«O¦s±¡®Ñ®e¶q %d(k)¶W¥X¤W­­ %d(k), ½Ð¾ã²z", sum, sumlimit);
      bell();
      refresh();
      igetch();
      return keep;
    }
  }
  return 0;
}


static void
do_hold_mail(fpath, receiver, holder)
  char *fpath;
  char *receiver;
  char *holder;
{
  char buf[80], title[128];

  fileheader mymail;

  sethomepath(buf, holder);
  stampfile(buf, &mymail);

  mymail.savemode = 'H';        /* hold-mail flag */
  mymail.filemode = FILE_READ;
  strcpy(mymail.owner, "[³Æ.§Ñ.¿ý]");
  if (receiver)
  {
    sprintf(title, "(%s) %s", receiver, save_title);
    strncpy(mymail.title, title, TTLEN);
  }
  else
    strcpy(mymail.title, save_title);

  if(mh_memoforward(holder, fpath, &mymail, sizeof(mymail)))
  {
    sethomedir(title, holder);
    if (append_record(title, &mymail, sizeof(mymail)) != -1)
    {
      unlink(buf);
      Link(fpath, buf);
    }
  }
}


static void
hold_mail(fpath, receiver)
  char *fpath;
  char *receiver;
{
  char buf[4];

  getdata(b_lines - 1, 0, "¬O§_¦Û¦s©³½Z(Y/N)¡H[N] ", buf, 4, LCECHO, 0);

  if (buf[0] == 'y')
    do_hold_mail(fpath, receiver, cuser.userid);
  if (is_watched(cuser.userid))
    do_hold_mail(fpath, receiver, "SYSOP");
}


int
do_send(userid, title)
  char *userid, *title;
{
  fileheader mhdr;
  struct stat st;
  char fpath[STRLEN], buf[80], *ip;
  char receiver[IDLEN];
  int fp;
  char genbuf[200];

#ifdef INTERNET_PRIVATE_EMAIL
  int internet_mail;

  if (strchr(userid, '@'))
  {
    internet_mail = 1;
  }
  else
  {
    internet_mail = 0;
#endif
    if (!getuser(userid))
      return -1;
    if (!(xuser.userlevel & PERM_READMAIL))
      return -3;

    if (!title)
      getdata(2, 0, "¥DÃD¡G", save_title, TTLEN, DOECHO, 0);
    /* MH */
    mh_delete_esc(save_title);
    /*    */
/*    curredit |= EDIT_MAIL;*/

#ifdef INTERNET_PRIVATE_EMAIL
  }
#endif
  curredit |= EDIT_MAIL;

  setutmpmode(SMAIL);

  fpath[0] = '\0';

#ifdef INTERNET_PRIVATE_EMAIL
  if (internet_mail)
  {
    int res, ch;
    char ans[4];
    char cmd[200];
    char pgppath[200];
    char publist[200];
    char* s;

    sprintf(pgppath, "home/%s/pgp", cuser.userid);
    sprintf(publist, "home/%s/publist", cuser.userid);

    if (s = Belong(publist, userid, ".@ \n\r\t")) {
       getdata(3, 0, "¦¬«H¤H¡G", receiver, TTLEN, DOECHO, s);
       if (strchr(receiver, '@'))
          strcpy(userid, receiver);
    }
    strcpy(receiver, userid);

    if (vedit(fpath, NA) == -1)
    {
      unlink(fpath);
      clear();
      return -2;
    }
    clear();
    strcpy(userid, receiver);
    prints("«H¥ó§Y±N±Hµ¹ %s\n¼ÐÃD¬°¡G%s\n", userid, title);

    if (dashd(pgppath))
       getdata(4, 0, "(S)±H¥X (P)¥ÎPGP½s½X (Q)©ñ±ó [S]? ", ans, 4, LCECHO, 0);
    else
       getdata(4, 0, "(S)±H¥X (Q)©ñ±ó [S]? ", ans, 4, LCECHO, 0);

    s = fpath + strlen(fpath);
    switch (*ans)
    {
    case 'q':
      outs("«H¥ó¤w¨ú®ø\n");
      res = -2;
      break;

    case 'p':
       if (dashd(pgppath)) {
           if (!belong(publist, userid)) {
              char buf[200];

              sprintf(buf, "<%s> ¤£¦b pgplist ùØ¡A¨ú®ø±H¥X¡C\n", userid);
              move(10, 0);
              outs(buf);
              hold_mail(fpath, userid);
              break;
           }
           outmsg("PGP½s½X¤¤...");
           refresh();
           sprintf(cmd, "PGPPATH=%s; export PGPPATH; /usr/local/bin/pgp +batchmode -ea %s %s > /dev/null 2>&1",
              pgppath, fpath, userid);
           system(cmd);
           strcpy(s, ".asc");
           if (!dashf(fpath)) {
              move(10, 0);
              outs("½s½X¥¢±Ñ\n");
              *s = 0;
              hold_mail(fpath, userid);
              break;
           }
       }
    default:
      outmsg("½Ðµy­Ô, «H¥ó¶Ç»¼¤¤...");
      refresh();
      res = bbs_sendmail(fpath, title, userid);
      if (*s == '.') {
         unlink(fpath);
         *s = 0;
      }
      outmsg("¤w¦¨¥\\±H¥X");
      hold_mail(fpath, userid);
    }
    unlink(fpath);
    return res;
  }
  else
  {
#endif

    if (vedit(fpath, YEA) == -1)
    {
      unlink(fpath);
      clear();
      return -2;
    }
    clear();

    sethomepath(genbuf, userid);
    stampfile(genbuf, &mhdr);
    Rename(fpath, genbuf);
    strcpy(mhdr.owner, cuser.userid);
    strncpy(mhdr.title, save_title, TTLEN);
    mhdr.savemode = '\0';

    if(mh_autoforward(userid, &mhdr, sizeof(mhdr), 1))
    {
      sethomedir(fpath, userid);
      if (append_record(fpath, &mhdr, sizeof(mhdr)) == -1)
        return -1;
    }
    else
    {
      unlink(genbuf);
    }
    hold_mail(genbuf, userid);
    return 0;

#ifdef INTERNET_PRIVATE_EMAIL
  }
#endif
}


void
my_send(uident)
  char *uident;
{
  switch (do_send(uident, NULL))
  {
  case -1:
    outs(err_uid);
    break;
  case -2:
    outs(msg_cancel);
    break;
  case -3:
    prints("¨Ï¥ÎªÌ [%s] µLªk¦¬«H", uident);
    break;
  }
  pressanykey();
}


int
m_send()
{
  char uident[40];

  stand_title("®ü­·ªº¸Ü");
  usercomplete(msg_uid, uident);
  if (uident[0])
    my_send(uident);
  return 0;
}


/* ------------------------------------------------------------ */
/* ¸s²Õ±H«H¡B¦^«H : multi_send, multi_reply                      */
/* ------------------------------------------------------------ */

extern struct word *toplev;


static void
multi_list(reciper)
  int *reciper;
{
  char uid[16];
  char genbuf[200];

  while (1)
  {
    stand_title("¸s²Õ§@·~");
    ShowNameList(4, 0, msg_cc);
    sprintf(genbuf,
"¤Þ¤J: (I)¦n¤Í (O)¤W½u³qª¾ (N)¤å³¹³qª¾ (0-9)¸s²Õ¦W³æ%s\n"
"½T»{: (W)¤ô²y (H)¤W½u³qª¾ (P)¤å³¹³qª¾ (M)±H«H¦W³æ\n"
"¨ä¥¦: (A)¼W¥[ (D)§R°£ (Q)¨ú®ø [M]? ",
       HAS_PERM(PERM_SYSOP) ? " (B)ª©¥D (R)¯S§O¦W³æ" : "");

    getdata(1, 0, genbuf, genbuf, 4, LCECHO, 0);
    switch (genbuf[0])
    {
    case 'a':
      while (1)
      {
        move(1, 0);
        usercomplete("½Ð¿é¤J­n¼W¥[ªº¥N¸¹(¥u«ö ENTER µ²§ô·s¼W): ", uid);
        if (uid[0] == '\0')
          break;

        move(2, 0);
        clrtoeol();

        if (!searchuser(uid))
          outs(err_uid);
        else if (!InNameList(uid))
        {
          AddNameList(uid);
          (*reciper)++;
        }
        ShowNameList(4, 0, msg_cc);
      }
      break;

    case 'd':
      while (*reciper)
      {
        move(1, 0);
        namecomplete("½Ð¿é¤J­n§R°£ªº¥N¸¹(¥u«ö ENTER µ²§ô§R°£): ", uid);
        if (uid[0] == '\0')
          break;
        if (RemoveNameList(uid))
        {
          (*reciper)--;
        }
        ShowNameList(4, 0, msg_cc);
      }
      break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      listfile[5] = genbuf[0];
      genbuf[0] = '1';

    case 'i':
      setuserfile(genbuf, genbuf[0] == '1' ? listfile : fn_overrides);
      ToggleNameList(reciper, genbuf, msg_cc);
      break;

    case 'b':
      if (HAS_PERM(PERM_SYSOP)) {
         make_bmlist();
         *reciper = CountNameList();
         return;
      }
      break;

    case 'o':
      setuserfile(genbuf, "alohaed");
      ToggleNameList(reciper, genbuf, msg_cc);
      break;

    case 'n':
      setuserfile(genbuf, "postlist");
      ToggleNameList(reciper, genbuf, msg_cc);
      break;

    case 'r':
      setuserfile(genbuf, fn_reject);
      ToggleNameList(reciper, genbuf, msg_cc);
      break;

    case 'q':
      *reciper = 0;
      return;
/*
woju
broadcast to group
*/
    case 'w': if (toplev) {
       struct word* p;
       char ans[4];

       *genbuf = 0;
       if (!getdata(0, 0, "¸s²Õ¤ô²y:", genbuf + 1, 60, DOECHO, 0)) {
          clear();
          break;
       }
       if (getdata(0, 0, "½T©w¥á¥X¸s²Õ¤ô²y? [Y]", ans, 4, LCECHO, 0) && *ans == 'n') {
          clear();
          break;
       }

       for (p = toplev; p; p = p->next) {
          user_info *uentp;
          int tuid;
          extern cmpuids();

          if ((tuid = searchuser(p->word))  && tuid != usernum &&
              (uentp = (user_info *) search_ulistn(cmpuids, tuid, 1)) && !(
              is_rejected(uentp) & 2 && !HAS_PERM(PERM_SYSOP) ||
              uentp->invisible && !HAS_PERM(PERM_SEECLOAK) && !HAS_PERM(PERM_SYSOP) ||
              !PERM_HIDE(currutmp) && PERM_HIDE(uentp) ||
              cuser.uflag & FRIEND_FLAG && !is_friend(uentp)
             ))
             my_write(uentp->pid, genbuf);
       }
      clear();
    }
       break;

    case 'h': {
      struct word* p;
      char ans[4];
      FILE *fp;

      if (getdata(0, 0, "½T»{¤W½u³qª¾¦W³æ? [Y]", ans, 4, LCECHO, 0) && *ans == 'n'){
         clear();
         break;
      }

      setuserfile(genbuf, "alohaed");

      if (fp = fopen(genbuf, "r")) {
         char buf[80];

         while (fgets(buf, 80, fp)) {
            char fpath[200];

            buf[strlen(buf) - 1] = 0;
            sethomefile(fpath, buf, "aloha");
            del_distinct(fpath, cuser.userid);
         }
         fclose(fp);
      }

      if (fp = fopen(genbuf, "w")) {
         for (p = toplev; p; p = p->next) {
            fprintf(fp, "%s\n", p->word);
            sethomefile(genbuf, p->word, "aloha");
            add_distinct(genbuf, cuser.userid);
         }
         fclose(fp);
      }
      clear();
    }
      break;
    case 'p': {
      struct word* p;
      char ans[4];
      FILE *fp;

      if (getdata(0, 0, "½T»{·s¤å³¹³qª¾¦W³æ? [Y]", ans, 4, LCECHO, 0) && *ans == 'n') {
         clear();
         break;
      }

      setuserfile(genbuf, "postlist");

      if (fp = fopen(genbuf, "r")) {
         char buf[80];

         while (fgets(buf, 80, fp)) {
            char fpath[200];

            buf[strlen(buf) - 1] = 0;
            sethomefile(fpath, buf, "postnotify");
            del_distinct(fpath, cuser.userid);
         }
         fclose(fp);
      }

      if (fp = fopen(genbuf, "w")) {
         for (p = toplev; p; p = p->next) {
            fprintf(fp, "%s\n", p->word);
            sethomefile(genbuf, p->word, "postnotify");
            add_distinct(genbuf, cuser.userid);
         }
         fclose(fp);
      }
      clear();
    }
    break;
    default:
      return;
    }
  }
}


static int
multi_send(title)
  char *title;
{
  FILE *fp;
  struct word *p;
  fileheader mymail;
  char fpath[TTLEN], *ptr;
  int reciper, listing;
  char genbuf[256];

  CreateNameList();

  listing = reciper = 0;

  if (*quote_file)
  {
    AddNameList(quote_user);
    reciper = 1;
    fp = fopen(quote_file, "r");
    while (fgets(genbuf, 256, fp))
    {
      if (strncmp(genbuf, "¡° ", 3))
      {
        if (listing)
          break;
      }
      else
      {
        if (listing)
        {
          strtok(ptr = genbuf + 3, " \n\r");
          do
          {
            if (searchuser(ptr) && !InNameList(ptr) && strcmp(cuser.userid, ptr))
            {
              AddNameList(ptr);
              reciper++;
            }
          } while (ptr = (char *) strtok(NULL, " \n\r"));
        }
        else if (!strncmp(genbuf + 3, "[³q§i]", 6))
          listing = 1;
      }
    }
    ShowNameList(4, 0, msg_cc);
  }

  multi_list(&reciper);
  move(1, 0);
  clrtobot();

  if (reciper)
  {
    setutmpmode(SMAIL);

    if (title)
    {
      do_reply_title(2, title);
    }
    else
    {
      getdata(2, 0, "¥DÃD¡G", fpath, 64, DOECHO, 0);
      sprintf(save_title, "[³q§i] %s", fpath);
    }

    setuserfile(fpath, fn_notes);

    if (fp = fopen(fpath, "w"))
    {
      fprintf(fp, "¡° [³q§i] ¦@ %d ¤H¦¬¥ó", reciper);
      listing = 80;

      for (p = toplev; p; p = p->next)
      {
        reciper = strlen(p->word) + 1;
        if (listing + reciper > 75)
        {
          listing = reciper;
          fprintf(fp, "\n¡°");
        }
        else
          listing += reciper;

        fprintf(fp, " %s", p->word);
      }
      memset(genbuf, '-', 75);
      genbuf[75] = '\0';
      fprintf(fp, "\n%s\n\n", genbuf);
      fclose(fp);
    }

    curredit |= EDIT_LIST;

    if (vedit(fpath, YEA) == -1)
    {
      unlink(fpath);
      curredit = 0;
      outs(msg_cancel);
      pressanykey();
      return;
    }

    stand_title("±H«H¤¤...");
    refresh();

    listing = 80;

    for (p = toplev; p; p = p->next)
    {
      reciper = strlen(p->word) + 1;
      if (listing + reciper > 75)
      {
        listing = reciper;
        outc('\n');
      }
      else
      {
        listing += reciper;
        outc(' ');
      }
      outs(p->word);

      /* Leeym */
      if (searchuser(p->word) && strcmp(STR_GUEST, p->word))
        sethomepath(genbuf, p->word);
      else
      continue;
      /*       */
      stampfile(genbuf, &mymail);
      unlink(genbuf);
      Link(fpath, genbuf);

      strcpy(mymail.owner, cuser.userid);
      strcpy(mymail.title, save_title);
      mymail.savemode = 'M';    /* multi-send flag */
      if(mh_autoforward(p->word, &mymail, sizeof(mymail), 1))
      {
        sethomedir(genbuf, p->word);
        if (append_record(genbuf, &mymail, sizeof(mymail)) == -1)
          outs(err_uid);
      }
      else
        unlink(genbuf);
    }
    hold_mail(fpath, NULL);
    unlink(fpath);
    curredit = 0;
  }
  else
  {
    outs(msg_cancel);
  }
  pressanykey();
}


static int
multi_reply(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  if (fhdr->savemode != 'M')
    return mail_reply(ent, fhdr, direct);

  stand_title("¸s²Õ¦^«H");
  strcpy(quote_user, fhdr->owner);
  setuserfile(quote_file, fhdr->filename);
  multi_send(fhdr->title);
  *quote_file = 0;
  return 0;
}


int
mail_list()
{
  stand_title("¸s²Õ§@·~");
  multi_send(NULL);
  return 0;
}


int
mail_all()
{
   FILE *fp;
   fileheader mymail;
   char fpath[TTLEN];
   char genbuf[200];
   extern struct UCACHE *uidshm;
   int i, unum;
   char* userid;
   void (*hsig)();


   stand_title("µ¹©Ò¦³¨Ï¥ÎªÌªº¨t²Î³q§i");
   setutmpmode(SMAIL);
   getdata(2, 0, "¥DÃD¡G", fpath, 64, DOECHO, 0);
#if 0
   sprintf(save_title, "[¨t²Î³q§i][1;32m %s[m", fpath);
#else
   sprintf(save_title, "[¨t²Î³q§i] %s", fpath);
#endif

   setuserfile(fpath, fn_notes);

   if (fp = fopen(fpath, "w")) {
      fprintf(fp, "¡° [¨t²Î³q§i] ³o¬O«Êµ¹©Ò¦³¨Ï¥ÎªÌªº«H\n");
      fprintf(fp, "---------------------------------------------------------------------------\n");
      fclose(fp);
    }

   *quote_file = 0;

   curredit |= EDIT_MAIL;
   if (vedit(fpath, YEA) == -1) {
      curredit = 0;
      unlink(fpath);
      outs(msg_cancel);
      pressanykey();
      return;
   }
   curredit = 0;

   hsig = signal(SIGHUP, SIG_IGN);

   setutmpmode(MAILALL);
   stand_title("±H«H¤¤...");

   sethomepath(genbuf, cuser.userid);
   stampfile(genbuf, &mymail);
   unlink(genbuf);
   Link(fpath, genbuf);
   unlink(fpath);
   strcpy(fpath, genbuf);

   strcpy(mymail.owner, "¯¸ªø");
   strcpy(mymail.title, save_title);
   mymail.savemode = 0;
   mymail.filemode |= FILE_MARKED;
   mh_autoforward(cuser.userid, &mymail, sizeof(mymail), 0);
   sethomedir(genbuf, cuser.userid);
   if (append_record(genbuf, &mymail, sizeof(mymail)) == -1)
      outs(err_uid);

   for (unum = uidshm->number, i = 0; i < unum; i++) {
      userid = uidshm->userid[i];
      if (strcmp(userid, "guest") && strcmp(userid, "new") && strcmp(userid, cuser.userid)
          && userid[0]) {
         sethomepath(genbuf, userid);
         stampfile(genbuf, &mymail);
         unlink(genbuf);
         Link(fpath, genbuf);

         strcpy(mymail.owner, "¯¸ªø");
         strcpy(mymail.title, save_title);
         mymail.savemode = 0;
         mymail.filemode |= FILE_MARKED;
         mh_autoforward(userid, &mymail, sizeof(mymail), 0);
         sethomedir(genbuf, userid);
         if (append_record(genbuf, &mymail, sizeof(mymail)) == -1)
            outs(err_uid);
         sprintf(genbuf, "%*s %5d / %5d", IDLEN + 1, userid, i + 1, unum);
         outmsg(genbuf);
         refresh();
      }
   }
   signal(SIGHUP,  hsig);
   return;
}

mail_mbox()
{
   char cmd[100];
   fileheader fhdr;

   sprintf(cmd, "tmp/%s.tgz", cuser.userid);
   sprintf(fhdr.title, "%s ¨p¤H¸ê®Æ", cuser.userid);
   /* Tzu */
   switch(doforward(cmd, &fhdr, 'Z'))  
   {
     case 0:
       outmsg("³Æ¥÷¥´¥]§¹²¦");
       igetch();
       break;
     case -1:
       outmsg(msg_fwd_err1);
       igetch();
       break;
     case -2:
       outmsg(msg_fwd_err2);
       igetch();
       break;
   }
   /*     */
}


int
m_group()
{
  int aborted;
  char ans[4];
  static char eans[4];
  int j;
  char genbuf[200];

  setuserfile(genbuf, "mlist.0");
  j = strlen(genbuf) - 1;

  getdata(b_lines - 1, 0, "Email-list (E)½s¿è (D)§R°£ (M)µo«H (Q)¨ú®ø¡H[Q] ", ans, 4, LCECHO, 0);

  aborted = 0;
  if (ans[0] == 'd')
    aborted = 1;
  if (ans[0] == 'e')
    aborted = 2;
  if (ans[0] == 'm')
    aborted = 3;

  if (aborted)
  {
    if (!getdata(b_lines - 1, 0, "½Ð¿ï¾Ü Email-list ÀÉ(0-9)¡H ", eans, 4, DOECHO, eans))
      eans[0] = '0';
    if (eans[0] >= '0' && eans[0] <= '9')
    {
      genbuf[j] = eans[0];
      if (aborted == 1)
      {
        unlink(genbuf);
        outs(msg_del_ok);
      }
      else if (aborted == 2)
      {
        aborted = vedit(genbuf, NA);
        if (!aborted)
          outs("§ó·s§¹²¦");
      }
      else if (more(genbuf, NA) != -1) {
         char address[STRLEN];
         char xtitle[TTLEN];
         char fpath[STRLEN] = "";
         FILE* fp;

         getdata(b_lines - 1, 0, "¥DÃD¡G", xtitle, TTLEN, DOECHO, 0);
         if (!*xtitle)
            return -2;
         curredit |= EDIT_MAIL;
         setutmpmode(SMAIL);

         if (vedit(fpath, NA) == -1) {
            unlink(fpath);
            clear();
            return -2;
         }
         clear();
         more(genbuf, NA);
         getdata(b_lines - 1, 0, "½T©w­n±Hµ¹¦Cªí¤¤ªº¤H¶Ü? (Y/N) [Y]",
            ans, 4, LCECHO, 0);
         switch (*ans)
         {
         case 'n':
            outs("\n«H¥ó¤w¨ú®ø");
            break;
         default:
            fp = fopen(genbuf, "r");
            while (fgets(address, STRLEN, fp)) {
               strtok(address, " ,\n");
               if (*address) {
                  outmsg(address);
                  refresh();
                  bbs_sendmail(fpath, xtitle, address);
               }
            }
            fclose(fp);
            getdata(b_lines - 1, 0, "¤w¶¶§Q±H¥X¡A¬O§_¦Û¦s©³½Z(Y/N)¡H[N]",
               ans, 4, LCECHO, 0);
            if (*ans == 'y') {
               sprintf(save_title, "%s (mlist.%c)", xtitle, *eans);
               do_hold_mail(fpath, 0, cuser.userid);
            }
         }
         unlink(fpath);
      }
    }
    pressanykey();
  }
  return 0;
}

int
m_list()
{
  int aborted;
  char genbuf[4];

  getdata(b_lines - 1, 0, "¦W³æÀÉ (E)½s¿è (D)§R°£ (Q)¨ú®ø¡H[Q] ",
    genbuf, 4, LCECHO, 0);

  if (genbuf[0] == 'd')
    aborted = 1;
  else if (genbuf[0] == 'e')
    aborted = 2;
  else
    aborted = 0;

  if (aborted)
  {
    char listpath[64], ans[4];

    getdata(b_lines - 1, 0, "½Ð¿ï¾Ü¦W³æ (0-9)¡H[0] ", ans, 3, DOECHO, 0);

    if (ans[0] == '\0')
      ans[0] = '0';
    if (ans[0] >= '0' && ans[0] <= '9')
    {
      listfile[5] = ans[0];
      setuserfile(listpath, listfile);
      if (aborted == 1)
      {
        if (more(listpath, NA) != -1)
           getdata(b_lines - 1, 0, "½T©w§R°£¶Ü(Y/N)?[N]",  ans, 3, LCECHO, 0);
        if (*ans == 'y') {
           unlink(listpath);
           outmsg(msg_del_ok);
        }
      }
      else
      {
        int reciper;

        stand_title("½s¿è¦W³æ");
        reciper = 0;
        CreateNameList();
        LoadNameList(&reciper, listpath, msg_cc);
        multi_list(&reciper);
        SaveNameList(listpath);
      }
    }
  }
  return FULLUPDATE;
}


static int
m_forward(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char uid[STRLEN];
  char *t;
  FILE *fp;

  stand_title("Âà¹F«H¥ó");
  usercomplete(msg_uid, uid);
  if (uid[0] == '\0')
  {
    return FULLUPDATE;
  }

  strcpy(quote_user, fhdr->owner);
  setuserfile(quote_file, fhdr->filename);
  sprintf(save_title, "%.64s (fwd)", fhdr->title);
  move(1, 0);
  clrtobot();
  prints("Âà«Hµ¹: %s\n¼Ð  ÃD: %s\n", uid, save_title);

  switch (do_send(uid, save_title))
  {
  case -1:
    outs(err_uid);
    break;
  case -2:
    outs(msg_cancel);
    break;
  case -3:
    prints("¨Ï¥ÎªÌ [%s] µLªk¦¬«H", uid);
    break;
  }
  *quote_file = 0;
  pressanykey();
  return FULLUPDATE;
}


/* JhLin: At most 128 mail */

int delmsgs[128];
int delcnt;
int mrd;


static int
read_new_mail(fptr)
  fileheader *fptr;
{
  static int idc;
  char done = NA, delete_it;
  char fname[256];
  char genbuf[4];

  if (fptr == NULL)
  {
    delcnt = 0;
    idc = 0;
    return 0;
  }
  idc++;
  if (fptr->filemode)
    return 0;
  clear();
  move(10, 0);
  prints("±z­nÅª¨Ó¦Û[%s]ªº°T®§(%s)¶Ü¡H", fptr->owner, fptr->title);
  getdata(11, 0, "½Ð±z½T©w(Y/N/Q)?[Y] ", genbuf, 3, DOECHO, 0);
  if (genbuf[0] == 'q')
    return QUIT;
  if (genbuf[0] == 'n')
    return 0;

  setuserfile(fname, fptr->filename);
  fptr->filemode |= FILE_READ;
  if (substitute_record(currmaildir, fptr, sizeof(*fptr), idc))
    return -1;

  mrd = 1;
  delete_it = NA;
  strcpy(vetitle, fptr->title);
  while (!done)
  {
    int more_result = more(fname, YEA);
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
       return 0;
    case 7:
      mail_reply(idc, fptr, currmaildir);
      return FULLUPDATE;
    case 8:
      multi_reply(idc, fptr, currmaildir);
      return FULLUPDATE;
    }
    move(b_lines, 0);
    clrtoeol();
    outs(msg_mailer);
    refresh();

    switch (igetkey())
    {
    case 'r':
    case 'R':
      mail_reply(idc, fptr, currmaildir);
      break;
    case 'x':
      m_forward(idc, fptr, currmaildir);
      break;
    case 'y':
      multi_reply(idc, fptr, currmaildir);
      break;
    case 'd':
    case 'D':
      delete_it = YEA;
    default:
      done = YEA;
    }
  }
  if (delete_it)
  {
    clear();
    prints("§R°£«H¥ó¡m%s¡n", fptr->title);
    getdata(1, 0, msg_sure_ny, genbuf, 2, LCECHO, 0);
    if (genbuf[0] == 'y')
    {
      unlink(fname);
      delmsgs[delcnt++] = idc;
    }
  }
  clear();
  return 0;
}


int
m_new()
{
  clear();
  mrd = 0;
  setutmpmode(RMAIL);
  read_new_mail(NULL);
  clear();
  curredit |= EDIT_MAIL;
  if (apply_record(currmaildir, read_new_mail, sizeof(fileheader)) == -1)
  {
    outs("¨S¦³·s«H¥ó¤F");
    pressanykey();
    return -1;
  }
  curredit = 0;
  if (delcnt)
  {
    while (delcnt--)
      delete_record(currmaildir, sizeof(fileheader), delmsgs[delcnt]);
  }
  outs(mrd ? "«H¤w¾\\²¦" : "¨S¦³·s«H¥ó¤F");
  pressanykey();
  return -1;
}

/* MH */
extern int thread_title;
/*    */

static void
mailtitle()
{
  showtitle("\0¶l¥ó¿ï³æ", BoardName);
  if((currmode & MODE_SELECT) && thread_title > 0)
    outs("[¡ö]Â÷¶}  [¡ô,¡õ]¿ï¾Ü  [¡÷,r]¾\\Åª«H¥ó  [R]¦^«H   [x]Âà¹F  [y]¸s²Õ¦^«H  ¨D§U[h]\n[7m"
         " ½s¸¹ ¦ê¦C¼Æ  ¨Ï¥Î¶q ¦ê¦C§@ªÌ   ¦ê  ¦C  ¼Ð  ÃD                                [0m");
  else
    outs("[¡ö]Â÷¶}  [¡ô,¡õ]¿ï¾Ü  [¡÷,r]¾\\Åª«H¥ó  [R]¦^«H   [x]Âà¹F  [y]¸s²Õ¦^«H  ¨D§U[h]\n[7m"
         " ½s¸¹   ¤é ´Á ¨Ï¥Î¶q §@ ªÌ      «H  ¥ó  ¼Ð  ÃD                                [0m");
}


static void
maildoent(num, ent)
  fileheader *ent;
{
  char *title, *mark, color, type = "+ Mm"[ent->filemode];
  char buf[200];
  int size;
  struct stat st;

/*
woju
taged for delete
*/
  if (ent->filemode & FILE_TAGED)
     type = 'D';

  title = subject(mark = ent->title);
  if (title == mark)
  {
    color = '1';
    mark = "¡º";
  }
  else
  {
    color = '3';
    mark = "R:";
  }

  size = 0;
  sprintf(buf, "home/%s/%s", cuser.userid, ent->filename);
  if (stat(buf, &st) == 0 && S_ISREG(st.st_mode) && st.st_nlink == 1)
     size = st.st_size / 1024;

/* MH */
  mh_delete_esc(title);
/*    */

#ifdef MH_COLORFUL_READ
  {
    struct tm date;
    char buf[6];
    int mh_color;
    
    if((currmode & MODE_SELECT) && thread_title == 1)
      mh_color = 7;
    else
    {
      strncpy(buf, ent->date, 5);
      mh_strtodate(buf, &date);
      mh_color = mh_rc[(date.tm_mday - 1) % MH_RCS];
    }
    if (strncmp(currtitle, title, 40))
      prints("%5d %c [1;3%dm%-7s%3d[0m   %-11.10s%s %.44s[m\n", num, type, mh_color,
        ent->date, size, ent->owner, mark, title);
    else
      prints("%5d %c [1;3%dm%-7s%3d[0m   %-11.10s[1;3%cm%s %.44s[0m\n", num, type, mh_color,
        ent->date, size, ent->owner, color, mark, title);
  }
#else
  if (strncmp(currtitle, title, 40))
    prints("%5d %c %-7s%3d   %-11.10s%s %.44s[m\n", num, type,
      ent->date, size, ent->owner, mark, title);
  else
    prints("%5d %c %-7s%3d   %-11.10s[1;3%cm%s %.44s[0m\n", num, type,
      ent->date, size, ent->owner, color, mark, title);
#endif
}

#ifdef POSTBUG
extern int bug_possible;
#endif


/*
woju
*/
static int
mail_del_tag(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char genbuf[3];

  getdata(1, 0, "½T©w§R°£¼Ð°O«H¥ó(Y/N)? [Y]", genbuf, 3, LCECHO, 0);
  if (genbuf[0] != 'n')
  {
    char buf[STRLEN];

    currfmode = FILE_TAGED;
    if (delete_files(direct, cmpfmode))
       return DIRCHANGED;
  }
  return FULLUPDATE;
}

m_idle(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
   t_idle();
   return FULLUPDATE;
}


static int
mail_del(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char genbuf[200];

  if (fhdr->filemode & FILE_MARKED)
    return DONOTHING;

  getdata(1, 0, msg_del_ny, genbuf, 3, LCECHO, 0);
  if (genbuf[0] == 'y')
  {
    char buf[STRLEN];
    char *t;
    extern int cmpfilename();

    strcpy(currfile, fhdr->filename);
    if (!delete_file(direct, sizeof(*fhdr), ent, cmpfilename))
    {
      setdirpath(genbuf, direct, fhdr->filename);
      unlink(genbuf);
      if( currmode & MODE_SELECT ){
         int now;
         sethomedir(genbuf,cuser.userid);
         now=getindex(genbuf,fhdr->filename);
         delete_file (genbuf, sizeof(fileheader),now,cmpfilename);
      }
      return DIRCHANGED;
    }
  }
  return FULLUPDATE;
}


/*
woju
static int
*/
mail_read(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char buf[64];
  char *t;
  char done, delete_it, replied;

  clear();
  setdirpath(buf, direct, fhdr->filename);
  strncpy(currtitle, subject(fhdr->title), 40);
  done = delete_it = replied = NA;
  strcpy(vetitle, fhdr->title);
  while (!done)
  {
/*
woju
*/
    fhdr->filemode |= FILE_READ;
    if (!strncmp("[·s]", fhdr->title, 4) && !(fhdr->filemode & FILE_MARKED))
       fhdr->filemode |= FILE_TAGED;
#if 0
    substitute_record(currmaildir, fhdr, sizeof(*fhdr), ent);
#else
    if(currmode & MODE_SELECT)
    {
      int now;
      
      now = getindex(currmaildir, fhdr->filename);
      substitute_record(currmaildir, fhdr, sizeof(*fhdr), now);
    }
    substitute_record(direct, fhdr, sizeof(*fhdr), ent);
#endif
    switch (more(buf, YEA)) {
    case -1:
       return DONOTHING;
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
      mail_reply(ent, fhdr, direct);
      return FULLUPDATE;
    case 8:
      multi_reply(ent, fhdr, direct);
      return FULLUPDATE;
    }
    move(b_lines, 0);
    clrtoeol();
    refresh();
    outs(msg_mailer);

    switch (igetkey())
    {
    case 'r':
    case 'R':
      replied = YEA;
      mail_reply(ent, fhdr, direct);
      break;
    case 'x':
      m_forward(ent, fhdr, direct);
      break;
    case 'y':
      multi_reply(ent, fhdr, direct);
      break;
    case 'd':
      delete_it = YEA;
    default:
      done = YEA;
    }
  }
  if (delete_it)
    mail_del(ent, fhdr, direct);
  else
  {
    fhdr->filemode |= FILE_READ;

#ifdef POSTBUG
    if (replied)
      bug_possible = YEA;
#endif

#if 0
    substitute_record(currmaildir, fhdr, sizeof(*fhdr), ent);
#else
    if(currmode & MODE_SELECT)
    {
      int now;
      
      now = getindex(currmaildir, fhdr->filename);
      substitute_record(currmaildir, fhdr, sizeof(*fhdr), now);
    }
    substitute_record(direct, fhdr, sizeof(*fhdr), ent);
#endif

#ifdef POSTBUG
    bug_possible = NA;
#endif
  }
  return FULLUPDATE;
}


/* ---------------------------------------------- */
/* in boards/mail ¦^«Hµ¹­ì§@ªÌ¡AÂà«H¯¸¥ç¥i        */
/* ---------------------------------------------- */

int
mail_reply(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char uid[STRLEN];
  char *t;
  FILE *fp;
  char genbuf[512];

  stand_title("¦^  «H");

  /* §PÂ_¬O boards ©Î mail */

  if (currutmp->mode == ANNOUNCE)
    sprintf(quote_file, "%s/%s", direct, fhdr->filename);
  else if (curredit & EDIT_MAIL)
    setuserfile(quote_file, fhdr->filename);
  else
    setbfile(quote_file, currboard, fhdr->filename);

  /* find the author */

  strcpy(quote_user, fhdr->owner);

  if (strchr(quote_user, '.') || strlen(quote_user) == IDLEN + 1)
  {
    genbuf[0] = '\0';
    if (fp = fopen(quote_file, "r"))
    {
      fgets(genbuf, 512, fp);
      fclose(fp);
    }

    t = strtok(genbuf, str_space);
    if (!strcmp(t, str_author1) || !strcmp(t, str_author2))
    {
      strcpy(uid, strtok(NULL, str_space));
    }
    else
    {
      outs("¿ù»~: §ä¤£¨ì§@ªÌ¡C");
      pressanykey();
      return FULLUPDATE;
    }
  }
  else
    strcpy(uid, quote_user);

  /* make the title */

  do_reply_title(3, fhdr->title);

  if (ent < 0) {
     char buf[200];
     static char receiver[200];
     FILE* fp;

     setbfile(buf, currboard, "mlist");
     if (fp = fopen(buf, "r")) {
        fgets(receiver, sizeof(receiver), fp);
        strtok(receiver, "\n\r");
        fclose(fp);
     }
     if (!*receiver)
        strcpy(receiver, uid);
     if (getdata(5, 0, "¦¬«H¤H¡G", buf, 70, DOECHO, receiver)) {
        strtok(buf, " \t()[]");
        strcpy(receiver, strcpy(uid, buf));
     }
  }
  prints("\n¦¬«H¤H: %s\n¼Ð  ÃD: %s\n", uid, save_title);

  /* edit, then send the mail */

  ent = curredit;
  switch (do_send(uid, save_title))
  {
  case -1:
    outs(err_uid);
    break;
  case -2:
    outs(msg_cancel);
    break;
  case -3:
    prints("¨Ï¥ÎªÌ [%s] µLªk¦¬«H", uid);
    break;
  }
  curredit = ent;
  pressanykey();
  *quote_file = 0;
  return FULLUPDATE;
}

int
mail_edit(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char uid[STRLEN];
  char *t;
  FILE *fp;
  char genbuf[200];

  setdirpath(genbuf, direct, fhdr->filename);
  vedit(genbuf, belong("etc/bbsadms", cuser.userid) ? 0 : 2);
  return FULLUPDATE;
}


static int
mail_mark(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  fhdr->filemode ^= FILE_MARKED;
  fhdr->filemode &= ~FILE_TAGED;
  substitute_record(currmaildir, fhdr, sizeof(*fhdr), ent);
  return (PART_REDRAW);
}



/*
woju
*/
static int
mail_tag(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  fhdr->filemode ^= FILE_TAGED;
  substitute_record(currmaildir, fhdr, sizeof(*fhdr), ent);
  return POS_NEXT;
}


mail_tag1(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  fhdr->filemode |= FILE_TAGED;
  substitute_record(currmaildir, fhdr, sizeof(*fhdr), ent);
}



/* help for mail reading */

static char *mail_help[] =
{
  "\0¹q¤l«H½c¾Þ§@»¡©ú",
  "\01°ò¥»©R¥O",
  "(p)(¡ô)    «e¤@½g¤å³¹",
  "(n)(¡õ)    ¤U¤@½g¤å³¹",
  "(P)(PgUp)  «e¤@­¶",
  "(N)(PgDn)  ¤U¤@­¶",
  "(##)(cr)   ¸õ¨ì²Ä ## µ§",
  "($)        ¸õ¨ì³Ì«á¤@µ§",
  "\01¶i¶¥©R¥O",
  "(r)(¡÷)    Åª«H",
  "(R)        ¦^«H",
  "(x)        Âà¹F«H¥ó",
  "(X)        Âà¿ý¤å³¹¨ì¨ä¥L¬ÝªO",
  "(y)        ¸s²Õ¦^«H",

#ifdef INTERNET_EMAIL
  "(F)        ±N«H¶Ç°e¦^±zªº¹q¤l«H½c",
#endif

  "(d)        ±þ±¼¦¹«H",
  "(D)        ±þ±¼«ü©w½d³òªº«H",
  "(m)        ±N«H¼Ð°O¡A¥H¨¾³Q²M°£",
  "(t)        ¼Ð°O±ý§R°£«H¥ó",
  "(^D)       §R°£¤w¼Ð°O«H¥ó",
  NULL
};


static int
m_help()
{
  show_help(mail_help);
  return FULLUPDATE;
}


static int
mail_cross_post(ent, fhdr, direct)
  int ent;
  fileheader *fhdr;
  char *direct;
{
  char xboard[20], fname[80], xfpath[80], xtitle[80], inputbuf[10];
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

    setuserfile(fname, fhdr->filename);
    if (ent)
    {
      xptr = fopen(xfpath, "w");

      strcpy(save_title, xfile.title);
      strcpy(xfpath, currboard);
      strcpy(currboard, xboard);
      write_header(xptr);
      strcpy(currboard, xfpath);

      fprintf(xptr, "¡° [¥»¤åÂà¿ý¦Û %s «H½c]\n\n", cuser.userid);

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
    if (!xfile.filemode && !author)
      outgo_post(&xfile, xboard);
    cuser.numposts++;
    substitute_record(fn_passwd, &cuser, sizeof(userec), usernum);
    outs("¤å³¹Âà¿ý§¹¦¨");
    pressanykey();
    currmode = currmode0;
  }
  return FULLUPDATE;
}

mail_cite(int ent, fileheader* fhdr, char* direct)
{
   char fpath[256];
   char title[TTLEN+1];
   static char xboard[20];
   char buf[20];
   boardheader *bp;
   boardheader *getbcache();

   setuserfile(fpath, fhdr->filename);
   strcpy(title, "¡º ");
   strncpy(title+3, fhdr->title, TTLEN-3);
   title[TTLEN] = '\0';
   a_copyitem(fpath, title, 0);
   move(2, 0);
   clrtoeol();
   move(3, 0);
   clrtoeol();
   move(1, 0);
   make_blist();
   namecomplete("¦¬¿ý¥»¤å³¹¤JºëµØ°Ï©ó¬ÝªO¡G", buf);
   if (*buf)
      strcpy(xboard, buf);
   if (*xboard && (bp = getbcache(xboard))) {
      setapath(fpath, xboard);
      a_menu(xboard, fpath, HAS_PERM(PERM_ALLBOARD) ? 2 :
        is_BM(bp->BM) ? 1 : 0);
   }
   return FULLUPDATE;
}


mail_Cite(int ent, fileheader* fhdr, char* direct)
{
   char fpath[256];
   char title[TTLEN+1];

   setuserfile(fpath, fhdr->filename);
   strcpy(title, "¡º ");
   strncpy(title+3, fhdr->title, TTLEN-3);
   title[TTLEN] = '\0';
   a_copyitem(fpath, title, 0);
   load_paste();
   if (*paste_path)
      a_menu(paste_title, paste_path, paste_level);
   return FULLUPDATE;
}

mail_Cites(int ent, fileheader* fhdr, char* direct)
{
   char fpath[256];

   setuserfile(fpath, fhdr->filename);
   load_paste();
   if (*paste_path && paste_level && dashf(fpath)) {
      fileheader fh;
      char newpath[MAXPATHLEN];

      strcpy(newpath, paste_path);
      stampfile(newpath, &fh);
      unlink(newpath);
      Link(fpath, newpath);
      strcpy(fh.owner, fhdr->owner);
      sprintf(fh.title, "¡º %.72s", fhdr->title);
      strcpy(strrchr(newpath, '/') + 1, ".DIR");
      append_record(newpath, &fh, sizeof(fh));
      return POS_NEXT;
   }
   bell();
   return DONOTHING;
}

int
edit_title();

mail_man()
{
   char buf[64];

   if (HAS_PERM(PERM_MAILLIMIT)) {
      int mode0 = currutmp->mode;
      int stat0 = currstat;

      sethomeman(buf, cuser.userid);
      a_menu(cuser.userid, buf, belong("etc/bbsadms", cuser.userid) ? 2 : 1);
      currutmp->mode = mode0;
      currstat = stat0;
      return FULLUPDATE;
   }
   return DONOTHING;
}


mail_save(int ent, fileheader* fhdr, char* direct)
{
   char fpath[256];
   char title[TTLEN+1];
   static char xboard[20];
   char buf[20];

   if (HAS_PERM(PERM_MAILLIMIT)) {
      mail_tag1(ent, fhdr, direct);
      setuserfile(fpath, fhdr->filename);
      strcpy(title, "¡º ");
      strncpy(title+3, fhdr->title, TTLEN-3);
      title[TTLEN] = '\0';
      a_copyitem(fpath, title, fhdr->owner);
      sethomeman(fpath, cuser.userid);
      a_menu(cuser.userid, fpath, belong("etc/bbsadms", cuser.userid) ? 2 : 1);
      return FULLUPDATE;
   }
   return DONOTHING;
}

static struct one_key mail_comms[] = {
  'z', mail_man,
  'c', mail_cite,
  'C', mail_Cite,
  Ctrl('C'), mail_Cites,
  's', mail_save,
  'd', mail_del,
  'D', del_range,
  'r', mail_read,
  'R', mail_reply,
  'E', mail_edit,
  'm', mail_mark,
  't', mail_tag,
  'T', edit_title,
  'x', m_forward,
  'X', mail_cross_post,
  Ctrl('D'), mail_del_tag,
  'y', multi_reply,
  Ctrl('I'), m_idle,
  'h', m_help,
  '\0', NULL
};

int enter = 0;

int
m_read()
{
  int mode0 = currutmp->mode;
  int stat0 = currstat;
  int tmp_thread_title;
  int tmp_currmode;
/*  static enter;*/

  if (enter > 3)
     return;
     
  /* "Push" currmode & thread_title */
  tmp_thread_title = thread_title;
  thread_title = 0;
  tmp_currmode = currmode;
  currmode &= ~MODE_SELECT;
  /*                     */

  ++enter;
  if (get_num_records(currmaildir, sizeof(fileheader)))
  {
    curredit = EDIT_MAIL;
    i_read(RMAIL, currmaildir, mailtitle, maildoent, mail_comms);
    currfmode = FILE_TAGED;
    if (search_rec(currmaildir, cmpfmode))
        mail_del_tag(0, 0, currmaildir);
    curredit = 0;
  }
  currutmp->mode = mode0;
  currstat = stat0;
  
  /* "Pop" currmode & thread_title */
  currmode = tmp_currmode;
  thread_title = tmp_thread_title;
  /*                    */
  
  --enter;
  return;
}


#ifdef INTERNET_EMAIL
#include <netdb.h>
#include <pwd.h>
#include <time.h>



/* ±H«H¥æµ¹ sendmail¡A¤U¦C¥i¥H¬Ù²¤ */

#if 0
#define BBSMAILDIR "/usr/spool/mqueue"


static void
spacestozeros(s)
  char *s;
{
  while (*s)
  {
    if (*s == ' ')
      *s = '0';
    s++;
  }
}


static int
getqsuffix(s)
  char *s;
{
  struct stat stbuf;
  char qbuf[STRLEN], dbuf[STRLEN];
  char c1 = 'A', c2 = 'A';
  int pos = strlen(BBSMAILDIR) + 3;

  sprintf(dbuf, "%s/dfAA%5d", BBSMAILDIR, currpid);
  sprintf(qbuf, "%s/qfAA%5d", BBSMAILDIR, currpid);
  spacestozeros(dbuf);
  spacestozeros(qbuf);
  while (1)
  {
    if (stat(dbuf, &stbuf) && stat(qbuf, &stbuf))
      break;
    if (c2 == 'Z')
    {
      c2 = 'A';
      if (c1 == 'Z')
        return -1;
      else
        c1++;
      dbuf[pos] = c1;
      qbuf[pos] = c1;
    }
    else
      c2++;
    dbuf[pos + 1] = c2;
    qbuf[pos + 1] = c2;
  }
  strcpy(s, &(qbuf[pos]));
  return 0;
}


static void
convert_tz(local, gmt, buf)
  int gmt, local;
  char *buf;
{
  local -= gmt;
  if (local < -11)
    local += 24;
  else if (local > 12)
    local -= 24;
  sprintf(buf, " %4d", abs(local * 100));
  spacestozeros(buf);
  if (local < 0)
    buf[0] = '-';
  else if (local > 0)
    buf[0] = '+';
  else
    buf[0] = '\0';
}


static int
createqf(title, qsuffix)
  char *title, *qsuffix;
{
  static int configured = 0;
  static char myhostname[STRLEN];
  static char myusername[20];
  char mytime[STRLEN];
  char idtime[STRLEN];
  char qfname[STRLEN];
  char t_offset[6];
  FILE *qfp;
  time_t timenow;
  int savehour;
  struct tm *gtime, *ltime;
  struct hostent *hbuf;
  struct passwd *pbuf;

  if (!configured)
  {
    /* get host name */
    gethostname(myhostname, STRLEN);
    hbuf = gethostbyname(myhostname);
    if (hbuf)
      strncpy(myhostname, hbuf->h_name, STRLEN);

    /* get bbs uident */
    pbuf = getpwuid(getuid());
    if (pbuf)
      strncpy(myusername, pbuf->pw_name, 20);
    if (hbuf && pbuf)
      configured = 1;
    else
      return -1;
  }

  /* get file name */
  sprintf(qfname, "%s/qf%s", BBSMAILDIR, qsuffix);
  if ((qfp = fopen(qfname, "w")) == NULL)
    return -1;

  /* get time */
  time(&timenow);
  ltime = localtime(&timenow);

#ifdef SYSV
  ascftime(mytime, "%a, %d %b %Y %T ", ltime);
#else
  strftime(mytime, sizeof(mytime), "%a, %d %b %Y %T ", ltime);
#endif

  savehour = ltime->tm_hour;
  gtime = gmtime(&timenow);
  strftime(idtime, sizeof(idtime), "%Y%m%d%y%H%M", gtime);
  convert_tz(savehour, gtime->tm_hour, t_offset);
  strcat(mytime, t_offset);
  fprintf(qfp, "P1000\nT%lu\nDdf%s\nS%s\nR%s\n", timenow, qsuffix,
    myusername, cuser.email);

  /* do those headers! */
  fprintf(qfp, "HReceived: by %s (" MYVERSION ")\n\tid %s; %s\n",
    myhostname, qsuffix, mytime);
  fprintf(qfp, "HReturn-Path: <%s@%s>\n", myusername, myhostname);
  fprintf(qfp, "HDate: %s\n", mytime);
  fprintf(qfp, "HMessage-Id: <%s.%s@%s>\n", idtime, qsuffix,
    myhostname);
  fprintf(qfp, "HFrom: %s@%s (%s in NTHU CS BBS)\n", myusername, myhostname, cuser.userid);
  fprintf(qfp, "HSubject: %s (fwd)\n", title);
  fprintf(qfp, "HTo: %s\n", cuser.email);
  fprintf(qfp, "HX-Forwarded-By: %s (%s)\n", cuser.userid,

#ifdef REALNAME
    cuser.realname);
#else
    cuser.username);
#endif

  fprintf(qfp, "HX-Disclaimer: %s ¹ï¥»«H¤º®e®¤¤£­t³d¡C\n", BoardName);
  fclose(qfp);
  return 0;
}
#endif


#if 0
int
bbs_sendmail(fpath, title, receiver)
  char *fpath, *title, *receiver;
{
  static int configured = 0;
  static char myhostname[STRLEN];
  static char myusername[20];
  struct hostent *hbuf;
  struct passwd *pbuf;
  char *ptr;
  char genbuf[300];
  time_t now = time(0);
  FILE *fin, *fout;

  if (fout = fopen("sendmail.log", "a")) {
     char* rmtusr = getenv("RFC931");
     int deny = *rmtusr == '?' && !HAS_PERM(PERM_INTERNET) && fpath;

     fprintf(fout, "%s <%s> %s(%s) => %s, %s, %s\n",
        Cdatelite(&now), deny ? "deny" : "pass",
        cuser.userid, rmtusr, receiver, title, fpath);
     fclose(fout);
     if (deny) {
        outmsg("[37;41m°e«H¥¢±Ñ[m: ¨Ó·½¥D¾÷¨S´£¨Ñrfc931©Î©|¥¼³q¹Lµù¥U");
        igetch();
        return -1;
     }
  }
  else
     return -1;

  /* ¤¤³~ÄdºI */
  if (ptr = strchr(receiver, ';'))
  {
    struct tm *ptime;
    time_t now;

    if (fout = fopen("hackerlog", "a+"))
    {
      time(&now);
      ptime = localtime(&now);
      fprintf(fout, "[%d/%d %d:%02d] %s from %s\n\t\t±H¥X %s\n",
        ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_hour, ptime->tm_min,
        cuser.userid, getenv("RFC931"), receiver);
      fclose(fout);
    }
    *ptr = '\0';
  }

  if (ptr = strstr(receiver, str_mail_address))
  {
    fileheader mymail;
    char hacker[20];
    int len;

    len = ptr - receiver;
    memcpy(hacker, receiver, len);
    hacker[len] = '\0';
    if (!searchuser(hacker))
    {
      return -2;
    }
    sethomepath(genbuf, hacker);
    stampfile(genbuf, &mymail);
    if (!strcmp(hacker, cuser.userid))
    {
      strcpy(mymail.owner, "[MH]");
      mymail.filemode = FILE_READ;
    }
    else
      strcpy(mymail.owner, cuser.userid);
    strncpy(mymail.title, title, TTLEN);
    unlink(genbuf);
    Link(fpath, genbuf);
    if(mh_autoforward(hacker, &mymail, sizeof(mymail), 1))
    {
      sethomedir(genbuf, hacker);
      return append_record(genbuf, &mymail, sizeof(mymail));
    }
    else
      unlink(genbuf);
  }
  
  /* setup the hostname and username */
  if (!configured)
  {
    /* get host name */
    gethostname(myhostname, STRLEN);
    hbuf = gethostbyname(myhostname);
    if (hbuf)
      strncpy(myhostname, hbuf->h_name, STRLEN);

    /* get bbs uident */
    pbuf = getpwuid(getuid());
    if (pbuf)
      strncpy(myusername, pbuf->pw_name, 20);
    if (hbuf && pbuf)
      configured = 1;
    else
      return -1;
  }

  /* Running the sendmail */

#ifdef  INTERNET_PRIVATE_EMAIL
  if (fpath == NULL)
  {
    sprintf(genbuf, "/usr/sbin/sendmail %s > /dev/null", receiver);
    fin = fopen("etc/confirm", "r");
  }
  else
  {
    sprintf(genbuf, "/usr/sbin/sendmail -f %s%s %s > /dev/null", cuser.userid, str_mail_address, receiver);
    fin = fopen(fpath, "r");
  }
  fout = popen(genbuf, "w");
  if (fin == NULL || fout == NULL)
    return -1;

  if (fpath)
    fprintf(fout, "Reply-To: %s%s\nFrom: %s%s\n",
      cuser.userid, str_mail_address, cuser.userid, str_mail_address);
#else
  sprintf(genbuf, "/usr/sbin/sendmail %s > /dev/null", receiver);
  fout = popen(genbuf, "w");
  fin = fopen(fpath ? fpath : "etc/confirm", "r");
  if (fin == NULL || fout == NULL)
    return -1;

  if (fpath)
    fprintf(fout, "From: %s@%s (%s)\n",
      myusername, myhostname, BBSNAME);
#endif

  fprintf(fout, "To: %s\nSubject: %s\n", receiver, title);
  fprintf(fout, "X-Disclaimer: " BOARDNAME
    "¹ï¥»«H¤º®e®¤¤£­t³d¡C\n\n");

  while (fgets(genbuf, 255, fin))
  {
    if (genbuf[0] == '.' && genbuf[1] == '\n')
      fputs(". \n", fout);
    else
      fputs(genbuf, fout);
  }
  fclose(fin);
  fprintf(fout, ".\n");
  pclose(fout);
  return 0;
}
#else
int
bbs_sendmail(fpath, title, receiver)
  char *fpath, *title, *receiver;
{
  mh_bbs_sendmail(fpath, title, receiver, NULL);
}
#endif

int
mh_bbs_sendmail(fpath, title, receiver, forwarder)
  char *fpath, *title, *receiver, *forwarder;
{
  static int configured = 0;
  static char myhostname[STRLEN];
  static char myusername[20];
  struct hostent *hbuf;
  struct passwd *pbuf;
  char *ptr;
  char genbuf[300];
  time_t now = time(0);
  FILE *fin, *fout;

  if (fout = fopen("sendmail.log", "a")) {
     char* rmtusr = getenv("RFC931");
     int deny = *rmtusr == '?' && !HAS_PERM(PERM_INTERNET) && fpath;

     if(forwarder == NULL)
     {
       fprintf(fout, "%s <%s> %s(%s) => %s, %s, %s\n",
          Cdatelite(&now), deny ? "deny" : "pass",
          cuser.userid, rmtusr, receiver, title, fpath);
     }
     else
     {
       fprintf(fout, "%s <%s> %s(%s) => %s => %s, %s, %s\n",
          Cdatelite(&now), deny ? "deny" : "pass",
          cuser.userid, rmtusr, forwarder, receiver, title, fpath);
     }
     fclose(fout);
     if (deny) {
        outmsg("[37;41m°e«H¥¢±Ñ[m: ¨Ó·½¥D¾÷¨S´£¨Ñrfc931©Î©|¥¼³q¹Lµù¥U");
        igetch();
        return -1;
     }
  }
  else
     return -1;

  /* ¤¤³~ÄdºI */
  if (ptr = strchr(receiver, ';'))
  {
    struct tm *ptime;
    time_t now;

    if (fout = fopen("hackerlog", "a+"))
    {
      time(&now);
      ptime = localtime(&now);
      if(forwarder == NULL)
      {
        fprintf(fout, "[%d/%d %d:%02d] %s from %s\n\t\t±H¥X %s\n",
          ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_hour, ptime->tm_min,
          cuser.userid, getenv("RFC931"), receiver);
      }
      else
      {
        fprintf(fout, "[%d/%d %d:%02d] %s (=> %s) from %s\n\t\t±H¥X %s\n",
          ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_hour, ptime->tm_min,
          cuser.userid, forwarder, getenv("RFC931"), receiver);
      }
      fclose(fout);
    }
    *ptr = '\0';
  }

  if (ptr = strstr(receiver, str_mail_address))
  {
    fileheader mymail;
    char hacker[20];
    int len;

    len = ptr - receiver;
    memcpy(hacker, receiver, len);
    hacker[len] = '\0';
    if (!searchuser(hacker))
    {
      return -2;
    }
    sethomepath(genbuf, hacker);
    stampfile(genbuf, &mymail);
    if (!strcmp(hacker, cuser.userid))
    {
      strcpy(mymail.owner, "[MH]");
      mymail.filemode = FILE_READ;
    }
    else
      strcpy(mymail.owner, cuser.userid);
    strncpy(mymail.title, title, TTLEN);
    unlink(genbuf);
    Link(fpath, genbuf);
    if(mh_autoforward(hacker, &mymail, sizeof(mymail), 1))
    {
      sethomedir(genbuf, hacker);
      return append_record(genbuf, &mymail, sizeof(mymail));
    }
    else
      unlink(genbuf);
  }
  
  /* setup the hostname and username */
  if (!configured)
  {
    /* get host name */
    gethostname(myhostname, STRLEN);
    hbuf = gethostbyname(myhostname);
    if (hbuf)
      strncpy(myhostname, hbuf->h_name, STRLEN);

    /* get bbs uident */
    pbuf = getpwuid(getuid());
    if (pbuf)
      strncpy(myusername, pbuf->pw_name, 20);
    if (hbuf && pbuf)
      configured = 1;
    else
      return -1;
  }

  /* Running the sendmail */

#ifdef  INTERNET_PRIVATE_EMAIL
  if (fpath == NULL)
  {
    sprintf(genbuf, "/usr/sbin/sendmail %s > /dev/null", receiver);
    fin = fopen("etc/confirm", "r");
  }
  else
  {
    sprintf(genbuf, "/usr/sbin/sendmail -f %s%s %s > /dev/null", cuser.userid, str_mail_address, receiver);
    fin = fopen(fpath, "r");
  }
  fout = popen(genbuf, "w");
  if (fin == NULL || fout == NULL)
    return -1;

  if (fpath)
    fprintf(fout, "Reply-To: %s%s\nFrom: %s%s\n",
      cuser.userid, str_mail_address, cuser.userid, str_mail_address);
#else
  sprintf(genbuf, "/usr/sbin/sendmail %s > /dev/null", receiver);
  fout = popen(genbuf, "w");
  fin = fopen(fpath ? fpath : "etc/confirm", "r");
  if (fin == NULL || fout == NULL)
    return -1;

  if (fpath)
    fprintf(fout, "From: %s@%s (%s)\n",
      myusername, myhostname, BBSNAME);
#endif

  /* MH */
  /* for RFC 2045/2047 */
  {
    unsigned char encoded_title[MH_ENCODED_TTLEN];
    
    fprintf(fout, "To: %s\nSubject: %s\n", receiver,
            mh_qp_encode(encoded_title, MH_ENCODED_TTLEN, title, "Big5"));
  }
  fprintf(fout, "Mime-Version: 1.0\n");
  fprintf(fout, "Content-Type: text/plain; charset=\"Big5\"\n");
  fprintf(fout, "Conten-Transfer-Endocing: 8bit\n");
  /*    */
  fprintf(fout, "X-Disclaimer: " BOARDNAME
    "¹ï¥»«H¤º®e®¤¤£­t³d¡C\n\n");

  while (fgets(genbuf, 255, fin))
  {
    if (genbuf[0] == '.' && genbuf[1] == '\n')
      fputs(". \n", fout);
    else
      fputs(genbuf, fout);
  }
  fclose(fin);
  fprintf(fout, ".\n");
  pclose(fout);
  return 0;
}


int
doforward(direct, fh, mode)
  char *direct;
  fileheader *fh;
  int mode;                     /* ¬O§_ uuencode */
{
  static char address[60];
  char fname[MAXPATHLEN];
  int return_no;
  char genbuf[200];

  if (!address[0] && cuser.userlevel)
    strcpy(address, cuser.email);

  if (address[0])
  {
    sprintf(genbuf, "½T©wÂà±Hµ¹ [%s] ¶Ü(Y/N/Q)¡H[Y] ", address);
    getdata(b_lines - 1, 0, genbuf, fname, 3, LCECHO, 0);

    if (fname[0] == 'q')
    {
      outmsg("¨ú®øÂà±H");
      return 1;
    }
    if (fname[0] == 'n')
      address[0] = '\0';
  }

  if (!address[0])
  {
    getdata(b_lines - 1, 0, "½Ð¿é¤JÂà±H¦a§}¡G", fname, 60, DOECHO, address);
    if (*fname)
        strcpy(address, fname);
    else {
      outmsg("¨ú®øÂà±H");
      return 1;
    }
  }
  if (!strchr(address, '@')) {
    if (searchuser(address)) {
        fileheader mhdr;
        char fpath[STRLEN];

        sprintf(fpath, "%s/%s", direct, fh->filename);
        sethomepath(genbuf, address);
        stampfile(genbuf, &mhdr);
        Link(fpath, genbuf);
        strcpy(mhdr.owner, cuser.userid);
        strncpy(mhdr.title, fh->title, TTLEN);
        mhdr.savemode = '\0';
        if(mh_autoforward(address, &mhdr, sizeof(mhdr), 1))
        {
          sethomedir(fpath, address);
          if (append_record(fpath, &mhdr, sizeof(mhdr)) == -1)
            return -1;
        }
        else
          unlink(genbuf);
        return 0;
    }
    else {
       outmsg(err_uid);
       refresh();
       return 1;
    }
  }

  if (invalidaddr(address))
    return -2;

  sprintf(fname, "¥¿Âà±Hµ¹ %s, ½Ðµy­Ô...", address);
  outmsg(fname);
  move(b_lines - 1, 0);
  if (mbbsd)
     redoscr();
  else
     refresh();

  if (mode == 'Z') {
     FILE* fp;
     int address_ok = valid_ident(address);

     if (fp = fopen("mbox_sent", "a")) {
        time_t now = time(0);

        fprintf(fp, "%c%-12s %s => %s\n",
           address_ok ? ' ' : '-', cuser.userid, Cdatelite(&now), address);
        fclose(fp);
     }
     if (!address_ok) {
         sprintf(fname, "µL®Äªº¤u§@¯¸¦ì§} %s", address);
         outmsg(fname);
         igetch();
         return -2;
      }
      
/* 2004/07/15 by Terry */
     sprintf(fname, "cd %s/home; tar cfz - %s | uuencode %s.tgz > %s/tmp/%s.tgz",
	     BBSHOME, cuser.userid, cuser.userid, BBSHOME, cuser.userid);
/*		       */
     system(fname);
     strcpy(fname, direct);
  }
  else if (mode == 'U')
  {
    char tmp_buf[128];

    sprintf(fname, "tmp/bbs.uu%05d", currpid);
    sprintf(tmp_buf, "/usr/bin/uuencode %s/%s uu.%05d > ~/%s",
      direct, fh->filename, currpid, fname);
    system(tmp_buf);
    sleep(1);
  }
  else
    sprintf(fname, "%s/%s", direct, fh->filename);

  return_no = bbs_sendmail(fname, fh->title, address);

  if (mode == 'Z')
    unlink(fname);

  return (return_no);
}
#endif


int
chkmail(rechk)
  int rechk;
{
  static time_t lasttime = 0;
  static int ismail = 0;
  struct stat st;
  fileheader fh;
  int fd;
  register numfiles;
  unsigned char ch;

  if (!rechk && !HAS_PERM(PERM_BASIC))
    return 0;

  if (stat(currmaildir, &st) < 0)
    return (ismail = 0);

  if ((lasttime >= st.st_mtime) && !rechk)
    return ismail;

  lasttime = st.st_mtime;
  numfiles = st.st_size / sizeof(fileheader);
  if (numfiles <= 0)
    return (ismail = 0);

  /* ------------------------------------------------ */
  /* ¬Ý¬Ý¦³¨S¦³«H¥óÁÙ¨SÅª¹L¡H±qÀÉ§À¦^ÀYÀË¬d¡A®Ä²v¸û°ª */
  /* ------------------------------------------------ */

  if ((fd = open(currmaildir, O_RDONLY)) > 0)
  {
    lseek(fd, st.st_size - 1, SEEK_SET);
    while (numfiles--)
    {
      read(fd, &ch, 1);
      if (!(ch & FILE_READ))
      {
        close(fd);
        return (ismail = 1);
      }
      lseek(fd, -(off_t)(sizeof(fileheader) + 1), SEEK_CUR);
    }
    close(fd);
  }
  return (ismail = 0);
}


#ifdef  EMAIL_JUSTIFY
void
mail_justify(userec muser)
{
   fileheader mhdr;
   char title[128], buf1[80];
   FILE* fp;

   sethomepath(buf1, muser.userid);
   stampfile(buf1, &mhdr);
   unlink(buf1);
/*
   strcpy(mhdr.owner, cuser.userid);
*/
   strcpy(mhdr.owner, "¯¸ªø");
   strncpy(mhdr.title, "[¼f®Ö³q¹L]", TTLEN);
   mhdr.savemode = 0;
   mhdr.filemode = 0;
/*
woju
  more("etc/justify", NA);
*/
  if (valid_ident(muser.email) && !invalidaddr(muser.email))
  {
    char title[80], *ptr;
    ushort checksum;            /* 16-bit is enough */
    char ch;

    checksum = getuser(muser.userid);
    ptr = muser.email;
    while (ch = *ptr++)
    {
      if (ch <= ' ')
        break;
      if (ch >= 'A' && ch <= 'Z')
        ch |= 0x20;
      checksum = (checksum << 1) ^ ch;
    }

    sprintf(title, "[SOB BBS]To %s(%d:%d) [User Justify]",
      muser.userid, getuser(muser.userid) + MAGIC_KEY, checksum);
    if (bbs_sendmail(NULL, title, muser.email) < 0)
      Link("etc/bademail", buf1);
    else
      Link("etc/replyemail", buf1);
  }
  else
      Link("etc/bademail", buf1);
  sethomedir(title, muser.userid);
  append_record(title, &mhdr, sizeof(mhdr));
}
#endif                          /* EMAIL_JUSTIFY */

