/*-------------------------------------------------------*/
/* edit.c       ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : simple ANSI/Chinese editor                   */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"

#define KEEP_EDITING    -2
#define SCR_WIDTH       80
#define BACKUP_LIMIT    100

textline *firstline = NULL;
textline *lastline = NULL;
textline *currline = NULL;
textline *blockline = NULL;
textline *top_of_win = NULL;
textline *deleted_lines = NULL;

extern int local_article;

char line[WRAPMARGIN  + 2];
int currpnt, currln, totaln;
int curr_window_line;
int redraw_everything;
int insert_character;
int my_ansimode;
int raw_mode;
int phone_mode = 0;
int edit_margin;
int blockln  = -1;
int blockpnt;
int prevln = -1;
int prevpnt;
int line_dirty;
int indent_mode;
int insert_c = ' ';

char fp_bak[] = "bak";
char *my_edit_mode[2] =
{"¨ú¥N", "´¡¤J"};

char save_title[STRLEN];


char* trim2(char* buffer)
/*---------------------------------------------------------
Remove(strip) left and right English and Chinese blanks in a line
----------------------------------------------------------*/
{
   int j;

   for (j = 0; buffer[j] == ' ' || strncmp(buffer + j, "¡@", 2) == 0; j++)
      if(strncmp(buffer + j, "¡@", 2) == 0)
         j++;
   memmove(buffer, buffer + j, strlen(buffer + j) + 1);
   for (j = strlen(buffer);
        buffer[j - 1] == ' ' || strncmp(buffer + j - 1, "¡@", 2) == 0; j--)
      if(strncmp(buffer + j - 1, "¡@", 2) == 0)
         j--;
   buffer[j] = 0;
   return buffer;
}



beginsig(char* s)
{
   char buf[10];
   char genbuf[100];

   strncpy(buf, s, 9);
   buf[9] = 0;
   strtok(buf, "\n\r");
   trim2(buf);
   return !strcmp(buf, "--");
}

/* ----------------------------------------------------- */
/* °O¾ÐÅéºÞ²z»P½s¿è³B²z                                  */
/* ----------------------------------------------------- */

static void
indigestion(i)
{
  fprintf(stderr, "ÄY­«¤º¶Ë %d\n", i);
}


/* ----------------------------------------------------- */
/* Thor: ansi ®y¼ÐÂà´«  for color ½s¿è¼Ò¦¡               */
/* ----------------------------------------------------- */


static int
ansi2n(int ansix, textline * line)
{
  register char *data, *tmp;
  register char ch;

  data = tmp = line->data;

  while(*tmp) {
    if (*tmp == KEY_ESC)
    {
      while((ch = *tmp) && !isalpha(ch))
        tmp++;
      if (ch)
        tmp++;
      continue;
    }
    if (ansix <= 0) break;
    tmp++;
    ansix--;
  }
  return tmp - data;
}

static int
n2ansi(int nx, textline * line)
{
  register ansix = 0;
  register char *tmp,*nxp;
  register char ch;

  tmp = nxp = line->data;
  nxp += nx;

  while(*tmp){
    if (*tmp == KEY_ESC)
    {
      while((ch = *tmp) && !isalpha(ch))
        tmp++;
      if (ch)
        tmp++;
      continue;
    }
    if (tmp >= nxp) break;
    tmp++;
    ansix++;
  }
  return ansix;
}


/* ----------------------------------------------------- */
/* ¿Ã¹õ³B²z¡G»²§U°T®§¡BÅã¥Ü½s¿è¤º®e                      */
/* ----------------------------------------------------- */

static void
edit_msg(void)
{
  static char *edit_mode[2] = {"¨ú¥N", "´¡¤J"};
  register int n = currpnt;

  if (my_ansimode)                      /* Thor: §@ ansi ½s¿è */
    n = n2ansi(n, currline);
  n++;
  move(b_lines, 0);
  clrtoeol();
  prints("\033[34;46m  ½s¿è¤å³¹  \033[31;47m  (Ctrl-G)\033[30m ½u¤W»²§U»¡©ú  \033[31m(^X,^Q)\033[30m ÀÉ®×³B²z ùø%s¢x%c%c%c%cùø %3d:%3d  \033[m",
    edit_mode[insert_character],
    my_ansimode ? 'A' : 'a', indent_mode ? 'I' : 'i',
    phone_mode ? 'P' : 'p', raw_mode ? 'R' : 'r',
    currln + 1, n);
}


static textline *
back_line(pos, num)
  register textline *pos;
  int num;
{
  while (num-- > 0)
  {
    register textline *item;

    if (pos && (item = pos->prev))
    {
      pos = item;
      currln--;
    }
  }
  return pos;
}


static textline *
forward_line(pos, num)
  register textline *pos;
  int num;
{
  while (num-- > 0)
  {
    register textline *item;

    if (pos && (item = pos->next))
    {
      pos = item;
      currln++;
    }
  }
  return pos;
}


static int
getlineno()
{
  int cnt = 0;
  textline *p = currline;

  while (p && (p != top_of_win))
  {
    cnt++;
    p = p->prev;
  }
  return cnt;
}


static char *
killsp(s)
  char *s;
{
  while (*s == ' ')
    s++;
  return s;
}


static textline *
alloc_line()
{
  extern void *malloc();
  register textline *p;

  if (p = (textline *) malloc(sizeof(textline)))
  {
    memset(p, 0, sizeof(textline));
    return p;
  }

  indigestion(13);
  abort_bbs();
}


/* ----------------------------------------------------- */
/* append p after line in list. keeps up with last line  */
/* ----------------------------------------------------- */

static void
append(p, line)
  register textline *p, *line;
{
  register textline *n;

  if (p->next = n = line->next)
    n->prev = p;
  else
    lastline = p;
  line->next = p;
  p->prev = line;
}


/* ----------------------------------------------------- */
/* delete_line deletes 'line' from the list,             */
/* and maintains the lastline, and firstline pointers.   */
/* ----------------------------------------------------- */

static void
delete_line(line)
  register textline *line;
{
  register textline *p = line->prev;
  register textline *n = line->next;

  if (!p && !n)
  {
    line->data[0] = line->len = 0;
    return;
  }
  if (n)
    n->prev = p;
  else
    lastline = p;
  if (p)
    p->next = n;
  else
    firstline = n;
  strcat(line->data, "\n");
  line->prev = deleted_lines;
  deleted_lines = line;
  totaln--;
}


int
ask (prompt)
     char *prompt;
{
  int ch;

  move (0, 0);
  clrtoeol ();
  standout ();
  prints ("%s", prompt);
  standend ();
  ch = igetkey ();
  move (0, 0);
  clrtoeol ();
  return (ch);
}


/*
woju
*/

undelete_line()
{
   textline* p = deleted_lines;

   textline* currline0 = currline;
   textline* top_of_win0 = top_of_win;
   int currpnt0 = currpnt;
   int currln0 = currln;
   int curr_window_line0 = curr_window_line;
   int indent_mode0 = indent_mode;

   if (!deleted_lines)
      return 0;

   indent_mode = 0;
   insert_string(deleted_lines->data);
   indent_mode = indent_mode0;
   deleted_lines = deleted_lines->prev;
   free(p);

   currline = currline0;
   top_of_win = top_of_win0;
   currpnt = currpnt0;
   currln = currln0;
   curr_window_line = curr_window_line0;
}


int
indent_spcs()
{
   textline* p;
   int spcs;

   if (!indent_mode)
      return 0;

   for (p = currline; p; p = p->prev) {
      for (spcs = 0; p->data[spcs] == ' '; ++spcs)
         ;
      if (p->data[spcs])
         return spcs;
   }
   return 0;
}

/* ----------------------------------------------------- */
/* split 'line' right before the character pos           */
/* ----------------------------------------------------- */

static void
split(line, pos)
  register textline *line;
  register int pos;
{
  if (pos <= line->len)
  {
    register textline *p = alloc_line();
    register char *ptr;
    int spcs = indent_spcs();

    totaln++;

    p->len = line->len - pos + spcs;
    line->len = pos;

    memset(p->data, ' ', spcs);
    p->data[spcs] = 0;
    strcat(p->data, (ptr = line->data + pos));
    ptr[0] = '\0';
    append(p, line);
    if (line == currline && pos <= currpnt)
    {
      currline = p;
      if (pos == currpnt)
         currpnt = spcs;
      else
         currpnt -= pos;
      curr_window_line++;
      currln++;
    }
    redraw_everything = YEA;
  }
}



/* ----------------------------------------------------- */
/* 1) lines were joined and one was deleted              */
/* 2) lines could not be joined                          */
/* 3) next line is empty                                 */
/* returns false if:                                     */
/* 1) Some of the joined line wrapped                    */
/* ----------------------------------------------------- */

