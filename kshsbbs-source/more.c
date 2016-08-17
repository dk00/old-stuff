/*-------------------------------------------------------*/
/* more.c       ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : simple & beautiful ANSI/Chinese browser      */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


static char *more_help[] = {
  "\0�\\Ū�峹�\\����ϥλ���",
  "\01��в��ʥ\\����",
  "(��)                  �W���@��",
  "(��)(Enter)           �U���@��",
  "(^B)(PgUp)(BackSpace) �W���@��",
  "(��)(PgDn)(Space)     �U���@��",
  "(0)(g)(Home)          �ɮ׶}�Y",
  "($)(G) (End)          �ɮ׵���",
  "\01��L�\\����",
  "(/)                   �j�M�r��",
  "(n/N)                 ���ƥ�/�ϦV�j�M",
  "(:)                   ���ܬY��",
  "(f/b)                 ���ܤU/�W�g",
  "(F/B)                 ���ܦP�@�j�M�D�D�U/�W�g",
  "(a/A)                 ���ܦP�@�@�̤U/�W�g",
  "([/])                 �D�D���\\Ū �W/�U",
  "(t)                   �D�D���`�Ǿ\\Ū",
  "(^S)                  ��峹�s�ܫH�c",
  "(^V)                  �\\Ū�H��",
  "(q)(��)               ����",
  "(h)(H)(?)             ���U�����e��",
NULL};

int beep = 0;


static int
readln(fp, buf)
  FILE *fp;
  char *buf;
{
  register int ch, i, len, bytes, in_ansi;

  len = bytes = in_ansi = i = 0;
  while (len < 80 && i < ANSILINELEN && (ch = getc(fp)) != EOF)
  {
    bytes++;
    if (ch == '\n')
    {
      break;
    }
    else if (ch == '\t')
    {
      do
      {
        buf[i++] = ' ';
      } while ((++len & 7) && len < 80);
    }
    else if (ch == '\a')
    {
      beep = 1;
    }
    else if (ch == '\033')
    {
      if (showansi)
        buf[i++] = ch;
      in_ansi = 1;
    }
    else if (in_ansi)
    {
      if (showansi)
        buf[i++] = ch;
      if (!strchr("[0123456789;,", ch))
        in_ansi = 0;
    }
    else if (isprint2(ch))
    {
      len++;
      buf[i++] = ch;
    }
  }
  buf[i] = '\0';
  return bytes;
}


