/*-------------------------------------------------------*/
/* board.c      ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : ¬ÝªO¡B¸s²Õ¥\¯à                               */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


#define BRC_MAXSIZE     24576
#define BRC_MAXNUM      80
#define BRC_STRLEN      15
#define BRC_ITEMSIZE    (BRC_STRLEN + 1 + BRC_MAXNUM * sizeof( int ))


int brc_size, brc_changed = 0;
int brc_list[BRC_MAXNUM], brc_num;
char brc_buf[BRC_MAXSIZE];
char brc_name[BRC_STRLEN];

static time_t brc_expire_time;


extern int numboards;
extern boardheader *bcache;

typedef struct
{
  int pos, total;
  char *name, *title, *BM;
  uschar unread, zap, bvote;
}      boardstat;

boardstat *nbrd;


int *zapbuf;
int brdnum, yank_flag = 0;
int ith_board;

char *boardprefix;

static char *str_local_board = "¡°";  /* ¥Nªí local board class */
static char *str_tw_board = "ùþ";  /* ¥Nªí non-tw board class */


/* ----------------------------------------------------- */
/* home/userid/.boardrc maintain                         */
/* ----------------------------------------------------- */

static char *fn_boardrc = ".boardrc";


static char *
brc_getrecord(ptr, name, pnum, list)
  char *ptr, *name;
  int *pnum, *list;
{
  int num;
  char *tmp;

  strncpy(name, ptr, BRC_STRLEN);
  ptr += BRC_STRLEN;
  num = (*ptr++) & 0xff;
  tmp = ptr + num * sizeof(int);
  if (num > BRC_MAXNUM)
    num = BRC_MAXNUM;
  *pnum = num;
  memcpy(list, ptr, num * sizeof(int));
  return tmp;
}


static char *
brc_putrecord(ptr, name, num, list)
  char *ptr, *name;
  int num, *list;
{
  if (num > 0 && list[0] > brc_expire_time)
  {
    if (num > BRC_MAXNUM)
      num = BRC_MAXNUM;

    while (num > 1 && list[num - 1] < brc_expire_time)
      num--;

    strncpy(ptr, name, BRC_STRLEN);
    ptr += BRC_STRLEN;
    *ptr++ = num;
    memcpy(ptr, list, num * sizeof(int));
    ptr += num * sizeof(int);
  }
  return ptr;
}


void
brc_update()
{
  if (brc_changed && cuser.userlevel)
  {
    char dirfile[STRLEN], *ptr;
    char tmp_buf[BRC_MAXSIZE - BRC_ITEMSIZE], *tmp;
    char tmp_name[BRC_STRLEN];
    int tmp_list[BRC_MAXNUM], tmp_num;
    int fd, tmp_size;

    ptr = brc_buf;
    if (brc_num > 0)
      ptr = brc_putrecord(ptr, brc_name, brc_num, brc_list);

    setuserfile(dirfile, fn_boardrc);
    if ((fd = open(dirfile, O_RDONLY)) != -1)
    {
      tmp_size = read(fd, tmp_buf, sizeof(tmp_buf));
      close(fd);
    }
    else
    {
      tmp_size = 0;
    }

    tmp = tmp_buf;
    while (tmp < &tmp_buf[tmp_size] && (*tmp >= ' ' && *tmp <= 'z'))
    {
      tmp = brc_getrecord(tmp, tmp_name, &tmp_num, tmp_list);
      if (strncmp(tmp_name, currboard, BRC_STRLEN))
        ptr = brc_putrecord(ptr, tmp_name, tmp_num, tmp_list);
    }
    brc_size = (int) (ptr - brc_buf);

    if ((fd = open(dirfile, O_WRONLY | O_CREAT, 0644)) != -1)
    {
      ftruncate(fd, 0);
      write(fd, brc_buf, brc_size);
      close(fd);
    }
    brc_changed = 0;
  }
}


