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
/*   mid = "[41;5m 學妹送來了情書 [0;1;44m";*/
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
 *           spc 是匹配 mid 的大小.
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
    prints("[1;44;37m【%s】%s[33m[41;5m%s[0;1;44m%s%s[3%s《%s》[0m\n",
      title, buf, mid, buf, " " + pad,
      currmode & MODE_SELECT ? (thread_title > 0 ? "6m串列" : "6m系列") : currmode & MODE_ETC ? "5m其他" :
      currmode & MODE_DIGEST ? "2m文摘" : "7m看板", currboard);
  }
  else
  {
    prints("[1;44;37m【%s】%s[33m%s%s%s[3%s《%s》[0m\n",
      title, buf, mid, buf, " " + pad,
      currmode & MODE_SELECT ? (thread_title > 0 ? "6m串列" : "6m系列") : currmode & MODE_ETC ? "5m其他" :
      currmode & MODE_DIGEST ? "2m文摘" : "7m看板", currboard);
  }
}


/* ------------------------------------ */
/* 動畫處理                              */
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


#define MAX_HISTORY     12      /* 動態看板保持 12 筆歷史記錄 */


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
  static char myweek[] = "天一二三四五六";
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
/* 用 mhsin_prints (in mhsin.c) 取代 kaede_prints */
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
{ char *msgs[] = {"關閉", "打開", "拔掉", "防水"};
/* MH */
/*  sprintf(mystatus, "[34;46m[%d/%d 星期%c%c %d:%02d]   [30;47m 目前紅樓裡有 [31m%d[30m 人, 我是 [31m%-13s[30m [Call機] [31m%s [0m",
    ptime->tm_mon + 1, ptime->tm_mday, myweek[i], myweek[i + 1],
    ptime->tm_hour, ptime->tm_min, count_ulist(), cuser.userid,
    msgs[currutmp->pager]);*/
  sprintf(mystatus, "[0;34;46m [%d/%d 星期%c%c %d:%02d] [30;47m 紅樓裡有 [31m%d[30m 人, 我是 [31m%-12s[30m [Call機:[31m%s[30m] %s[水球][30m [0m",
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
/*  m_user, PERM_ACCOUNTS, "UUser          使用者資料",*/
NULL, 0, NULL};

static int
Fixed()
{
  domenu(CLASS,"測試新功\能",'0',fixedlist);
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
  mh_board, PERM_SYSOP, "BBoard        設定看板",
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
    domenu(ADMIN, "系統維護", 'X', mh_adminlist);
  }
  return 0;
}

int m_sh_registerfile();
int m_sh_xchatd();

static struct commands m_systemlist[] = {
  m_sh_registerfile, PERM_SYSOP, "RRegister      刪除register.new.tmp",
  m_sh_xchatd, PERM_SYSOP, "XXchatd        管理Xchatd/Xchatd3",
  NULL, 0, NULL};

m_system(void)
{
  domenu(ADMIN, "系統維護", 'R', m_systemlist);
  return 0;
}
/*    */

static struct commands adminlist[] = {

  m_user, PERM_ACCOUNTS, "UUser          使用者資料",
  m_newbrd, PERM_BOARD, "NNew Board     開闢新看板",
  m_board, PERM_BOARD, "BBoard         設定看板",
  m_register, PERM_ACCOUNTS, "RRegister      審核註冊表單",
  x_file, PERM_SYSOP, "XXfile         編輯系統檔案",
  x_showload, PERM_SYSOP, "LLoad          顯示系統負荷",

  mh_admin, PERM_SYSOP, "TTest          Test",
  mh_test_form, PERM_SYSOP, "FForm          Form",
  m_system, PERM_SYSOP, "SSystem        系統工具",

#ifdef  HAVE_MAILCLEAN
  m_mclean, PERM_SYSOP, "MMail Clean    清理使用者個人信箱",
#endif

#ifdef  HAVE_ADM_SHELL
  x_csh, PERM_SYSOP, "SShell         執行系統 Shell",
#endif

#ifdef  HAVE_REPORT
  m_trace, PERM_SYSOP, "TTrace         設定是否記錄除錯資訊",
#endif

NULL, 0, NULL};


/* ----------------------------------------------------- */
/* class menu                                            */
/* ----------------------------------------------------- */

int board(), tw_board(), local_board(), Boards(), Post(), Read(), Select();

static int Class2();

int New();

