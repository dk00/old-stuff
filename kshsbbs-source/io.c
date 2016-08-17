/*-------------------------------------------------------*/
/* io.c         ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : basic console/screen/keyboard I/O routines   */
/* create : 95/02/28                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/

#include "bbs.h"

#ifdef AIX
#include <sys/select.h>
#endif

#ifdef  Linux
#define OBUFSIZE  (2048)
#define IBUFSIZE  (128)
#else
#define OBUFSIZE  (4096)
#define IBUFSIZE  (256)
#endif

#define INPUT_ACTIVE    0
#define INPUT_IDLE      1

static char outbuf[OBUFSIZE];
static int obufsize = 0;

static char inbuf[IBUFSIZE];
static int ibufsize = 0;
static int icurrchar = 0;

static int i_mode = INPUT_ACTIVE;

extern int dumb_term;


/* ----------------------------------------------------- */
/* �w����ܰʺA�ݪO                                      */
/* ----------------------------------------------------- */


#ifdef  HAVE_MOVIE
#define STAY_TIMEOUT    (30*60)
extern void movie();

static void
hit_alarm_clock()
{
  static int stay_time = 0;
  static int idle_time = 0;

  if (currutmp->pid != currpid)
  {
    setup_utmp(XMODE);          /* ���s�t�m shm */
  }

  if (i_mode == INPUT_IDLE)
  {
    idle_time += MOVIE_INT;
    if (!(PERM_HIDE(currutmp) || currutmp->mode == MAILALL)
        && idle_time > IDLE_TIMEOUT)
    {
      clear();
      fprintf(stderr, "�W�L���m�ɶ��IBooting...\n");
      abort_bbs();
    }
  }
  else
  {
    currutmp->uptime = time(NULL);
    idle_time = 0;
    i_mode = INPUT_IDLE;
  }

  if (currstat && (currstat < CLASS  || currstat == MAILALL))
    movie(0);
  alarm(MOVIE_INT);

  stay_time += MOVIE_INT;
/* MH */
  if (chkmail(0) && stay_time > 10 * 60) /* ���n�b�I���� */
/*  if (chkmail(0) && stay_time > 10 * 60 || stay_time > STAY_TIMEOUT)*/
/*    */
  {
    /* �b�o�̴��� user �𮧤@�U */
    char *msg[7] = {"�����y, �|�|��, �ܤf��....",
                    "�z�w�g���F�b�Ӥp���o! �_�Ӭ��ʤ@�U�a!",
                    "���S���H���L�A�ܦ��y�O?",
                    "�A���U�h�n�o���H�F��~~~",
                    "���S�����n���Ʊ��ѤF�B�z�O?",
                    "�ΡE�\\�E��E��",
                    "��! ����!!!"};
/*
woju
*/
    time_t now = time(0);

    char buf[100];
    int i = rand() % 7;

    sprintf(currmsg, "[1;33;41m[%s] %s[m", Cdate(&now),
       chkmail(0) ? "�H�c���٦��S�ݹL���H�@!" : msg[i]);
/*
woju
*/
    if (chkmail(0))
       kill(currpid, SIGUSR2);
    stay_time = 0;
  }
/*
  if (idle_time > IDLE_TIMEOUT - 60)
  {
    sprintf(currmsg, "[1;5;37;41mĵ�i�G�z�w���m�L�[�A"
                       "�Y�L�^���A�t�ΧY�N�����I�I[m");
    kill(currpid, SIGUSR2);
  }
*/
}


void
init_alarm()
{
  alarm(0);
  signal(SIGALRM, hit_alarm_clock);
  alarm(MOVIE_INT);
}

#else                           /* HAVE_MOVIE */

static void
hit_alarm_clock()
{
  if (HAS_PERM(PERM_NOTIMEOUT) || PERM_HIDE(currutmp) || currstat == MAILALL)
    return;
  if (i_mode == INPUT_IDLE)
  {
    clear();
    fprintf(stderr, "�W�L���m�ɶ��IBooting...\n");
    kill(currpid, SIGHUP);
  }
  i_mode = INPUT_IDLE;
  alarm(IDLE_TIMEOUT);
}


void
init_alarm()
{
  signal(SIGALRM, hit_alarm_clock);
  alarm(IDLE_TIMEOUT);
}
#endif                          /* HAVE_MOVIE */


/* ----------------------------------------------------- */
/* output routines                                       */
/* ----------------------------------------------------- */


oflush()
{
  if (obufsize)
  {
    write(1, outbuf, obufsize);
    obufsize = 0;
  }
}


output(s, len)
  char *s;
{
  /* Invalid if len >= OBUFSIZE */

  if (obufsize + len > OBUFSIZE)
  {
    write(1, outbuf, obufsize);
    obufsize = 0;
  }
  memcpy(outbuf + obufsize, s, len);
  obufsize += len;
}