int
brc_initial(boardname)
  char *boardname;
{
  char dirfile[STRLEN], *ptr;
  int fd;

  if (strcmp(currboard, boardname) == 0)
  {
    return brc_num;
  }
  brc_update();
  strcpy(currboard, boardname);
  if (brc_buf[0] == '\0')
  {
    setuserfile(dirfile, fn_boardrc);
    if ((fd = open(dirfile, O_RDONLY)) != -1)
    {
      brc_size = read(fd, brc_buf, sizeof(brc_buf));
      close(fd);
    }
    else
    {
      brc_size = 0;
    }
  }
  ptr = brc_buf;
  while (ptr < &brc_buf[brc_size] && (*ptr >= ' ' && *ptr <= 'z'))
  {
    ptr = brc_getrecord(ptr, brc_name, &brc_num, brc_list);
    if (strncmp(brc_name, currboard, BRC_STRLEN) == 0)
      return brc_num;
  }
  strncpy(brc_name, boardname, BRC_STRLEN);
  brc_num = brc_list[0] = 1;
  return 0;
}


void
brc_addlist(fname)
  char *fname;
{
  int ftime, n, i;

  if (!cuser.userlevel)
    return;

  ftime = atoi(&fname[2]);
  if (ftime <= brc_expire_time
     /* || fname[0] != 'M' || fname[1] != '.' */ )
  {
    return;
  }
  if (brc_num <= 0)
  {
    brc_list[brc_num++] = ftime;
    brc_changed = 1;
    return;
  }
  if ((brc_num == 1) && (ftime < brc_list[0]))
    return;
  for (n = 0; n < brc_num; n++)
  {
    if (ftime == brc_list[n])
    {
      return;
    }
    else if (ftime > brc_list[n])
    {
      if (brc_num < BRC_MAXNUM)
        brc_num++;
      for (i = brc_num - 1; --i >= n; brc_list[i + 1] = brc_list[i]);
      brc_list[n] = ftime;
      brc_changed = 1;
      return;
    }
  }
  if (brc_num < BRC_MAXNUM)
  {
    brc_list[brc_num++] = ftime;
    brc_changed = 1;
  }
}


int
brc_unread(fname)
  char *fname;
{
  int ftime, n;

  ftime = atoi(&fname[2]);
  if (ftime <= brc_expire_time
     /* || fname[0] != 'M' || fname[1] != '.' */ )
    return 0;
  if (brc_num <= 0)
    return 1;
  for (n = 0; n < brc_num; n++)
  {
    if (ftime > brc_list[n])
      return 1;
    else if (ftime == brc_list[n])
      return 0;
  }
  return 0;
}


/* ----------------------------------------------------- */
/* .bbsrc processing                                     */
/* ----------------------------------------------------- */

char *str_bbsrc = ".bbsrc";

static void
load_zapbuf()
{
  register int n, size;
  char fname[60];

  /* MAXBOARDS ==> ¦Ü¦h¬Ý±o¨£ 4 ­Ó·sªO */

  n = numboards + 4;
  size = n * sizeof(int);
  zapbuf = (int *) malloc(size);
  while (n)
    zapbuf[--n] = login_start_time;
  setuserfile(fname, str_bbsrc);
  if ((n = open(fname, O_RDONLY, 0600)) != -1)
  {
    read(n, zapbuf, size);
    close(n);
  }
  if (!nbrd)
    nbrd = (boardstat *) malloc(MAXBOARD * sizeof(boardstat));
  brc_expire_time = login_start_time - 30 * 86400;
}


/*static void*/  /* MH */ /* mhsin.c ¸Ì­±·|¥Î¨ì, ©Ò¥H¤£­n¥Î static void */
void
save_zapbuf()
{
  register int fd, size;
  char fname[60];

  setuserfile(fname, str_bbsrc);
  if ((fd = open(fname, O_WRONLY | O_CREAT, 0600)) != -1)
  {
    size = numboards * sizeof(int);
    write(fd, zapbuf, size);
    close(fd);
  }
}

/*
woju
Ref: bbs.c: brdperm(char* brdname, char* userid)
*/