static int
join(line)
  register textline *line;
{
  register textline *n;
  register int ovfl;

  if (!(n = line->next))
    return YEA;
  if (!*killsp(n->data))
    return YEA;

  ovfl = line->len + n->len - WRAPMARGIN;
  if (ovfl < 0)
  {
    strcat(line->data, n->data);
    line->len += n->len;
    delete_line(n);
    return YEA;
  }
  else
  {
    register char *s;

    s = n->data + n->len - ovfl - 1;
    while (s != n->data && *s == ' ')
      s--;
    while (s != n->data && *s != ' ')
      s--;
    if (s == n->data)
      return YEA;
    split(n, (s - n->data) + 1);
    if (line->len + n->len >= WRAPMARGIN)
    {
      indigestion(0);
      return YEA;
    }
    join(line);
    n = line->next;
    ovfl = n->len - 1;
    if (ovfl >= 0 && ovfl < WRAPMARGIN - 2)
    {
      s = &(n->data[ovfl]);
      if (*s != ' ')
      {
        strcpy(s, " ");
        n->len++;
      }
    }
    return NA;
  }
}


static void
insert_char(ch)
  register int ch;
{
  register textline *p = currline;
  register int i = p->len;
  register char *s;
  int wordwrap = YEA;

  if (currpnt > i)
  {
    indigestion(1);
    return;
  }
  if (currpnt < i && !insert_character)
  {
    p->data[currpnt++] = ch;
    if (my_ansimode) /* Thor: ansi ½s¿è, ¥i¥Hoverwrite, ¤£»\¨ì ansi code */
       currpnt = ansi2n(n2ansi(currpnt, p),p);
  }
  else
  {
    while (i >= currpnt)
    {
      p->data[i + 1] = p->data[i];
      i--;
    }
    p->data[currpnt++] = ch;
    i = ++(p->len);
  }
  if (i < WRAPMARGIN)
    return;
  split(p, WRAPMARGIN / 2);
}


insert_string(str)
  char *str;
{
  int ch;

  while (ch = *str++)
  {

#ifdef BIT8
    if (isprint2(ch) || ch == '')
#else
    if (isprint(ch))
#endif

    {
      insert_char(ch);
    }
    else if (ch == '\t')
    {
      do
      {
        insert_char(' ');
      } while (currpnt & 0x7);
    }
    else if (ch == '\n')
      split(currline, currpnt);
  }
}


static void
delete_char()
{
  register int len;

  if (len = currline->len)
  {
    register int i;
    register char *s;

    if (currpnt >= len)
    {
      indigestion(1);
      return;
    }
    for (i = currpnt, s = currline->data + i; i != len; i++, s++)
      s[0] = s[1];
    currline->len--;
  }
}



/* ----------------------------------------------------- */
/* QP code : "0123456789ABCDEF"                          */
/* ----------------------------------------------------- */


static int
qp_code(x)
  register int x;
{
  if (x >= '0' && x <= '9')
    return x - '0';
  if (x >= 'a' && x <= 'f')
    return x - 'a' + 10;
  if (x >= 'A' && x <= 'F')
    return x - 'A' + 10;
  return -1;
}


/* ------------------------------------------------------------------ */
/* BASE64 :                                                           */
/* "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" */
/* ------------------------------------------------------------------ */


static int
base64_code(x)
  register int x;
{
  if (x >= 'A' && x <= 'Z')
    return x - 'A';
  if (x >= 'a' && x <= 'z')
    return x - 'a' + 26;
  if (x >= '0' && x <= '9')
    return x - '0' + 52;
  if (x == '+')
    return 62;
  if (x == '/')
    return 63;
  return -1;
}


/* ----------------------------------------------------- */
/* judge & decode QP / BASE64                            */
/* ----------------------------------------------------- */

char*
str_decode(unsigned char* src)
{
  unsigned char* dst = src;
  char* ans = src;
  register int is_qp, is_base64, is_done;
  register int c1, c2, c3, c4;

  is_qp = is_base64 = 1;
  for (c1 = 0; c1 < 10; c1++)
     if (base64_code(src[c1]) == -1) {
        is_base64 = 0;
        break;
     }
  for (is_done = 0; c1 = *src; src++)
  {
    if (c1 == '?' && src[1] == '=')
      continue;
    else if (c1 == '\n')        /* chuan: multi line encoding */
    {
      if (!is_base64)
         *dst++ = c1;
      is_done = is_qp = is_base64 = 0;
      continue;
    }
    else if (is_qp && c1 == '=')
    {
      c1 = *++src;
      if (!*src)
         break;
      c2 = *++src;
      if (!*src)
         break;
      *dst++ = (qp_code(c1) << 4) | qp_code(c2);
      if (dst[-1] == (unsigned char)-1)
         --dst;
    }
    else if (is_base64 && !is_done)
    {
      while (isspace(c1))
      {
        c1 = *++src;
      }
      if (!c1)
        break;
      do
      {
        c2 = *++src;
      } while (isspace(c2));
      if (!c2)
        break;
      do
      {
        c3 = *++src;
      } while (isspace(c3));
      if (!c3)
        break;
      do
      {
        c4 = *++src;
      } while (isspace(c4));
      if (!c4)
        break;
      if (c1 == '=' || c2 == '=')
      {
        is_done = 1;
        continue;
      }
      c2 = base64_code(c2);
      *dst++ = (base64_code(c1) << 2) | ((c2 & 0x30) >> 4);
      if (c3 == '=')
        is_done = 1;
      else
      {
        c3 = base64_code(c3);
        *dst++ = ((c2 & 0xF) << 4) | ((c3 & 0x3c) >> 2);
        if (c4 == '=')
          is_done = 1;
        else
        {
          *dst++ = ((c3 & 0x03) << 6) | base64_code(c4);
        }
      }
    }
    else if ((c1 == '=') && (src[1] == '?'))
    {
      /* c2 : qmarks, c3 : code_kind */

      c2 = c3 = 0;

      for (;;)
      {
        c1 = *++src;
        if (c1 != '?')
        {
          if (c2 == 2)
            c3 = c1 | 0x20;
        }
        else
        {
          if (++c2 >= 3)
            break;
        }
      }

      if (c3 == 'q')
        is_qp = 1;
      else if (c3 == 'b')
        is_base64 = 1;
    }
    else
      *dst++ = c1;
  }
  if (!is_base64 && dst[-1] == '=')
     dst[-1] = '\n';
  *dst = '\0';
  return ans;
}




static void
load_file(fp)
  FILE *fp;
{
  int indent_mode0 = indent_mode;

  outmsg("¸ü¤JÀÉ®×¤¤...");
  refresh();
  indent_mode = 0;
  while (fgets(line, WRAPMARGIN + 2, fp))
    insert_string(line);
  fclose(fp);
  indent_mode = indent_mode0;
}


/* ----------------------------------------------------- */
/* ¼È¦sÀÉ                                                */
/* ----------------------------------------------------- */

static char *
ask_tmpbuf()
{
  static char fp_buf[10] = "buf.0";
  static char msg[] = "½Ð¿ï¾Ü¼È¦sÀÉ (0-9)[0]: ";

  msg[19] = fp_buf[4];
  do
  {
    if (!getdata(3, 0, msg, fp_buf + 4, 4, DOECHO, 0))
      fp_buf[4] = msg[19];
  } while (fp_buf[4] < '0' || fp_buf[4] > '9');
  return fp_buf;
}


static void
read_tmpbuf(int n)
{
  FILE *fp;
  char fp_tmpbuf[80];
  char tmpfname[] = "buf.0";
  char *tmpf;
  char ans[4] = "y";

  if (0 <= n && n <= 9) {
     tmpfname[4] = '0' + n;
     tmpf = tmpfname;
  }
  else {
     tmpf = ask_tmpbuf();
     n = tmpf[4] - '0';
  }

  setuserfile(fp_tmpbuf, tmpf);

/*
woju
*/
  if (n != 0 && n != 5 && more(fp_tmpbuf, NA) != -1)
     getdata(b_lines - 1, 0, "½T©wÅª¤J¶Ü(Y/N)?[Y]",  ans, 4, LCECHO, 0);
  if (*ans != 'n' && (fp = fopen(fp_tmpbuf, "r")))
  {
    prevln = currln;
    prevpnt = currpnt;
    load_file(fp);
    while (curr_window_line >= b_lines)
    {
      curr_window_line--;
      top_of_win = top_of_win->next;
    }
  }
}


static void
write_tmpbuf()
{
  FILE *fp;
  char fp_tmpbuf[80], ans[4];
  textline *p;

  setuserfile(fp_tmpbuf, ask_tmpbuf());
  if (dashf(fp_tmpbuf))
  {
    more(fp_tmpbuf, NA);
    getdata(b_lines - 1, 0, "¼È¦sÀÉ¤w¦³¸ê®Æ (A)ªþ¥[ (W)ÂÐ¼g (Q)¨ú®ø¡H[A] ",
      ans, 4, LCECHO, 0);

    if (ans[0] == 'q')
      return;
  }

  fp = fopen(fp_tmpbuf, (ans[0] == 'w' ? "w" : "a+"));
  for (p = firstline; p; p = p->next)
  {
    if (p->next || p->data[0])
      fprintf(fp, "%s\n", p->data);
  }
  fclose(fp);
}


static void
erase_tmpbuf()
{
  char fp_tmpbuf[80];
  char ans[4] = "n";

  setuserfile(fp_tmpbuf, ask_tmpbuf());
/*
woju
*/
  if (more(fp_tmpbuf, NA) != -1)
     getdata(b_lines - 1, 0, "½T©w§R°£¶Ü(Y/N)?[N]",  ans, 4, LCECHO, 0);
  if (*ans == 'y')
     unlink(fp_tmpbuf);
}