void
ochar(c)
{
  if (obufsize > OBUFSIZE - 1)
  {
    write(1, outbuf, obufsize);
    obufsize = 0;
  }
  outbuf[obufsize++] = c;
}


/* ----------------------------------------------------- */
/* input routines                                        */
/* ----------------------------------------------------- */


static int i_newfd = 0;
static struct timeval i_to, *i_top = NULL;
static int (*flushf) () = NULL;


void
add_io(fd, timeout)
  int fd;
  int timeout;
{
  i_newfd = fd;
  if (timeout)
  {
    i_to.tv_sec = timeout;
    i_to.tv_usec = 0;
    i_top = &i_to;
  }
  else
    i_top = NULL;
}


void
add_flush(flushfunc)
  int (*flushfunc) ();
{
  flushf = flushfunc;
}


int
num_in_buf()
{
  return icurrchar - ibufsize;
}


int
igetch()
{
  int ch;

  for (;;)
  {
    if (ibufsize == icurrchar)
    {
      fd_set readfds;
      struct timeval to;

      to.tv_sec = to.tv_usec = 0;
      FD_ZERO(&readfds);
      FD_SET(0, &readfds);
      if (i_newfd)
        FD_SET(i_newfd, &readfds);
      if ((ch = select(FD_SETSIZE, &readfds, NULL, NULL, &to)) <= 0)
      {
        if (flushf)
          (*flushf) ();

        if (dumb_term)
          oflush();
        else
          refresh();

        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        if (i_newfd)
          FD_SET(i_newfd, &readfds);

        while ((ch = select(FD_SETSIZE, &readfds, NULL, NULL, i_top)) < 0)
        {
          if (errno == EINTR)
            continue;
          else
          {
            perror("select");
            return -1;
          }
        }
        if (ch == 0)
          return I_TIMEOUT;
      }
      if (i_newfd && FD_ISSET(i_newfd, &readfds))
        return I_OTHERDATA;

      while ((ibufsize = read(0, inbuf, IBUFSIZE)) <= 0)
      {
        if (ibufsize == 0)
          longjmp(byebye, -1);
        if (ibufsize < 0 && errno != EINTR)
          longjmp(byebye, -1);
      }
      icurrchar = 0;
    }

    i_mode = INPUT_ACTIVE;
    ch = inbuf[icurrchar++];
/*
woju
already processed at hit_alarm_clock()
*/
    if (!dumb_term)
       currutmp->uptime = time(0);
    if (ch != Ctrl('L'))
      return (ch);
    redoscr();
  }
}


char* phone_char(char c)
{
   switch (c) {
          case '1':
             return "�t";
          case 'q':
             return "�u";
          case 'a':
             return "�v";
          case 'z':
             return "�w";
          case '2':
             return "�x";
          case 'w':
             return "�y";
          case 's':
             return "�z";
          case 'x':
             return "�{";
          case 'e':
             return "�|";
          case 'd':
             return "�}";
          case 'c':
             return "�~";
          case 'r':
             return "��";
          case 'f':
             return "��";
          case 'v':
             return "��";
          case '5':
             return "��";
          case 't':
             return "��";
          case 'g':
             return "��";
          case 'b':
             return "��";
          case 'y':
             return "��";
          case 'h':
             return "��";
          case 'n':
             return "��";
          case 'u':
             return "��";
          case 'j':
             return "��";
          case 'm':
             return "��";
          case '8':
             return "��";
             break;
          case 'i':
             return "��";
          case 'k':
             return "��";
          case ',':
             return "��";
          case '9':
             return "��";
          case 'o':
             return "��";
          case 'l':
             return "��";
          case '.':
             return "��";
          case '0':
             return "��";
          case 'p':
             return "��";
          case ';':
             return "��";
          case '/':
             return "��";
          case '-':
             return "��";
          case '6':
             return "��";
          case '3':
             return "��";
          case '4':
             return "��";
          case '7':
             return "��";
   }
  return 0;
}


