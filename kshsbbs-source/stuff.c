/*-------------------------------------------------------*/
/* stuff.c      ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : utility routines                             */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


/* ----------------------------------------------------- */
/* set file path for boards/user home                    */
/* ----------------------------------------------------- */

char *str_home_file = "home/%s/%s";
char *str_board_file = "boards/%s/%s";
char *str_dotdir = ".DIR";


void
sethomepath(buf, userid)
  char *buf, *userid;
{
  sprintf(buf, "home/%s", userid);
}


void
sethomedir(buf, userid)
  char *buf, *userid;
{
  sprintf(buf, str_home_file, userid, str_dotdir);
}


void
sethomeman(buf, userid)
  char *buf, *userid;
{
  sprintf(buf, str_home_file, userid, "man");
}


void
sethomefile(buf, userid, fname)
  char *buf, *userid, *fname;
{
  sprintf(buf, str_home_file, userid, fname);
}


void
setuserfile(buf, fname)
  char *buf, *fname;
{
  sprintf(buf, str_home_file, cuser.userid, fname);
}


void
setapath(buf, boardname)
  char *buf, *boardname;
{
  sprintf(buf, "man/boards/%s", boardname);
}


/*
    ===== Added by mgtsai, Sep 10th, '96 =====
*/
void
setadir(buf, path)
  char *buf, *path;
{
  sprintf(buf, "%s/%s", path, str_dotdir);
}
/* ===== end ===== */


void
setbpath(buf, boardname)
  char *buf, *boardname;
{
  sprintf(buf, "boards/%s", boardname);
}


void
setbdir(buf, boardname)
  char *buf, *boardname;
{
  sprintf(buf, str_board_file, boardname,
    currmode & MODE_ETC ? ".ETC" : currmode & MODE_DIGEST ? fn_mandex : str_dotdir);
}


void
setbfile(buf, boardname, fname)
  char *buf, *boardname, *fname;
{
  sprintf(buf, str_board_file, boardname, fname);
}


void
setdirpath(buf, direct, fname)
  char *buf, *direct, *fname;
{
  strcpy(buf, direct);
  direct = strrchr(buf, '/');
  strcpy(direct + 1, fname);
}


char *
subject(title)
  char *title;
{
  if (!strncasecmp(title, str_reply, 3))
  {
    title += 3;
    if (*title == ' ')
      title++;
  }
  return title;
}


/* ----------------------------------------------------- */
/* 字串轉換檢查函數                                      */
/* ----------------------------------------------------- */

/* Case Independent strncmp */

int
ci_strncmp(s1, s2, n)
  register char *s1, *s2;
  register int n;
{
  register char c1, c2;
  register int diff;

  do
  {
    c1 = *s1++;
    if (c1 >= 'A' && c1 <= 'Z')
      c1 |= 32;

    c2 = *s2++;
    if (c2 >= 'A' && c2 <= 'Z')
      c2 |= 32;

    if (diff = c1 - c2)
      return (diff);
  } while (--n && c1);

  return 0;
}


void
str_lower(t, s)
  char *t, *s;
{
  register uschar ch;

  do
  {
    ch = *s++;
    *t++ = char_lower(ch);
  } while (ch);
}


int
strstr_lower(str, tag)
  char *str, *tag;              /* tag : lower-case string */
{
  char buf[STRLEN];
  char buf1[STRLEN];

  str_lower(buf, str);
  str_lower(buf1, tag);
  return (int) strstr(buf, buf1);
}


char*
trim(buf)                       /* remove trailing space */
  char *buf;
{
  char *p = buf;

  while (*p)
    p++;
  while (--p >= buf)
  {
    if (*p == ' ')
      *p = '\0';
    else
      break;
  }
  return buf;
}


/* ----------------------------------------------------- */
/* 字串檢查函數：英文、數字、檔名、E-mail address        */
/* ----------------------------------------------------- */


#ifdef BIT8
int
isprint2(ch)
  char ch;
{
  return ((ch & 0x80) ? 1 : isprint(ch));
}
#endif


int
not_alpha(ch)
  register char ch;
{
  return (ch < 'A' || (ch > 'Z' && ch < 'a') || ch > 'z');
}


int
not_alnum(ch)
  register char ch;
{
  return (ch < '0' || (ch > '9' && ch < 'A') ||
    (ch > 'Z' && ch < 'a') || ch > 'z');
}


int
invalid_fname(str)
  char *str;
{
  char ch;

  if (strspn(str, ".") == strlen(str))
     return 1;
  while (ch = *str++)
  {
    if (not_alnum(ch) && !strchr("@[]-._", ch))
      return 1;
  }
  return 0;
}