int
Ben_Perm(bptr)
  boardheader *bptr;
{
  register int level;
  register char *ptr, *str;
  char buf[64], manager[IDLEN + 1];
  int result = 1;  /* MH */

/* MH */
  if(bptr->bmode & MH_BMODE_READ)
  {
    setbfile(buf, bptr->brdname, MH_FN_BRD_ALLOWREAD);
    if(belong(buf, cuser.userid))
      return 1;

    setbfile(buf, bptr->brdname, MH_FN_BRD_DENYREAD);
    if(belong(buf, cuser.userid))
      return 0;
    if(!HAVE_PERM(PERM_LOGINOK) && belong(buf, MH_UN_NOTLOGINOK))
      return 0;
    if(!HAVE_PERM(PERM_BM) && belong(buf, MH_UN_NOTBM))
      return 0;
    if(!HAVE_PERM(PERM_ADMIN) && belong(buf, MH_UN_NOTADMIN))
      return 0;
  }
/*    */

  level = bptr->level;
  if ((level & PERM_POSTMASK) || HAS_PERM(level))
    return 1;

  ptr = bptr->BM;
  if (ptr[0] <= ' ')
    return 0;

  if (is_BM(ptr))
    return 1;

  /* ¯¦±K¬ÝªO¡G®Ö¹ï­º®uªO¥Dªº¦n¤Í¦W³æ */

  if ((level & 0xffff) != PERM_SYSOP)
    return 0;

  strncpy(manager, ptr, IDLEN + 1);
  if (ptr = strchr(manager, '/'))
    ptr[0] = '\0';
  sethomefile(buf, manager, fn_overrides);
  return (belong(buf, cuser.userid));
}


/*static void*/  /* MH */ /* mhsin.c ¸Ì­±·|¥Î¨ì, ©Ò¥H¤£­n¥Î static void */
void
load_boards()
{
  boardheader *bptr;
  boardstat *ptr;
  char brdclass[5];
  int n;

  resolve_boards();
  if (!zapbuf)
    load_zapbuf();

  ith_board = brdnum = 0;
  for (n = 0; n < numboards; n++)
  {
    bptr = &bcache[n];
    if (bptr->brdname[0] == '\0')
      continue;
    

    if (boardprefix)
    {
      if (boardprefix == str_local_board)
      {
        strncpy(brdclass, bptr->title + 4, 2);
        brdclass[2] = '\0';
      }
      else
      {
        strncpy(brdclass, bptr->title, 4);
        brdclass[4] = '\0';
      }
      if (!strncmp(boardprefix, "Collection", strlen("Collection"))) {
         if ((bptr->level & PERM_POST) == 0)
            continue;
      }
      else if (boardprefix == str_tw_board)
      {
        if (strstr(bptr->title, str_tw_board))
           continue;
      }
      else if (strstr(boardprefix, brdclass) == NULL)
         continue;
    }


    
    if (Ben_Perm(bptr) && (yank_flag == 1 ||
        yank_flag == 2 && have_author(bptr->brdname) ||
        yank_flag != 2 && zapbuf[n]))
    {
      ptr = &nbrd[brdnum++];
      ptr->name = bptr->brdname;
      ptr->title = bptr->title;
      ptr->BM = bptr->BM;
      ptr->pos = n;
      ptr->total = -1;
      ptr->bvote = bptr->bvote;
      ptr->zap = (zapbuf[n] == 0);
    }
  }

  /* ¦pªG user ±N©Ò¦³ boards ³£ zap ±¼¤F */

  if (!brdnum && !boardprefix)
     if (yank_flag == 0)
        yank_flag = 1;
     else if (yank_flag == 2)
        yank_flag = 0;
}

static int
search_board(num)
{
  static char genbuf[IDLEN + 2];
  char buf[200];

  if (num >= 0) {
     sprintf(buf, "%s[%s]: ", "½Ð¿é¤J¬ÝªO¦WºÙ", genbuf);
     getdata(b_lines - 1, 0, buf, buf, IDLEN + 1, DOECHO, 0);
     if (*buf)
        strcpy(genbuf, buf);
     move(b_lines - 1, 0);
     clrtoeol();
     move(b_lines, 0);
     if (genbuf[0])
     {
       int n = num;

       do {
         if (++n >= brdnum)
           n = 0;
         if (strstr_lower(nbrd[n].name, genbuf) || strstr_lower(nbrd[n].title, genbuf))
           return n;
       } while (n != num);
     }
  }
  else {
     move(0,0);
     clrtoeol();
     CreateNameList();
     for (num = 0; num < brdnum; num++)
        AddNameList(nbrd[num].name);
     namecomplete(MSG_SELECT_BOARD, genbuf);
     for (num = 0; num < brdnum; num++)
        if (!strcmp(nbrd[num].name, genbuf))
           return num;
  }
  return -1;
}