static struct commands classlist[] = {
  board, 0,       "00[1;31m紅樓築夢[0m       本站管理/測試國",
  board, 0,    "11[1;33m校園資訊[0m       學校概況/各處室/活動訊息",
  Class2, 0,          "22學生活動       聯會/社團/班板/校友",
  board, 0,          "33課業討論       各科討論/大學科系與生活",
  board, 0,          "44電腦專區       作業系統/網路/程式",
  board, 0,          "55休閒娛樂       休閒不忘讀書，讀書不忘休閒!?",
  board, 0,          "66心情物語       心情/聊天/感性",
  board, 0,          "77人文社會       關心人，關懷社會",
  local_board, 0,          "88其他類別       無法分類的",
  Boards, 0,         "BBoards ─────┬─ 所有看板",
  New, 0,            "NNew              ├─ 閱\讀所有新作品",
  Post, PERM_POST,   "PPost             ├─ 發表文章",
  Read, 0,           "RRead             ├─ 閱\讀文章",
  Select, 0,         "RSelect           └─ 選擇看板",

  NULL, 0, NULL};
  
/* Tzu */  
static struct commands classlist2[] = {
 
 board, 0,          "00KS88         88級雄中班板",
 board, 0,          "11KS89         89級雄中班板",
 board, 0,          "22KS90         90級雄中班板",
 board, 0,          "33KS91         91級雄中班板",
 board, 0,          "44KS92         92級雄中班板",
 board, 0,          "55KS93         93級雄中班板",
 board, 0,          "66KS94         94級雄中班板",
 board, 0,          "77KS95         95級雄中班板",
 board, 0,          "88KS96         96級雄中班板",
 board, 0,          "99KG89         89級雄女班板",
 board, 0,          "AAKG90         90級雄女班板",
 board, 0,          "BBKG91         91級雄女班板",
 board, 0,          "CCKG92         92級雄女班板",
 board, 0,          "DDKG93         93級雄女班板",
 board, 0,          "FFKG94         94級雄女班板",
 board, 0,          "GGKG95         95級雄女班板",
 board, 0,          "HHKG96         96級雄女班板", 
 board, 0,          "II社團         雄中雄女社團/學聯會",

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
  m_new, PERM_READMAIL, "RNew           閱\讀新進郵件",
  m_read, PERM_READMAIL,"RRead          多功\能讀信選單",
  m_send, PERM_BASIC,   "RSend          站內寄信",
  m_list, PERM_BASIC,   "LList          編輯群組名單",
  mail_list, PERM_BASIC,"RMail List     群組寄信",
  m_sysop, 0,           "YYes, sir!     諂媚站長",

#ifdef INTERNET_PRIVATE_EMAIL
  m_internet, PERM_INTERNET, "RInternet      寄信到 Internet",
  m_group, PERM_SYSOP,       "GGroup         Group Internet mail",
#endif
  mail_mbox,PERM_INTERNET, "RZip UserHome  把所有私人資料打包回去",
  mail_all, PERM_SYSOP,  "RAll           寄信給所有使用者",
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

  t_users, 0, "UUsers         夢的瞭望臺",
/*t_friends, PERM_LOGINOK, "FFriends       探訪親愛好友",*/
/*t_list, 0, "LList          下海漁友資訊",*/
  t_monitor, PERM_BASIC, "MMonitor       警衛牌監視器",
  t_override, PERM_LOGINOK, "UOverRide      編輯好友名單",
  t_reject, PERM_LOGINOK, "UBlack         編輯壞人名單",
  t_pager, PERM_BASIC, "PPager         切換呼叫器",
  t_idle, 0, "IIdle          發呆",
  t_query, 0, "QQuery         濤客包打聽",
  t_talk, PERM_PAGE, "TTalk          松軒談心室",
  t_chat, PERM_CHAT, "CChat          紅樓聊天坊",
  t_display, 0, "DDisplay       顯示上幾次熱訊",
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

  u_info, PERM_BASIC, "IInfo          設定個人資料與密碼",
/* MH */
  Preference, PERM_LOGINOK, "PPreference    雜項設定",
/*    */
  u_ansi, 0, "AANSI          切換 ANSI [36m彩[35m色[37m/[30;47m黑[1;37m白[40;0m模示",
  u_movie, 0, "MMovie         切換動畫模示",

#ifdef  HAVE_SUICIDE
  u_kill, PERM_BASIC, "IKill          讓我屎吧",
#endif