#if 0
getdata(line, col, prompt, buf, len, echo, ans)
  int line, col;
  char *prompt, *buf, *ans;
  int len, echo;
{
  register int ch;
  int clen;
  int x, y;
  extern unsigned char scr_cols;
#define MAXLASTCMD 6
  static char lastcmd[MAXLASTCMD][80];

  if (prompt)
  {
    move(line, col);
    clrtoeol();
    if (strchr(prompt, KEY_ESC))
       edit_outs(prompt);
    else
       outs(prompt);
  }
  else
    clrtoeol();

  if (dumb_term || !echo)
  {
    len--;
    clen = 0;
    while ((ch = igetch()) != '\r')
    {
      if (ch == '\n')
        break;

      if (ch == '\177' || ch == Ctrl('H'))
      {
        if (!clen)
        {
          bell();
          continue;
        }
        clen--;
        if (echo)
        {
          ochar(Ctrl('H'));
          ochar(' ');
          ochar(Ctrl('H'));
        }
        continue;
      }

#ifdef BIT8
      if (!isprint2(ch))
#else
      if (!isprint(ch))
#endif

      {
        if (echo)
          bell();
        continue;
      }
      if (clen >= len)
      {
        if (echo)
          bell();
        continue;
      }
      buf[clen++] = ch;
      if (echo)
        ochar(ch);
    }
    buf[clen] = '\0';
    outc('\n');
    oflush();
  }
  else
  {
   int cmdpos = MAXLASTCMD -1;
   int currchar = 0;
   int phone_mode = 0;
   int keydown;
   int dirty;
   char* pstr;

    getyx(&y, &x);
    standout();
    for (clen = len--; clen; clen--)
      outc(' ');
    standend();

    if (ans) {
       int i;

       strncpy(buf, ans, len);
       buf[len] = 0;
       for (i = strlen(buf) + 1; i < len; i++)
          buf[i] = 0;
       move(y, x);
       edit_outs(buf);
       clen = currchar = strlen(buf);

    }
    else
       memset(buf, 0, len);

    dirty = 0;
    while (move(y, x + currchar), (ch = igetkey()) != '\r')
    {
/*
woju
*/
       keydown = 0;
       switch (ch) {
       case KEY_DOWN:
       case Ctrl('N'):
          keydown = 1;
       case Ctrl('P'):
       case KEY_UP: {
          int i;

          if (clen && dirty) {
             for (i = MAXLASTCMD - 1; i; i--)
                strcpy(lastcmd[i], lastcmd[i - 1]);
             strncpy(lastcmd[0], buf, len);
          }

          i = cmdpos;
          do {
             if (keydown)
                --cmdpos;
             else
                ++cmdpos;
             if (cmdpos < 0)
                cmdpos = MAXLASTCMD - 1;
             else if (cmdpos == MAXLASTCMD)
                cmdpos = 0;
          } while (cmdpos != i && (!*lastcmd[cmdpos]
                   || !strncmp(buf, lastcmd[cmdpos], len)));
          if (cmdpos == i)
             continue;

          strncpy(buf, lastcmd[cmdpos], len);
          buf[len] = 0;

          move(y, x);                   /* clrtoeof */
          for (i = 0; i <= clen; i++)
             outc(' ');
          move(y, x);

          edit_outs(buf);
          clen = currchar = strlen(buf);
          dirty = 0;
          continue;
       }
       case KEY_LEFT:
          if (currchar)
             --currchar;
          continue;
       case KEY_RIGHT:
          if (buf[currchar])
             ++currchar;
          continue;
       case KEY_ESC:
           if (KEY_ESC_arg == 'p')
              phone_mode ^= 1;
           else if (KEY_ESC_arg == 'c')
              capture_screen();
           else if (KEY_ESC_arg == 'n')
              scr_exec(edit_note);
           else if (KEY_ESC == 'U' && currstat != IDLE  &&
               !(currutmp->mode == 0 &&
                 (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3)))
              scr_exec(t_users);
           continue;
       }

      if (ch == '\n' || ch == '\r')
         break;

/* MH */
/* */
      if(ch == Ctrl('U') && (currutmp->mode == 0 && currutmp->chatid[0] == 3))
      {
          return MH_UP;
      }
      if(ch == Ctrl('D') && (currutmp->mode == 0 && currutmp->chatid[0] == 3))
      {
          return MH_DOWN;
      }
/*    */
      
/* MH */
      if (ch == Ctrl('R'))
      {
        if(!(currutmp->mode == 0 &&
            (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3)))
        {
         extern screenline* big_picture;
         screenline* screen0 = calloc(t_lines, sizeof(screenline));

         memcpy(screen0, big_picture, t_lines * sizeof(screenline));

         mh_throw_water_ball();
         memcpy(big_picture, screen0, t_lines * sizeof(screenline));
         free(screen0);
         redoscr();
         continue;
        }
        else if(currutmp->mode == 0 && currutmp->chatid[0] == 2 && currstat == ROWB)
        {
/*         extern screenline* big_picture;
         screenline* screen0 = calloc(t_lines, sizeof(screenline));

         memcpy(screen0, big_picture, t_lines * sizeof(screenline));

         mh_throw_water_ball();
         memcpy(big_picture, screen0, t_lines * sizeof(screenline));
         free(screen0);
         redoscr();
         return 0;*/
         return MH_CTRLR;
        }
      }
/*    */

      if (ch == Ctrl('I') && currstat != IDLE &&
          !(currutmp->mode == 0 &&
            (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3))) {
         scr_exec(t_idle);
         continue;
      }
      if (ch == Ctrl('B')) {
         scr_exec(m_read);
         continue;
      }
      if (ch == '\177' || ch == Ctrl('H'))
      {
        if (currchar) {
           int i;

           currchar--;
           clen--;
           for (i = currchar; i <= clen; i++)
              buf[i] = buf[i + 1];
           move(y, x + clen);
           outc(' ');
           move(y, x);
           edit_outs(buf);
           dirty = 1;
        }
        continue;
      }
      if (ch == Ctrl('Y')) {
         int i;

         buf[0] = 0;
         currchar = 0;
         move(y, x);                    /* clrtoeof */
         for (i = 0; i < clen; i++)
            outc(' ');
         clen = 0;
         continue;
      }
      if (ch == Ctrl('D')) {
        if (buf[currchar]) {
           int i;

           clen--;
           for (i = currchar; i <= clen; i++)
              buf[i] = buf[i + 1];
           move(y, x + clen);
           outc(' ');
           move(y, x);
           edit_outs(buf);
           dirty = 1;
        }
        continue;
      }
      if (ch == Ctrl('K')) {
         int i;

         buf[currchar] = 0;
         move(y, x + currchar);
         for (i = currchar; i < clen; i++)
            outc(' ');
         clen = currchar;
         dirty = 1;
         continue;
      }
      if (ch == Ctrl('A')) {
         currchar = 0;
         continue;
      }
      if (ch == Ctrl('E')) {
         currchar = clen;
         continue;
      }


      if (!(phone_mode && (pstr = phone_char(ch)) || isprint2(ch) || ch == Ctrl('U') && HAS_PERM(PERM_SYSOP)))
      {
        continue;
      }
      if (clen + (phone_mode && pstr) >= len || x + clen >= scr_cols)
      {
        continue;
      }
/*
woju
*/
      if (buf[currchar]) {               /* insert */
         int i;

         for (i = currchar; buf[i] && i + (phone_mode && pstr) < len && i + (phone_mode && pstr) < 80; i++)
            ;
         buf[i + 1 + (phone_mode && pstr)] = 0;
         for (; i > currchar; i--)
            buf[i + (phone_mode && pstr)] = buf[i - 1];
      }
      else                              /* append */
         buf[currchar + 1 + (phone_mode && pstr)] = '\0';
      if (ch == Ctrl('U'))
         ch = KEY_ESC;
      if (phone_mode && pstr) {
          buf[currchar] = pstr[0];
          buf[currchar + 1] = pstr[1];
      }
      else
         buf[currchar] = ch;
      move(y, x + currchar);
      edit_outs(buf + currchar);
      currchar++;
      currchar += phone_mode && pstr;
      clen++;
      clen += phone_mode && pstr;
      dirty = 1;
    }
    buf[clen] = '\0';
    if (clen > 1) {
       for (cmdpos = MAXLASTCMD - 1; cmdpos; cmdpos--)
          strcpy(lastcmd[cmdpos], lastcmd[cmdpos - 1]);
       strncpy(lastcmd[0], buf, len);
    }
    if (echo) {
      move(y, x + clen);
      outc('\n');
    }
    refresh();
  }
  if ((echo == LCECHO) && ((ch = buf[0]) >= 'A') && (ch <= 'Z'))
    buf[0] = ch | 32;
  return clen;
}