/* ----------------------------------------------------- */
/* ½s¿è¾¹¦Û°Ê³Æ¥÷                                        */
/* ----------------------------------------------------- */


void
auto_backup()
{
  if (currline)
  {
    FILE *fp;
    textline *p, *v;
    char bakfile[64];

    setuserfile(bakfile, fp_bak);
    if (fp = fopen(bakfile, "w"))
    {
      for (p = firstline; p; p = v)
      {
        v = p->next;
        fprintf(fp, "%s\n", p->data);
        free(p);
      }
      fclose(fp);
    }
    currline = NULL;
  }
}


void
restore_backup()
{
  char bakfile[80], buf[80];

  setuserfile(bakfile, fp_bak);
  if (dashf(bakfile))
  {
    stand_title("½s¿è¾¹¦Û°Ê´_­ì");
    getdata(1, 0, "±z¦³¤@½g¤å³¹©|¥¼§¹¦¨¡A(S)¼g¤J¼È¦sÀÉ (Q)ºâ¤F¡H[S] ",
      buf, 4, LCECHO, 0);
    if (buf[0] != 'q')
    {
      setuserfile(buf, ask_tmpbuf());
      Rename(bakfile, buf);
    }
    else
      unlink(bakfile);
  }
}


/* ----------------------------------------------------- */
/* ¤Þ¥Î¤å³¹                                              */
/* ----------------------------------------------------- */


static int
garbage_line(str)               /* quote deletion */
  char *str;
{
  int qlevel = 0;

  while (*str == ':' || *str == '>')
  {
    if (*(++str) == ' ')
      str++;
    if (qlevel++ >= 1)
      return 1;
  }
  while (*str == ' ' || *str == '\t')
    str++;
  if (qlevel >= 1)
  {
    if (!strncmp(str, "¡° ", 3) || !strncmp(str, "==>", 3) ||
      strstr(str, ") ´£¨ì:\n"))
      return 1;
  }
  return (*str == '\n');
}



static void
do_quote()
{
  int op;
  char buf[256], word[256];

  getdata(b_lines - 1, 0, "½Ð°Ý­n¤Þ¥Î­ì¤å¶Ü(Y/N/All/Repost/Decode)¡H[Y] ", buf, 3, LCECHO, 0);
  op = buf[0];

  if (op != 'n')
  {
    FILE *inf;

    if (inf = fopen(quote_file, "r"))
    {
      char *ptr;
      int indent_mode0 = indent_mode;

      fgets(buf, 256, inf);
      str_decode(buf);
      if (ptr = strrchr(buf, ')'))
        ptr[1] = '\0';
      else if (ptr = strrchr(buf, '\n'))
        ptr[0] = '\0';

      if (ptr = strchr(buf, ':'))
      {
        char *str;

        while (*(++ptr) == ' ');

        /* ¶¶¤â²o¦Ï¡A¨ú±o author's address */
        if ((curredit & EDIT_BOTH) && (str = strchr(quote_user, '.')))
        {
          strcpy(++str, ptr);
          str = strchr(str, ' ');
          str[0] = '\0';
        }
      }
      else
        ptr = quote_user;

      indent_mode = 0;
      insert_string("¡° ¤Þ­z¡m");
      insert_string(ptr);
      insert_string("¡n¤§»Ê¨¥¡G\n");

      if (op != 'a' && op != 'd')            /* ¥h±¼ header */
      {
        while (fgets(buf, 256, inf) && buf[0] != '\n');
      }

      if (op == 'd')
      {
         if (fgets(buf, 256, inf)) {
            str_decode(buf);
            if (buf[strlen(buf) - 1] != '\n')
               strcat(buf, "\n");
            insert_string(buf);
         }
         while (fgets(buf, 256, inf))
         {
           str_decode(buf);
/* MH */
/* ¥Î mhsin_prints (in mhsin.c) ¨ú¥N kaede_prints */
/*           insert_string(kaede_prints(buf));*/
             insert_string(mhsin_prints(buf, 255));
/*    */
         }
         insert_string("\
> ------------------------------------------------------------------------ <\n");
      }
      else if (op == 'a')
      {
        while (fgets(buf, 256, inf))
        {
          insert_char(':');
          insert_char(' ');
/* MH */
/* ¥Î mhsin_prints (in mhsin.c) ¨ú¥N kaede_prints */
/*          insert_string(kaede_prints(buf));*/
          insert_string(mhsin_prints(buf, 255));
/*    */
        }
      }
      else if (op == 'r')
      {
        while (fgets(buf, 256, inf))
/* MH */
/* ¥Î mhsin_prints (in mhsin.c) ¨ú¥N kaede_prints */
/*          insert_string(kaede_prints(str_decode(buf)));*/
          insert_string(mhsin_prints(str_decode(buf), 255));
/*    */
      }
      else
      {
        if (curredit & EDIT_LIST)       /* ¥h±¼ mail list ¤§ header */
        {
          while (fgets(buf, 256, inf) && (!strncmp(buf, "¡° ", 3)));
        }

        while (fgets(buf, 256, inf))
        {
          if (beginsig(buf))
            break;
          if (!garbage_line(buf))
          {
            insert_char(':');
            insert_char(' ');
/* MH */
/* ¥Î mhsin_prints (in mhsin.c) ¨ú¥N kaede_prints */
/*            insert_string(kaede_prints(buf));*/
            insert_string(mhsin_prints(buf, 255));
/*    */
          }
        }
      }
      indent_mode = indent_mode0;
      fclose(inf);
    }
  }
}

/* ----------------------------------------------------- */
/* ¼f¬d user µoªí¤å³¹¦r¼Æ   Tzu                          */
/* ----------------------------------------------------- */

static int
check_words()   
{
  register textline *p = firstline;
  register char *str;
  int  i;
  int  words;
  
  words=0;
  
  while (p)
  {
    
    /* Tzu: ¶K¤å³¹·|Â_½u
    if (beginsig(str = p->data))
      break;*/
      
    str=p->data;
    if(!str)
      break;
    if(beginsig(str))
      break;
                       
    if (!(!strncmp(str, "¡° ", 3) ||
          (strlen(str) > 1 &&  /* MH: «OÀI¤@ÂI */
           (str[1] == ' ' &&
            ((str[0] == ':') ||
             (str[0] == '>')))))) {
       for(i = 0; i < strlen(str); i++)
         if(str[i] != ' ' && isprint2(str[i]))
           words++;
    }
      
    if (words > 40) {
      return 1;
    }
      
    p = p->next;                     
  }
  return 0;
}


/* ----------------------------------------------------- */
/* ¼f¬d user ¤Þ¨¥ªº¨Ï¥Î                                  */
/* ----------------------------------------------------- */


static int
check_quote()
{
  register textline *p = firstline;
  register char *str;
  int post_line;
  int included_line;

  post_line = included_line = 0;
  while (p)
  {
    if (beginsig(str = p->data))
      break;
    if (str[1] == ' ' && ((str[0] == ':') || (str[0] == '>')))
    {
      included_line++;
    }
    else
    {
      while (*str == ' ' || *str == '\t')
        str++;
      if (*str)
        post_line++;
    }
    p = p->next;
  }

  if ((included_line >> 2) > post_line)
  {
    move(4, 0);

    outs("\
        ¥»½g¤å³¹ªº¤Þ¨¥¤ñ¨Ò¶W¹L 80%¡A½Ð±z°µ¨Ç·Lªº­×¥¿¡G\n\n\
         [1;33m1) ¼W¥[¤@¨Ç¤å³¹ ©Î  2) §R°£¤£¥²­n¤§¤Þ¨¥[0m");

    if (1/*HAS_PERM(PERM_SYSOP)*/) /* Kaede */
    {
      char ans[4];
      getdata(12, 12, "(E)Ä~Äò½s¿è (W)±j¨î¼g¤J¡H[E] ", ans, 4, LCECHO, 0);
      if (ans[0] == 'w')
        return 0;
    }
    else
        pressanykey();
    return 1;
  }
  return 0;
}

/* ----------------------------------------------------- */
/* §PÂ_¯ZªO by Tzu                                       */
/* ----------------------------------------------------- */

#ifdef TZU_USE_CLASSBOARDS
static int 
is_classboard(char *brdname)
{
  return (!strncasecmp("KS", brdname, 2) ||
      !strncasecmp("KG", brdname, 2) ||
      !strncasecmp("Kcl", brdname, 3));
}
#endif


/* ----------------------------------------------------- */
/* ÀÉ®×³B²z¡GÅªÀÉ¡B¦sÀÉ¡B¼ÐÃD¡BÃ±¦WÀÉ                    */
/* ----------------------------------------------------- */


static void
read_file(fpath)
  char *fpath;
{
  FILE *fp;

  if ((fp = fopen(fpath, "r")) == NULL)
  {
    if (fp = fopen(fpath, "w+"))
    {
      fclose(fp);
      return;
    }
    indigestion(4);
    abort_bbs();
  }
  load_file(fp);
}