/*static int*/  /* MH */ /* mhsin.c ¸Ì­±·|¥Î¨ì, ©Ò¥H¤£­n¥Î static void */
int
check_newpost(ptr)
  boardstat *ptr;
{
  fileheader fh;
  struct stat st;
  char fname[FNLEN];
  char genbuf[200];
  int fd, total;

  ptr->total = ptr->unread = 0;
  setbdir(genbuf, ptr->name);
  if ((fd = open(genbuf, O_RDWR)) < 0)
    return 0;
  fstat(fd, &st);
  total = st.st_size / sizeof(fh);
  if (total <= 0)
  {
    close(fd);
    return 0;
  }
  ptr->total = total;
  if (!brc_initial(ptr->name))
  {
    ptr->unread = 1;
  }
  else
  {
    lseek(fd, (total - 1) * sizeof(fh), SEEK_SET);
    if (read(fd, fname, FNLEN) > 0 && brc_unread(fname))
    {
      ptr->unread = 1;
    }
  }
  close(fd);
  return 1;
}


/*static int*/  /* MH */ /* mhsin.c ¸Ì­±·|¥Î¨ì, ©Ò¥H¤£­n¥Î static void */
int
unread_position(dirfile, ptr)
  char *dirfile;
  boardstat *ptr;
{
  fileheader fh;
  char fname[FNLEN];
  register int num, fd, step, total;

  total = ptr->total;
  num = total + 1;
  if (ptr->unread && (fd = open(dirfile, O_RDWR)) > 0)
  {
    if (!brc_initial(ptr->name))
    {
      num = 1;
    }
    else
    {
      num = total - 1;
      step = 4;
      while (num > 0)
      {
        lseek(fd, num * sizeof(fh), SEEK_SET);
        if (read(fd, fname, FNLEN) <= 0 || !brc_unread(fname))
          break;
        num -= step;
        if (step < 32)
          step += step >> 1;
      }
      if (num < 0)
        num = 0;
      while (num < total)
      {
        lseek(fd, num * sizeof(fh), SEEK_SET);
        if (read(fd, fname, FNLEN) <= 0 || brc_unread(fname))
          break;
        num++;
      }
    }
    close(fd);
  }
  if (num < 0)
    num = 0;
  return num;
}


static void
brdlist_foot()
{
  prints("[34;46m  ¿ï¾Ü¬ÝªO  [31;47m  (c)[30m·s¤å³¹¼Ò¦¡  [31m(v/V)[30m¼Ð°O¤wÅª/¥¼Åª  [31m(y)[30m¿z¿ï%s  [31m(z)[30m¤Á´«¿ï¾Ü  [0m",
    yank_flag ? "³¡¥÷" : "¥þ³¡");
}


/*
woju
*/
have_author(char* brdname)
{
   char dirname[200];
   int n, fd;

   ioctl(0, FIONREAD, &n);
   if (n)
      return 0;
   sprintf(dirname, "´M§ä¦³ [37;45m%.15s[m ¤å³¹ªº¬Ýª©: %-16.15s [%3d / %d]",
      currauthor, brdname, ++ith_board, numboards);
   outmsg(dirname);

   refresh();
   setbdir(dirname, brdname);

   strcpy(currowner, currauthor);
   if ((fd = open(dirname, O_RDONLY, 0)) != -1) {
      struct stat st;
      fileheader* fhdr;
      int num, i;

      fstat(fd, &st);
      if (fhdr = malloc(st.st_size)) {
         num = read(fd, fhdr, st.st_size) / sizeof(fileheader);
         close(fd);
      }
      else {
         close(fd);
         return 0;
      }

      for (i = 0; i < num; i++)
        if (!strcasecmp(fhdr[i].owner, currauthor)) {
           free(fhdr);
           return ++i;
        }
      free(fhdr);
   }
   return 0;
}