/* MH */
mh_getdata(line, col, prompt, buf, len, echo, ans, rud)
  int line, col, rud;
  char *prompt, *buf, *ans;
  int len, echo;
{
  register int ch;
  int clen;
  int x, y;
  extern unsigned char scr_cols;
#define MAXLASTCMD 6
  static char lastcmd[MAXLASTCMD][80];

  if (prompt)
  {
    move(line, col);
    clrtoeol();
    if (strchr(prompt, KEY_ESC))
       edit_outs(prompt);
    else
       outs(prompt);
  }
  else
    clrtoeol();

  if (dumb_term || !echo)
  {
    len--;
    clen = 0;
    while ((ch = igetch()) != '\r')
    {
      if (ch == '\n')
        break;

      if (ch == '\177' || ch == Ctrl('H'))
      {
        if (!clen)
        {
          bell();
          continue;
        }
        clen--;
        if (echo)
        {
          ochar(Ctrl('H'));
          ochar(' ');
          ochar(Ctrl('H'));
        }
        continue;
      }

#ifdef BIT8
      if (!isprint2(ch))
#else
      if (!isprint(ch))
#endif

      {
        if (echo)
          bell();
        continue;
      }
      if (clen >= len)
      {
        if (echo)
          bell();
        continue;
      }
      buf[clen++] = ch;
      if (echo)
        ochar(ch);
    }
    buf[clen] = '\0';
    outc('\n');
    oflush();
  }
  else
  {
   int cmdpos = MAXLASTCMD -1;
   int currchar = 0;
   int phone_mode = 0;
   int keydown;
   int dirty;
   char* pstr;

    getyx(&y, &x);
    standout();
    for (clen = len--; clen; clen--)
      outc(' ');
    standend();

    if (ans) {
       int i;

       strncpy(buf, ans, len);
       buf[len] = 0;
       for (i = strlen(buf) + 1; i < len; i++)
          buf[i] = 0;
       move(y, x);
       edit_outs(buf);
       clen = currchar = strlen(buf);

    }
    else
       memset(buf, 0, len);

    dirty = 0;
    while (move(y, x + currchar), (ch = igetkey()) != '\r')
    {
/*
woju
*/
       keydown = 0;
       switch (ch) {
       case KEY_DOWN:
       case Ctrl('N'):
          keydown = 1;
       case Ctrl('P'):
       case KEY_UP: {
          int i;

          if (clen && dirty) {
             for (i = MAXLASTCMD - 1; i; i--)
                strcpy(lastcmd[i], lastcmd[i - 1]);
             strncpy(lastcmd[0], buf, len);
          }

          i = cmdpos;
          do {
             if (keydown)
                --cmdpos;
             else
                ++cmdpos;
             if (cmdpos < 0)
                cmdpos = MAXLASTCMD - 1;
             else if (cmdpos == MAXLASTCMD)
                cmdpos = 0;
          } while (cmdpos != i && (!*lastcmd[cmdpos]
                   || !strncmp(buf, lastcmd[cmdpos], len)));
          if (cmdpos == i)
             continue;

          strncpy(buf, lastcmd[cmdpos], len);
          buf[len] = 0;

          move(y, x);                   /* clrtoeof */
          for (i = 0; i <= clen; i++)
             outc(' ');
          move(y, x);

          edit_outs(buf);
          clen = currchar = strlen(buf);
          dirty = 0;
          continue;
       }
       case KEY_LEFT:
          if (currchar)
             --currchar;
          continue;
       case KEY_RIGHT:
          if (buf[currchar])
             ++currchar;
          continue;
       case KEY_ESC:
           if (KEY_ESC_arg == 'p')
              phone_mode ^= 1;
           else if (KEY_ESC_arg == 'c')
              capture_screen();
           else if (KEY_ESC_arg == 'n')
              scr_exec(edit_note);
           else if (KEY_ESC == 'U' && currstat != IDLE  &&
               !(currutmp->mode == 0 &&
                 (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3)))
              scr_exec(t_users);
           continue;
       }

      if (ch == '\n' || ch == '\r')
         break;

/* MH */
/* */
      if(ch == Ctrl('U') && rud)
      {
          return MH_UP;
      }
      if(ch == Ctrl('D') && rud)
      {
          return MH_DOWN;
      }
/*    */
      
/* MH */
      if (ch == Ctrl('R'))
      {
        if(!(currutmp->mode == 0 &&
            (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3)))
        {
         extern screenline* big_picture;
         screenline* screen0 = calloc(t_lines, sizeof(screenline));

         memcpy(screen0, big_picture, t_lines * sizeof(screenline));

         mh_throw_water_ball();
         memcpy(big_picture, screen0, t_lines * sizeof(screenline));
         free(screen0);
         redoscr();
         continue;
        }
        else if(currutmp->mode == 0 && currutmp->chatid[0] == 2 && currstat == ROWB)
        {
/*         extern screenline* big_picture;
         screenline* screen0 = calloc(t_lines, sizeof(screenline));

         memcpy(screen0, big_picture, t_lines * sizeof(screenline));

         mh_throw_water_ball();
         memcpy(big_picture, screen0, t_lines * sizeof(screenline));
         free(screen0);
         redoscr();
         return 0;*/
         return MH_CTRLR;
        }
      }
/*    */

      if (ch == Ctrl('I') && currstat != IDLE &&
          !(currutmp->mode == 0 &&
            (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3))) {
         scr_exec(t_idle);
         continue;
      }
      if (ch == Ctrl('B')) {
         scr_exec(m_read);
         continue;
      }
      if (ch == '\177' || ch == Ctrl('H'))
      {
        if (currchar) {
           int i;

           currchar--;
           clen--;
           for (i = currchar; i <= clen; i++)
              buf[i] = buf[i + 1];
           move(y, x + clen);
           outc(' ');
           move(y, x);
           edit_outs(buf);
           dirty = 1;
        }
        continue;
      }
      if (ch == Ctrl('Y')) {
         int i;

         buf[0] = 0;
         currchar = 0;
         move(y, x);                    /* clrtoeof */
         for (i = 0; i < clen; i++)
            outc(' ');
         clen = 0;
         continue;
      }
      if (ch == Ctrl('D')) {
        if (buf[currchar]) {
           int i;

           clen--;
           for (i = currchar; i <= clen; i++)
              buf[i] = buf[i + 1];
           move(y, x + clen);
           outc(' ');
           move(y, x);
           edit_outs(buf);
           dirty = 1;
        }
        continue;
      }
      if (ch == Ctrl('K')) {
         int i;

         buf[currchar] = 0;
         move(y, x + currchar);
         for (i = currchar; i < clen; i++)
            outc(' ');
         clen = currchar;
         dirty = 1;
         continue;
      }
      if (ch == Ctrl('A')) {
         currchar = 0;
         continue;
      }
      if (ch == Ctrl('E')) {
         currchar = clen;
         continue;
      }


      if (!(phone_mode && (pstr = phone_char(ch)) || isprint2(ch) || ch == Ctrl('U') && HAS_PERM(PERM_SYSOP)))
      {
        continue;
      }
      if (clen + (phone_mode && pstr) >= len || x + clen >= scr_cols)
      {
        continue;
      }
/*
woju
*/
      if (buf[currchar]) {               /* insert */
         int i;

         for (i = currchar; buf[i] && i + (phone_mode && pstr) < len && i + (phone_mode && pstr) < 80; i++)
            ;
         buf[i + 1 + (phone_mode && pstr)] = 0;
         for (; i > currchar; i--)
            buf[i + (phone_mode && pstr)] = buf[i - 1];
      }
      else                              /* append */
         buf[currchar + 1 + (phone_mode && pstr)] = '\0';
      if (ch == Ctrl('U'))
         ch = KEY_ESC;
      if (phone_mode && pstr) {
          buf[currchar] = pstr[0];
          buf[currchar + 1] = pstr[1];
      }
      else
         buf[currchar] = ch;
      move(y, x + currchar);
      edit_outs(buf + currchar);
      currchar++;
      currchar += phone_mode && pstr;
      clen++;
      clen += phone_mode && pstr;
      dirty = 1;
    }
    buf[clen] = '\0';
    if (clen > 1) {
       for (cmdpos = MAXLASTCMD - 1; cmdpos; cmdpos--)
          strcpy(lastcmd[cmdpos], lastcmd[cmdpos - 1]);
       strncpy(lastcmd[0], buf, len);
    }
    if (echo) {
      move(y, x + clen);
      outc('\n');
    }
    refresh();
  }
  if ((echo == LCECHO) && ((ch = buf[0]) >= 'A') && (ch <= 'Z'))
    buf[0] = ch | 32;
  return clen;
}
/*    */
#endif