int
more(fpath, promptend)
  char *fpath;
  int promptend;
{
  extern char* strcasestr();
  static char *head[3] = {"�@��", "���D", "�ɶ�"};
  char *ptr, *word, buf[256];
  struct stat st;
  FILE *fp;
  usint pagebreak[MAXPAGES], pageno, lino;
  int line, ch, viewed, pos, numbytes;
  int header = 0;
  int local = 0;
  char search_char0;
  static char search_str[41];
  typedef char* (*FPTR)();
  static FPTR fptr;
  int searching = 0;
  int scrollup = 0;

  memset(pagebreak, 0, sizeof(pagebreak));
  if (*search_str)
     search_char0 = *search_str;
  *search_str = 0;
  if (!(fp = fopen(fpath, "r")))
    return -1;

  if (fstat(fileno(fp), &st))
    return -1;

  pagebreak[0] = pageno = viewed = line = pos = 0;
  clear();

  while ((numbytes = readln(fp, buf)) || (line == t_lines))
  {
    if (scrollup) {
       rscroll();
       move(0, 0);
    }
    if (numbytes)               /* �@���ƳB�z */
    {
      if (!viewed)              /* begin of file */
      {
        if (showansi)           /* header processing */
        {
          if (!strncmp(buf, str_author1, LEN_AUTHOR1))
          {
            line = 3;
            word = buf + LEN_AUTHOR1;
            local = 1;
          }
          else if (!strncmp(buf, str_author2, LEN_AUTHOR2))
          {
            line = 4;
            word = buf + LEN_AUTHOR2;
          }

          while (pos < line)
          {
            if (!pos && ((ptr = strstr(word, str_post1)) ||
                (ptr = strstr(word, str_post2))))
            {
              ptr[-1] = '\0';
              prints("[47;34m %s [44;37m%-53.53s[47;34m %.4s [44;37m%-13s[0m\n", head[0], word, ptr, ptr + 5);
            }
            else if (pos < 3)
              prints("[47;34m %s [44;37m%-72.72s[0m\n", head[pos], word);

            viewed += numbytes;
            numbytes = readln(fp, buf);
            pos++;
          }
          if (pos)
          {
            header = 1;
            prints("[36m%s[0m\n", msg_seperator);
            line = pos = 4;
          }
        }
        lino = pos;
        word = NULL;
      }

      /* ���B�z�ޥΪ� & �ި� */

      if ((buf[1] == ' ') && (buf[0] == ':' || buf[0] == '>'))
        word = "[36m";
      else if ((buf[0] == '�' && buf[1] == '�') || !strncmp(buf, "==>", 3))
        word = "[32m";

      if (word)
        outs(word);
      {
/*
woju
*/
        char msg[500], *pos;

        if (*search_str && (pos = fptr(buf, search_str))) {
           char SearchStr[41];
           char buf1[100], *pos1;

           strncpy(SearchStr, pos, strlen(search_str));
           SearchStr[strlen(search_str)] = 0;
           searching = 0;
           sprintf(msg, "%.*s[7m%s[0m", pos - buf, buf,
              SearchStr);
           while (pos = fptr(pos1 = pos + strlen(search_str), search_str)) {
              sprintf(buf1, "%.*s[7m%s[0m", pos - pos1, pos1, SearchStr);
              strcat(msg, buf1);
           }
           strcat(msg, pos1);
/* MH */
/* �� mhsin_prints (in mhsin.c) ���N kaede_prints */
/*           outs(kaede_prints(msg));*/
           outs(mhsin_prints(msg, 500));
/*    */
        }
        else {
/* MH */
/* �� mhsin_prints (in mhsin.c) ���N kaede_prints */
/*           outs(kaede_prints(buf));*/
           outs(mhsin_prints(buf, 255));
/*    */
        }
      }
      if (word) {
        outs("[0m");
        word = NULL;
      }
      outch('\n');

      if (beep)
      {
        bell();
        beep = 0;
      }

      if (line < b_lines)       /* �@����Ū�� */
        line++;

      if (line == b_lines && searching == -1) {
        if (pageno > 0)
           fseek(fp, viewed = pagebreak[--pageno], SEEK_SET);
        else
           searching = 0;
        lino = pos = line = 0;
        clear();
        continue;
      }

      if (scrollup) {
         move(line = b_lines, 0);
         clrtoeol();
         for (pos = 1; pos < b_lines; pos++)
            viewed += readln(fp, buf);
      }
      else if (pos == b_lines)  /* ���ʿù� */
        scroll();
      else
        pos++;


      if (!scrollup && ++lino >= b_lines && pageno < MAXPAGES - 1)
      {
        pagebreak[++pageno] = viewed;
        lino = 1;
      }

      if (scrollup) {
         lino = scrollup;
         scrollup = 0;
      }
      viewed += numbytes;       /* �֭pŪ�L��� */
    }
    else
      line = b_lines;           /* end of END */


    if (promptend && (!searching && line == b_lines || viewed == st.st_size))
    {
      /* Kaede ��n 100% �ɤ��� */
/*
      if (viewed == st.st_size && viewed - numbytes == pagebreak[1])
        continue;
*/
      move(b_lines, 0);
      if (viewed == st.st_size) {
         if (searching == 1)
            searching = 0;
/*
woju
*/
         prints("[0m[44m  �s�� P.%d(%d%%)  [31;47m  (h)[30m�D�U  [31m����[PgUp][PgDn][Home][End][30m��в���  [31m��[q][30m����  [0m", pageno,
(viewed * 100) / st.st_size);
      }
      else if (pageno == 1 && lino == 1) {
         if (searching == -1)
            searching = 0;
         prints("[0m[1;33;45m  �s�� P.%d(%d%%)  [0;31;47m  (h)[30m�D�U  [31m����[PgUp][PgDn][Home][End][30m��в���  [31m��[q][30m����  [0m",
pageno, (viewed * 100) / st.st_size);
      }
      else
         prints("[0m[0;34;46m  �s�� P.%d(%d%%)  [31;47m  (h)[30m�D�U  [31m����[PgUp][PgDn][Home][End][30m��в���  [31m��[q][30m����  [0m", pageno,
(viewed * 100) / st.st_size);

      while (line == b_lines || (line > 0 && viewed == st.st_size))
      {
        switch (ch = igetkey())
        {
        case ':': {
           char buf[10];
           int i = 0;

           getdata(b_lines - 1, 0, "Goto Page: ", buf, 5, DOECHO, 0);
           sscanf(buf, "%d", &i);
           if (0 < i && i <  MAXPAGES && (i == 1 || pagebreak[i - 1]))
              pageno = i - 1;
           else if (pageno)
              pageno--;
           lino = line = 0;
           break;
        }

        case '/': {
           char buf[100];
           char ans[4] = "n";

           *search_str = search_char0;
           sprintf(buf, "/[%s] ", search_str);
           getdata(b_lines - 1, 0, buf, buf, 40, DOECHO, 0);
           if (*buf)
              search_char0 = *strcpy(search_str, buf);

           if (*search_str) {
              searching = 1;
              if (getdata(b_lines - 1, 0, "�Ϥ��j�p�g(Y/N/Q)? [N] ", ans, 4, LCECHO, 0) && *ans == 'y')
                 fptr = strstr;
              else
                 fptr = strcasestr;
           }
           if (*ans == 'q')
              searching = 0;
           if (pageno)
              pageno--;
           lino = line = 0;
           break;
        }
        case 'n':
           if (*search_str) {
              searching = 1;
              if (pageno)
                 pageno--;
              lino = line = 0;
           }
           break;
        case 'N':
           if (*search_str) {
              searching = -1;
              if (pageno)
                 pageno--;
              lino = line = 0;
           }
           break;
        case 'r':
        case 'R':
        case 'Y':
           fclose(fp);
           return 7;
        case 'y':
           fclose(fp);
           return 8;
        case 'A':
           fclose(fp);
           return 9;
        case 'a':
           fclose(fp);
           return 10;
        case 'F':
           fclose(fp);
           return 11;
        case 'B':
           fclose(fp);
           return 12;
        case KEY_LEFT:
          fclose(fp);
          return 6;
        case 'q':
          fclose(fp);
          return 0;
        case 'b':
           fclose(fp);
           return 1;
        case 'f':
           fclose(fp);
           return 3;
        case ']':       /* Kaede ���F�D�D�\Ū��K */
           fclose(fp);
           return 4;
        case '[':       /* Kaede ���F�D�D�\Ū��K */
           fclose(fp);
           return 2;
        case '=':       /* Kaede ���F�D�D�\Ū��K */
           fclose(fp);
           return 5;
        case Ctrl('F'):
        case KEY_PGDN:
          line = 1;
          break;
        case 't':
          if (viewed == st.st_size) {
             fclose(fp);
             return 4;
          }
          line = 1;
          break;
        case ' ':
          if (viewed == st.st_size) {
             fclose(fp);
             return 3;
          }
          line = 1;
          break;
        case KEY_RIGHT:
          if (viewed == st.st_size) {
             fclose(fp);
             return 0;
          }
          line = 1;
          break;
        case '\r':
        case '\n':
        case KEY_DOWN:
          if (viewed == st.st_size ||
              promptend == 2 && (ch == '\r' || ch == '\n')) {
             fclose(fp);
             return 3;
          }
          line = t_lines - 2;
          break;

        case '$':
        case 'G':
        case KEY_END:
          line = t_lines;
          break;

        case '0':
        case 'g':
        case KEY_HOME:
          pageno = line = 0;
          break;

        case 'h':
        case 'H':
        case '?':
          /* Kaede Buggy ... */
          show_help(more_help);
          if (pageno)
             pageno--;
          lino = line = 0;
          break;

        case 'E':
          if (strcmp(fpath, "etc/ve.hlp")) {
             fclose(fp);
             vedit(fpath, HAS_PERM(PERM_SYSOP) ? 0 : 2);
             return 0;
          }
          break;
/* MH */
        case Ctrl('R'):
         mh_throw_water_ball();
         if(pageno)
            pageno --;
         lino = line = 0;
         break;
/*    */          

        case KEY_ESC:
           if (KEY_ESC_arg == 'n') {
              edit_note();
              if (pageno)
                 pageno--;
              lino = line = 0;
           }
           else if (KEY_ESC_arg == 'c')
              capture_screen();
           break;

        case Ctrl('U'):
           t_users();
           if (pageno)
              pageno--;
           lino = line = 0;
           break;

        case Ctrl('V'):
           m_read();
           if (pageno)
              pageno--;
           lino = line = 0;
           break;

        case Ctrl('I'):
           t_idle();
           if (pageno)
              pageno--;
           lino = line = 0;
           break;

        case KEY_UP:
           line = -1;
           break;

        case Ctrl('S'): {
           char genbuf[200];
           fileheader mhdr;

           sethomepath(genbuf, cuser.userid);
           stampfile(genbuf, &mhdr);
           Link(fpath, genbuf);
           strcpy(mhdr.owner, cuser.userid);
           strncpy(mhdr.title, vetitle, TTLEN);
           mhdr.savemode = '\0';
           mhdr.filemode = FILE_READ;
           sethomedir(genbuf, cuser.userid);
           append_record(genbuf, &mhdr, sizeof(mhdr));
           break;
        }
        case Ctrl('B'):
        case KEY_PGUP:
          if (pageno > 1)
          {
            if (lino < 2)
               pageno -= 2;
            else
               pageno--;
            lino = line = 0;
          }
          else if (pageno && lino > 1)
            pageno = line = 0;
          break;
        case Ctrl('H'):
          if (pageno > 1)
          {
            if (lino < 2)
               pageno -= 2;
            else
               pageno--;
            lino = line = 0;
          }
          else if (pageno && lino > 1)
            pageno = line = 0;
/*
woju
*/
          else {
             fclose(fp);
             return 1;
          }
        }
      }

      if (line > 0)
      {
        move(b_lines, 0);
        clrtoeol();
        refresh();
      }
      else if (line < 0) {                      /* Line scroll up */
         if (pageno <= 1) {
            if (lino == 1 || !pageno) {
               fclose(fp);
               return 1;
            }
            if (header && lino <= 5) {
               fseek(fp, viewed = pagebreak[scrollup = lino = pageno = 0] = 0, SEEK_SET);
               clear();
            }
         }
         if (pageno && lino > 1 + local) {
            line =  (lino - 2) - local;
            if (pageno > 1 && viewed == st.st_size)
               line += local;
            scrollup = lino - 1;
            fseek(fp, viewed = pagebreak[pageno - 1], SEEK_SET);
            while (line--)
               viewed += readln(fp, buf);
         }
         else if (pageno > 1) {
            scrollup = b_lines - 1;
            line = (b_lines - 2) - local;
            fseek(fp, viewed = pagebreak[--pageno - 1], SEEK_SET);
            while (line--)
               viewed += readln(fp, buf);
         }
         line = pos = 0;
      }
      else
      {
        pos = 0;
        fseek(fp, viewed = pagebreak[pageno], SEEK_SET);
        clear();
      }
    }
  }

  fclose(fp);
  if (promptend)
  {
    pressanykey();
    clear();
  }
  else
    outs(reset_color);
  return 0;
}

