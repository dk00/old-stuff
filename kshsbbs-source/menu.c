/*-------------------------------------------------------*/
/* menu.c       ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : menu/help/movie routines                     */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


/* ------------------------------------- */
/* help & menu processring               */
/* ------------------------------------- */


int refscreen = NA;
extern char *boardprefix;

/* MH */
extern int thread_title;
/*    */  

void
showtitle(title, mid1)
  char *title, *mid1;
{
  char buf[100], *mid, midbuf[TTLEN + 1];
  int spc, pad;
  int havemail;

  mid = strncpy(midbuf, mid1, TITLELEN);
  midbuf[TITLELEN] = '\0';
  spc = strlen(mid);
  havemail = NA;
  if (title[0] == 0)
    title++;
  else if (chkmail(0))
  {
/* MH */
/*   mid = "[41;5m �ǩf�e�ӤF���� [0;1;44m";*/
    havemail = YEA;
    switch(cuserrc.mailmsg_type)
    {
      case MH_USERRC_MAILMSG_USERDEFINE:
        mid = cuserrc.mailmsg;
        break;
      case MH_USERRC_MAILMSG_SELECT:
        mid = mailmsgs[cuserrc.mailmsg_num];
        break;
      case MH_USERRC_MAILMSG_RANDOM:
        mid = mailmsgs[cuserrc.mailmsg_num];
        break;
      default:
      case MH_USERRC_MAILMSG_SEX:
        mid = mailmsgs[mailmsg_num[cuser.sex]];
        break;
    }
/*    */

/*
 * CyberMax:
 *           spc �O�ǰt mid ���j�p.
 */
    spc = 0;  /* MH 22 */
  }

  spc = 66 - strlen(title) - strlen(mid) - strlen(currboard);  /* MH */
/*
woju
*/
  if (spc < 0) {
     mid[(strlen(mid) + spc >= 0 ? strlen(mid) + spc : 0)] = '\0';
     spc = 0;
  }
  pad = 1 - spc & 1;
  spc >>= 1;
  memset(buf, ' ', spc);
  buf[spc] = '\0';
/*    */

  clear();
  
  if(havemail)
  {
    prints("[1;44;37m�i%s�j%s[33m[41;5m%s[0;1;44m%s%s[3%s�m%s�n[0m\n",
      title, buf, mid, buf, " " + pad,
      currmode & MODE_SELECT ? (thread_title > 0 ? "6m��C" : "6m�t�C") : currmode & MODE_ETC ? "5m��L" :
      currmode & MODE_DIGEST ? "2m��K" : "7m�ݪO", currboard);
  }
  else
  {
    prints("[1;44;37m�i%s�j%s[33m%s%s%s[3%s�m%s�n[0m\n",
      title, buf, mid, buf, " " + pad,
      currmode & MODE_SELECT ? (thread_title > 0 ? "6m��C" : "6m�t�C") : currmode & MODE_ETC ? "5m��L" :
      currmode & MODE_DIGEST ? "2m��K" : "7m�ݪO", currboard);
  }
}


/* ------------------------------------ */
/* �ʵe�B�z                              */
/* ------------------------------------ */


/* 2003/08/30 by Terry */
#define FILMROW 11

unsigned char menu_row = 13;
/*		       */
unsigned char menu_column = 15;
char mystatus[160];


static int
u_movie()
{
  cuser.uflag ^= MOVIE_FLAG;
  return 0;
}


#define MAX_HISTORY     12      /* �ʺA�ݪO�O�� 12 �����v�O�� */


/*
    ===== changer by mgtsai, Sep 15th, '96 =====
*/

/* MH */
extern my_outs(register char *str);
/*    */

