/*-------------------------------------------------------*/
/* announce.c   ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : ºëµØ°Ï¾\Åª¡B½s¿ï                             */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/

/*==========

    This file is re-edited by Tsai Menguang (mgtsai), Sep 10th, '96

    Change the announce directory structure as .DIR format

==========*/


#include <sys/param.h>
#include "bbs.h"
#include <time.h>

#define FHSZ            sizeof(fileheader)

#define ADDITEM         0
#define ADDGROUP        1
#define ADDGOPHER       2
#define ADDLINK         3


enum
{
  NOBODY, MANAGER, SYSOP
};


typedef struct
{
  fileheader *header;
  char mtitle[STRLEN];
  char *path;
  int num, page, now, level;
}      MENU;


static char copyfile[MAXPATHLEN];
static char copytitle[TTLEN+1];
static char copyowner[IDLEN + 2];
static char *mytitle = BOARDNAME "§G§iÄæ";
static char *err_dup_fn = "¨t²Î¤¤¤w¦³¦P¦WÀÉ®×¦s¦b¤F¡I";
static char *a_title;
static char paste_fname[200];

#define MAXITEMS        200     /* ¤@¼h¥Ø¿ý¤¤³Ì¦h¦³´X¶µ¡H */
#define PATHLEN         128


union x_item
{
  struct                        /* bbs_item */
  {
    char fdate[9];              /* [mm/dd/yy] */
    char editor[13];            /* user ID */
    char fname[31];
  }      B;

  struct                        /* gopher_item */
  {
    char path[81];
    char server[48];
    int port;
  }      G;
};


typedef struct
{
  char title[TTLEN + 1];
  union x_item X;
}      ITEM;


typedef struct
{
  ITEM *item[MAXITEMS];
  char mtitle[STRLEN];
  char *path;
  int num, page, now, level;
}      GMENU;



static void
g_showmenu(pm)
  GMENU *pm;
{
  static char *mytype = "½s    ¿ï     µ·¸ô¤§®È";
  char *title, *editor, *fname, *fdate, ch;
  int n, max, mode;
  ITEM *item;

  showtitle("ºëµØ¤å³¹", pm->mtitle);
  prints("  [1;36m½s¸¹    ¼Ð      ÃD%56s[m", mytype);

  if (pm->num)
  {
    n = pm->page;
    max = n + p_lines;
    if (max > pm->num)
      max = pm->num;
    while (n < max)
    {
      item = pm->item[n++];
      title = item->title;
      ch = title[1];
      prints("\n%5d. %-72.71s", n, title);
    }
  }
  else
  {
    outs("\n  ¡mºëµØ°Ï¡n©|¦b§l¨ú¤Ñ¦a¶¡ªº¤éºë¤ëµØ :)");
  }

  move(b_lines, 1);
  outs(pm->level ?
    "[34;46m ¡iªO  ¥D¡j [31;47m  (h)[30m»¡©ú  [31m(q/¡ö)[30mÂ÷¶}  [31m(a)[30m·s¼W¤å³¹  [31m(g)[30m·s¼W¥Ø¿ý  [31m(e)[30m½s¿èÀÉ®×  [m" :
    "[34;46m ¡i¥\\¯àÁä¡j [31;47m  (h)[30m»¡©ú  [31m(q/¡ö)[30mÂ÷¶}  [31m(k¡ôj¡õ)[30m²¾°Ê´å¼Ð  [31m(enter/¡÷)[30mÅª¨ú¸ê®Æ  [m");
}

/*-------------------------------------------------------*/


#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>