static void
show_brdlist(head, clsflag, newflag)
{
  if (clsflag)
  {
    showtitle("¬ÝªO¦Cªí", BoardName);
    prints("[¡ö]¥D¿ï³æ [¡÷]¾\\Åª [¡ô¡õ]¿ï¾Ü [y]¸ü¤J [S]±Æ§Ç [/]·j´M [TAB]¤åºK¡E¬ÝªO [h]¨D§U\n"
      "[7m%-20s Ãþ  §O %-32s§ë²¼ ªO    ¥D     [0m",
      newflag ? "Á`¼Æ ¥¼Åª ¬Ý  ªO" : "  ½s¸¹  ¬Ý  ªO", "¤¤   ¤å   ±Ô   ­z");
    move(b_lines, 0);
    brdlist_foot();
  }

  if (brdnum > 0)
  {
    boardstat *ptr;
    int myrow;

    myrow = 2;
    while (++myrow < b_lines)
    {
      move(myrow, 0);
      if (head < brdnum)
      {
        ptr = &nbrd[head++];
        if (yank_flag == 2)
          prints("%5d %c ", head, 'A');
        else if (!newflag)
          prints("%5d %c ", head, ptr->zap ? '-' : ' ');
        else if (ptr->zap)
        {
          ptr->total = ptr->unread = 0;
          outs("   ¡ß ¡ß");
        }
        else
        {
          if (ptr->total == -1)
            check_newpost(ptr);
          if (newflag)
             prints("%6d%s", ptr->total, ptr->unread ? "£¾" : "¡C");
        }
        prints("%-13s%-42.42s%c %.13s",
          ptr->name, ptr->title, " VR"[ptr->bvote], ptr->BM);
      }
      clrtoeol();
    }
  }
}


char *choosebrdhelp[] = {
  "\0¬ÝªO¿ï³æ»²§U»¡©ú",
  "\01°ò¥»«ü¥O",
  "(p)(¡ô)        ¤W¤@­Ó¬ÝªO",
  "(n)(¡õ)        ¤U¤@­Ó¬ÝªO",
  "(P)(^B)(PgUp)  ¤W¤@­¶¬ÝªO",
  "(N)(^F)(PgDn)  ¤U¤@­¶¬ÝªO",
  "($)            ³Ì«á¤@­Ó¬ÝªO",
  "(¼Æ¦r)         ¸õ¦Ü¸Ó¶µ¥Ø",
  "\01¶i¶¥«ü¥O",
  "(TAB)          ¬ÝªO/¤åºK ¼Ò¦¡¤Á´«",
  "(r)(¡÷)(Rtn)   ¶i¤J¦h¥\\¯à¾\\Åª¿ï³æ",
  "(q)(¡ö)        ¦^¨ì¥D¿ï³æ",
  "(z)            ­q¾\\/¤Ï­q¾\\¬ÝªO",
  "(y)            ¦C¥X/¤£¦C¥X©Ò¦³¬ÝªO",
  "(v/V)          ³q³q¬Ý§¹/¥þ³¡¥¼Åª",
  "(S)            «ö·Ó¦r¥À/¤ÀÃþ±Æ§Ç",
  "(/)            ·j´M¬ÝªO",
  "(Z)            ­q¾\\/¤Ï­q¾\\.....¬ÝªO",
NULL};


/* ®Ú¾Ú title ©Î name °µ sort */

/*static int*/  /* MH */ /* mhsin.c ¸Ì­±·|¥Î¨ì, ©Ò¥H¤£­n¥Î static void */
int
cmpboard(brd, tmp)
  boardstat *brd, *tmp;
{
  register int type = 0;

  if (!(cuser.uflag & BRDSORT_FLAG))
    type = strncmp(brd->title, tmp->title, 6);
  if (!type)
    type = strcasecmp(brd->name, tmp->name);
  return type;
}