#ifndef VEDITOR
void
write_header(fp)
  FILE *fp;
{
  time_t now = time(0);

  if (curredit & EDIT_MAIL || curredit & EDIT_LIST)
  {
    fprintf(fp, "%s %s (%s)\n", str_author1, cuser.userid,

#if defined(REALINFO) && defined(MAIL_REALNAMES)
      cuser.realname);
#else
      cuser.username);
#endif
  }
  else
  {
    char *ptr;

    /* ²£¥Í²Î­p¸ê®Æ */

    struct
    {
      char author[IDLEN + 1];
      char board[IDLEN + 1];
      char title[66];
      time_t date;              /* last post's date */
      int number;               /* post number */
    }      postlog;

    strcpy(postlog.author, cuser.userid);

#ifdef HAVE_ANONYMOUS
    if (!strcmp(currboard, ANONYMOUS_BOARD))
      strcpy(postlog.author, ANONYMOUS_USER);
#endif

    strcpy(postlog.board, currboard);
    ptr = save_title;
    if (!strncmp(ptr, str_reply, 4))
      ptr += 4;
    strncpy(postlog.title, ptr, 65);
    postlog.date = now;
    postlog.number = 1;
#ifdef TZU_USE_CLASSBOARDS
    if (is_classboard(currboard)) 
      append_record(".post_classboards", &postlog, sizeof(postlog));    
    else
#endif
      append_record(".post", &postlog, sizeof(postlog));

#ifdef HAVE_ANONYMOUS
    if (!strcmp(currboard, ANONYMOUS_BOARD))
      fprintf(fp, "%s %s (%s) %s %s\n", str_author1, ANONYMOUS_USER,
        ANONYMOUS_NICKNAME, local_article ? str_post2 : str_post1, currboard);
    else
    {
      fprintf(fp, "%s %s (%s) %s %s\n", str_author1, cuser.userid,

#if defined(REALINFO) && defined(POSTS_REALNAMES)
        cuser.realname
#else
        cuser.username
#endif

        ,local_article ? str_post2 : str_post1, currboard);
    }
#else
    fprintf(fp, "%s %s (%s) %s %s\n", str_author1, cuser.userid,

#if defined(REALINFO) && defined(POSTS_REALNAMES)
      cuser.realname
#else
      cuser.username
#endif

      ,local_article ? str_post2 : str_post1, currboard);
#endif
  }
  save_title[72] = '\0';
  fprintf(fp, "¼ÐÃD: %s\n®É¶¡: %s\n", save_title, ctime(&now));
}


addsig()
{
  FILE *fs;
  int i;
  char buf[WRAPMARGIN + 1];
  char fpath[STRLEN];
  char ch;
  static char msg[] = "½Ð¿ï¾ÜÃ±¦WÀÉ (1-9, 0=¤£¥[)[0]: ";

  if (!currutmp->userlevel)
     return;
  i = showsignature(fpath);
  msg[27] = ch = '0' | (cuser.uflag & SIG_FLAG);
  getdata(0, 0, msg, buf, 4, DOECHO, 0);

  if (ch != buf[0] && buf[0] >= '0' && buf[0] <= '9')
  {
    ch = buf[0];
    cuser.uflag = (cuser.uflag & ~SIG_FLAG) | (ch & SIG_FLAG);
  }


  if (ch != '0') {
    fpath[i] = ch;
    if (fs = fopen(fpath, "r"))
    {
      insert_string("\n--\n");
      for (i = 0; i < MAXSIGLINES && fgets(buf, sizeof(buf), fs); i++)
        insert_string(buf);
      fclose(fs);
    }
  }
}

/* MH */
/* post «á¥[Ã±¦WÀÉ */
addsignature(fp)
 FILE *fp;
{
  FILE *fs;
  int i;
  char buf[WRAPMARGIN + 1];
  char mhbuf[20] = "sig.0", fname[200];
  char ch;
  static char msg[] = "½Ð¿ï¾ÜÃ±¦WÀÉ (1-9, 0=¤£¥[)[0]: ";

  if (!currutmp->userlevel)
     return;
#ifdef MH_OLD_SIG
  msg[27] = ch = '0' | (cuser.uflag & SIG_FLAG);
#else
  msg[27] = ch = (cuserrc.sig_num + '0');
#endif
  i = mh_showsignature(msg);
  if(i == 0)
    i = ch;
  else
#ifdef MH_OLD_SIG
    cuser.uflag = (cuser.uflag & ~SIG_FLAG) | (i & SIG_FLAG);
#else
    cuserrc.sig_num = (i & 0xf);
#endif
  if(i != '0')
  {
    mhbuf[4] = i;
    setuserfile(fname, mhbuf);
    if (fs = fopen(fname, "r"))
    {
      fputs("\n--\n", fp);
      for (i = 0; i < MAXSIGLINES && fgets(buf, sizeof(buf), fs); i++)
        fputs(buf, fp);
      fclose(fs);
    }
  }
}
/*       */

void
addorigin(fp)
  FILE *fp;
{
  extern bad_user(char* name);

/*
woju
*/
  if (!strcmp(cuser.userid, "guest") || bad_user(cuser.userid)) {
     fprintf(fp, "\n--\n¡° Origin: %s ¡» From: %s\n", BoardName, getenv("RFC931"));
     return;
  }

#ifdef  HAVE_ORIGIN
#ifdef  HAVE_ANONYMOUS
  if (!(curredit & (EDIT_MAIL | EDIT_LIST)) && !strcmp(currboard, ANONYMOUS_BOARD))
    fprintf(fp, "\n--\n¡° Origin: %s ¡» From: %s\n", BoardName, ANONYMOUS_HOME);
  else
    fprintf(fp, "\n--\n¡° Origin: %s ¡» From: %s\n", BoardName, fromhost);
#else

/* 2004/07/04 by Terry */
    fprintf(fp, "\n--\n[37mOrigin:             [1;36m.-~^^~-.[m\n"
            "[1;37m°ª¶¯¤¤¾Ç- [31m¬õ ¼Ó [33m¿v [36m(  [35m-¹Ú-[36m  )  [0;37m-=[[1;33;44mbbs.kshs.kh.edu.tw[0;37m]=-\n"
            "         [1;32m. ¡C o ¢Ý  [36m~-.__.-~   [0;32mFrom:%s[m", fromhost);
/*		       */

#endif
#endif
}
#endif


static int
write_file(fpath, saveheader)
  char *fpath;
  int saveheader;
{
  FILE *fp;
  textline *p, *v;
  char ans[TTLEN], *msg;
  int aborted = 0;
  char pgppath[200];
  char fnamepgp[MAXPATHLEN];
  char cmd[3 * MAXPATHLEN];
  FILE *fpgp;

  stand_title("ÀÉ®×³B²z");

  move(1, 0);
/* MH */
/* bug killed */
/* Á×§K¦b¡u«D post, mail ±¡§Î¡v¤U¥X²{¡u¼ÐÃD¡GXX¡v */
/* ex: ­ì¥»¦b½sÃ±¦WÀÉ­n¦sÀÉ®É·|¥X²{¡u¼ÐÃD¡GXX¡v */
  if (currstat == POSTING || currstat == SMAIL)
    prints("¼ÐÃD¡G%s", save_title);
/*    */
  if (currstat == SMAIL)
    msg = "[S]Àx¦s (A)©ñ±ó (T)§ï¼ÐÃD (E)Ä~Äò (R/W/D)Åª¼g§R¼È¦sÀÉ¡H";
  else if (local_article)
    msg = "[L]¯¸¤º«H¥ó (S)Àx¦s (A)©ñ±ó (T)§ï¼ÐÃD (E)Ä~Äò (R/W/D)Åª¼g§R¼È¦sÀÉ¡H";
  else
    msg = "[S]Àx¦s (L)¯¸¤º«H¥ó (A)©ñ±ó (T)§ï¼ÐÃD (E)Ä~Äò (R/W/D)Åª¼g§R¼È¦sÀÉ¡H";
  getdata(2, 0, msg, ans, 3, LCECHO, 0);

  switch (ans[0])
  {
  case 'a':
  case 'q':
    outs("¤å³¹[1m ¨S¦³ [0m¦s¤J");
    sleep(1);
    aborted = -1;
    break;

  case 'r':
    read_tmpbuf(-1);

  case 'e':
    return KEEP_EDITING;

  case 'w':
    write_tmpbuf();
    return KEEP_EDITING;

  case 'd':
    erase_tmpbuf();
    return KEEP_EDITING;

  case 't':
    if (getdata(4, 0, "·s¼ÐÃD¡G", ans, TTLEN, DOECHO, save_title))
      strcpy(save_title, ans);
    return KEEP_EDITING;

  case 's':
    if (!HAS_PERM(PERM_LOGINOK))
    {
        local_article = 1;
        move(2, 0);
        prints("±z©|¥¼³q¹L¨­¥÷½T»{¡A¥u¯à Local Save¡C\n");
/*        pressanykey();*/
    }
    else
        local_article = 0;
    break;

  case 'l':
    local_article = 1;
    break;

  case 'p': /* pgp sign */
    local_article = 2;
    break;
  }

  if (saveheader == 2 && !aborted) {
     stand_title("¼g¤J¥¢±Ñ: §ï¼g¨ì¼È¦sÀÉ");
     write_tmpbuf();
     return KEEP_EDITING;
  }

  if (!aborted)
  {
    if (saveheader && !(curredit & EDIT_MAIL) && check_quote())
      return KEEP_EDITING;

    if (!*fpath)
    {
      sethomepath(fpath, cuser.userid);
      strcpy(fpath, tempnam(fpath, "ve_"));
    }

    if ((fp = fopen(fpath, "w")) == NULL)
    {
      indigestion(5);
      abort_bbs();
    }

    if (saveheader)
      write_header(fp);
  }

  fpgp = 0;
  if (local_article == 2) { /* pgp sign */
     local_article = 0;
     sprintf(pgppath, "home/%s/pgp", cuser.userid);
     sprintf(fnamepgp, "%s.pgp", fpath);
     if (dashd(pgppath) && (fpgp = fopen(fnamepgp, "w"))) {
        fclose(fp);
        fp = fpgp;
     }
  }

  for (p = firstline; p; p = v)
  {
    v = p->next;
    if (!aborted)
    {
      msg = p->data;
      if (v || msg[0])
      {
        trim(msg);
        fprintf(fp, "%s\n", msg);
      }
    }
    free(p);
  }
  currline = NULL;

  if (!aborted)
  {
/* MH */
/* Ã±¦WÀÉ§ï¦b post «á¦A¥[¤J¡]¨Ï¥ÎªÌ«ØÄ³§ïªº¡^ */
     if (currstat == POSTING || currstat == SMAIL)
     {
        addsignature(fp);
        addorigin(fp);
     }
/*       */
     fclose(fp);
     if (fpgp) {
        outmsg("PGP½s½X¤¤...");
        refresh();
        sprintf(cmd, "PGPPATH=%s; PGPPASSFD=0; export PGPPATH PGPPASSFD;\
echo `cat home/%s/pgp.phrase` | /usr/local/bin/pgp +batchmode -o- -sat \
+clearsig=on %s >> %s 2>/dev/null", pgppath, cuser.userid, fnamepgp, fpath);
        if (system(cmd)) {
           sprintf(cmd, "cat %s >> %s", fnamepgp, fpath);
#ifdef SunOS
           if (!mbbsd)
#endif
           system(cmd);
        }
        unlink(fnamepgp);
    }
#if 0
    if (currstat == POSTING)
      if (!check_words())
        return 2;     /* too few words sign by Tzu */
#endif
    if (local_article && (currstat == POSTING))
      return 1;
  }
  
  return aborted;
}