  u_editplan, PERM_LOGINOK, "QQueryEdit     編輯名片檔",
/*  u_editsig, PERM_LOGINOK, "SSignature     編輯簽名檔",*/
  mh_u_editsig, PERM_LOGINOK, "SSignature     編輯簽名檔",
  u_cloak, PERM_CLOAK, "CCloak         隱身術",
  u_lock, PERM_BASIC, "LLockScreen    鎖定螢幕",
#ifndef MH_USEFORM
  u_register, PERM_BASIC, "RRegister      填寫《註冊申請單》",
#else
  mh_u_register, PERM_BASIC, "RRegister      填寫《註冊申請單》",
#endif
  u_list, PERM_BASIC, "UUsers         列出註冊名單",
NULL, 0, NULL};

/* MH */
int p_mailmsg();
int p_autoforward();
int p_welcome();

static struct commands profilelist[] = {

  p_mailmsg, PERM_LOGINOK, "MMailmsg       選擇新信提示訊息",
  p_autoforward, PERM_LOGINOK, "AAutoforward   設定自動轉寄",
  p_welcome, PERM_LOGINOK, "WWelcome       選擇進站畫面",
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
  x_gpl, 0,     "LLicense       GNU 使用執照",
#endif

#ifdef HAVE_INFO
  x_program, 0, "PProgram       本程式之版本與版權宣告",
#endif

  x_note, 0,    "NNote          《合作社的言論廣場》",
  /*x_note2, 0,    "FFull Note     《合作社的言論廣場（完整版）》",*/
  x_week, 0,    "WWeek          《本週五十大義行榜》",
  x_issue, 0,   "IIssue         《今日義言十大排行》",
  x_today, 0,   "TToday         《今日濤客人次統計》",
  x_yesterday, 0, "YYesterday     《昨日濤客人次統計》",
  x_birthday, 0, "BBirthday      《生日快樂！》",
  x_user, 0,    "UUsers         《留級與補考》",
  /* x_topboardman, 0,    "11boardman     《看板精華區評比》",   */

#ifdef HAVE_WWW
  x_www, PERM_LOGINOK, "WWWW Browser   汪汪汪",
#endif

#ifdef HAVE_BRIDGE
  x_bridge, PERM_LOGINOK, "BBridge        跨海大橋",
#endif

#ifdef BBSDOORS
  x_bbsnet, PERM_LOGINOK, "BBBSNet        通往其他 BBS 站",
#endif

NULL, 0, NULL};


/* ----------------------------------------------------- */
/* main menu                                             */
/* ----------------------------------------------------- */

static int
admin()
{
  domenu(ADMIN, "系統維護", 'B', adminlist);
  return 0;
}

static int

Class()
{
  domenu(CLASS, "分類看板", '0', classlist);
  return 0;
}

/* Tzu */
static int
Class2()    /* 班社版 */
{
  domenu(CLASS2, "雜項設定", '0', classlist2);
  return 0;
}
/*     */

static int
Mail()
{
  domenu(MAIL, "電子郵件", 'R', maillist);
  return 0;
}

static int
Talk()
{
  domenu(TMENU, "聊天說話", 'U', talklist);
  return 0;
}

static int
User()
{
  domenu(UMENU, "個人設定", 'A', userlist);
  return 0;
}

/* MH */
static int
Preference()
{
  domenu(PMENU, "雜項設定", 'M', profilelist);
  return 0;
}
/*    */

static int
Xyz()
{
  domenu(XMENU, "工具程式", 'N', xyzlist);
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

  admin,PERM_ADMIN, "00Admin       【 系統維護區 】",

#ifdef HAVE_TIN
  x_tin, PERM_LOGINOK, "11Discuss     【 News討論區 】",
#endif

#ifdef HAVE_GOPHER
  x_gopher, PERM_LOGINOK, "22Gopher       資料豐富之查詢系統",
#endif

  Announce, 0,  "AAnnounce     【 精華公佈欄 】",
  Boards, 0,    "BBoards       【 佈告討論區 】",
  Class, 0,     "CClass        【 分組討論區 】",
  Mail, PERM_BASIC, "MMail         【 私人信件區 】",
  Talk, 0,      "TTalk         【 休閒聊天區 】",
  User, 0,      "UUser         【 個人設定區 】",
  Xyz, 0,       "XXyz          【 系統工具區 】",
  Welcome, 0,   "WWelcome       觀賞歡迎畫面",
  Goodbye, 0,   "GGoodbye       去Ｋ書了，掰掰……",

NULL, 0, NULL};
/* INDENT ON */