movie(i)
  int i;
{
  int max_film = 0;
  int max_history;
  static short history[MAX_HISTORY];
  static char myweek[] = "�Ѥ@�G�T�|����";
  struct tm *ptime;
  time_t now;

  if ((currstat != CLASS) && (currstat != CLASS2) && (currstat != DBACK) && (cuser.uflag & MOVIE_FLAG))
  {
    fileheader item;
    char notes[999][FNLEN];
    char pbuf[256], buf[256];
    FILE *fp;
    int num, id, j;

    bzero(notes, sizeof notes);
    setapath(pbuf, "Note");
    setadir(buf, pbuf);
    num = get_num_records(buf, sizeof item);

    for (max_film = 20, j = 0; j < num; j++)
      if (get_record(buf, &item, sizeof item, j) != -1)
        if (item.title[3] == '<' && item.title[7] == '>' &&
          item.title[4] >= '0' && item.title[4] <= '9' &&
          item.title[5] >= '0' && item.title[5] <= '9' &&
          item.title[6] >= '0' && item.title[6] <= '9') {
            id = (item.title[4] - '0') * 100 +
              (item.title[5] - '0') * 10 + item.title[6] - '0';
            if (id == 0) {
              if (atoi(&item.title[8]) > 0)
                max_film = atoi(&item.title[8]);
              else
                strcpy(notes[id], item.filename);
            } else if (id == 999)
              strcpy(notes[0], item.filename);
            else if (id < 999)
              strcpy(notes[id], item.filename);
          }
    max_history = max_film - 2;
    if (max_history > MAX_HISTORY - 1)
      max_history = MAX_HISTORY - 1;


    do {
      if (!i)
        i = (rand() % max_film) + 1;
      for (now = max_history; now >= 0; now--)
        if (i == history[now]) {
          i = 0;
          break;
        }
    } while (i == 0);

/*
    while (!i) {
      i = (rand() % max_film) + 1;
      for (now = max_history; now >= 0; now--)
        if (i == history[now]) {
          i = 0;
          break;
        }
    }
*/
    memcpy(history, &history[1], max_history * sizeof(short));
    history[max_history] = now = i;

    if (i == 999)       /* Goodbye my friend */
      i = 0;
    sprintf(buf, "%s/%s", pbuf, notes[i]);
    if (*notes[i] && (fp = fopen(buf, "r")))
    {
/* 2003/08/30 by Terry */
      for (i = 1; i < FILMROW + 1; i++)
/*		       */
      {
        move(i, 0);
        clrtoeol();
        refresh();
        if (now)
        {
          if (fgets(buf, ANSILINELEN, fp))
          {
/* MH */
/* �� mhsin_prints (in mhsin.c) ���N kaede_prints */
/*            my_outs(buf);*/
/*            prints(buf, cuser.userid, cuser.userid);*/
            prints(mhsin_prints(buf, 255), cuser.userid, cuser.userid);
/*    */
          }
          else
            now = 0;
        }
      }
      fclose(fp);
      outs(reset_color);
    }
  }

  time(&now);
  ptime = localtime(&now);
  i = ptime->tm_wday << 1;
{ char *msgs[] = {"����", "���}", "�ޱ�", "����"};
/* MH */
/*  sprintf(mystatus, "[34;46m[%d/%d �P��%c%c %d:%02d]   [30;47m �ثe���Ӹ̦� [31m%d[30m �H, �ڬO [31m%-13s[30m [Call��] [31m%s [0m",
    ptime->tm_mon + 1, ptime->tm_mday, myweek[i], myweek[i + 1],
    ptime->tm_hour, ptime->tm_min, count_ulist(), cuser.userid,
    msgs[currutmp->pager]);*/
  sprintf(mystatus, "[0;34;46m [%d/%d �P��%c%c %d:%02d] [30;47m ���Ӹ̦� [31m%d[30m �H, �ڬO [31m%-12s[30m [Call��:[31m%s[30m] %s[���y][30m [0m",
    ptime->tm_mon + 1, ptime->tm_mday, myweek[i], myweek[i + 1],
    ptime->tm_hour, ptime->tm_min, count_ulist(), cuser.userid,
    msgs[currutmp->pager],
    currutmp->have_wb ? "[34m" : "[37m");
/*    */
}
  outmsg(mystatus);
  refresh();
}

/* ===== end ===== */


static int
show_menu(p)
  struct commands *p;
{
  register int n = 0;
  register char *s;

  movie(currstat);
  move(menu_row, 0);

  while (s = p[n].desc)
  {
    if (HAS_PERM(p[n].level))
      prints("%*s  ([1;36m%c[0m)%s\n", menu_column, "", s[1], s + 2);
    n++;
  }
  return n - 1;
}


int
domenu(cmdmode, cmdtitle, cmd, cmdtable)
  char *cmdtitle;
  int cmdmode, cmd;
  struct commands cmdtable[];
{
  int lastcmdptr;
  int n, pos, total, i;
  int err;
  int chkmailbox();
  static char cmd0[LOGIN];

  if (cmd0[cmdmode])
     cmd = cmd0[cmdmode];