mh_getdata(line, col, prompt, buf, len, echo, ans, mode, statep)
  int line, col;
  char *prompt, *buf, *ans;
  int len, echo;
  int mode, *statep;
{
  register int ch;
  int clen;
  int x, y;
  extern unsigned char scr_cols;
#define MAXLASTCMD 6
  static char lastcmd[MAXLASTCMD][80];

  if (prompt)
  {
    move(line, col);
    clrtoeol();
    if (strchr(prompt, KEY_ESC))
       edit_outs(prompt);
    else
       outs(prompt);
  }
  else
    clrtoeol();

  if (dumb_term || !echo)
  {
    len--;
    clen = 0;
    while ((ch = igetch()) != '\r')
    {
      if (ch == '\n')
        break;

      if (ch == '\177' || ch == Ctrl('H'))
      {
        if (!clen)
        {
          bell();
          continue;
        }
        clen--;
        if (echo)
        {
          ochar(Ctrl('H'));
          ochar(' ');
          ochar(Ctrl('H'));
        }
        continue;
      }

#ifdef BIT8
      if (!isprint2(ch))
#else
      if (!isprint(ch))
#endif

      {
        if (echo)
          bell();
        continue;
      }
      if (clen >= len)
      {
        if (echo)
          bell();
        continue;
      }
      buf[clen++] = ch;
      if (echo)
        ochar(ch);
    }
    buf[clen] = '\0';
    outc('\n');
    oflush();
  }
  else
  {
   int cmdpos = MAXLASTCMD -1;
   int currchar = 0;
   int phone_mode = 0;
   int keydown;
   int dirty;
   char* pstr;

    getyx(&y, &x);
    standout();
    for (clen = len--; clen; clen--)
      outc(' ');
    standend();

    if (ans) {
       int i;

       strncpy(buf, ans, len);
       buf[len] = 0;
       for (i = strlen(buf) + 1; i < len; i++)
          buf[i] = 0;
       move(y, x);
       edit_outs(buf);
       clen = currchar = strlen(buf);

    }
    else
       memset(buf, 0, len);

    dirty = 0;
    while (move(y, x + currchar), (ch = igetkey()) != '\r')
    {
/*
woju
*/
       keydown = 0;
       switch (ch) {
       case KEY_DOWN:
       case Ctrl('N'):
          keydown = 1;
       case Ctrl('P'):
       case KEY_UP: {
          int i;

          if (clen && dirty) {
             for (i = MAXLASTCMD - 1; i; i--)
                strcpy(lastcmd[i], lastcmd[i - 1]);
             strncpy(lastcmd[0], buf, len);
          }

          i = cmdpos;
          do {
             if (keydown)
                --cmdpos;
             else
                ++cmdpos;
             if (cmdpos < 0)
                cmdpos = MAXLASTCMD - 1;
             else if (cmdpos == MAXLASTCMD)
                cmdpos = 0;
          } while (cmdpos != i && (!*lastcmd[cmdpos]
                   || !strncmp(buf, lastcmd[cmdpos], len)));
          if (cmdpos == i)
             continue;

          strncpy(buf, lastcmd[cmdpos], len);
          buf[len] = 0;

          move(y, x);                   /* clrtoeof */
          for (i = 0; i <= clen; i++)
             outc(' ');
          move(y, x);

          edit_outs(buf);
          clen = currchar = strlen(buf);
          dirty = 0;
          continue;
       }
       case KEY_LEFT:
          if (currchar)
             --currchar;
          continue;
       case KEY_RIGHT:
          if (buf[currchar])
             ++currchar;
          continue;
       case KEY_ESC:
           if (KEY_ESC_arg == 'p')
              phone_mode ^= 1;
           else if (KEY_ESC_arg == 'c')
              capture_screen();
           else if (KEY_ESC_arg == 'n')
              scr_exec(edit_note);
           else if (KEY_ESC == 'U' && currstat != IDLE  &&
               !(currutmp->mode == 0 &&
                 (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3)))
              scr_exec(t_users);
           continue;
       }

      if (ch == '\n' || ch == '\r')
         break;

/* MH */
      if(ch == Ctrl('U'))
        if(currutmp->mode == 0 && currutmp->chatid[0] == 3)
        {
          return MH_UP;
        }
        else if(mode & MH_GETDATA_UD)
        {
          if(mode & MH_GETDATA_STATE)
          {
            *statep = MH_UP;
            break;
          }
          else
            return MH_UP;
        }
      if(ch == Ctrl('D'))
        if(currutmp->mode == 0 && currutmp->chatid[0] == 3)
        {
          return MH_DOWN;
        }
        else if(mode & MH_GETDATA_UD)
        {
          if(mode & MH_GETDATA_STATE)
          {
            *statep = MH_DOWN;
            break;
          }
          else
            return MH_DOWN;
        }
      if(ch == KEY_TAB && (mode & MH_GETDATA_TAB))
      {
        if(mode & MH_GETDATA_STATE)
        {
          *statep = MH_TAB;
          break;
        }
        else
         return MH_TAB;
      }
/*    */
      
/* MH */
      if (ch == Ctrl('R'))
      {
        if(!(currutmp->mode == 0 &&
            (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3)))
        {
         extern screenline* big_picture;
         screenline* screen0 = calloc(t_lines, sizeof(screenline));

         memcpy(screen0, big_picture, t_lines * sizeof(screenline));

         mh_throw_water_ball();
         memcpy(big_picture, screen0, t_lines * sizeof(screenline));
         free(screen0);
         redoscr();
         continue;
        }
        else if(currutmp->mode == 0 && currutmp->chatid[0] == 2 && currstat == ROWB)
        {
         return MH_CTRLR;
        }
      }
/*    */

/*
woju
*/
/*      if (currutmp->msgs[0].last_pid && ch == Ctrl('R') &&
          !(currutmp->mode == 0 &&
            (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3))) {
         extern screenline* big_picture;
         screenline* screen0 = calloc(t_lines, sizeof(screenline));

         memcpy(screen0, big_picture, t_lines * sizeof(screenline));

         show_last_call_in();
         my_write(currutmp->msgs[0].last_pid, "���y��^�h�G");
         memcpy(big_picture, screen0, t_lines * sizeof(screenline));
         free(screen0);
         redoscr();
         continue;
      }*/
      if (ch == Ctrl('I') && currstat != IDLE &&
          !(currutmp->mode == 0 &&
            (currutmp->chatid[0] == 2 || currutmp->chatid[0] == 3))) {
         scr_exec(t_idle);
         continue;
      }
      if (ch == Ctrl('B')) {
         scr_exec(m_read);
         continue;
      }
      if (ch == '\177' || ch == Ctrl('H'))
      {
        if (currchar) {
           int i;

           currchar--;
           clen--;
           for (i = currchar; i <= clen; i++)
              buf[i] = buf[i + 1];
           move(y, x + clen);
           outc(' ');
           move(y, x);
           edit_outs(buf);
           dirty = 1;
        }
        continue;
      }
      if (ch == Ctrl('Y')) {
         int i;

         buf[0] = 0;
         currchar = 0;
         move(y, x);                    /* clrtoeof */
         for (i = 0; i < clen; i++)
            outc(' ');
         clen = 0;
         continue;
      }
      if (ch == Ctrl('D')) {
        if (buf[currchar]) {
           int i;

           clen--;
           for (i = currchar; i <= clen; i++)
              buf[i] = buf[i + 1];
           move(y, x + clen);
           outc(' ');
           move(y, x);
           edit_outs(buf);
           dirty = 1;
        }
        continue;
      }
      if (ch == Ctrl('K')) {
         int i;

         buf[currchar] = 0;
         move(y, x + currchar);
         for (i = currchar; i < clen; i++)
            outc(' ');
         clen = currchar;
         dirty = 1;
         continue;
      }
      if (ch == Ctrl('A')) {
         currchar = 0;
         continue;
      }
      if (ch == Ctrl('E')) {
         currchar = clen;
         continue;
      }


      if (!(phone_mode && (pstr = phone_char(ch)) || isprint2(ch) || ch == Ctrl('U') && HAS_PERM(PERM_SYSOP)))
      {
        continue;
      }
      if (clen + (phone_mode && pstr) >= len || x + clen >= scr_cols)
      {
        continue;
      }
/*
woju
*/
      if (buf[currchar]) {               /* insert */
         int i;

         for (i = currchar; buf[i] && i + (phone_mode && pstr) < len && i + (phone_mode && pstr) < 80; i++)
            ;
         buf[i + 1 + (phone_mode && pstr)] = 0;
         for (; i > currchar; i--)
            buf[i + (phone_mode && pstr)] = buf[i - 1];
      }
      else                              /* append */
         buf[currchar + 1 + (phone_mode && pstr)] = '\0';
      if (ch == Ctrl('U'))
         ch = KEY_ESC;
      if (phone_mode && pstr) {
          buf[currchar] = pstr[0];
          buf[currchar + 1] = pstr[1];
      }
      else
         buf[currchar] = ch;
      move(y, x + currchar);
      edit_outs(buf + currchar);
      currchar++;
      currchar += phone_mode && pstr;
      clen++;
      clen += phone_mode && pstr;
      dirty = 1;
    }
    buf[clen] = '\0';
    if (clen > 1) {
       for (cmdpos = MAXLASTCMD - 1; cmdpos; cmdpos--)
          strcpy(lastcmd[cmdpos], lastcmd[cmdpos - 1]);
       strncpy(lastcmd[0], buf, len);
    }
    if (echo) {
      move(y, x + clen);
      outc('\n');
    }
    refresh();
  }
  if ((echo == LCECHO) && ((ch = buf[0]) >= 'A') && (ch <= 'Z'))
    buf[0] = ch | 32;
  return clen;
}