FILE *
go_cmd(node, sock)
  ITEM *node;
  int *sock;
{
  struct sockaddr_in sin;
  struct hostent *host;
  struct in_addr addr;          /* u_long */
  char *site;
  FILE *fp;

  *sock = socket(AF_INET, SOCK_STREAM, 0);

  if (*sock < 0)
  {
    perror("ERROR(get socket)");
    return NULL;
  }
  (void) memset((char *) &sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(node->X.G.port);

  host = gethostbyname(site = node->X.G.server);
  if (host == NULL)
    sin.sin_addr.s_addr = inet_addr(site);
  else
    (void) memcpy(&sin.sin_addr.s_addr, host->h_addr, host->h_length);

  if (connect(*sock, (struct sockaddr *) & sin, sizeof(sin)) < 0)
  {
    perror("ERROR(connect)");
    return NULL;
  }
  fp = fdopen(*sock, "r+");
  if (fp != NULL)
  {
    setbuf(fp, (char *) 0);
    fprintf(fp, "%s\r\n", node->X.G.path);
    fflush(fp);
  }
  else
    close(*sock);
  return fp;
}


char *
nextfield(data, field)
  register char *data, *field;
{
  register int ch;

  while (ch = *data)
  {
    data++;
    if ((ch == '\t') || (ch == '\r' && *data == '\n'))
      break;
    *field++ = ch;
  }
  *field = '\0';
  return data;
}

FILE* my_open(char* path)
{
   FILE* ans = 0;
   char buf[80];
   struct stat st;
   time_t now = time(0);

   if (stat(path, &st) == 0 && st.st_mtime < now - 3600 * 24 * 7) {
/*
woju
      getdata(b_lines - 1, 0, "¤w¶W¹L¤@¬P´Á¨S§ó·s¡A¬O§_§ó·s¸ê®Æ(Y/N)¡H[Y] ",
         buf, 4, LCECHO, 0);
      if (*buf != 'n')
*/
         return fopen(path, "w");
   }

   if (ans = fopen(path, "r+")) {
      fclose(ans);
      return 0;
/*
return directly due to currutmp->pager > 1 mode (real copy)
*/
      fgets(buf, 80, ans);
      if (!strncmp(buf, str_author1, strlen(str_author1))
          || *buf == '0' || *buf == '1') {
         fclose(ans);
         return 0;
      }

      rewind(ans);
   }
   else
      ans = fopen(path, "w");
   return ans;
}


static jmp_buf jbuf;


static void
cleanup(sig)
  int sig;
{
  int status;

  signal(SIGCHLD, SIG_IGN);
  wait(&status);
}


static void
isig(sig)
  int sig;
{
  signal(SIGINT, SIG_IGN);
  longjmp(jbuf, 1);
}


go_proxy(char* fpath, ITEM *node, int update)
{
  struct stat st;
  char *ptr, *str, *server;
  int ch, mode;
  FILE* fo;
  pid_t pid;

#define PROXY_HOME      "proxy/"

  strcpy(fpath, PROXY_HOME);
  ptr = fpath + sizeof(PROXY_HOME) - 1;

  str = server = node->X.G.server;
  while (ch = *str)
  {
    str++;
    if (ch == '.')
    {
      if (!strcmp(str, "edu.tw"))
        break;
    }
    else if ( ch >= 'A' && ch <= 'Z')
    {
      ch |= 0x20;
    }
    *ptr++ = ch;
  }
  *ptr = '\0';
  mkdir(fpath, 0755);

  *ptr++ = '/';
  if(!node->X.G.path[0])
     strcpy(node->X.G.path, "1/");
  str = node->X.G.path;
  while (ch = *str)
  {
    str++;
    if (ch == '/')
    {
      ch = '.';
    }
    *ptr++ = ch;
  }
  *ptr = '\0';

  /* expire proxy data */

  if (fo = update ? fopen(fpath, "w") : my_open(fpath))
  {
    FILE *fp;
    char buf[512];
    int sock;

    if (fo == NULL)
      return;

    outmsg("¡¹ «Ø¥ß proxy ¸ê®Æ³s½u¤¤ ... («ö CTRL-D Â÷¶})");
    refresh();

    signal(SIGINT, isig);
    signal(SIGCHLD, cleanup);
    if ((pid = fork()) < 0)
    {
      fclose(fo);
      return;
    }
    if (!pid)
    {
      while (igetch() != Ctrl('D'));
      kill(getppid(), SIGINT);
      exit(0);
    }

    sock = -1;
    if (setjmp(jbuf))
    {
      system("stty raw -echo");
      if (sock != -1)
        close(sock);
      fseek(fo, 0, SEEK_SET);
      fwrite("", 0, 0, fo);
      fclose(fo);
      return;
    }

    fp = go_cmd(node, &sock);
    if (fp == NULL)
    {
      signal(SIGINT, SIG_IGN);
      kill(pid, SIGKILL);
      fclose(fo);
      return;
    }

    str = node->title;
    ch = str[1];
    if (ch == (char) 0xbc && !(HAS_PERM(PERM_SYSOP) && currutmp->pager > 1))
    {
      time_t now;

      time(&now);
      fprintf(fo, "§@ªÌ: %s (³s½uºëµØ°Ï)\n¼ÐÃD: %s\n®É¶¡: %s\n",
        server, str + 3, ctime(&now)
        );
    }

    while (fgets(buf, 511, fp))
    {
      if (!strcmp(buf, ".\r\n"))
        break;
      if (ptr = strstr(buf, "\r\n"))
        strcpy(ptr, "\n");
      fputs(buf, fo);
    }
    signal(SIGINT, SIG_IGN);
    kill(pid, SIGKILL);
    fclose(fo);
    fclose(fp);
  }
}

g_additem(GMENU *pm, ITEM *myitem)
{
  if (pm->num < MAXITEMS)
  {
    ITEM *newitem = (ITEM *) malloc(sizeof(ITEM));

    memcpy(newitem, myitem, sizeof(ITEM));
    pm->item[(pm->num)++] = newitem;
  }
}




go_menu(GMENU *pm, ITEM *node, int update)
{
  FILE *fp;
  char buf[512], *ptr, *title;
  ITEM item;
  int ch;

  go_proxy(buf, node, update);

  pm->num = 0;
  if (fp = fopen(buf, "r"))
  {
    title = item.title;
    while (fgets(buf, 511, fp))
    {
      ptr = buf;
      ch = *ptr++;
      if (ch != '0' && ch != '1')
        continue;

      strcpy(title, "¡¼ ");
      if (ch == '1')
        title[1] = (char) 0xbd;

      ptr = nextfield(ptr, title + 3);
      if (!*ptr)
        continue;
      title[sizeof(item.title) - 1] = '\0';

      ptr = nextfield(ptr, item.X.G.path);
      if (!*ptr)
        continue;

      ptr = nextfield(ptr, item.X.G.server);
      if (!*ptr)
        continue;

      nextfield(ptr, buf);
      item.X.G.port = atoi(buf);

      g_additem(pm, &item);
    }
    fclose(fp);
  }
}


/*
woju, mgtsai
*/
g_searchtitle(GMENU* pm, int rev)
{
   char buf[100];
   static char search_str[30];
   int pos;

   sprintf(buf, "%c[%s] ", rev ? '?' : '/', search_str);
   if (getdata(b_lines - 1, 1, buf, buf, 40, DOECHO, 0))
      strcpy(search_str, buf);

   if (!*search_str)
      return pm->now;

   str_lower(buf, search_str);

   rev = rev ? -1 : 1;
   pos = pm->now;
   do {
      pos += rev;
      if (pos == pm->num)
         pos = 0;
      else if (pos < 0)
         pos = pm->num - 1;
      if (strstr_lower(pm->item[pos]->title, buf))
         return pos;
   } while (pos != pm->now);
   return pm->now;
}

g_showhelp()
{
  clear();
  outs("[36m¡i " BOARDNAME "³s½uºëµØ°Ï¨Ï¥Î»¡©ú ¡j[m\n\n\
[¡ö][q]         Â÷¶}¨ì¤W¤@¼h¥Ø¿ý\n\
[¡ô][k]         ¤W¤@­Ó¿ï¶µ\n\
[¡õ][j]         ¤U¤@­Ó¿ï¶µ\n\
[¡÷][r][enter]  ¶i¤J¥Ø¿ý¡þÅª¨ú¤å³¹\n\
[b][PgUp]       ¤W­¶¿ï³æ\n\
[^F][PgDn][Spc] ¤U­¶¿ï³æ\n\
[##]            ²¾¨ì¸Ó¿ï¶µ\n\
[^S]            ±N¤å³¹¦s¨ì«H½c\n\
[R]             §ó·s¸ê®Æ\n\
[N]             ¬d¸ßÀÉ¦W\n\
[c][C][^C]      «þ¨©¤å³¹/¨Ã¸õ¦Ü¤W¦¸¶K¤å³¹ªº¦a¤è/ª½±µ¶K¨ì¤W¦¸¶Kªº¦a¤è\n");
  pressanykey();
}


gem(char* maintitle, ITEM* path, int update)
{
  GMENU me;
  int ch;
  char fname[MAXPATHLEN];

  strncpy(me.mtitle, maintitle, 40);
  me.mtitle[40] = 0;
  go_menu(&me, path, update);

  /* ºëµØ°Ï-tree ¤¤³¡¥÷µ²ºcÄÝ©ó cuser ==> BM */

  me.level = 0;
  me.page = 9999;
  me.now = 0;
  for (;;)
  {
    if (me.now >= me.num && me.num > 0)
      me.now = me.num - 1;
    else if (me.now < 0)
      me.now = 0;

    if (me.now < me.page || me.now >= me.page + p_lines)
    {
      me.page = me.now - (me.now % p_lines);
      g_showmenu(&me);
    }
    ch = cursor_key(2 + me.now - me.page, 0);

    if (ch == 'q' || ch == 'Q' || ch == KEY_LEFT)
      break;

    if (ch >= '0' && ch <= '9')
    {
      if ((ch = search_num(ch, me.num)) != -1)
        me.now = ch;
      me.page = 9999;
      continue;
    }

    switch (ch)
    {
    case KEY_UP:
    case 'k':
      if (--me.now < 0)
        me.now = me.num - 1;
      break;

    case KEY_DOWN:
    case 'j':
      if (++me.now >= me.num)
        me.now = 0;
      break;

    case KEY_PGUP:
    case 'b':
      if (me.now >= p_lines)
        me.now -= p_lines;
      else if (me.now > 0)
        me.now = 0;
      else
        me.now = me.num - 1;
      break;

    case ' ':
    case KEY_PGDN:
    case Ctrl('F'):
      if (me.now < me.num - p_lines)
        me.now += p_lines;
      else if (me.now < me.num - 1)
        me.now = me.num - 1;
      else
        me.now = 0;
      break;

    case 'h':
      g_showhelp();
      me.page = 9999;
      break;
    case '?':
    case '/':
       me.now = g_searchtitle(&me, ch == '?');
       me.page = 9999;
       break;
    case 'N':
       if (HAS_PERM(PERM_SYSOP)) {
          go_proxy(fname, me.item[me.now], 0);
          move(b_lines - 1, 0);
          outs(fname);
          pressanykey();
          me.page = 9999;
       }
       break;
    case 'c':
    case 'C':
    case Ctrl('C'):
      if (me.now < me.num) {
        ITEM *node = me.item[me.now];
        char *title = node->title;
        int mode = title[1];

        load_paste();
        if (mode == (char) 0xbc || ch == Ctrl('C'))
        {
          struct stat st;

          if (mode == (char) 0xbc)
             go_proxy(fname, node, 0);
          if (ch == Ctrl('C') && *paste_path && paste_level) {
             char newpath[MAXPATHLEN];
             fileheader item;

             strcpy(newpath, paste_path);
             if (mode == (char) 0xbc) {
                stampfile(newpath, &item);
                unlink(newpath);
                Link(fname, newpath);
             }
             else
                stampdir(newpath, &item);
             strcpy(item.owner, cuser.userid);
             if (currutmp->pager > 1) {
                title[43] = 0;
                trim(title);
             }
             sprintf(item.title, "%s%.72s",
                (currutmp->pager > 1) ? "" :
                (mode == (char) 0xbc) ? "¡º " : "¡» ", title + 3);
             strcpy(strrchr(newpath, '/') + 1, ".DIR");
             append_record(newpath, &item, FHSZ);
             if (++me.now >= me.num)
               me.now = 0;
             break;
          }
          if (mode == (char) 0xbc) {
             a_copyitem(fname, title + ((currutmp->pager > 1) ? 3 :0), 0);
             if (ch == 'C' && *paste_path)
                a_menu(paste_title, paste_path, paste_level);
             me.page = 9999;
          }
          else
             bell();
        }
      }
      break;

/*
woju
*/
    case Ctrl('S'):
      if (me.now < me.num) {
        ITEM *node = me.item[me.now];
        char *title = node->title;
        int mode = title[1];

        if (mode == (char) 0xbc)
        {
          fileheader fhdr;

          go_proxy(fname, node, 0);
          strcpy(fhdr.owner, "³s½uºëµØ°Ï");
          strcpy(fhdr.title, title);
          if (save_mail(-1, &fhdr, fname) == POS_NEXT)
             if (++me.now >= me.num)
               me.now = 0;
        }
        else
           bell();
      }
      break;
/* MH */
      case Ctrl('R'):
       mh_throw_water_ball();
       me.page = 9999;
       break;
/*    */

    case KEY_ESC: if (KEY_ESC_arg == 'n') {
       edit_note();
       me.page = 9999;
       }
       break;

    case Ctrl('U'):
       t_users();
       me.page = 9999;
       break;

    case Ctrl('B'):
       m_read();
       me.page = 9999;
       break;

    case Ctrl('I'):
       t_idle();
       me.page = 9999;
       break;

    case 's':
       AnnounceSelect();
       me.page = 9999;
       break;

    case '\n':
    case '\r':
    case KEY_RIGHT:
    case 'r':
    case 'R':
      if (me.now < me.num)
      {
        ITEM *node = me.item[me.now];
        char *title = node->title;
        int mode = title[1];
        int update = (ch == 'R') ? 1 : 0;

        title += 3;

        if (mode == (char) 0xbc)
        {
          int more_result;

          go_proxy(fname, node, update);
          strcpy(vetitle, title);
          while (more_result = more(fname, YEA)) {
             if (more_result == 1) {
                if (--me.now < 0) {
                   me.now = me.num - 1;
                   break;
                }
             }
             else if (more_result == 3) {
                if (++me.now >= me.num) {
                   me.now = 0;
                   break;
                }
             }
             else
                break;
             node = me.item[me.now];
             if (node->title[1] != (char) 0xbc)
                break;
             go_proxy(fname, node, update);
             strcpy(vetitle, title);
          }
        }
        else if (mode == (char) 0xbd)
        {
          gem(title, node, update);
        }
        me.page = 9999;
      }
      break;
    }
  }
  for (ch = 0; ch < me.num; ch++)
    free(me.item[ch]);
}

/*-------------------------------------------------------*/


valid_dirname(char* fname)
{
   int l = strlen(fname);

   if (!strchr("MDSGH", *fname))
      return 0;
   if (fname[1] != '.')
      return 0;
   if (fname[l - 2] != '.')
      return 0;
   if (fname[l - 1] != 'A')
      return 0;
   return 1;
}


copy_stamp(char* fpath, char* fname)
{
   time_t dtime;
   char *ip = fpath + strlen(fpath) + 3;
   struct stat st;

   if (!valid_dirname(fname + 1)) {
      fileheader fhdr;

      stampfile(fpath, &fhdr);
      return;
   }
   dtime = atoi(fname + 3);
   strcat(fpath, fname);
   do {
      sprintf(ip, "%d.A", dtime++);
   } while (!stat(fpath, &st));
}


static void
a_timestamp(buf, time)
  char *buf;
  time_t *time;
{
  struct tm *pt = localtime(time);
  sprintf(buf, "%02d/%02d/%04d", pt->tm_mon + 1, pt->tm_mday, pt->tm_year + 1900);
}


static void
a_additem(pm, myheader)
  MENU *pm;
  fileheader *myheader;
{
  char buf[MAXPATHLEN];

  setadir(buf, pm->path);
  if (append_record(buf, myheader, FHSZ) == -1)
    return;
  pm->now = pm->num++;
}


static void
a_loadname(pm)
  MENU *pm;
{
  char buf[MAXPATHLEN];
  int len;

  setadir(buf, pm->path);
  len = get_records(buf, pm->header, FHSZ, pm->page+1, p_lines);
  if (len < p_lines)
    bzero(&pm->header[len], FHSZ*(p_lines-len));
}


static void
a_showmenu(pm)
  MENU *pm;
{
  char *title, *editor;
  int n;
  fileheader *item;
  char buf[MAXPATHLEN];
  time_t dtime;

  showtitle("ºëµØ¤å³¹", pm->mtitle);
  prints("   [1;36m½s¸¹    ¼Ð      ÃD%56s[0m", "½s    ¿ï      ¤é    ´Á");

  if (pm->num)
  {
    setadir(buf, pm->path);
    a_loadname(pm);
    for (n = 0; n < p_lines && pm->page + n < pm->num; n++) {
      item = &pm->header[n];
      title = item->title;
      editor = item->owner;
      dtime = atoi(&item->filename[2]);
      a_timestamp(buf, &dtime);
      prints("\n%6d. %-47.46s%-13s[%s]", pm->page+n+1, mono(title), editor, buf);
    }
  }
  else
  {
    outs("\n  ¡mºëµØ°Ï¡n©|¦b§l¨ú¤Ñ¦a¶¡ªº¤é¤ëºëµØ¤¤... :)");
  }

  move(b_lines, 1);
  outs(pm->level ?
    "[34;46m ¡iªO  ¥D¡j [31;47m  (h)[30m»¡©ú  [31m(q/¡ö)[30mÂ÷¶}  [31m(n)[30m·s¼W¤å³¹  [31m(g)[30m·s¼W¥Ø¿ý  [31m(e)[30m½s¿èÀÉ®×  [0m" :
    "[34;46m ¡i¥\\¯àÁä¡j [31;47m  (h)[30m»¡©ú  [31m(q/¡ö)[30mÂ÷¶}  [31m(k¡ôj¡õ)[30m²¾°Ê´å¼Ð  [31m(enter/¡÷)[30mÅª¨ú¸ê®Æ  [0m");
}


static void
a_showhelp(level)
int level;
{
  clear();
  outs("[36m¡i " BOARDNAME "¤½§GÄæ¨Ï¥Î»¡©ú ¡j[m\n\n\
[¡ö][q]         Â÷¶}¨ì¤W¤@¼h¥Ø¿ý\n\
[¡ô][k]         ¤W¤@­Ó¿ï¶µ\n\
[¡õ][j]         ¤U¤@­Ó¿ï¶µ\n\
[¡÷][r][enter]  ¶i¤J¥Ø¿ý¡þÅª¨ú¤å³¹\n\
[b][PgUp]       ¤W­¶¿ï³æ\n\
[^F][PgDn][Spc] ¤U­¶¿ï³æ\n\
[##]            ²¾¨ì¸Ó¿ï¶µ\n\
[F][U]          ±N¤å³¹±H¦^ Internet ¶l½c/±N¤å³¹ uuencode «á±H¦^¶l½c\n\
[^S]            ±N¤å³¹¦s¨ì«H½c\n");

  if (level >= MANAGER)
  {
    outs("\n[36m¡i ªO¥D±M¥ÎÁä ¡j[m\n\
[n/g/G]         ·s¼W¤å³¹/¶}ÅP¥Ø¿ý/«Ø¥ß³s½u\n\
[t/e]           ­×§ï¤å³¹¼ÐÃD/¤º®e\n\
[m/d/p/a]       ²¾°Ê/§R°£/Öß¶K/ªþ¥[¤å³¹\n\
[P]             °O¿ý¥Ø«e¦ì¸m¥H¨ÑC/^C¥Î(¥imulti-login¥æ¤¬°t¦X)\n\
[c/C/^C]        «þ¨©¤å³¹/¨Ã¸õ¦Ü¤W¦¸¶K¤å³¹ªº¦a¤è/ª½±µ¶K¨ì¤W¦¸¶Kªº¦a¤è\n");
  }

  if (level >= SYSOP)
  {
    outs("\n[36m¡i ¯¸ªø±M¥ÎÁä ¡j[m\n\
[f/o/l]         ½s¿è¼ÐÃD²Å¸¹/§ï½s¿ï/«Øsymbolic link\n\
[B]             ¤Á´«¦Ü¬Ýª©¼Ò¦¡\n\
[N]             ¬d¸ßÀÉ¦W\n");
  }
  pressanykey();
}


static void
a_moveitem(pm)
  MENU *pm;
{
  fileheader *tmp;
  char newnum[4];
  int num, max, min;
  char buf[MAXPATHLEN];
  int fail;

  sprintf(buf, "½Ð¿é¤J²Ä %d ¿ï¶µªº·s¦¸§Ç¡G", pm->now + 1);
  if (!getdata(b_lines - 1, 1, buf, newnum, 6, DOECHO, 0))
    return;
  num = (newnum[0] == '$') ? 9999 : atoi(newnum) - 1;
  if (num >= pm->num)
    num = pm->num - 1;
  else if (num < 0)
    num = 0;
  setadir(buf, pm->path);
  min = num < pm->now ? num : pm->now;
  max = num > pm->now ? num : pm->now;
  tmp = (fileheader *) calloc(max + 1, FHSZ);

  fail = 0;
  if (get_records(buf, tmp, FHSZ, 1, min) != min)
    fail = 1;
  if (num > pm->now) {
    if (get_records(buf, &tmp[min], FHSZ, pm->now+2, max-min) != max-min)
      fail = 1;
    if (get_records(buf, &tmp[max], FHSZ, pm->now+1, 1) != 1)
      fail = 1;
  } else {
    if (get_records(buf, &tmp[min], FHSZ, pm->now+1, 1) != 1)
      fail = 1;
    if (get_records(buf, &tmp[min+1], FHSZ, num+1, max-min) != max-min)
      fail = 1;
  }
  if (!fail)
    substitute_record(buf, tmp, FHSZ * (max + 1), 1);
  pm->now = num;
  free(tmp);
}


static void
/* 2003/08/30 by Terry */
a_delete(pm, ch)
  MENU *pm;
  int ch;
/*		       */
{
  char fpath[MAXPATHLEN], buf[MAXPATHLEN];
  char fname[STRLEN];
  char ans[4];

  strcpy(fname, pm->header[pm->now - pm->page].filename);
  sprintf(fpath, "%s/%s", pm->path, fname);
  setadir(buf, pm->path);

  if (*fname == 'H') {
    getdata(b_lines - 1, 1, "±z½T©w­n§R°£¦¹ Gopher link ¶Ü(Y/N)¡H[N] ", ans, 3, LCECHO, 0);
    if (ans[0] != 'y')
      return;
    if (delete_record(buf, FHSZ, pm->now + 1) == -1)
      return;
    unlink(fpath);
  }
  else if (dashl(fpath))
  {
    getdata(b_lines - 1, 1, "±z½T©w­n§R°£¦¹ symbolic link ¶Ü(Y/N)¡H[N] ", ans, 3, LCECHO, 0);
    if (ans[0] != 'y')
      return;
    if (delete_record(buf, FHSZ, pm->now + 1) == -1)
      return;
    unlink(fpath);
  }
  else if (dashf(fpath))
  {
    getdata(b_lines - 1, 1, "±z½T©w­n§R°£¦¹ÀÉ®×¶Ü(Y/N)¡H[N] ", ans, 3, LCECHO, 0);
    if (ans[0] != 'y')
      return;
    if (delete_record(buf, FHSZ, pm->now + 1) == -1)
      return;
    unlink(fpath);
  }
  else if (dashd(fpath))
  {
    getdata(b_lines - 1, 1, "±z½T©w­n§R°£¾ã­Ó¥Ø¿ý¶Ü(Y/N)¡H[N] ", ans, 3, LCECHO, 0);
    if (ans[0] != 'y')
      return;
      
/* 2003/08/30 by Terry */
    if (ch == 'D')
    {
      ans[0] == '\0';
      getdata(b_lines - 1, 1, "½Ð±z¦A¦¸½T©w¬O§_­n§R°£¾ã­ÓºëµØ°Ï(Y/N)¡H[N] ", ans, 3, LCECHO, 0);
      
      if (ans[0] != 'y')
        return;
    }
 /*		       */
 
    if (delete_record(buf, FHSZ, pm->now + 1) == -1)
      return;
    sprintf(buf, "/bin/rm -rf %s", fpath);
    system(buf);
  }
  else
     delete_record(buf, FHSZ, pm->now + 1);

  pm->num--;
}


load_paste()
{
   struct stat st;
   FILE* fp;

   if (!*paste_fname)
      setuserfile(paste_fname, "paste_path");
   if (stat(paste_fname, &st) == 0 && st.st_mtime > paste_time
       && (fp = fopen(paste_fname, "r"))) {
      int i;

      fgets(paste_path, MAXPATHLEN, fp);
      i = strlen(paste_path) - 1;
      if (paste_path[i] == '\n')
         paste_path[i] = 0;
      fgets(paste_title, STRLEN, fp);
      i = strlen(paste_title) - 1;
      if (paste_title[i] == '\n')
         paste_title[i] = 0;
      fscanf(fp, "%d", &paste_level);
      paste_time = st.st_mtime;
      fclose(fp);
   }
}

static void
a_pasteitem(pm)
  MENU *pm;
{
  char newpath[MAXPATHLEN];
  char buf[MAXPATHLEN * 2];
  char ans[2];
  int i;
  fileheader item;

  move(b_lines - 1, 1);
  if (copyfile[0])
  {
    if (dashd(copyfile))
    {
      for (i = 0; copyfile[i] && copyfile[i] == pm->path[i]; i++);
      if (!copyfile[i])
      {
        /* Tzu */
        mh_pressanykey("±N¥Ø¿ý«þ¶i¦Û¤vªº¤l¥Ø¿ý¤¤¡A·|³y¦¨µL½a°j°é¡I");
        /*outs("±N¥Ø¿ý«þ¶i¦Û¤vªº¤l¥Ø¿ý¤¤¡A·|³y¦¨µL½a°j°é¡I");
        igetch();*/
        return;
      }
    }

    sprintf(buf, "½T©w­n«þ¨©[%.40s]¶Ü(Y/N)¡H[N] ", copytitle);
    getdata(b_lines - 1, 1, buf, ans, 3, LCECHO, 0);
    if (ans[0] == 'y')
    {
      char* fname = strrchr(copyfile, '/');

      strcpy(paste_path, pm->path);
      strcpy(paste_title, pm->mtitle);
      paste_level = pm->level;
      paste_time = time(0);

      strcpy(newpath, pm->path);
      copy_stamp(newpath, fname);

      if (access(pm->path, X_OK | R_OK | W_OK))
         mkdir(pm->path, 0755);

      memset(&item, 0, sizeof(fileheader));
      strcpy(item.filename, strrchr(newpath, '/') + 1);

      if (HAS_PERM(PERM_SYSOP) && dashl(copyfile)) {
        int len;
        char buffer[201];

        len = readlink(copyfile, buffer, sizeof(buffer) - 1);
        if (len < 0) {
           /* Tzu */
           mh_pressanykey("µLªk«þ¨©¡I(readlink)");
           /*outs("µLªk«þ¨©¡I(readlink)");
           igetch();*/
           return;
        }
        buffer[len] = 0;
        sprintf(buf, "/bin/ln -s %s %s", buffer, newpath);
      }
      else if (dashf(copyfile))
      {
        if (currutmp->pager < 2 && *item.filename != 'H')
           memcpy(copytitle, "¡º", 2);
        sprintf(buf, "/bin/cp %s %s", copyfile, newpath);
      }
      else if (dashd(copyfile))
      {
        mkdir(newpath, 0755);
        if (currutmp->pager < 2)
           memcpy(copytitle, "¡»", 2);
        sprintf(buf, "/bin/cp -r %s/* %s/.D* %s", copyfile, copyfile, newpath);
      }
      else
      {
        /* Tzu */
        mh_pressanykey("µLªk«þ¨©¡I");
        /*outs("µLªk«þ¨©¡I");
        igetch();*/
        return;
      }
      strcpy(item.owner, *copyowner ? copyowner : cuser.userid);
      strcpy(item.title, copytitle);
      system(buf);
      a_additem(pm, &item);
      copyfile[0] = '\0';
    }
  }
  else
  {
    /* Tzu */
    mh_pressanykey("½Ð¥ý°õ¦æ copy ©R¥O«á¦A paste");
    /*outs("½Ð¥ý°õ¦æ copy ©R¥O«á¦A paste");
    igetch();*/
  }
}


static void
a_appenditem(pm)
  MENU *pm;
{
  char newpath[MAXPATHLEN];
  char fname[MAXPATHLEN];
  char buf[ANSILINELEN];
  char ans[2];
  int i;
  fileheader item;
  FILE *fp, *fin;

  move(b_lines - 1, 1);
  if (copyfile[0])
  {
    if (dashf(copyfile))
    {
      sprintf(fname, "%s/%s", pm->path, pm->header[pm->now-pm->page].filename);
      if (dashf(fname))
      {
        sprintf(buf, "½T©w­n±N[%s]ªþ¥[©ó¦¹¶Ü(Y/N)¡H[N] ", copytitle);
        getdata(b_lines - 2, 1, buf, ans, 3, LCECHO, 0);
        if (ans[0] == 'y')
        {
          if (fp = fopen(fname, "a+"))
          {
            if (fin = fopen(copyfile, "r"))
            {
              memset(buf, '-', 74);
              buf[74] = '\0';
              fprintf(fp, "\n> %s <\n\n", buf);
              getdata(b_lines - 1, 1, "¬O§_¦¬¿ýÃ±¦WÀÉ³¡¥÷(Y/N)¡H[Y] ", ans, 3, LCECHO, 0);
              while (fgets(buf, sizeof(buf), fin))
              {
                if ((ans[0] == 'n' || ans[0] == 'N') &&
                    (!strcmp(buf, "--\n") || !strcmp(buf, "-- \n")))
                  break;
                fputs(buf, fp);
              }
              fclose(fin);
              copyfile[0] = '\0';
            }
            fclose(fp);
          }
        }
      }

      else {
        /* Tzu */
        mh_pressanykey("ÀÉ®×¤£±oªþ¥[©ó¦¹¡I");
        /*outs("ÀÉ®×¤£±oªþ¥[©ó¦¹¡I");
        igetch();*/
      }
    }

    else
    {
      /* Tzu */
      mh_pressanykey("¤£±oªþ¥[¾ã­Ó¥Ø¿ý©óÀÉ®×«á¡I");
      /*outs("¤£±oªþ¥[¾ã­Ó¥Ø¿ý©óÀÉ®×«á¡I");
      igetch();*/
    }
  }
  else
  {
    /* Tzu */
    mh_pressanykey("½Ð¥ý°õ¦æ copy ©R¥O«á¦A append");
    /*outs("½Ð¥ý°õ¦æ copy ©R¥O«á¦A append");
    igetch();*/
  }
}


static void
a_forward(path, pitem, mode)
  char *path;
  fileheader *pitem;
  int mode;
{
  fileheader fhdr;

  strcpy(fhdr.filename, pitem->filename);
  strcpy(fhdr.title, pitem->title);
  switch (doforward(path, &fhdr, mode))
  {
  case 0:
    outmsg(msg_fwd_ok);
    break;
  case -1:
    outmsg(msg_fwd_err1);
    break;
  case -2:
    outmsg(msg_fwd_err2);
    break;
  }
}


/*
woju, mgtsai
*/
static int
a_searchtitle(pm, rev)
  MENU *pm;
  int rev;
{
   char buf[100];
   static char search_str[30];
   int pos;

   sprintf(buf, "%c[%s] ", rev ? '?' : '/', search_str);
   if (getdata(b_lines - 1, 1, buf, buf, 40, DOECHO, 0))
      strcpy(search_str, buf);

   if (!*search_str)
      return pm->now;

   str_lower(buf, search_str);

   rev = rev ? -1 : 1;
   pos = pm->now;
   do {
      pos += rev;
      if (pos == pm->num)
         pos = 0;
      else if (pos < 0)
         pos = pm->num - 1;
      if (pos < pm->page || pos >= pm->page + p_lines) {
         pm->page = pos - pos % p_lines;
         a_loadname(pm);
      }
      if (strstr_lower(pm->header[pos - pm->page].title, buf)
          || strstr_lower(pm->header[pos - pm->page].owner, buf))
         return pos;
   } while (pos != pm->now);
   return pm->now;
}


/* ===== Added by mgtsai, Sep 10th, '96 ===== */

static void
a_newtitle(pm)
  MENU *pm;
{
  char buf[MAXPATHLEN];
  fileheader item;

  memcpy(&item, &pm->header[pm->now - pm->page], FHSZ);
  if (getdata(b_lines - 1, 1, "·s¼ÐÃD¡G", buf, 60, DOECHO, item.title + 3))
  {
    strcpy(item.title + 3, buf);
    setadir(buf, pm->path);
    substitute_record(buf, &item, FHSZ, pm->now + 1);
  }
}

/* Tzu ¥H«á­n¥Î¦A¥´¶} ^_^*/
/*static void
a_newowner(pm)
  MENU *pm;
{
  char buf[MAXPATHLEN];
  fileheader item;
      
  memcpy(&item, &pm->header[pm->now - pm->page], FHSZ);
  if (getdata(b_lines - 1, 1, "½s¿ï¡G", buf, 15, DOECHO, item.owner))
  {
    strcpy(item.owner, buf);
    setadir(buf, pm->path);
    substitute_record(buf, &item, FHSZ, pm->now + 1);
  }
}*/

static void
a_editsign(pm)
  MENU *pm;
{
  char buf[MAXPATHLEN];
  fileheader item;

  memcpy(&item, &pm->header[pm->now - pm->page], FHSZ);
  strncpy(buf, item.title, 3);
  buf[3] = 0;
  trim(buf);
  if (getdata(b_lines - 1, 1, "²Å¸¹¡G", buf, 5, DOECHO, buf))
  {
    item.title[0] = buf[0] ? buf[0] : ' ';
    item.title[1] = buf[1] ? buf[1] : ' ';
    item.title[2] = buf[2] ? buf[2] : ' ';
    setadir(buf, pm->path);
    substitute_record(buf, &item, FHSZ, pm->now + 1);
  }
}


static void
a_showname(pm)
  MENU *pm;
{
  char buf[MAXPATHLEN];
  int len;
  int i;
  int sym;

  move(b_lines - 1, 1);
  sprintf(buf, "%s/%s", pm->path, pm->header[pm->now - pm->page].filename);
  if (dashl(buf)) {
    prints("¦¹ symbolic link ¦WºÙ¬° %s\n", pm->header[pm->now - pm->page].filename);
    if ((len = readlink(buf, buf, MAXPATHLEN-1)) >= 0) {
      buf[len] = '\0';
      for (i = 0; BBSHOME[i] && buf[i] == BBSHOME[i]; i++);
      if (!BBSHOME[i] && buf[i] == '/') {
        if (belong("etc/bbsadms", cuser.userid))
          sym = 1;
        else {
          sym = 0;
          for (i++; BBSHOME "/man"[i] && buf[i] == BBSHOME "/man"[i]; i++);
          if (!BBSHOME "/man"[i] && buf[i] == '/')
            sym = 1;
        }
        if (sym) {
          pressanykey();
          move(b_lines - 1, 1);
          prints("¦¹ symbolic link «ü¦V %s\n", &buf[i+1]);
        }
      }
    }
  } else if (dashf(buf))
    prints("¦¹¤å³¹¦WºÙ¬° %s",
       belong("etc/bbsadms", cuser.userid) ? buf : pm->header[pm->now - pm->page].filename);
  else if (dashd(buf))
    prints("¦¹¥Ø¿ý¦WºÙ¬° %s",
       belong("etc/bbsadms", cuser.userid) ? buf : pm->header[pm->now - pm->page].filename);
  else
    outs("¦¹¶µ¥Ø¤w·l·´, «ØÄ³±N¨ä§R°£¡I");
  pressanykey();
}


static void
a_newitem(pm, mode)
  MENU *pm;
{
  static char *mesg[4] = {
    "[·s¼W¤å³¹] ½Ð¿é¤J¼ÐÃD¡G",      /* ADDITEM */
    "[·s¼W¥Ø¿ý] ½Ð¿é¤J¼ÐÃD¡G",      /* ADDGROUP */
    "[·s¼W³s½u] ½Ð¿é¤J¼ÐÃD¡G",      /* ADDGOPHER */
    "½Ð¿é¤J¼ÐÃD¡G"};                /* ADDLINK */

  char fpath[MAXPATHLEN], buf[MAXPATHLEN], lpath[MAXPATHLEN];
  fileheader item;
  time_t dtime;
  int s, d;

  strcpy(fpath, pm->path);

  switch (mode)
  {
  case ADDITEM:
    stampfile(fpath, &item);
    strcpy(item.title, "¡º ");  /* A1BA */
    break;

  case ADDGROUP:
    stampdir(fpath, &item);
    strcpy(item.title, "¡» ");  /* A1BB */
    break;

  case ADDGOPHER:
    stampfile(fpath, &item);
    {
       char* s;

       if (s = strrchr(fpath, '/')) {
          unlink(fpath);
          s[1] = 'H';
          *item.filename = 'H';
       }
       else {
          /* Tzu */
          mh_pressanykey("¥Øªº¦a¸ô®|¤£¦Xªk¡I");
          /*outs("¥Øªº¦a¸ô®|¤£¦Xªk¡I");
          igetch();*/
          return;
       }
    }
    strcpy(item.title, "¡¸ ");  /* A1BB */
    break;

  case ADDLINK:
    stamplink(fpath, &item);
    if (!getdata(b_lines - 2, 1, "¥Øªº¦a¸ô®|¡G", buf, 61, DOECHO, 0))
      return;
    if (invalid_pname(buf)) {
      unlink(fpath);
      /* Tzu */
      mh_pressanykey("¥Øªº¦a¸ô®|¤£¦Xªk¡I");
      /*outs("¥Øªº¦a¸ô®|¤£¦Xªk¡I");
      igetch();*/
      return;
    }
    sprintf(lpath, "%s%s%s",
      BBSHOME, belong("etc/bbsadms", cuser.userid) ? "/" : "/man/" , buf);
    if (dashf(lpath))
      strcpy(item.title, "¡³ ");        /* A1B3 */
    else if (dashd(lpath))
      strcpy(item.title, "¡´ ");        /* A1B4 */
    else
    {
      unlink(fpath);
      /* Tzu */
      mh_pressanykey("¥Øªº¦a¸ô®|¤£¦Xªk¡I");
      /*outs("¥Øªº¦a¸ô®|¤£¦Xªk¡I");
      igetch();*/
      return;
    }
  }

  if (!getdata(b_lines - 1, 1, mesg[mode], &item.title[3], 55, DOECHO, 0))
  {
    if (mode == ADDGROUP)
      rmdir(fpath);
    else
      unlink(fpath);
    return;
  }

  switch (mode)
  {
  case ADDITEM:
  case ADDGOPHER:
    buf[0] = '\0';
    if (vedit(buf, 0) == -1) {
      unlink(buf);
      pressanykey();
      return;
    }
    Rename(buf, fpath);
    break;

  case ADDLINK:
    unlink(fpath);
    if (symlink(lpath, fpath) == -1) {
      /* Tzu */
      mh_pressanykey("µLªk«Ø¥ß symbolic link");
      /*outs("µLªk«Ø¥ß symbolic link");
      igetch();*/
      return;
    }
    break;
  }
  strcpy(item.owner, cuser.userid);
  a_additem(pm, &item);
}


a_copyitem(char* fpath, char* title, char* owner)
{
   strcpy(copyfile, fpath);
   strcpy(copytitle, title);
   if (owner)
      strcpy(copyowner, owner);
   else
      *copyowner = 0;
   /* Tzu */
   mh_pressanykey("ÀÉ®×¼Ð°O§¹¦¨¡C[ª`·N] «þ¨©«á¤~¯à§R°£­ì¤å!");
   /*outmsg("ÀÉ®×¼Ð°O§¹¦¨¡C[ª`·N] «þ¨©«á¤~¯à§R°£­ì¤å!");
   igetch(); */
}

/* ===== end ===== */



void
atitle()
{
  showtitle("ºëµØ¤å³¹", a_title);
  outs("\
[¡ö]Â÷¶} [¡÷]¾\\Åª [^P]µoªí¤å³¹ [b]³Æ§Ñ¿ý [d]§R°£ [q]ºëµØ°Ï [TAB]¤åºK [h]elp\n\
[7m  ½s¸¹   ¤é ´Á  §@  ªÌ       ¤å  ³¹  ¼Ð  ÃD                                   [0m");
}


void
adoent(num, ent)
  int num;
  fileheader *ent;
{
  char *mark, *title, color;
  int type;
  time_t dtime;
  char buf[20];

  if (ent->filemode & FILE_TAGED)
     type = 'D';
  else
     type = ' ';

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

  dtime = atoi(&ent->filename[2]);
  a_timestamp(buf, &dtime);
  buf[5] = 0;
  if (strncmp(currtitle, title, 40))
    prints("%6d %c %-7s%-13.12s%s %s\n", num, type,
      buf, ent->owner, mark, title);
  else
    prints("%6d %c %-7s%-13.12s[1;3%cm%s %s[0m\n", num, type,
      buf, ent->owner, color, mark, title);
}



a_menu(char* maintitle, char* path, int lastlevel)
{
  MENU me;
  char fname[MAXPATHLEN];
  int ch;
  int mode0 = currutmp->mode;
  int stat0 = currstat;
  extern struct one_key read_comms[];
  void *(*readdoent) ();

  setutmpmode(ANNOUNCE);
  me.header = (fileheader *) calloc(p_lines, FHSZ);
  me.path = path;
  strcpy(me.mtitle, maintitle);
  setadir(fname, me.path);
  me.num = get_num_records(fname, FHSZ);

  /* ºëµØ°Ï-tree ¤¤³¡¥÷µ²ºcÄÝ©ó cuser ==> BM */

  if (!(me.level = lastlevel))
  {
    char *ptr;

    if (ptr = strrchr(me.mtitle, '['))
      me.level = is_BM(ptr + 1);
  }

  me.page = 9999;
  me.now = 0;
  for (;;)
  {
    if (me.now >= me.num)
      me.now = me.num - 1;
    if (me.now < 0)
      me.now = 0;


    if (me.page == 10000) {
       me.page = me.now - (me.now % p_lines);
       if (me.num) {
          a_loadname(&me);
          ch = '\n';
       }
    }
    else {
       if (me.now < me.page || me.now >= me.page + p_lines)
       {
   /*
         me.page = me.now - ((me.page == 10000 && me.now > p_lines / 2) ?
            (p_lines / 2) : (me.now % p_lines));
   */
         me.page = me.now - (me.now % p_lines);
         a_showmenu(&me);
       }
       ch = cursor_key(2 + me.now - me.page, 0);
    }

    if (ch == 'q' || ch == 'Q' || ch == KEY_LEFT)
      break;

    if (ch >= '1' && ch <= '9')
    {
      if ((ch = search_num(ch, me.num)) != -1)
        me.now = ch;
      me.page = 10000;
      continue;
    }

    switch (ch)
    {
    case KEY_UP:
    case 'k':
      if (--me.now < 0)
        me.now = me.num - 1;
      break;

    case KEY_DOWN:
    case 'j':
      if (++me.now >= me.num)
        me.now = 0;
      break;

    case KEY_PGUP:
    case 'b':
      if (me.now >= p_lines)
        me.now -= p_lines;
      else if (me.now > 0)
        me.now = 0;
      else
        me.now = me.num - 1;
      break;

    case ' ':
    case KEY_PGDN:
    case Ctrl('F'):
      if (me.now < me.num - p_lines)
        me.now += p_lines;
      else if (me.now < me.num - 1)
        me.now = me.num - 1;
      else
        me.now = 0;
      break;

    case '0':
       me.now = 0;
       break;
    case '?':
    case '/':
       me.now = a_searchtitle(&me, ch == '?');
       me.page = 9999;
       break;
    case '$':
       me.now = me.num -1;
       break;
    case 'h':
      a_showhelp(me.level);
      me.page = 9999;
      break;
/* MH */
   case Ctrl('R'):
       mh_throw_water_ball();
       me.page = 9999;
       break;
/*    */

   case KEY_ESC: if (KEY_ESC_arg == 'n') {
      edit_note();
      me.page = 9999;
      }
      break;

   case Ctrl('U'):
      t_users();
      me.page = 9999;
      break;

   case Ctrl('B'):
      m_read();
      me.page = 9999;
      break;

   case Ctrl('I'):
      t_idle();
      me.page = 9999;
      break;

    case 's':
       AnnounceSelect();
       me.page = 9999;
       break;

    case 'e':
    case 'E':
       sprintf(fname, "%s/%s", path, me.header[me.now-me.page].filename);
       if (dashf(fname))
       {
          *quote_file = 0;
          if (vedit(fname, (me.level >= MANAGER) ? 0 : 2) != -1) {
             char fpath[MAXPATHLEN];
             fileheader fhdr;

             strcpy(fpath, path);
             stampfile(fpath, &fhdr);
             unlink(fpath);
             if (strrchr(fname, '/')[1] == 'H')
                *fhdr.filename = strrchr(fpath, '/')[1] = 'H';
             Rename(fname, fpath);
             strcpy(me.header[me.now-me.page].filename, fhdr.filename);
             strcpy(me.header[me.now-me.page].owner, cuser.userid);
             setadir(fpath, path);
             substitute_record(fpath, me.header+me.now-me.page, sizeof(fhdr), me.now  + 1);
          }
          me.page = 9999;
       }
       break;

    case 'P':
       if (HAS_PERM(PERM_LOGINOK)) {
          FILE* fp;

          strcpy(paste_path, me.path);
          strcpy(paste_title, me.mtitle);
          paste_level = me.level;
          if (!*paste_fname)
             setuserfile(paste_fname, "paste_path");
          if (fp = fopen(paste_fname, "w")) {
             fprintf(fp, "%.*s\n%.*s\n%d\n",
                MAXPATHLEN  - 1, paste_path,
                STRLEN - 1, paste_title,
                paste_level);
             fclose(fp);
          }
       }
       else
          bell();
       break;

    case 'c':
    case 'C':
    case Ctrl('C'):
      if (me.now < me.num) {
        fileheader* fhdr = me.header + me.now - me.page;

        load_paste();
        sprintf(fname, "%s/%s", path, fhdr->filename);
        if (ch == Ctrl('C') && *paste_path && paste_level && dashf(fname)) {
            char newpath[MAXPATHLEN];
            fileheader item;

            strcpy(newpath, paste_path);
            stampfile(newpath, &item);
            unlink(newpath);
            Link(fname, newpath);
            strcpy(item.owner, fhdr->owner);
            strcpy(item.title, fhdr->title + ((currutmp->pager > 1) ? 3 : 0));
            strcpy(strrchr(newpath, '/') + 1, ".DIR");
            append_record(newpath, &item, FHSZ);
            if (++me.now >= me.num)
              me.now = 0;
            break;
        }
        a_copyitem(fname, fhdr->title + ((currutmp->pager > 1) ? 3 : 0), fhdr->owner);
        if (ch == 'C' && *paste_path)
           a_menu(paste_title, paste_path, paste_level);
        me.page = 9999;
      }
      break;

    case Ctrl('S'):
      if (me.now < me.num) {
        fileheader* fhdr = me.header + me.now - me.page;
        sprintf(fname, "%s/%s", path, fhdr->filename);
        if (save_mail(0, fhdr, fname) == POS_NEXT)
           if (++me.now >= me.num)
             me.now = 0;
      }
      break;
    case '\n':
    case '\r':
    case KEY_RIGHT:
    case 'r':
    case 'R':
      if (me.now < me.num) {
        fileheader *fhdr = &me.header[me.now-me.page];

        sprintf(fname, "%s/%s", path, fhdr->filename);
        if (*fhdr->filename == 'H' && fhdr->filename[1] == '.') {
          ITEM item;
          char buf[200];
          char* s;
          int port;
          FILE* fp;

          if (fp = fopen(fname, "r")) {
             fgets(buf, 200, fp);
             fclose(fp);
          }
          else
             *buf = 0;
          s = strtok(buf, ": \n\r");
          if (!s)
             s = "localhost";
          strcpy(item.X.G.server, s);
          strcpy(buf, "1/");
          item.X.G.port = 70;
          if (s = strtok(0, " \n\r:")) {
             strcat(buf, *s == '/' ? s + 1 : s);
             if ((s = strtok(0, " :/\n\r")) && (port = atoi(s)))
                item.X.G.port = port;
          }
          strcpy(item.X.G.path, buf);
          gem(fhdr->title, &item, (ch == 'R') ? 1 : 0);
        }
        else if (dashf(fname)) {
          int more_result;

          strcpy(vetitle, me.header[me.now-me.page].title + 3);
          while (more_result = more(fname, YEA)) {
             if (more_result == 1) {
                if (--me.now < 0) {
                   me.now = me.num - 1;
                   break;
                }
             }
             else if (more_result == 3) {
                if (++me.now >= me.num) {
                   me.now = 0;
                   break;
                }
             }
             else if (more_result == 7 || more_result == 8) {
                int mode0 = currutmp->mode;
                int stat0 = currstat;

                mail_reply(me.now, me.header + me.now - me.page, path);
                currutmp->mode = mode0;
                currstat = stat0;
                me.page = 9999;
                break;
             }
             else
                break;
             if (me.now < me.page || me.now >= me.page + p_lines)
                break;
             sprintf(fname, "%s/%s", path, me.header[me.now-me.page].filename);
             strcpy(vetitle, me.header[me.now-me.page].title + 3);
             if (!dashf(fname))
                break;
          }
        }
        else if (dashd(fname))
          a_menu(me.header[me.now-me.page].title, fname, me.level);
        me.page = 9999;
      }
      break;

    case 'F':
    case 'U':
    case 'Z':
      sprintf(fname, "%s/%s", path, me.header[me.now-me.page].filename);
/*
woju
      if (me.now < me.num && HAS_PERM(PERM_BASIC) && dashf(fname))
*/
      if (me.now < me.num && HAS_PERM(PERM_FORWARD) && dashf(fname)) /* MH */
      {
        if (ch == 'Z')
          z_download(fname);
        else
          a_forward(path, &me.header[me.now-me.page], ch);
      }
      else
        outmsg("µLªkÂà±H¦¹¶µ¥Ø");

      me.page = 9999;
      refresh();
      sleep(1);
      break;
    }

    if (me.level >= MANAGER)
    {
      int page0 = me.page;

      switch (ch)
      {
      case 'n':
        a_newitem(&me, ADDITEM);
        me.page = 9999;
        break;
      case 'g':
        a_newitem(&me, ADDGROUP);
        me.page = 9999;
        break;
      case 'G':
        a_newitem(&me, ADDGOPHER);
        me.page = 9999;
        break;
      case 'p':
        a_pasteitem(&me);
        me.page = 9999;
        break;
      case 'a':
        a_appenditem(&me);
        me.page = 9999;
        break;
      default:
        me.page = page0;
        break;
      }

      if (me.num)
        switch (ch)
        {
        case 'm':
          a_moveitem(&me);
          me.page = 9999;
          break;

        case 'D':
          me.page = -1;
        case 'd':
 /* 2003/08/30 by Terry */
 	  a_delete(&me, ch);
 /*		        */
          me.page = 9999;
          break;

        case 't':
          a_newtitle(&me);
          me.page = 9999;
          break;
        }
    }

    if (me.level == SYSOP)
    {
      switch (ch)
      {
      /* Tzu ³Æ¦Ó¤£¥Î*/
      /*case 'o': 
        a_newowner(&me);
        me.page = 9999;
        break;*/
      case 'f':
        a_editsign(&me);
        me.page = 9999;
        break;
      case 'l':
        a_newitem(&me, ADDLINK);
        me.page = 9999;
        break;
      case 'N':
        a_showname(&me);
        me.page = 9999;
        break;
      case 'B':
         setadir(fname, me.path);
         a_title = maintitle;
         i_read(0, fname, atitle, adoent, read_comms);
         me.page = 9999;
         break;
      }
    }
  }

  free(me.header);
  currutmp->mode = mode0;
  currstat = stat0;
}



AnnounceSelect()
{
   static char xboard[20];
   char buf[20];
   char fpath[256];
   boardheader *bp;
   boardheader *getbcache();

   move(2, 0);
   clrtoeol();
   move(3, 0);
   clrtoeol();
   move(1, 0);
   make_blist();
   namecomplete("¿ï¾ÜºëµØ°Ï¬ÝªO¡G", buf);
   if (*buf)
      strcpy(xboard, buf);
   if (*xboard && (bp = getbcache(xboard))) {
      setapath(fpath, xboard);
      a_menu(xboard, fpath, HAS_PERM(PERM_SYSOP) ? 2 : (HAS_PERM(PERM_ALLBOARD) || HAS_PERM(PERM_BM) && is_BM(bp->BM)) ? 1 : 0);
   }
   return FULLUPDATE;
}


int
Announce()
{
  a_menu(mytitle, "man", (HAS_PERM(PERM_SYSOP) ? SYSOP : NOBODY));
  return 0;
}

/* Tzu: ±qchat°Êµüªºhelp ·Q¨ìªººëµØ°Ï¨D§U¨t²Î */
int
AnnounceHelp(name)
    char *name;
{
  char buf[50];
  sprintf(buf, "man/%s", name);
  a_menu(mytitle, buf, (HAS_PERM(PERM_SYSOP) ? SYSOP : NOBODY));
  return FULLUPDATE;
}
/*     */