edit_outs(text)
  char *text;
{
  register int column = 0;
  register char ch;

  while ((ch = *text++) && (++column < SCR_WIDTH))
  {
    outch(ch == 27 ? '*' : ch);
  }
}

block_outs(char* text, int column)
{
  register char ch;

  while ((ch = *text++) && (++column < SCR_WIDTH))
  {
    outch(ch == 27 ? '*' : ch);
  }
}

int outs();

static void
display_buffer()
{
  register textline *p;
  register int i;
  int inblock;
  char buf[WRAPMARGIN + 2];
  int min, max;
  int (*OUTS)();

  if (currpnt > blockpnt) {
     min = blockpnt;
     max = currpnt;
  }
  else {
     min = currpnt;
     max = blockpnt;
  }

  OUTS = my_ansimode ? outs : edit_outs;

  for (p = top_of_win, i = 0; i < b_lines; i++)
  {

    move(i, 0);
    clrtoeol();
/*
woju
*/
    if (blockln >= 0
        && (blockln <= currln
              && blockln <= (currln - curr_window_line + i)
              &&            (currln - curr_window_line + i) <= currln
           ||
                 currln  <= (currln - curr_window_line + i)
              &&            (currln - curr_window_line + i) <= blockln)) {
       outs("[7m");
       inblock = 1;
    }
    else
       inblock = 0;
    if (p)
    {
      if (currln == blockln && p == currline && max > min) {
         if (min > edit_margin) {
            outs("[0m");
            strncpy(buf, p->data + edit_margin, min - edit_margin);
            buf[min - edit_margin] = 0;
            block_outs(buf, 0);
         }
         outs("[7m");
         if (min > edit_margin) {
            strncpy(buf, p->data + min, max - min);
            buf[max - min] = 0;
            block_outs(buf, min - edit_margin);
         }
         else {
            strncpy(buf, p->data + edit_margin, max - edit_margin);
            buf[max - edit_margin] = 0;
            block_outs(buf, 0);
         }
         outs("[0m");
         block_outs(p->data + max, max - edit_margin);
      }
      else
         OUTS(&p->data[edit_margin]);
      p = p->next;
      if (inblock)
         outs("[0m");
    }
    else
      outch('~');
  }
  edit_msg();
}


/*
woju
lino == 0 for prompt
*/

goto_line(int lino)
{
   char buf[10];

   if (lino > 0 || getdata(b_lines - 1, 0, "¸õ¦Ü²Ä´X¦æ:", buf, 10, DOECHO, 0)
       && sscanf(buf, "%d", &lino) && lino > 0) {
      textline* p;

      prevln = currln;
      prevpnt = currpnt;
      p = firstline;
      currln = lino - 1;

      while (--lino && p->next)
         p = p->next;

      if (p)
         currline = p;
      else {
         currln = totaln;
         currline = lastline;
      }
      currpnt = 0;
      if (currln < 11) {
         top_of_win = firstline;
         curr_window_line = currln;
      }
      else {
         int i;
         curr_window_line = 11;

         for (i = curr_window_line; i; i--)
            p = p->prev;
            top_of_win = p;
      }
   }
   redraw_everything = YEA;
}



char* strcasestr(const char* big, const char* little)
{
   char* ans = (char*)big;
   int len = strlen(little);
   char* endptr = (char*)big + strlen(big) - len;

   while (ans <= endptr)
      if (!strncasecmp(ans, little, len))
         return ans;
      else
         ans++;
   return 0;
}


/*
woju
mode:
    0: prompt
    1: forward
    -1: backward
*/
search_str(int mode)
{
   static char str[80];
   char buf[100];
   typedef char* (*FPTR)();
   static FPTR fptr;
   char ans[4] = "n";

   if (!mode) {
      sprintf(buf, "´M§ä¦r¦ê[%s]", str);
      if (getdata(b_lines - 1, 0, buf, buf, 40, DOECHO, 0))
         strcpy(str, buf);
      if (*str)
         if (getdata(b_lines - 1, 0, "°Ï¤À¤j¤p¼g(Y/N/Q)? [N] ", ans, 4, LCECHO, 0)
             && *ans == 'y')
            fptr = strstr;
         else
            fptr = strcasestr;
   }

   if (*str && *ans != 'q') {
      textline* p;
      char* pos  = 0;
      int lino;

      if (mode >= 0) {
         for (lino = currln, p = currline; p; p = p->next, lino++) {
            if (*str == KEY_ESC) {
               if (!strncmp(str + 1, p->data, strlen(str + 1))
                   && (lino != currln || currpnt)) {
                  pos = p->data;
                  break;
               }
            }
            else if ((pos =
                      fptr(p->data + (lino == currln ? currpnt + 1 : 0), str))
                && (lino != currln || pos - p->data != currpnt))
               break;
         }
      }
      else {
         for (lino = currln, p = currline; p; p = p->prev, lino--) {
            if (*str == KEY_ESC) {
               if (!strncmp(str + 1, p->data, strlen(str + 1))
                   && (lino != currln || currpnt)) {
                  pos = p->data;
                  break;
               }
            }
            if ((pos = fptr(p->data, str))
                && (lino != currln || pos - p->data != currpnt))
               break;
            else
               pos = 0;
         }
      }
      if (pos) {
         prevln = currln;
         prevpnt = currpnt;
         currline = p;
         currln = lino;
         currpnt = pos - p->data;
         if (lino < 11) {
            top_of_win = firstline;
            curr_window_line = currln;
         }
         else {
            int i;
            curr_window_line = 11;

            for (i = curr_window_line; i; i--)
               p = p->prev;
            top_of_win = p;
         }
         redraw_everything = YEA;
      }
   }
   if (!mode)
      redraw_everything = YEA;
}