getdata(line, col, prompt, buf, len, echo, ans)
  int line, col;
  char *prompt, *buf, *ans;
  int len, echo;
{
  return mh_getdata(line, col, prompt, buf, len, echo, ans, MH_GETDATA_NONE, NULL);
}



/*
woju
*/
#define TRAP_ESC

#ifdef  TRAP_ESC
int KEY_ESC_arg;

int
igetkey()
{
  int mode;
  int ch, last;

  mode = last = 0;
  while (1)
  {
    ch = igetch();
    if (mode == 0)
    {
      if (ch == KEY_ESC)
        mode = 1;
      else
        return ch;              /* Normal Key */
    }
    else if (mode == 1)
    {                           /* Escape sequence */
      if (ch == '[' || ch == 'O')
        mode = 2;
      else if (ch == '1' || ch == '4')
        mode = 3;
      else
      {
        KEY_ESC_arg = ch;
        return KEY_ESC;
      }
    }
    else if (mode == 2)
    {                           /* Cursor key */
      if (ch >= 'A' && ch <= 'D')
        return KEY_UP + (ch - 'A');
      else if (ch >= '1' && ch <= '6')
        mode = 3;
      else
        return ch;
    }
    else if (mode == 3)
    {                           /* Ins Del Home End PgUp PgDn */
      if (ch == '~')
        return KEY_HOME + (last - '1');
      else
        return ch;
    }
    last = ch;
  }
}

#else                           /* TRAP_ESC */

int
igetkey(void)
{
  int mode;
  int ch, last;

  mode = last = 0;
  while (1)
  {
    ch = igetch();
    if (ch == KEY_ESC)
      mode = 1;
    else if (mode == 0)         /* Normal Key */
      return ch;
    else if (mode == 1)
    {                           /* Escape sequence */
      if (ch == '[' || ch == 'O')
        mode = 2;
      else if (ch == '1' || ch == '4')
        mode = 3;
      else
        return ch;
    }
    else if (mode == 2)
    {                           /* Cursor key */
      if (ch >= 'A' && ch <= 'D')
        return KEY_UP + (ch - 'A');
      else if (ch >= '1' && ch <= '6')
        mode = 3;
      else
        return ch;
    }
    else if (mode == 3)
    {                           /* Ins Del Home End PgUp PgDn */
      if (ch == '~')
        return KEY_HOME + (last - '1');
      else
        return ch;
    }
    last = ch;
  }
}
#endif                          /* TRAP_ESC */