int
invalid_pname(str)
  char *str;
{
  char *p1, *p2, *p3;

  p1 = str;
  while (*p1) {
     if (!(p2 = strchr(p1, '/')))
        p2 = str + strlen(str);
     if (p1 + 1 > p2 || p1 + strspn(p1, ".") == p2)
        return 1;
     for (p3 = p1; p3 < p2; p3++)
        if (not_alnum(*p3) && !strchr("@[]-._", *p3))
          return 1;
     p1 = p2 + (*p2 ? 1 : 0);
  }
  return 0;
}



int
valid_ident(ident)
  char *ident;
{
  static char *invalid[] = {"unknown@", "root@", "gopher@", "bbs@",
  "@bbs", "guest@", "@ppp", "@slip", NULL};
  char buf[128];
  int i;

  str_lower(buf, ident);
  for (i = 0; invalid[i]; i++)
    if (strstr(buf, invalid[i]))
      return 0;
  return 1;
}


int
is_BM(list)
  char *list;                   /* 板主：BM list */
{
  register int ch, len;

  ch = list[0];
  if ((ch > ' ') && (ch < 128))
  {
    len = strlen(cuser.userid);
    do
    {
      if (!ci_strncmp(list, cuser.userid, len))
      {
        ch = list[len];
        if ((ch == 0) || (ch == '/') || (ch == ']'))
          return 1;
      }
      while (ch = *list++)
      {
        if (ch == '/')
          break;
      }
    } while (ch);
  }
  return 0;
}


/*
woju
*/
int
userid_is_BM(userid, list)
  char *userid, *list;                  /* 板主：BM list */
{
  register int ch, len;

  ch = list[0];
  if ((ch > ' ') && (ch < 128))
  {
    len = strlen(userid);
    do
    {
      if (!ci_strncmp(list, userid, len))
      {
        ch = list[len];
        if ((ch == 0) || (ch == '/') || (ch == ']'))
          return 1;
      }
      while (ch = *list++)
      {
        if (ch == '/')
          break;
      }
    } while (ch);
  }
  return 0;
}


int
is_watched(name)
  char *name;
{
  char buf[40];
  FILE *list;

  if (list = fopen("watching", "r"))
  {
    while (fgets(buf, 40, list))
    {
      buf[strlen(buf) - 1] = '\0';
      if (!strcmp(buf, name))
        return 1;
    }
    fclose(list);
  }
/*
woju
  else
    pressanykey();
*/
  return 0;
}


/* ----------------------------------------------------- */
/* 檔案檢查函數：檔案、目錄、屬於                        */
/* ----------------------------------------------------- */


int
dashl(fname)
  char *fname;
{
  struct stat st;

  return (lstat(fname, &st) == 0 && S_ISLNK(st.st_mode));
}


dashf(fname)
  char *fname;
{
  struct stat st;

  return (stat(fname, &st) == 0 && S_ISREG(st.st_mode));
}


int
dashd(fname)
  char *fname;
{
  struct stat st;

  return (stat(fname, &st) == 0 && S_ISDIR(st.st_mode));
}


int
belong(filelist, key)
  char *filelist;
  char *key;
{
  FILE *fp;
  int rc = 0;

  if (fp = fopen(filelist, "r"))
  {
    char buf[STRLEN], *ptr;

    while (fgets(buf, STRLEN, fp))
    {
      if ((ptr = strtok(buf, str_space)) && !strcasecmp(ptr, key))
      {
        rc = 1;
        break;
      }
    }
    fclose(fp);
  }
  return rc;
}


char*
Belong(char* file, char* key, char* sep)
{
   FILE* fp;

   if (fp = fopen(file, "r")) {
      static char ans[STRLEN];
      char Key[STRLEN], Ans[STRLEN];
      char* ptr;

      strncpy(Key, key, STRLEN - 1);
      Key[STRLEN - 1] = 0;
      if (!strtok(Key, sep))
         return 0;
      while (fgets(ans, STRLEN, fp))
      {
         strcpy(Ans, ans);
         if ((ptr = strtok(Ans, sep)) && !strcasecmp(ptr, Key)) {
            fclose(fp);
            strtok(ans, str_space);
            return ans;
         }
      }
      fclose(fp);
   }
   return 0;
}

char *
Cdate(clock)
  time_t *clock;
{
  static char foo[22];
  struct tm *mytm = localtime(clock);

  strftime(foo, 22, "%D %T %a", mytm);
  return (foo);
}