match_paren()
{
   static char parens[] = "()[]{}<>";
   int type, mode;
   int parenum = 0;
   char *ptype;
   textline* p;
   int lino;
   int c, i;

   if (!(ptype = strchr(parens, currline->data[currpnt])))
      return;

   type = (ptype - parens) / 2;
   parenum += ((ptype - parens) % 2) ? -1 : 1;


   if (parenum > 0) {
     for (lino = currln, p = currline; p; p = p->next, lino++) {
         lino = lino;
         for (i = (lino == currln) ? currpnt + 1 : 0; i < strlen(p->data); i++)
            if (p->data[i] == '/' && p->data[++i] == '*') {
               ++i;
               while (1) {
                  while(i < strlen(p->data) - 1
                      && !(p->data[i] == '*' && p->data[i + 1] == '/'))
                     i++;
                  if (i >= strlen(p->data) - 1 && p->next) {
                     p = p->next;
                     ++lino;
                     i = 0;
                  }
                  else
                     break;
               }
            }
            else if ((c = p->data[i]) == '\'' || c == '"') {
               while (1) {
                  while (i < (int)(strlen(p->data) - 1))
                     if (p->data[++i] == '\\' && i < strlen(p->data) - 2)
                        ++i;
                     else if (p->data[i] == c)
                        goto end_quote;
                  if (i >= strlen(p->data) - 1 && p->next) {
                     p = p->next;
                     ++lino;
                     i = -1;
                  }
                  else
                     break;
               }
end_quote:
               ;
            }
            else if ((ptype = strchr(parens, p->data[i]))
                     && (ptype - parens) / 2 == type)
               if (!(parenum += ((ptype - parens) % 2) ? -1 : 1))
                  goto p_outscan;
     }
   }
   else {
      for (lino = currln, p = currline; p; p = p->prev, lino--)
         for (i = (lino == currln) ? currpnt - 1 : strlen(p->data) - 1;
              i >= 0; i--)
            if (p->data[i] == '/' && p->data[--i] == '*' && i >= 0) {
               --i;
               while (1) {
                  while(i > 0
                      && !(p->data[i] == '*' && p->data[i - 1] == '/'))
                     i--;
                  if (i <= 0 && p->prev) {
                     p = p->prev;
                     --lino;
                     i = strlen(p->data) - 1;
                  }
                  else
                     break;
               }
            }
            else if ((c = p->data[i]) == '\'' || c == '"') {
               while (1) {
                  while (i > 0)
                     if (i > 1 && p->data[i - 2] == '\\')
                        i -= 2;
                     else if ((p->data[--i]) == c)
                        goto begin_quote;
                  if (i <= 0 && p->prev) {
                     p = p->prev;
                     --lino;
                     i = strlen(p->data);
                  }
                  else
                     break;
               }
begin_quote:
               ;
            }
            else if ((ptype = strchr(parens, p->data[i]))
                     && (ptype - parens) / 2 == type)
               if (!(parenum += ((ptype - parens) % 2) ? -1 : 1))
                  goto p_outscan;
   }

p_outscan:

   if (!parenum) {
      int top = currln - curr_window_line;
      int bottom = currln - curr_window_line + b_lines - 1;

      currpnt = i;
      currline = p;
      curr_window_line += lino - currln;
      currln = lino;

      if (lino < top || lino > bottom) {
         if (lino < 11) {
            top_of_win = firstline;
            curr_window_line = currln;
         }
         else {
            int i;
            curr_window_line = 11;

            for (i = curr_window_line; i; i--)
               p = p->prev;
            top_of_win = p;
         }
         redraw_everything = YEA;
      }
   }
}

block_del(int hide)
{
   if (blockln < 0) {
      blockln = currln;
      blockpnt = currpnt;
      blockline = currline;
   }
   else {
      char fp_tmpbuf[80];
      FILE* fp;
      textline *begin, *end, *p;
      int lines;
      char tmpfname[10] = "buf.0";
      char ans[6] = "w+n";

      move(b_lines - 1, 0);
      clrtoeol();
      if (hide == 1)
         tmpfname[4] = 'q';
      else if (!hide && !getdata(b_lines - 1, 0, "§â°Ï¶ô²¾¦Ü¼È¦sÀÉ (0:Cut, 5:Copy, 6-9, q: Cancel)[0] ",  tmpfname + 4, 4, LCECHO, 0))
         tmpfname[4] = '0';
      if (tmpfname[4] < '0' || tmpfname[4] > '9')
         tmpfname[4] = 'q';
      if ('1' <= tmpfname[4] && tmpfname[4] <= '9') {
         setuserfile(fp_tmpbuf, tmpfname);
         if (tmpfname[4] != '5' && dashf(fp_tmpbuf)) {
            more(fp_tmpbuf, NA);
            getdata(b_lines - 1, 0, "¼È¦sÀÉ¤w¦³¸ê®Æ (A)ªþ¥[ (W)ÂÐ¼g (Q)¨ú®ø¡H[W] ", ans, 4, LCECHO, 0);
            if (*ans == 'q')
               tmpfname[4] = 'q';
            else if (*ans != 'a')
               *ans = 'w';
          }
          if (tmpfname[4] != '5') {
             getdata(b_lines - 1, 0, "§R°£°Ï¶ô(Y/N)?[N] ", ans + 2, 4, LCECHO, 0);
             if (ans[2] != 'y')
                ans[2] = 'n';
          }
      }
      else if (hide != 3)
         ans[2] = 'y';

      tmpfname[5] = ans[1] = ans[3] = 0;
      if (tmpfname[4] != 'q') {
         if (currln >= blockln) {
            begin = blockline;
            end = currline;
         }
         else {
            begin = currline;
            end = blockline;
         }

         if (ans[2] == 'y' && !(begin == end && currpnt != blockpnt)) {
            if (currln > blockln) {
               curr_window_line -= (currln - blockln);
               currln = blockln;
               if (curr_window_line < 0) {
                  curr_window_line = 0;
                  if (end->next)
                     top_of_win = end->next;
                  else
                     top_of_win = begin->prev;
               }
            }
            if (!curr_window_line)
               if (end->next)
                  top_of_win = end->next;
               else
                  top_of_win = begin->prev;

            if (begin->prev)
               begin->prev->next = end->next;
            else if (end->next)
               top_of_win = firstline = end->next;
            else {
               currline = top_of_win = firstline = lastline = alloc_line();
               currln = curr_window_line = edit_margin = 0;
            }

            if (end->next)
               (currline = end->next)->prev = begin->prev;
            else if (begin->prev) {
               currline = (lastline = begin->prev);
               currln--;
               if (curr_window_line > 0)
                  curr_window_line--;
            }
         }

         setuserfile(fp_tmpbuf, tmpfname);
         if (fp = fopen(fp_tmpbuf, ans)) {
            if (begin == end && currpnt != blockpnt) {
               char buf[WRAPMARGIN + 2];

               if (currpnt > blockpnt) {
                  strcpy(buf, begin->data + blockpnt);
                  buf[currpnt - blockpnt] = 0;
               }
               else {
                  strcpy(buf, begin->data + currpnt);
                  buf[blockpnt - currpnt] = 0;
               }
               fputs(buf, fp);
            }
            else {
               for (p = begin; p != end; p = p->next)
                  fprintf(fp, "%s\n", p->data);
               fprintf(fp, "%s\n", end->data);
            }
            fclose(fp);
         }

         if (ans[2] == 'y') {
            if (begin == end && currpnt != blockpnt) {
               int min, max;

               if (currpnt > blockpnt) {
                  min = blockpnt;
                  max = currpnt;
               }
               else {
                  min = currpnt;
                  max = blockpnt;
               }
               strcpy(begin->data + min, begin->data + max);
               begin->len -= max - min;
               currpnt = min;
            }
            else {
               for (p = begin; p != end; totaln--)
                  free((p = p->next)->prev);
               free(end);
               totaln--;
               currpnt = 0;
            }
         }
      }
      blockln = -1;
      redraw_everything = YEA;
   }
}


block_shift_left()
{
   textline *begin, *end, *p;

   if (currln >= blockln) {
      begin = blockline;
      end = currline;
   }
   else {
      begin = currline;
      end = blockline;
   }
   p = begin;
   while (1) {
      if (p->len) {
         strcpy(p->data, p->data + 1);
         --p->len;
      }
      if (p == end)
         break;
      else
         p = p->next;
   }
   if (currpnt > currline->len)
      currpnt = currline->len;
   redraw_everything = YEA;
}

block_shift_right()
{
   textline *begin, *end, *p;

   if (currln >= blockln) {
      begin = blockline;
      end = currline;
   }
   else {
      begin = currline;
      end = blockline;
   }
   p = begin;
   while (1) {
      if (p->len < WRAPMARGIN) {
         int i = p->len + 1;

         while (i--)
            p->data[i + 1] = p->data[i];
         p->data[0] = insert_character ? ' ' : insert_c;
         ++p->len;
      }
      if (p == end)
         break;
      else
         p = p->next;
   }
   if (currpnt > currline->len)
      currpnt = currline->len;
   redraw_everything = YEA;
}

transform_to_color(char* line)
{
   while (line[0] && line[1])
      if (line[0] == '*' && line[1] == '[') {
         line[0] = KEY_ESC;
         line += 2;
      }
      else
         ++line;
}


block_color()
{
   textline *begin, *end, *p;

   if (currln >= blockln) {
      begin = blockline;
      end = currline;
   }
   else {
      begin = currline;
      end = blockline;
   }
   p = begin;
   while (1) {
      transform_to_color(p->data);
      if (p == end)
         break;
      else
         p = p->next;
   }
   block_del(1);
}


/* ----------------------------------------------------- */
/* ½s¿è³B²z¡G¥Dµ{¦¡¡BÁä½L³B²z                            */
/* ----------------------------------------------------- */


extern int my_write();