  setutmpmode(cmdmode);
  if (cmdmode == CLASS || cmdmode == CLASS2)
  {
    menu_row = 3;
    menu_column = 10;
  }

  showtitle(cmdtitle, BoardName);
  total = show_menu(cmdtable);
  outmsg(mystatus);

  lastcmdptr = pos = 0;

  do
  {

    /* MH */
    for(i = 0; i < total && cmdtable[i].desc[1] != cmd; i ++)
      ;
    if(i < total && !HAS_PERM(cmdtable[i].level))
      cmd = KEY_DOWN;
/*    if(cmdtable[lastcmdptr].desc[1] == cmd &&
       !HAS_PERM(cmdtable[lastcmdptr].level))
      cmd = KEY_DOWN;*/
    /*    */
    i = -1;
    switch (cmd)
    {
/* MH */
      case Ctrl('R'):
       mh_throw_water_ball();
       refscreen = YEA;
       i = lastcmdptr;
       break;
/*    */

    case Ctrl('U'):
       t_users();
       refscreen = YEA;
       i = lastcmdptr;
       break;
    case Ctrl('B'):
       m_read();
       refscreen = YEA;
       i = lastcmdptr;
       break;
    case Ctrl('C'):
       if (*paste_path) {
          a_menu(paste_title, paste_path, paste_level);
          refscreen = YEA;
       }
       i = lastcmdptr;
       break;
    case KEY_ESC:
       if (KEY_ESC_arg == 'c')
          capture_screen();
       else if (KEY_ESC_arg == 'n') {
          edit_note();
          refscreen = YEA;
       }
       i = lastcmdptr;
       break;
    case Ctrl('I'):
       t_idle();
       refscreen = YEA;
       i = lastcmdptr;
       break;
    case Ctrl('N'):
       New();
       refscreen = YEA;
       i = lastcmdptr;
       break;
    case Ctrl('A'):
       if (mail_man() == FULLUPDATE)
          refscreen = YEA;
       i = lastcmdptr;
       break;
    case KEY_DOWN:
      i = lastcmdptr;

    case KEY_HOME:
    case KEY_PGUP:
      do
      {
        if (++i > total)
          i = 0;
      } while (!HAS_PERM(cmdtable[i].level));
      break;

    case KEY_END:
    case KEY_PGDN:
      i = total;
      break;

    case KEY_UP:
      i = lastcmdptr;
      do
      {
        if (--i < 0)
          i = total;
      } while (!HAS_PERM(cmdtable[i].level));
      break;

    case KEY_LEFT:
    case 'e':
    case 'E':
      if (cmdmode == MMENU)
      {
        cmd = 'G';
      }
      else if ((cmdmode == MAIL) && chkmailbox())
      {
        cmd = 'R';
      }
      else
      {
        if (cmdmode == CLASS)
        {
/* 2003/08/30 by Terry */
	  menu_row = 13;
/*		       */
          menu_column = 15;
        }
        return 0;
      }

    default:
       if ((cmd == 's'  || cmd == 'r') && (currstat == MMENU || currstat == TMENU || currstat == XMENU))  {
          if (cmd == 's')
             ReadSelect();
          else
             Read();
          refscreen = YEA;
          i = lastcmdptr;
          break;
       }

      if (cmd == '\n' || cmd == '\r' || cmd == KEY_RIGHT)
      {
        if (cmdmode == CLASS || cmdmode == CLASS2)
          boardprefix = cmdtable[lastcmdptr].desc + 2;

        move(b_lines, 0);
        clrtoeol();

        currstat = XMODE;

        if ((err = (*cmdtable[lastcmdptr].cmdfunc) ()) == QUIT)
          return;

        currutmp->mode = currstat = cmdmode;

        if (err == XEASY)
        {
          refresh();
          sleep(1);
        }
        else if (err != XEASY + 1 || err == FULLUPDATE)
          refscreen = YEA;

        if (err != -1)
          cmd = cmdtable[lastcmdptr].desc[0];
        else
          cmd = cmdtable[lastcmdptr].desc[1];
        cmd0[cmdmode] = cmdtable[lastcmdptr].desc[0];
      }

      if (cmd >= 'a' && cmd <= 'z')
        cmd &= ~0x20;
      while (++i <= total)
      {
        if (cmdtable[i].desc[1] == cmd)
          break;
      }
    }

    if (i > total || !HAS_PERM(cmdtable[i].level))
    {
      continue;
    }

    if (refscreen)
    {
      showtitle(cmdtitle, BoardName);
      show_menu(cmdtable);
      outmsg(mystatus);
      refscreen = NA;
    }

    cursor_clear(menu_row + pos, menu_column);
/*
woju
    move(menu_row + pos, menu_column);
    outs(STR_UNCUR);
*/
    n = pos = -1;
    while (++n <= (lastcmdptr = i))
    {
      if (HAS_PERM(cmdtable[n].level))
        pos++;
    }
    cursor_show(menu_row + pos, menu_column);
/*
woju
    move(menu_row + pos, menu_column);
    outs(STR_CURSOR);
*/
    /*outmsg(mystatus);*/
  } while (((cmd = igetkey()) != EOF) || refscreen);