char *
Cdatelite(clock)
  time_t *clock;
{
  static char foo[18];
  struct tm *mytm = localtime(clock);

  strftime(foo, 18, "%D %T", mytm);
  return (foo);
}


#ifdef  HAVE_CTIME
char *
Ctime(clock)
  time_t *clock;
{
  char *foo;
  char *ptr = ctime(clock);

  if (foo = strrchr(ptr, '\n'))
    *foo = '\0';
  return (ptr);
}
#endif


void
pressanykey()
{
  int ch;

  outmsg("[0;37;45;1m                        ● 請按 [33m(Space/Return)[37m 繼續 ●                       [0m");
  do
  {
    ch = igetkey();
    if (ch == KEY_ESC && KEY_ESC_arg == 'c')
       capture_screen();
  } while ((ch != ' ') && (ch != KEY_LEFT) && (ch != '\r') && (ch != '\n'));
  move(b_lines, 0);
  clrtoeol();
  refresh();
}

/* MH */
void
mh_pressanykey(char *msg)
{
  int ch;
  char buf[512];

  sprintf(buf, "[37;45;1m%s[0m", msg);
  outmsg(buf);
  do
  {
    ch = igetkey();
    if (ch == KEY_ESC && KEY_ESC_arg == 'c')
       capture_screen();
  } while ((ch != ' ') && (ch != KEY_LEFT) && (ch != '\r') && (ch != '\n'));
  move(b_lines, 0);
  clrtoeol();
  refresh();
}
/*    */

void
bell()
{
  char sound[3], *ptr;

  ptr = sound;
  memset(ptr, Ctrl('G'), sizeof(sound));
  write(1, ptr, sizeof(sound));
}

int
search_num(ch, max)
{
  int clen = 1;
  int x, y;
  extern unsigned char scr_cols;
  char genbuf[10];

  outmsg("[7m 跳至第幾項：[0m");
  outc(ch);
  genbuf[0] = ch;
  getyx(&y, &x);
  x--;
  while ((ch = igetch()) != '\r')
  {
    if (ch == 'q' || ch == 'e')
      return -1;
    if (ch == '\n')
      break;
    if (ch == '\177' || ch == Ctrl('H'))
    {
      if (clen == 0)
      {
        bell();
        continue;
      }
      clen--;
      move(y, x + clen);
      outc(' ');
      move(y, x + clen);
      continue;
    }
    if (!isdigit(ch))
    {
      bell();
      continue;
    }
    if (x + clen >= scr_cols || clen >= 6)
    {
      bell();
      continue;
    }
    genbuf[clen++] = ch;
    outc(ch);
  }
  genbuf[clen] = '\0';
  move(b_lines, 0);
  clrtoeol();
  if (genbuf[0] == '\0')
    return -1;
  clen = atoi(genbuf);
  if (clen == 0)
    return 0;
  if (clen > max)
    return max;
  return clen - 1;
}


void
stand_title(title)
  char *title;
{
  clear();
  prints("[1;37;46m【 %s 】[0m\n", title);
}


/* opus : cursor position */

void
cursor_show(row, column)
  int row, column;
{
  move(row, column);
  outs(STR_CURSOR);
  move(row, column + 1);
}


void
cursor_clear(row, column)
  int row, column;
{
  move(row, column);
  outs(STR_UNCUR);
}


int
cursor_key(row, column)
  int row, column;
{
  int ch;

  cursor_show(row, column);
  ch = igetkey();
  move(row, column);
  outs(STR_UNCUR);
  return ch;
}


void
printdash(mesg)
  char *mesg;
{
  int head = 0, tail;

  if (mesg)
    head = (strlen(mesg) + 1) >> 1;

  tail = head;

  while (head++ < 38)
    outch('-');

  if (tail)
  {
    outch(' ');
    outs(mesg);
    outch(' ');
  }

  while (tail++ < 38)
    outch('-');
  outch('\n');
}

void
show_help(helptext)
  char *helptext[];
{
  char *str;
  int i;

  clear();
  for (i = 0; (str = helptext[i]); i++)
  {
    if (*str == '\0')
      prints("[1m【 %s 】[0m\n", str + 1);
    else if (*str == '\01')
      prints("\n[36m【 %s 】[m\n", str + 1);
    else
      prints("        %s\n", str);
  }
  pressanykey();
}

char*
mono(char* s)
{
   int i, j;
   static char ans[200];

   for (i = j = 0; s[i] && j < 199; i++)
      if (s[i] == KEY_ESC)
         while (s[++i] && s[i] != 'm')
            ;
      else
         ans[j++] = s[i];
   ans[j] = 0;

   return ans;
}