int
vedit(fpath, saveheader)
  char *fpath;
  int saveheader;
{
  int ch, foo;
  int lastindent = -1;
  int last_margin;
  int mode0 = currutmp->mode;
  int destuid0 = currutmp->destuid;
  char* pstr;
  extern char* phone_char();

  textline* firstline0 = firstline;
  textline* lastline0 = lastline;
  textline* currline0 = currline;
  textline* blockline0 = blockline;
  textline* top_of_win0 = top_of_win;
  int local_article0 = local_article;
  int currpnt0 = currpnt;
  int currln0 = currln;
  int totaln0 = totaln;
  int curr_window_line0 = curr_window_line;
  int insert_character0 = insert_character;
  int my_ansimode0 = my_ansimode;
  int edit_margin0 = edit_margin;
  int blockln0 = blockln;

  currutmp->mode = EDITING;
  currutmp->destuid = currstat;
  insert_character = redraw_everything = 1;
  prevln = blockln = -1;

  line_dirty = currpnt = totaln = my_ansimode = 0;
  currline = top_of_win = firstline = lastline = alloc_line();

  if (*fpath)
  {
    read_file(fpath);
  }

  if (*quote_file)
  {
    do_quote();
    *quote_file = '\0';
    if (quote_file[79] == 'L')
      local_article = 1;
  }
#ifndef VEDITOR
/* MH */
/* Ã±¦WÀÉ§ï¦b post «á¦A¥[¤J¡]¨Ï¥ÎªÌ«ØÄ³§ïªº¡^ */
/*  if (currstat == POSTING || currstat == SMAIL)
     addsig();*/
/*       */
#endif


  currline = firstline;
  currpnt = currln = curr_window_line = edit_margin = last_margin = 0;

  while (1)
  {
    if (redraw_everything || blockln >=0)
    {
      display_buffer();
      redraw_everything = NA;
    }
    if (my_ansimode)
       ch = n2ansi(currpnt, currline);
    else
       ch = currpnt - edit_margin;
    move(curr_window_line, ch);
    if (!line_dirty && strcmp(line, currline->data))
       strcpy(line, currline->data);
    ch = igetkey();

    if (raw_mode)
       switch (ch) {
       case Ctrl('S'):
       case Ctrl('Q'):
       case Ctrl('T'):
          continue;
          break;
       }

    if (phone_mode && (pstr = phone_char(ch)) || ch < 0x100 && isprint2(ch))
    {
      if (phone_mode && pstr)
         insert_string(pstr);
      else
         insert_char(ch);
      lastindent = -1;
      line_dirty = 1;
    }
    else
    {
      if (ch == Ctrl('P') || ch == KEY_UP || ch == KEY_DOWN || ch == Ctrl('N'))
      {
        if (lastindent == -1)
          lastindent = currpnt;
      }
      else
        lastindent = -1;

/*
woju
*/
      if (ch == KEY_ESC)
         switch (KEY_ESC_arg) {
         case ',':
            ch = Ctrl(']');
            break;
         case '.':
            ch = Ctrl('T');
            break;
         case 'v':
            ch = KEY_PGUP;
            break;
         case 'a':
         case 'A':
            ch = Ctrl('V');
            break;
         case 'X':
            ch = Ctrl('X');
            break;
         case 'q':
            ch = Ctrl('Q');
            break;
         case 'o':
            ch = Ctrl('O');
            break;
         case '-':
            ch = Ctrl('_');
            break;
         case 's':
            ch = Ctrl('S');
            break;
         }

      switch (ch)
      {
      case Ctrl('X'):           /* Save and exit */
        foo = write_file(fpath, saveheader);
        if (foo != KEEP_EDITING)
        {
          currutmp->mode = mode0;
          currutmp->destuid = destuid0;
          firstline = firstline0;
          lastline = lastline0;
          currline = currline0;
          blockline = blockline0;
          top_of_win = top_of_win0;
          local_article = local_article0;
          currpnt = currpnt0;
          currln = currln0;
          totaln = totaln0;
          curr_window_line = curr_window_line0;
          insert_character = insert_character0;
          my_ansimode = my_ansimode0;
          edit_margin = edit_margin0;
          blockln = blockln0;
          return foo;
        }
        line_dirty = 1;
        redraw_everything = YEA;
        break;

      case Ctrl('W'):
         if (blockln >= 0)
            block_del(2);
         line_dirty = 1;
         break;


      case Ctrl('Q'):           /* Quit without saving */
        ch = ask("µ²§ô¦ý¤£Àx¦s (Y/N)? [N]: ");
        if (ch == 'y' || ch == 'Y') {
          currutmp->mode = mode0;
          currutmp->destuid = destuid0;
          firstline = firstline0;
          lastline = lastline0;
          currline = currline0;
          blockline = blockline0;
          top_of_win = top_of_win0;
          local_article = local_article0;
          currpnt = currpnt0;
          currln = currln0;
          totaln = totaln0;
          curr_window_line = curr_window_line0;
          insert_character = insert_character0;
          my_ansimode = my_ansimode0;
          edit_margin = edit_margin0;
          blockln = blockln0;
          return -1;
        }
        line_dirty = 1;
        redraw_everything = YEA;
        break;

      case Ctrl('C'):
        ch = insert_character;
        insert_character = redraw_everything = YEA;

        if (!my_ansimode)
        {
          insert_string(reset_color);
        }
        else
        {
          char ans[4];
          move(b_lines - 2, 55);
          outs("\033[1;33;40mB\033[41mR\033[42mG\033[43mY\033[44mL\033[45mP\033[46mC\033[47mW\033[m");
          if (getdata(b_lines - 1, 0, "½Ð¿é¤J  «G«×/«e´º/­I´º[¥¿±`¥Õ¦r¶Â©³][0wb]¡G", ans, 4, LCECHO, 0))
          {
            char t[] = "BRGYLPCW";
            char color[15];
            char *tmp, *apos = ans;
            int fg, bg;
            strcpy(color, "\033[");
            if (isdigit(*apos))
            {
              sprintf(color, "%s%c", color, *(apos++));
              if (*apos)
                sprintf(color, "%s;", color);
            }
            if (*apos)
            {
              if (tmp = strchr(t, toupper(*(apos++))))
                fg = tmp - t + 30;
              else
                fg = 37;
              sprintf(color, "%s%d", color, fg);
            }
            if (*apos)
            {
              if (tmp = strchr(t, toupper(*(apos++))))
                bg = tmp - t + 40;
              else
                bg = 40;
              sprintf(color, "%s;%d", color, bg);
            }
            sprintf(color, "%sm", color);
            insert_string(color);
          }
          else
            insert_string(reset_color);
        }
        insert_character = ch;
        line_dirty = 1;
        break;

      case KEY_ESC:
         line_dirty = 0;
         switch (KEY_ESC_arg) {
         case 'U':
            t_users();
            redraw_everything = YEA;
            line_dirty = 1;
            break;
         case 'm':
            m_read();
            redraw_everything = YEA;
            line_dirty = 1;
            break;
         case 'i':
            t_idle();
            redraw_everything = YEA;
            line_dirty = 1;
            break;
         case 'n':
            search_str(1);
            edit_margin = currpnt < SCR_WIDTH - 1 ? 0 : currpnt / 72 * 72;
            if (edit_margin != last_margin)
               redraw_everything = NA;
            break;
         case 'p':
            search_str(-1);
            edit_margin = currpnt < SCR_WIDTH - 1 ? 0 : currpnt / 72 * 72;
            if (edit_margin != last_margin)
               redraw_everything = NA;
            break;
         case 'L':
         case 'J':
         case 'g':
            goto_line(0);
            break;
         case ']':
            match_paren();
            break;
         case '0':
         case '5':
         case '6':
         case '7':
         case '8':
         case '9':
         {
            int currln0 = currln;
            int currpnt0 = currpnt;

            read_tmpbuf(KEY_ESC_arg - '0');
            redraw_everything = (currln0 == currln && currpnt0 != currpnt) ? NA : YEA;
         }
            break;
         case 'l':                       /* block delete */
         case ' ':
            block_del(0);
            line_dirty = 1;
            break;
         case 'u':
            if (blockln >= 0)
               block_del(1);
            line_dirty = 1;
            break;
         case 'c':
            if (blockln >= 0)
               block_del(3);
            line_dirty = 1;
            break;
         case 'y':
            undelete_line();
            break;
         case 'P':
            phone_mode ^= 1;
            line_dirty = 1;
            break;
         case 'R':
            raw_mode ^= 1;
            line_dirty = 1;
            break;
         case 'I':
            indent_mode ^= 1;
            line_dirty = 1;
            break;
         case 'j':
            if (blockln >= 0)
               block_shift_left();
            else if (currline->len) {
               int currpnt0 = currpnt;
               currpnt = 0;
               delete_char();
               currpnt = (currpnt0 <= currline->len) ? currpnt0 : currpnt0 - 1;
               if (my_ansimode)
                   currpnt = ansi2n(n2ansi(currpnt, currline),currline);
            }
            line_dirty = 1;
            break;
         case 'k':
            if (blockln >= 0)
               block_shift_right();
            else {
               int currpnt0 = currpnt;
               currpnt = 0;
               insert_char(' ');
               currpnt = currpnt0;
            }
            line_dirty = 1;
            break;
         case 'f':
            while (currpnt < currline->len && isalnum(currline->data[++currpnt]))
               ;
            while (currpnt < currline->len && isspace(currline->data[++currpnt]))
               ;
            line_dirty = 1;
            break;
         case 'b':
            while (currpnt && isalnum(currline->data[--currpnt]))
               ;
            while (currpnt && isspace(currline->data[--currpnt]))
               ;
            line_dirty = 1;
            break;
         case 'd':
            while (currpnt < currline->len) {
               delete_char();
               if (!isalnum(currline->data[currpnt]))
                  break;
            }
            while (currpnt < currline->len) {
               delete_char();
               if (!isspace(currline->data[currpnt]))
                  break;
            }
            line_dirty = 1;
            break;
         default:
            line_dirty = 1;
         }
         break;
      case Ctrl('_'):
         if (strcmp(line, currline->data)) {
            char buf[WRAPMARGIN];

            strcpy(buf, currline->data);
            strcpy(currline->data, line);
            strcpy(line, buf);
            currline->len = strlen(currline->data);
            currpnt = 0;
            line_dirty = 1;
         }
         break;
      case Ctrl('S'):
         search_str(0);
         edit_margin = currpnt < SCR_WIDTH - 1 ? 0 : currpnt / 72 * 72;
         if (edit_margin != last_margin)
            redraw_everything = NA;
         break;
      case Ctrl('U'):
        insert_char('');
        line_dirty = 1;
        break;

      case Ctrl('V'):                   /* Toggle ANSI color */
         my_ansimode ^= 1;
         if (my_ansimode && blockln >= 0)
            block_color();
         clear();
         redraw_everything = YEA;
         line_dirty = 1;
         break;

      case Ctrl('I'):
        do
        {
          insert_char(' ');
        }
        while (currpnt & 0x7);
        line_dirty = 1;
        break;

      case '\r':
      case '\n':
        split(currline, currpnt);
        line_dirty = 0;
        break;

/* MH */
        case Ctrl('R'):
          mh_throw_water_ball();
          redraw_everything = YEA;
          line_dirty = 1;
          break;
/*    */

      case Ctrl('G'):
      case Ctrl('Z'):
        more("etc/ve.hlp", YEA);
        redraw_everything = YEA;
        line_dirty = 1;
        break;

      case Ctrl('L'):
        clear();
        redraw_everything = YEA;
        line_dirty = 1;
        break;

      case KEY_LEFT:
        if (currpnt) {
          if (my_ansimode)
             currpnt = n2ansi(currpnt, currline);
          currpnt--;
          if (my_ansimode)
             currpnt = ansi2n(currpnt, currline);
          line_dirty = 1;
        }
        else if (currline->prev)
        {
          curr_window_line--;
          currln--;
          currline = currline->prev;
          currpnt = currline->len;
          line_dirty = 0;
        }
        break;

      case KEY_RIGHT:
        if (currline->len != currpnt) {
          if (my_ansimode)
             currpnt = n2ansi(currpnt, currline);
          currpnt++;
          if (my_ansimode)
             currpnt = ansi2n(currpnt, currline);
          line_dirty = 1;
        }
        else if (currline->next)
        {
          currpnt = 0;
          curr_window_line++;
          currln++;
          currline = currline->next;
          line_dirty = 0;
        }
        break;

      case KEY_UP:
      case Ctrl('P'):
        if (currline->prev)
        {
          if (my_ansimode)
             ch = n2ansi(currpnt,currline);
          curr_window_line--;
          currln--;
          currline = currline->prev;
          if (my_ansimode)
             currpnt = ansi2n(ch , currline);
          else
             currpnt = (currline->len > lastindent) ? lastindent : currline->len;
          line_dirty = 0;
        }
        break;

      case KEY_DOWN:
      case Ctrl('N'):
        if (currline->next)
        {
          if (my_ansimode)
             ch = n2ansi(currpnt,currline);
          currline = currline->next;
          curr_window_line++;
          currln++;
          if (my_ansimode)
             currpnt = ansi2n(ch , currline);
          else
             currpnt = (currline->len > lastindent) ? lastindent : currline->len;
          line_dirty = 0;
        }
        break;
      case Ctrl('B'):
      case KEY_PGUP:
        redraw_everything = currln;
        top_of_win = back_line(top_of_win, 22);
        currln = redraw_everything;
        currline = back_line(currline, 22);
        curr_window_line = getlineno();
        if (currpnt > currline->len)
          currpnt = currline->len;
        redraw_everything = YEA;
        line_dirty = 0;
        break;

      case KEY_PGDN:
      case Ctrl('F'):
        redraw_everything = currln;
        top_of_win = forward_line(top_of_win, 22);
        currln = redraw_everything;
        currline = forward_line(currline, 22);
        curr_window_line = getlineno();
        if (currpnt > currline->len)
          currpnt = currline->len;
        redraw_everything = YEA;
        line_dirty = 0;
        break;

      case KEY_END:
      case Ctrl('E'):
        trim(currline->data);
        currpnt = currline->len = strlen(currline->data);
        line_dirty = 1;
        break;

      case Ctrl(']'):   /* start of file */
        prevln = currln;
        prevpnt = currpnt;
        currline = top_of_win = firstline;
        currpnt = currln = curr_window_line = 0;
        redraw_everything = YEA;
        line_dirty = 0;
        break;

      case Ctrl('T'):           /* tail of file */
        prevln = currln;
        prevpnt = currpnt;
        top_of_win = back_line(lastline, 23);
        currline = lastline;
        curr_window_line = getlineno();
        currln = totaln;
        redraw_everything = YEA;
        currpnt = 0;
        line_dirty = 0;
        break;

      case KEY_HOME:
      case Ctrl('A'):
        currpnt = 0;
        line_dirty = 1;
        break;

      case KEY_INS:             /* Toggle insert/overwrite */
      case Ctrl('O'):
        if (blockln >= 0 && insert_character) {
           char ans[4];

           getdata(b_lines - 1, 0, "°Ï¶ô·L½Õ¥k²¾´¡¤J¦r¤¸(¹w³]¬°ªÅ¥Õ¦r¤¸)", ans, 4, DOECHO, 0);
           insert_c = (*ans) ? *ans : ' ';
        }
        insert_character ^= 1;
        line_dirty = 1;
        break;

      case Ctrl('H'):
      case '\177':              /* backspace */
        line_dirty = 1;
        if (my_ansimode) {
           my_ansimode = 0;
           clear();
           redraw_everything = YEA;
        }
        else {
           if (currpnt == 0)
           {
             textline *p;

             if (!currline->prev)
             {
               break;
             }
             line_dirty = 0;
             curr_window_line--;
             currln--;
             currline = currline->prev;
             currpnt = currline->len;
             redraw_everything = YEA;
             if (*killsp(currline->next->data) == '\0')
             {
               delete_line(currline->next);
               break;
             }
             p = currline;
             while (!join(p))
             {
               p = p->next;
               if (p == NULL)
               {
                 indigestion(2);
                 abort_bbs();
               }
             }
             break;
           }
           currpnt--;
           delete_char();
        }
        break;

      case Ctrl('D'):
      case KEY_DEL:             /* delete current character */
         line_dirty = 1;
        if (currline->len == currpnt)
        {
          textline *p = currline;

          while (!join(p))
          {
            p = p->next;
            if (p == NULL)
            {
              indigestion(2);
              abort_bbs();
            }
          }
          line_dirty = 0;
          redraw_everything = YEA;
        }
        else {
           delete_char();
           if (my_ansimode)
              currpnt = ansi2n(n2ansi(currpnt, currline),currline);
        }
        break;

      case Ctrl('Y'):           /* delete current line */
        currline->len = currpnt = 0;

      case Ctrl('K'):           /* delete to end of line */
        if (currline->len == 0)
        {
          textline *p = currline->next;

          if (!p)
          {
            p = currline->prev;
            if (!p)
            {
              break;
            }
            if (curr_window_line > 0)
            {
              curr_window_line--;
              currln--;
            }
          }
          if (currline == top_of_win)
            top_of_win = p;
          delete_line(currline);
          currline = p;
          redraw_everything = YEA;
          line_dirty = 0;
          break;
        }

        if (currline->len == currpnt)
        {
          textline *p = currline;

          while (!join(p))
          {
            p = p->next;
            if (p == NULL)
            {
              indigestion(2);
              abort_bbs();
            }
          }
          redraw_everything = YEA;
          line_dirty = 0;
          break;
        }
        currline->len = currpnt;
        currline->data[currpnt] = '\0';
        line_dirty = 1;
        break;
      }

      if (currln < 0)
        currln = 0;
      if (curr_window_line < 0)
      {
        curr_window_line = 0;
        if (!top_of_win->prev)
        {
          indigestion(6);
        }
        else
        {
          top_of_win = top_of_win->prev;
          rscroll();
        }
      }
      if (curr_window_line == b_lines)
      {
        curr_window_line = t_lines - 2;
        if (!top_of_win->next)
        {
          indigestion(7);
        }
        else
        {
          top_of_win = top_of_win->next;
          move(b_lines, 0);
          clrtoeol();
          scroll();
        }
      }
    }
    edit_margin = currpnt < SCR_WIDTH - 1 ? 0 : currpnt / 72 * 72;

    if (!redraw_everything)
    {
      if (edit_margin != last_margin)
      {
        last_margin = edit_margin;
        redraw_everything = YEA;
      }
      else
      {
         move(curr_window_line, 0);
         clrtoeol();
         if (my_ansimode)
           outs(currline->data);
         else
            edit_outs(&currline->data[edit_margin]);
         edit_msg();
      }
    }
  }
}