static void
choose_board(newflag)
{
  static int num = 0;
  boardstat *ptr;
  int head, ch, tmp;
  char genbuf[200];
  extern time_t board_visit_time;

  setutmpmode(newflag ? READNEW : READBRD);
  brdnum = 0;
  if (!cuser.userlevel)         /* guest yank all boards */
    yank_flag = 1;

  do
  {
    if (brdnum <= 0)
    {
      load_boards();
      if (brdnum <= 0)
        break;
      qsort(nbrd, brdnum, sizeof(boardstat), cmpboard);
      head = -1;
    }

    if (num < 0)
      num = 0;
    else if (num >= brdnum)
      num = brdnum - 1;

    if (head < 0)
    {
      if (newflag)
      {
        tmp = num;
        while (num < brdnum)
        {
          ptr = &nbrd[num];
          if (ptr->total == -1)
            check_newpost(ptr);
          if (ptr->unread)
            break;
          num++;
        }
        if (num >= brdnum)
          num = tmp;
      }
      head = (num / p_lines) * p_lines;
      show_brdlist(head, 1, newflag);
    }
    else if (num < head || num >= head + p_lines)
    {
      head = (num / p_lines) * p_lines;
      show_brdlist(head, 0, newflag);
    }

    ch = cursor_key(3 + num - head, 0);

    switch (ch)
    {
    case 'e':
    case KEY_LEFT:
    case EOF:
      ch = 'q';
    case 'q':
      break;

    case 'c':
      if (yank_flag == 2) {
         newflag = yank_flag = 0;
         brdnum = -1;
      }
      show_brdlist(head, 1, newflag ^= 1);
      break;

/*
woju
*/
    case 'A':
    case 'a': {
      if (yank_flag != 2 ) {
         if (getdata(1, 0, "§@ªÌ ", genbuf, IDLEN + 2, DOECHO, currauthor))
            strncpy(currauthor, genbuf, IDLEN + 2);
         if (*currauthor)
            yank_flag = 2;
         else
            yank_flag= 0;
      }
      else
         yank_flag = 0;
      brdnum = -1;
      show_brdlist(head, 1, newflag);
      break;
    }
    case KEY_PGUP:
    case 'P':
    case 'b':
      if (num)
      {
        num -= p_lines;
        break;
      }

    case KEY_END:
    case '$':
      num = brdnum - 1;
      break;

    case ' ':
    case KEY_PGDN:
    case 'N':
    case Ctrl('F'):
      if (num == brdnum - 1)
        num = 0;
      else
        num += p_lines;
      break;

/* MH */
        case Ctrl('R'):
         mh_throw_water_ball();
         show_brdlist(head, 1, newflag);
         break;
/*    */

    case KEY_ESC: if (KEY_ESC_arg == 'n') {
       edit_note();
       show_brdlist(head, 1, newflag);
       }
       break;
    case Ctrl('U'):
       t_users();
       show_brdlist(head, 1, newflag);
       break;
    case Ctrl('B'):
       m_read();
       show_brdlist(head, 1, newflag);
       break;

    case Ctrl('I'):
       t_idle();
       show_brdlist(head, 1, newflag);
       break;

    case KEY_UP:
    case 'p':
    case 'k':
      if (num-- <= 0)
        num = brdnum - 1;
      break;

    case KEY_DOWN:
    case 'n':
    case 'j':
      if (++num < brdnum)
        break;

    case '0':
    case KEY_HOME:
      num = 0;
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
      if ((tmp = search_num(ch, brdnum)) >= 0)
        num = tmp;
      brdlist_foot();
      break;

    case 'h':
      show_help(choosebrdhelp);
      show_brdlist(head, 1, newflag);
      break;

    case Ctrl('A'):
       Announce();
       show_brdlist(head, 1, newflag);
       break;

    case '/':
      if ((tmp = search_board(num)) >= 0)
        num = tmp;
      show_brdlist(head, 1, newflag);
      break;

    case 'S':
      cuser.uflag ^= BRDSORT_FLAG;
      qsort(nbrd, brdnum, sizeof(boardstat), cmpboard);
      head = 999;
      break;

    case 'y':
      if (yank_flag == 2)
         yank_flag = 0;
      else
         yank_flag ^= 1;
      brdnum = -1;
      break;

    case 'z':                   /* opus: no perm check ? */
      if (HAS_PERM(PERM_BASIC))
      {
        ptr = &nbrd[num];
        ptr->zap = !ptr->zap;
        ptr->total = -1;
        zapbuf[ptr->pos] = (ptr->zap ? 0 : login_start_time);
        head = 999;
      }
      break;

    /* MH */
    /* 2003/10/16 */
    case 'Z':
      if(HAS_PERM(PERM_BASIC))
      {
        int a;
        int v = (brdnum ? !nbrd[0].zap : 0);
        
        for(a = 0; a < brdnum; a ++)
        {
          ptr = &nbrd[a];
          ptr->zap = v;
          ptr->total = -1;
          zapbuf[ptr->pos] = (ptr->zap ? 0 : login_start_time);
          head = 999;
        }
      }
      break;
    /*    */
    
    case 'v':
    case 'V':
      ptr = &nbrd[num];
      brc_initial(ptr->name);
      if (ch == 'v')
      {
        ptr->unread = 0;
        zapbuf[ptr->pos] = time((time_t *) &brc_list[0]);
      }
      else
        zapbuf[ptr->pos] = brc_list[0] = ptr->unread = 1;
      brc_num = brc_changed = 1;
      brc_update();
      if (newflag)
        show_brdlist(head, 0, 1);
      break;

    case 's':
       if ((tmp = search_board(-1)) < 0) {
          show_brdlist(head, 1, newflag);
          break;
       }
       num = tmp;
    case KEY_RIGHT:
    case '\n':
    case '\r':
    case 'r':
      {
        char buf[STRLEN];

        ptr = &nbrd[num];
        brc_initial(ptr->name);

        if (yank_flag == 2)
        {
          setbdir(buf, currboard);
          tmp = have_author(currboard) - 1;
          head = tmp - t_lines / 2;
          getkeep(buf, head > 1 ? head : 1, -(tmp + 1));
        }
        else if (newflag)
        {
          setbdir(buf, currboard);
          tmp = unread_position(buf, ptr);
          head = tmp - t_lines / 2;
          getkeep(buf, head > 1 ? head : 1, tmp + 1);
        }
        board_visit_time = zapbuf[ptr->pos];
        if (!ptr->zap)
          time((time_t *) &zapbuf[ptr->pos]);

/* MH */
/* ¥Î¨Ó°O¿ý¯S©wªº¤H³y³X¯S©wªºªO */
        if(mh_belong(MH_FN_LOG_BRDLIST, MH_BELONG_BOARD, currboard))
        {
          FILE *fp, *fp2;
          time_t now;
          struct tm *ptime;
          char buf[100];

          sprintf(buf, "boards/%s/" MH_FN_LOG_BRD_LIST, currboard);
          if(mh_belong(buf, MH_BELONG_USER, cuser.userid))
          {
            sprintf(buf, BBSHOME "/boards/%s/" MH_FN_LOG_BRD_LOG, currboard);
            fp = fopen(buf, "a+");
            fp2 = fopen(BBSHOME "/" MH_FN_LOG_BRDLOG, "a+");
            {
              time(&now);
              ptime = localtime(&now);
              strcpy(buf, asctime(ptime));
              mh_delete_nl(buf);
              fprintf(fp, "%s %s\n", buf, cuser.userid);
              fprintf(fp2, "%s %s %s\n", buf, cuser.userid, currboard);
              fclose(fp);
              fclose(fp2);
            }
          }
        }
/*    */

        Read();

        ptr->total = head = -1;
        setutmpmode(newflag ? READNEW : READBRD);
      }
    }
  } while (ch != 'q');
  save_zapbuf();
}


int
board()
{
  choose_board(1);
  return 0;
}


int
local_board()
{
  boardprefix = str_local_board;
  choose_board(1);
  return 0;
}

int tw_board()
{
  boardprefix = str_tw_board;
  choose_board(1);
  return 0;
}

int
Boards()
{
  boardprefix = NULL;
  choose_board(0);
  return 0;
}


int
New()
{
  int mode0 = currutmp->mode;
  int stat0 = currstat;
  char currboard0[IDLEN + 2];

  boardprefix = NULL;
  choose_board(1);
  currutmp->mode = mode0;
  currstat = stat0;
  return 0;
}