  abort_bbs();
}
/* INDENT OFF */


/* ----------------------------------------------------- */
/* new function menu                                      */
/* ----------------------------------------------------- */
void  note();
static struct commands fixedlist[]={
/*  m_user, PERM_ACCOUNTS, "UUser          �ϥΪ̸��",*/
NULL, 0, NULL};

static int
Fixed()
{
  domenu(CLASS,"���շs�\\��",'0',fixedlist);
  return 0;
}
/* ----------------------------------------------------- */
/* administrator's maintain menu                         */
/* ----------------------------------------------------- */

int m_user(), m_newbrd(), m_board(), m_register(), x_file(), x_showload();

#ifdef  HAVE_ADM_SHELL
int x_csh();
#endif

#ifdef  HAVE_MAILCLEAN
int m_mclean();
#endif

#ifdef  HAVE_REPORT
int m_trace();
#endif

#ifdef SYS_VOTE
int m_vote();
#endif

/* MH */
int mh_board();
int mh_maxproc();
int mh_pre_class();
int mh_pre_daily();
int mh_test_list();
int mh_test_form();
int mh_test_scroll();
int mh_edit_hotnews();
int mh_note();
int mh_decloak();
int mh_generic_test();

int mh_sizeof(void)
{
  char buf[256];
  
  move(19, 0);
  sprintf(buf, "user_info: %d, mh_userrc: %d, cuserrc: %d", sizeof(user_info), sizeof(mh_userrc), sizeof(cuserrc));
  outs(buf);
  pressanykey();
}

static struct commands mh_adminlist[] = {
  mh_board, PERM_SYSOP, "BBoard        �]�w�ݪO",
  mh_sizeof, PERM_SYSOP, "SSizeof       Sizeof",
  mh_maxproc, PERM_SYSOP, "MMaxProc      MaxProc",
  mh_pre_class, PERM_SYSOP, "CClass        Class",
  mh_pre_daily, PERM_SYSOP, "DDaily        Daily",
  mh_test_list, PERM_SYSOP, "LList         List",
  mh_test_form, PERM_SYSOP, "FForm         Form",
  mh_test_scroll, PERM_SYSOP, "SScroll       Scroll",
  mh_edit_hotnews, PERM_SYSOP, "HHotNews      HotNews",
  mh_note, PERM_SYSOP, "NNote        Note",
  mh_decloak, PERM_SYSOP, "DDecloak     Decloak",
  mh_generic_test, PERM_SYSOP, "GGeneric      Generic",
  NULL, 0, NULL};

mh_admin()
{
  if(belong("etc/MHAdmin", cuser.userid))
  {
    domenu(ADMIN, "�t�κ��@", 'X', mh_adminlist);
  }
  return 0;
}

int m_sh_registerfile();
int m_sh_xchatd();

static struct commands m_systemlist[] = {
  m_sh_registerfile, PERM_SYSOP, "RRegister      �R��register.new.tmp",
  m_sh_xchatd, PERM_SYSOP, "XXchatd        �޲zXchatd/Xchatd3",
  NULL, 0, NULL};

m_system(void)
{
  domenu(ADMIN, "�t�κ��@", 'R', m_systemlist);
  return 0;
}
/*    */

static struct commands adminlist[] = {

  m_user, PERM_ACCOUNTS, "UUser          �ϥΪ̸��",
  m_newbrd, PERM_BOARD, "NNew Board     �}�P�s�ݪO",
  m_board, PERM_BOARD, "BBoard         �]�w�ݪO",
  m_register, PERM_ACCOUNTS, "RRegister      �f�ֵ��U���",
  x_file, PERM_SYSOP, "XXfile         �s��t���ɮ�",
  x_showload, PERM_SYSOP, "LLoad          ��ܨt�έt��",

  mh_admin, PERM_SYSOP, "TTest          Test",
  mh_test_form, PERM_SYSOP, "FForm          Form",
  m_system, PERM_SYSOP, "SSystem        �t�Τu��",

#ifdef  HAVE_MAILCLEAN
  m_mclean, PERM_SYSOP, "MMail Clean    �M�z�ϥΪ̭ӤH�H�c",
#endif

#ifdef  HAVE_ADM_SHELL
  x_csh, PERM_SYSOP, "SShell         ����t�� Shell",
#endif

#ifdef  HAVE_REPORT
  m_trace, PERM_SYSOP, "TTrace         �]�w�O�_�O��������T",
#endif

NULL, 0, NULL};


/* ----------------------------------------------------- */
/* class menu                                            */
/* ----------------------------------------------------- */

int board(), tw_board(), local_board(), Boards(), Post(), Read(), Select();

static int Class2();

int New();

static struct commands classlist[] = {
  board, 0,       "00[1;31m���ӿv��[0m       �����޲z/���հ�",
  board, 0,    "11[1;33m�ն��T[0m       �Ǯշ��p/�U�B��/���ʰT��",
  Class2, 0,          "22�ǥͬ���       �p�|/����/�Z�O/�դ�",
  board, 0,          "33�ҷ~�Q��       �U��Q��/�j�Ǭ�t�P�ͬ�",
  board, 0,          "44�q���M��       �@�~�t��/����/�{��",
  board, 0,          "55�𶢮T��       �𶢤���Ū�ѡAŪ�Ѥ��ѥ�!?",
  board, 0,          "66�߱����y       �߱�/���/�P��",
  board, 0,          "77�H����|       ���ߤH�A���h���|",
  local_board, 0,          "88��L���O       �L�k������",
  Boards, 0,         "BBoards �w�w�w�w�w�s�w �Ҧ��ݪO",
  New, 0,            "NNew              �u�w �\\Ū�Ҧ��s�@�~",
  Post, PERM_POST,   "PPost             �u�w �o��峹",
  Read, 0,           "RRead             �u�w �\\Ū�峹",
  Select, 0,         "RSelect           �|�w ��ܬݪO",

  NULL, 0, NULL};
  
/* Tzu */  
static struct commands classlist2[] = {
 
 board, 0,          "00KS88         88�Ŷ����Z�O",
 board, 0,          "11KS89         89�Ŷ����Z�O",
 board, 0,          "22KS90         90�Ŷ����Z�O",
 board, 0,          "33KS91         91�Ŷ����Z�O",
 board, 0,          "44KS92         92�Ŷ����Z�O",
 board, 0,          "55KS93         93�Ŷ����Z�O",
 board, 0,          "66KS94         94�Ŷ����Z�O",
 board, 0,          "77KS95         95�Ŷ����Z�O",
 board, 0,          "88KS96         96�Ŷ����Z�O",
 board, 0,          "99KG89         89�Ŷ��k�Z�O",
 board, 0,          "AAKG90         90�Ŷ��k�Z�O",
 board, 0,          "BBKG91         91�Ŷ��k�Z�O",
 board, 0,          "CCKG92         92�Ŷ��k�Z�O",
 board, 0,          "DDKG93         93�Ŷ��k�Z�O",
 board, 0,          "FFKG94         94�Ŷ��k�Z�O",
 board, 0,          "GGKG95         95�Ŷ��k�Z�O",
 board, 0,          "HHKG96         96�Ŷ��k�Z�O", 
 board, 0,          "II����         �������k����/���p�|",

 NULL, 0, NULL};

/*      */


/* ----------------------------------------------------- */
/* mail menu                                             */
/* ----------------------------------------------------- */

int m_new(), m_read(), m_send(), m_list(), mail_list(), m_sysop(),
    mail_all(), mail_mbox(), m_group();

#ifdef INTERNET_PRIVATE_EMAIL
int m_internet();
#endif

static struct commands maillist[] = {
  m_new, PERM_READMAIL, "RNew           �\\Ū�s�i�l��",
  m_read, PERM_READMAIL,"RRead          �h�\\��Ū�H���",
  m_send, PERM_BASIC,   "RSend          �����H�H",
  m_list, PERM_BASIC,   "LList          �s��s�զW��",
  mail_list, PERM_BASIC,"RMail List     �s�ձH�H",
  m_sysop, 0,           "YYes, sir!     �ԴA����",

#ifdef INTERNET_PRIVATE_EMAIL
  m_internet, PERM_INTERNET, "RInternet      �H�H�� Internet",
  m_group, PERM_SYSOP,       "GGroup         Group Internet mail",
#endif
  mail_mbox,PERM_INTERNET, "RZip UserHome  ��Ҧ��p�H��ƥ��]�^�h",
  mail_all, PERM_SYSOP,  "RAll           �H�H���Ҧ��ϥΪ�",
NULL, 0, NULL};


/* ----------------------------------------------------- */
/* Talk menu                                             */
/* ----------------------------------------------------- */

int t_friends(), t_users(), t_list(), t_idle(), t_query(), t_monitor();
int t_pager(), t_talk(), t_chat(), t_override(), t_reject();
/* Thor: for ask last call-in message */
int t_display();

#ifdef HAVE_IRC
int x_irc();
#endif

static struct commands talklist[] = {

  t_users, 0, "UUsers         �ڪ��A��O",
/*t_friends, PERM_LOGINOK, "FFriends       ���X�˷R�n��",*/
/*t_list, 0, "LList          �U�����͸�T",*/
  t_monitor, PERM_BASIC, "MMonitor       ĵ�õP�ʵ���",
  t_override, PERM_LOGINOK, "UOverRide      �s��n�ͦW��",
  t_reject, PERM_LOGINOK, "UBlack         �s���a�H�W��",
  t_pager, PERM_BASIC, "PPager         �����I�s��",
  t_idle, 0, "IIdle          �o�b",
  t_query, 0, "QQuery         �ܫȥ]��ť",
  t_talk, PERM_PAGE, "TTalk          �Q�a�ͤ߫�",
  t_chat, PERM_CHAT, "CChat          ���Ӳ�ѧ{",
  t_display, 0, "DDisplay       ��ܤW�X�����T",
NULL, 0, NULL};


/* ----------------------------------------------------- */
/* User menu                                             */
/* ----------------------------------------------------- */

int u_info(), u_editsig(), u_editplan(), u_register();
int u_cloak(), u_ansi(), u_movie(), u_lock(), u_list();
/* MH */
int mh_u_editsig();
int mh_u_register();
/*    */

static int Preference();

#ifdef  HAVE_SUICIDE
int u_kill();
#endif

static struct commands userlist[] = {

  u_info, PERM_BASIC, "IInfo          �]�w�ӤH��ƻP�K�X",
/* MH */
  Preference, PERM_LOGINOK, "PPreference    �����]�w",
/*    */
  u_ansi, 0, "AANSI          ���� ANSI [36m�m[35m��[37m/[30;47m��[1;37m��[40;0m�ҥ�",
  u_movie, 0, "MMovie         �����ʵe�ҥ�",

#ifdef  HAVE_SUICIDE
  u_kill, PERM_BASIC, "IKill          ���ګ˧a",
#endif

  u_editplan, PERM_LOGINOK, "QQueryEdit     �s��W����",
/*  u_editsig, PERM_LOGINOK, "SSignature     �s��ñ�W��",*/
  mh_u_editsig, PERM_LOGINOK, "SSignature     �s��ñ�W��",
  u_cloak, PERM_CLOAK, "CCloak         �����N",
  u_lock, PERM_BASIC, "LLockScreen    ��w�ù�",
#ifndef MH_USEFORM
  u_register, PERM_BASIC, "RRegister      ��g�m���U�ӽг�n",
#else
  mh_u_register, PERM_BASIC, "RRegister      ��g�m���U�ӽг�n",
#endif
  u_list, PERM_BASIC, "UUsers         �C�X���U�W��",
NULL, 0, NULL};

/* MH */
int p_mailmsg();
int p_autoforward();
int p_welcome();

static struct commands profilelist[] = {

  p_mailmsg, PERM_LOGINOK, "MMailmsg       ��ܷs�H���ܰT��",
  p_autoforward, PERM_LOGINOK, "AAutoforward   �]�w�۰���H",
  p_welcome, PERM_LOGINOK, "WWelcome       ��ܶi���e��",
  NULL, 0, NULL};
/*    */

/* ----------------------------------------------------- */
/* XYZ tool menu                                         */
/* ----------------------------------------------------- */

int x_user(), x_note(), x_issue(), x_week(), x_today(), x_yesterday(), x_birthday();
/*int x_note2();*/
int x_topboardman(); 

#ifdef  HAVE_License
int x_gpl();
#endif

#ifdef HAVE_INFO
int x_program();
#endif

#ifdef SYS_VOTE
int x_vote(), x_results();
#endif

#ifdef HAVE_WWW
int x_www();
#endif

#ifdef HAVE_BRIDGE
int x_bridge();
#endif

#ifdef BBSDOORS
int x_bbsnet();
#endif


static struct commands xyzlist[] = {

#ifdef  HAVE_License
  x_gpl, 0,     "LLicense       GNU �ϥΰ���",
#endif

#ifdef HAVE_INFO
  x_program, 0, "PProgram       ���{���������P���v�ŧi",
#endif

  x_note, 0,    "NNote          �m�X�@�������׼s���n",
  /*x_note2, 0,    "FFull Note     �m�X�@�������׼s���]���㪩�^�n",*/
  x_week, 0,    "WWeek          �m���g���Q�j�q��]�n",
  x_issue, 0,   "IIssue         �m����q���Q�j�Ʀ�n",
  x_today, 0,   "TToday         �m�����ܫȤH���έp�n",
  x_yesterday, 0, "YYesterday     �m�Q���ܫȤH���έp�n",
  x_birthday, 0, "BBirthday      �m�ͤ�ּ֡I�n",
  x_user, 0,    "UUsers         �m�d�ŻP�ɦҡn",
  /* x_topboardman, 0,    "11boardman     �m�ݪO��ذϵ���n",   */

#ifdef HAVE_WWW
  x_www, PERM_LOGINOK, "WWWW Browser   �L�L�L",
#endif

#ifdef HAVE_BRIDGE
  x_bridge, PERM_LOGINOK, "BBridge        ����j��",
#endif

#ifdef BBSDOORS
  x_bbsnet, PERM_LOGINOK, "BBBSNet        �q����L BBS ��",
#endif

NULL, 0, NULL};


/* ----------------------------------------------------- */
/* main menu                                             */
/* ----------------------------------------------------- */

static int
admin()
{
  domenu(ADMIN, "�t�κ��@", 'B', adminlist);
  return 0;
}

static int

Class()
{
  domenu(CLASS, "�����ݪO", '0', classlist);
  return 0;
}

/* Tzu */
static int
Class2()    /* �Z���� */
{
  domenu(CLASS2, "�����]�w", '0', classlist2);
  return 0;
}
/*     */

static int
Mail()
{
  domenu(MAIL, "�q�l�l��", 'R', maillist);
  return 0;
}

static int
Talk()
{
  domenu(TMENU, "��ѻ���", 'U', talklist);
  return 0;
}

static int
User()
{
  domenu(UMENU, "�ӤH�]�w", 'A', userlist);
  return 0;
}

/* MH */
static int
Preference()
{
  domenu(PMENU, "�����]�w", 'M', profilelist);
  return 0;
}
/*    */

static int
Xyz()
{
  domenu(XMENU, "�u��{��", 'N', xyzlist);
  return 0;
}


int Announce(), Boards(), Goodbye(), Welcome();

#ifdef HAVE_TIN
int x_tin();
#endif

#ifdef HAVE_GOPHER
int x_gopher();
#endif

struct commands cmdlist[] = {

  admin,PERM_ADMIN, "00Admin       �i �t�κ��@�� �j",

#ifdef HAVE_TIN
  x_tin, PERM_LOGINOK, "11Discuss     �i News�Q�װ� �j",
#endif

#ifdef HAVE_GOPHER
  x_gopher, PERM_LOGINOK, "22Gopher       ����״I���d�ߨt��",
#endif

  Announce, 0,  "AAnnounce     �i ��ؤ��G�� �j",
  Boards, 0,    "BBoards       �i �G�i�Q�װ� �j",
  Class, 0,     "CClass        �i ���հQ�װ� �j",
  Mail, PERM_BASIC, "MMail         �i �p�H�H��� �j",
  Talk, 0,      "TTalk         �i �𶢲�Ѱ� �j",
  User, 0,      "UUser         �i �ӤH�]�w�� �j",
  Xyz, 0,       "XXyz          �i �t�Τu��� �j",
  Welcome, 0,   "WWelcome       �[���w��e��",
  Goodbye, 0,   "GGoodbye       �h�ٮѤF�A�T�T�K�K",

NULL, 0, NULL};
/* INDENT ON */
