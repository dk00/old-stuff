/*-------------------------------------------------------*/
/* mhsin.c                 ( KSHS BBS Ver 0.00 )         */
/*-------------------------------------------------------*/
/* target : MH's functions                               */
/* create : 1998/04/14                                   */
/* update : 1998/09/02                                   */
/*-------------------------------------------------------*/

#include "bbs.h"
#include "rfc2047.h"

#undef MH_SHOW_JUSTIFY

#define MH_CLASS_FILE "etc/classlist"
#define MH_DAILY_FILE "etc/daily"

/* in board.c */
typedef struct
{
  int pos, total;
  char *name, *title, *BM;
  uschar unread, zap, bvote;
}      boardstat;
extern int brdnum;
extern int yank_flag;
extern boardstat *nbrd;
extern int cmpboard();
extern int *zapbuf;
extern time_t board_visit_time;
/*            */


extern char *sex[8];

#define MH_LISTTYPES (15)

/*struct ListType
{
  char name[];
  char filename[];
};*/

/*struct ListType listtypes[] = {{"¦n¤Í¦W³æ", "overrides"}, {"Ãa¤H¦W³æ", "reject"},
       {"*/
/*char *listtypes[] = {"¸s²Õ¦W³æ0", "¸s²Õ¦W³æ1", "¸s²Õ¦W³æ2", "¸s²Õ¦W³æ3",
                     "¸s²Õ¦W³æ4", "¸s²Õ¦W³æ5", "¸s²Õ¦W³æ6", "¸s²Õ¦W³æ7",
                     "¸s²Õ¦W³æ8", "¸s²Õ¦W³æ9", "¦n¤Í¦W³æ", "Ãa¤H¦W³æ",
                     "¤W¯¸³qª¾¦W³æ", "¸s²Õ¤ô²y¦W³æ", "·s¤å³¹³qª¾¦W³æ"};
#define MH_LIST_OVERRIDES (10)
#define MH_LIST_REJECT (11)
#define MH_LIST_ALOHA (12)
#define MH_LIST_WB (13)
#define MH_LIST_NP (14)*/

int Copy(char *src, char *dst)
{
  char buf[256];
  
  sprintf(buf, "/bin/cp -f %s %s", src, dst);
  return system(buf);
}

void mh_log(char fname[], char mode[], char str[])
{
  FILE *fp;
  
  if((fp = fopen(fname, "a+")) != NULL)
  {
    time_t now;
    
    now = time(NULL);
    fprintf(fp, "%s %s %-12s %s\n", Cdate(&now), mode, cuser.userid, str);
    fclose(fp);
  }
}

void mh_strcat_before(char *des, char *source)
{
  char tmp[512];
  
  strcpy(tmp, des);
  strcpy(des, source);
  strcat(des, tmp);

  return;  
}

char *mh_num_to_chinese(int num, char *str)
{
  int a, b, c, d;
  char cnums[][3] = {"¹s", "¤@", "¤G", "¤T", "¥|", "¤­", "¤»", "¤C", "¤K", "¤E"};
  char cunits[][3] = {"", "¤Q", "¦Ê", "¤d"};
  char cunits2[][3] = {"", "¸U", "»õ", "¥ü", "¨Ê", "¥è"};
  
  b = 0;
  c = 0;
  str[0] = '\0';
  do
  {
    a = num % 10;
    num /= 10;
    if(a != 0)
      mh_strcat_before(str, cunits[c % 4]);
    if((a != 0 || c % 4 != 0) && (a != 0 || b != 0) && ((a != 1 || c % 4 != 1) || num != 0))  /* "¤@¤Q" ==> "¤Q" && "¹s¹s" ==> "¹s" */
      mh_strcat_before(str, cnums[a]);
    b = a;
    c ++;
    if(c % 4 == 0)
      d = num % 10000;
    if((c % 4 == 0 && c > 0) && num != 0 && d != 0)
      mh_strcat_before(str, cunits2[c / 4]);
  } while(num != 0);
  if(strlen(str) == 0)
    strcat(str, "¹s");
  
  return str;
}

char *mh_num_to_chinese_nu(int num, char *str)
{
  int a;
  char cnums[][3] = {"¹s", "¤@", "¤G", "¤T", "¥|", "¤­", "¤»", "¤C", "¤K", "¤E"};
  
  str[0] = '\0';
  do
  {
    a = num % 10;
    num /= 10;
    mh_strcat_before(str, cnums[a]);
  } while(num != 0);
  
  return str;
}

char *mh_delete_nl(char *str)
{
  char *sp;
  
  sp = str;
  while(*sp != '\n' && *sp != '\0')
    sp ++;
  *sp = '\0';
  
  return str;
}

char *mh_delete_esc(char *str)
{
  char *sp;
  
  sp = str;
  while(*sp != '\0')
  {
    if(*sp == '\033')
      *sp = '*';
    sp ++;
  }
  return str;
}

char *mhsin_prints(char *str, int len)
{
  char tmp1[512], tmp2[512];
  char mhbuf[512];
  char *sp, *np;
  char tmp3;
  
  strncpy(mhbuf, str, 500);
  sp = mhbuf;
  while(sp = strstr(sp, "\033*"))
  {
    int flag;
    
    flag = 1;
    tmp3 = sp[0];
    sp[0] = '\0';
    np = sp + 3;
    switch(*(np - 1))
    {
      case 's':  /* user ID */
        sprintf(tmp1, "%s%s%s", mhbuf, cuser.userid, np);
        break;
      case 'u':  /* user data */
        np ++;
        switch(*(np - 1))
        {
          case 'i':  /* user ID */
            sprintf(tmp1, "%s%s%s", mhbuf, cuser.userid, np);
            break;
          case 'n':  /* user nickname */
            sprintf(tmp1, "%s%s%s", mhbuf, cuser.username, np);
            break;
          case 'r':  /* user real name */
            sprintf(tmp1, "%s%s%s", mhbuf, cuser.realname, np);
            break;
          case 'l':  /* user login num */
            sprintf(tmp1, "%s%d%s", mhbuf, cuser.numlogins, np);
            break;
          case 'p':  /* user post num */
            sprintf(tmp1, "%s%d%s", mhbuf, cuser.numposts, np);
            break;
          case 'f':  /* user first login date */
            sprintf(tmp1, "%s%s%s", mhbuf, mh_delete_nl(ctime(&cuser.firstlogin)), np);
            break;
          case 'd':  /* user last login date */
            sprintf(tmp1, "%s%s%s", mhbuf, mh_delete_nl(ctime(&cuser.lastlogin)), np);
            break;
          case 'h':  /* user last login host */
            sprintf(tmp1, "%s%s%s", mhbuf, cuser.lasthost, np);
            break;
          case 'm':  /* user's e-mail address */
            sprintf(tmp1, "%s%s%s", mhbuf, cuser.email, np);
            break;
          case 'a':  /* user's address */
            sprintf(tmp1, "%s%s%s", mhbuf, cuser.lasthost, np);
/*            sprintf(tmp1, "%s%s%s", mhbuf, cuser.address, np); */
            break;
#ifdef MH_SHOW_JUSTIFY
          case 'j':  /* user's justify */
            sprintf(tmp1, "%s%s%s", mhbuf, cuser.justify, np);
            break;
#endif
          case 'b':  /* user's birthday */
            {
              np ++;
              switch(*(np - 1))
              {
                case 'y':  /* year */
                  sprintf(tmp1, "%s%d%s", mhbuf, cuser.year + 1900, np);
                  break;
                case 'Y':  /* chinese year */
                  mh_num_to_chinese_nu(cuser.year + 1900, tmp2);
                  sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
                  break;
                case 'z':  /* c_year */
                  sprintf(tmp1, "%s%d%s", mhbuf, cuser.year - 11, np);
                  break;
                case 'Z':  /* chinese c_year */
                  mh_num_to_chinese(cuser.year - 11, tmp2);
                  sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
                  break;
                case 'm':  /* month */
                  sprintf(tmp1, "%s%d%s", mhbuf, cuser.month, np);
                  break;
                case 'M':  /* chinese month */
                  mh_num_to_chinese(cuser.month, tmp2);
                  sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
                  break;
                case 'd':  /* day */
                  sprintf(tmp1, "%s%d%s", mhbuf, cuser.day, np);
                  break;
                case 'D':  /* chinese day */
                  mh_num_to_chinese(cuser.day, tmp2);
                  sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
                  break;
                default:
                  break;
              }
            }
            break;
          case 'x':  /* user's sex */
            sprintf(tmp1, "%s%s%s", mhbuf, sex[cuser.sex], np);
            break;
          default:
            break;
        }
        break;
      case 't':  /* time */
        {
          time_t now;
          struct tm *ptime;
          char cwdays[][3] = {"¤é", "¤@", "¤G", "¤T", "¥|", "¤­", "¤»"};

          np ++;
          time(&now);
          ptime = localtime(&now);
          switch(*(np - 1))
          {
            case 'a':  /* ASCII time */
              sprintf(tmp1, "%s%s%s", mhbuf, mh_delete_nl(asctime(ptime)), np);
              break;
            case 'y':  /* year */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_year + 1900, np);
              break;
            case 'Y':  /* chinese year */
              mh_num_to_chinese_nu(ptime->tm_year + 1900, tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            case 'z':  /* c_year */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_year - 11, np);
              break;
            case 'Z':  /* chinese c_year */
              mh_num_to_chinese(ptime->tm_year - 11, tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            case 'm':  /* month */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_mon + 1, np);
              break;
            case 'M':  /* chinese month */
              mh_num_to_chinese(ptime->tm_mon + 1, tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            case 'd':  /* day */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_mday, np);
              break;
            case 'D':  /* chinese day */
              mh_num_to_chinese(ptime->tm_mday, tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            case 'w':  /* wday */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_wday, np);
              break;
            case 'W':  /* chinese wday */
              sprintf(tmp1, "%s%s%s", mhbuf, cwdays[ptime->tm_wday], np);
              break;
            case 'h':  /* 24-hour */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_hour, np);
              break;
            case 'H':  /* chinese 24-hour */
              mh_num_to_chinese(ptime->tm_hour, tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            case 'i':  /* 12-hour */
              sprintf(tmp1, "%s%d%s", mhbuf, ((ptime->tm_hour > 12) ?
                      (ptime->tm_hour - 12) : ptime->tm_hour), np);
              break;
            case 'I':  /* chinese 12-hour */
              mh_num_to_chinese(((ptime->tm_hour > 12) ?
                                (ptime->tm_hour - 12) : ptime->tm_hour), tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            case 'p':  /* AM or PM */
              sprintf(tmp1, "%s%s%s", mhbuf, ((ptime->tm_hour > 12) ?
                      "PM" : "AM"), np);
              break;
            case 'P':  /* ¤W¤È or ¤U¤È */
              sprintf(tmp1, "%s%s%s", mhbuf, ((ptime->tm_hour > 12) ?
                      "¤U¤È" : "¤W¤È"), np);
              break;
            case 'n':  /* minute */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_min, np);
              break;
            case 'N':  /* chinese minute */
              mh_num_to_chinese(ptime->tm_min, tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            case 's':  /* second */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_sec, np);
              break;
            case 'S':  /* chinese second */
              mh_num_to_chinese(ptime->tm_sec, tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            case 'e':  /* yday */
              sprintf(tmp1, "%s%d%s", mhbuf, ptime->tm_yday, np);
              break;
            case 'E':  /* chinese yday */
              mh_num_to_chinese(ptime->tm_yday, tmp2);
              sprintf(tmp1, "%s%s%s", mhbuf, tmp2, np);
              break;
            default:
              flag = 0;
              break;
          }
        }
        break;
      default:
        flag = 0;
        break;
    }
    if(flag == 1)
    {
      sp[0] = tmp3;
      strncpy(mhbuf, tmp1, 500 - strlen(mhbuf));
      if(strlen(mhbuf) >= 500)
        break;
    }
    sp ++;
  }
  
  strncpy(str, mhbuf, len);
  return str;
}

void load_userrc(void)
{
  FILE *fp;
  int a, b;
  char buf[256];
  struct stat mhstat;
  
  memset(&cuserrc, 0, sizeof(cuserrc));
  setuserfile(buf, ".userrc");
  if(stat(buf, &mhstat) == -1)
  /* file doesn't exist */
  {
    log_usies("Load .userrc", ".userrc doesn't exist");
    log_usies("Load .userrc", "that's ok");
    if((fp = fopen(buf, "wb")) == NULL)
    {
      log_usies("Load .userrc", "can't create new .userrc, exit");
      u_exit();
    }
    fwrite(&cuserrc, sizeof(cuserrc), 1, fp);
    fclose(fp);
  }
  else if(mhstat.st_size < sizeof(cuserrc))
  /* .userrc is smaller than sizeof(cuserrc), old version? */
  {
    log_usies("Load .userrc", ".userrc is smaller than sizeof(cuserrc), older version?");
    sprintf(buf, ".userrc: %d, sizeof(cuserrc): %d, sizeof(mh_userrc): %d", mhstat.st_size, sizeof(cuserrc), sizeof(mh_userrc));
    log_usies("Load .userrc", buf);
  }
  else if(mhstat.st_size > sizeof(cuserrc))
  /* .userrc is greater than sizeof(cuserrc), old version? */
  {
    log_usies("Load .userrc", ".userrc is greater than sizeof(cuserrc), older version?");
    sprintf(buf, ".userrc: %d, sizeof(cuserrc): %d", mhstat.st_size, sizeof(cuserrc));
    log_usies("Load .userrc", buf);
    log_usies("Load .userrc", "unlink old .userrc and create new one");
    setuserfile(buf, ".userrc");
    unlink(buf);
    if((fp = fopen(buf, "wb")) == NULL)
    {
      log_usies("Load .userrc", "can't create new .userrc, exit");
      u_exit();
    }
    fwrite(&cuserrc, sizeof(cuserrc), 1, fp);
    fclose(fp);
  }
  
  setuserfile(buf, ".userrc");
  if((fp = fopen(buf, "rb")) == NULL)
  {
    log_usies("Load .userrc", "can't read .userrc, exit");
    u_exit();
  }
  fread(&cuserrc, sizeof(cuserrc), 1, fp);
  fclose(fp);
}


void save_userrc(void)
{
  FILE *fp;
  char buf[256];
  
  setuserfile(buf, ".userrc");
  if((fp = fopen(buf, "wb")) == NULL)
  {
    log_usies("Save .userrc", "can't write file");
    u_exit();
  }
  fwrite(&cuserrc, sizeof(cuserrc), 1, fp);
  fclose(fp);
}

#if 1
int p_mailmsg(void)
{
  char tmp1;
  int a, b;
  char buf[80];
  char ibuf[80];
  
  tmp1 = ' ';
  do
  {
    clear();
    for(a = 0;a < MAX_MAILMSGS;a ++)
    {
      move(a + 3, 5);
      sprintf(buf, "[%d] %s", a + 1, mailmsgs[a]);
      outs(buf);
    }
    move(a + 3, 5);
    sprintf(buf, "[u] %s", cuserrc.mailmsg);
    outs(buf);
    move(a + 4, 5);
    sprintf(buf, "(«ØÄ³¦b¦Û©w°T®§«e«á¦U¥[¤@­Ó¥b§ÎªÅ¥Õ¥H«O«ù¬üÆ[)");
    outs(buf);
    move(a + 5, 5);
    if(cuserrc.mailmsg_type == MH_USERRC_MAILMSG_SELECT)
    {
      sprintf(buf, "¥Ø«e¿ï¾Ü: [%d]", cuserrc.mailmsg_num + 1);
    }
    else
    {
      sprintf(buf, "¥Ø«e¿ï¾Ü: [%c]", 
              (cuserrc.mailmsg_type == MH_USERRC_MAILMSG_SEX) ? 'x' :
              (cuserrc.mailmsg_type == MH_USERRC_MAILMSG_RANDOM) ? 'r' :
              (cuserrc.mailmsg_type == MH_USERRC_MAILMSG_USERDEFINE) ? 'u' : ' ');
    }
    outs(buf);
    sprintf(buf, "(1¡ã%d) ¿ï¾Ü°T®§, (x) ¨Ì·Ó©Ê§O¨M©w, (u) ¦Û©w°T®§, (r) ÀH¾÷, (q) Â÷¶}, ½Ð¿ï¾Ü:", MAX_MAILMSGS);
    getdata(22, 0, buf, ibuf, 3, DOECHO, 0);
    switch(ibuf[0])
    {
      case 'x':
      case 'X':
        cuserrc.mailmsg_type = MH_USERRC_MAILMSG_SEX;
        cuserrc.mailmsg_num = mailmsg_num[cuser.sex];
        break;
      case 'u':
      case 'U':
        cuserrc.mailmsg_type = MH_USERRC_MAILMSG_USERDEFINE;
        cuserrc.mailmsg_num = mailmsg_num[cuser.sex];
        getdata(21, 0, "½Ð¿é¤J¦Û©w°T®§:", ibuf, MAILMSGLEN, DOECHO, cuserrc.mailmsg);
        strcpy(cuserrc.mailmsg, ibuf);
        break;
      case 'r':
      case 'R':
        cuserrc.mailmsg_type = MH_USERRC_MAILMSG_RANDOM;
        cuserrc.mailmsg_num = random() % MAX_MAILMSGS;
        break;
      case 'q':
      case 'Q':
        tmp1 = 'q';
        break;
      default:
        b = atoi(ibuf);
        if(b < 1 || b > MAX_MAILMSGS)
          break;
        cuserrc.mailmsg_type = MH_USERRC_MAILMSG_SELECT;
        cuserrc.mailmsg_num = b - 1;
        break;
    }
  } while(tmp1 != 'q');
}

#else
int p_mailmsg(void)
{
  char tmp1;
  int a, b;
  char buf[80];
  char ibuf[80];
  
  tmp1 = ' ';
  do
  {
    clear();
    for(a = 0;a < MAX_MAILMSGS;a ++)
    {
      move(a + 3, 5);
      sprintf(buf, "[%d] %s", a + 1, mailmsgs[a]);
      outs(buf);
    }
    move(a + 3, 5);
    sprintf(buf, "[u] %s", currutmp->mailmsg);
    outs(buf);
    move(a + 4, 5);
    sprintf(buf, "(«ØÄ³¦b¦Û©w°T®§«e«á¦U¥[¤@­Ó¥b§ÎªÅ¥Õ¥H«O«ù¬üÆ[)");
    outs(buf);
    move(a + 5, 5);
    if(currutmp->mailmsg_type == MAILMSG_TYPE_SELECT)
    {
      sprintf(buf, "¥Ø«e¿ï¾Ü: [%d]", currutmp->mailmsg_num + 1);
    }
    else
    {
      sprintf(buf, "¥Ø«e¿ï¾Ü: [%c]", currutmp->mailmsg_type);
    }
    outs(buf);
    sprintf(buf, "(1¡ã%d) ¿ï¾Ü°T®§, (x) ¨Ì·Ó©Ê§O¨M©w, (u) ¦Û©w°T®§, (r) ÀH¾÷, (q) Â÷¶}, ½Ð¿ï¾Ü:", MAX_MAILMSGS);
    getdata(22, 0, buf, ibuf, 3, DOECHO, 0);
    switch(ibuf[0])
    {
      case 'x':
      case 'X':
        currutmp->mailmsg_type = MAILMSG_TYPE_SEX;
        currutmp->mailmsg_num = mailmsg_num[cuser.sex];
        break;
      case 'u':
      case 'U':
        currutmp->mailmsg_type = MAILMSG_TYPE_USERDEFINE;
        currutmp->mailmsg_num = mailmsg_num[cuser.sex];
        getdata(21, 0, "½Ð¿é¤J¦Û©w°T®§:", ibuf, MAILMSGLEN, DOECHO, currutmp->mailmsg);
        strcpy(currutmp->mailmsg, ibuf);
        break;
      case 'r':
      case 'R':
        currutmp->mailmsg_type = MAILMSG_TYPE_RANDOM;
        currutmp->mailmsg_num = random() % MAX_MAILMSGS;
        break;
      case 'q':
      case 'Q':
        tmp1 = 'q';
        break;
      default:
        b = atoi(ibuf);
        if(b < 1 || b > MAX_MAILMSGS)
          break;
        currutmp->mailmsg_type = MAILMSG_TYPE_SELECT;
        currutmp->mailmsg_num = b - 1;
        break;
    }
  } while(tmp1 != 'q');
}
#endif

int p_autoforward(void)
{
  char buf[256];
  int a, b;
  int continue_flag = YEA;
  
  do
  {
    clear();
    a = 3;
    sprintf(buf, "[A] %-30s ¡G %s", "¦Û°ÊÂà±H«H¥ó",
            (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO) ? "£¾" : "¡Ñ");
    move(a ++, 0);
    outs(buf);
    sprintf(buf, "[%sm[B] %-30s ¡G %s[0m",
            (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO) ? "0;37" : "1;30",
            "«O¯d³Æ¥÷©ó«H½c¤¤",
            (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_COPY) ? "£¾" : "¡Ñ");
    move(a ++, 0);
    outs(buf);
    sprintf(buf, "[%sm[C] %-30s ¡G %s[0m",
            (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO) ? "0;37" : "1;30",
            "Âà±H³Æ§Ñ¿ý",
            (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_MEMOFORWARD) ? "£¾" : "¡Ñ");
    move(a ++, 0);
    outs(buf);
    sprintf(buf, "[%sm[D] %-30s ¡G %s[0m",
            ((cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO) &&
             (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_MEMOFORWARD)) ? "0;37" : "1;30",
            "«O¯d³Æ§Ñ¿ý³Æ¥÷",
            (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_MEMOCOPY) ? "£¾" : "¡Ñ");
    move(a ++, 0);
    outs(buf);
    sprintf(buf, "[%sm[E] Âà±H¦a§}¡G %-*s[0m",
            (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO) ? "0;37" : "1;30",
            EMAILLEN, cuserrc.forward_addr);
    move(a ++, 0);
    outs(buf);
    getdata(22, 0, "(a¡ãe) §ïÅÜ¿ï¶µ (q) Â÷¶}, ½Ð¿ï¾Ü¡G", buf, 3, DOECHO, 0);
    switch(buf[0])
    {
      case 'a':
        cuserrc.autoforward ^= MH_USERRC_AUTOFORWARD_AUTO;
        break;
      case 'b':
        if(cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO)
          cuserrc.autoforward ^= MH_USERRC_AUTOFORWARD_COPY;
        break;
      case 'c':
        if(cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO)
          cuserrc.autoforward ^= MH_USERRC_AUTOFORWARD_MEMOFORWARD;
        break;
      case 'd':
        if((cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO) && 
           (cuserrc.autoforward & MH_USERRC_AUTOFORWARD_MEMOFORWARD))
          cuserrc.autoforward ^= MH_USERRC_AUTOFORWARD_MEMOCOPY;
        break;
      case 'e':
        if(cuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO)
          getdata(21, 0, "½Ð¿é¤JÂà±H¦a§}¡G", cuserrc.forward_addr, EMAILLEN, DOECHO, cuserrc.forward_addr);
        break;
      case 'q':
        continue_flag = NA;
        break;
    }
  } while(continue_flag);
  save_userrc();
  return 0;
}

int p_welcome(void)
{
  char buf[256];
  usint tmpwelcome;
  usint value[MH_USERRC_WELCOME_MAX]
                 = {MH_USERRC_WELCOME_NOTE, MH_USERRC_WELCOME_DAY,
                    MH_USERRC_WELCOME_WEEK, MH_USERRC_WELCOME_TOPUSER,
                    MH_USERRC_WELCOME_TODAY, /*MH_USERRC_WELCOME_NOTE2*/};
  char *string[MH_USERRC_WELCOME_MAX]
                 = {MH_USERRC_WELCOME_NOTE_STR, MH_USERRC_WELCOME_DAY_STR,
                    MH_USERRC_WELCOME_WEEK_STR, MH_USERRC_WELCOME_TOPUSER_STR,
                    MH_USERRC_WELCOME_TODAY_STR, /*MH_USERRC_WELCOME_NOTE2_STR*/};
  int continue_flag;
  int a;
  
  continue_flag = YEA;
  tmpwelcome = cuserrc.welcome;
  do
  {
    clear();
    for(a = 0; a < MH_USERRC_WELCOME_MAX; a ++)
    {
      sprintf(buf, "%2d. %-30.30s  %s", a + 1, string[a], (tmpwelcome & value[a] ? "£¾" : "¡Ñ"));
      move(a + 3, 0);
      outs(buf);
    }
    a ++;
    sprintf(buf, "(1~%d) ¤Á´«, (q) Â÷¶}, ½Ð¿ï¾Ü: ", MH_USERRC_WELCOME_MAX);
    getdata(a + 3, 0, buf, buf, 3, DOECHO, NULL);
    if(buf[0] == 'q')
    {
      continue_flag = NA;
    }
    else if((a = atoi(buf) - 1) >= 0 && a < MH_USERRC_WELCOME_MAX)
    {
      tmpwelcome ^= value[a];
    }
  } while(continue_flag);
  if(tmpwelcome != cuserrc.welcome)
  {
    getdata(22, 0, "½T©w¶Ü¡H (y/N) ", buf, 3, DOECHO, NULL);
    if(buf[0] == 'y' || buf[0] == 'Y')
    {
      cuserrc.welcome = tmpwelcome;
      save_userrc();
    }
  }
  return 0;
}

int mh_do_forward(char *forward_addr, char *userid, char *fpath, fileheader *pmhdr, int hdrsize)
{
  char buf[256];
  FILE *fp;
  mh_userrc tuserrc;
  fileheader thdr;
  int internet_mail = NA;
#ifdef INTERNET_PRIVATE_EMAIL
  
  if(strchr(forward_addr, '@') != NULL)
  {
    internet_mail = YEA;
  }
#endif  
  if(!internet_mail)
  {
    if(!getuser(forward_addr))
    {
      sprintf(buf, "no such user: %s", forward_addr);
      log_usies("Autoforward", buf);
      return -2;
    }
    if(!(xuser.userlevel & PERM_READMAIL))
    {
      sprintf(buf, "user %s can't read mail", forward_addr);
      log_usies("Autoforward", buf);
      return -2;
    }
    sethomepath(buf, forward_addr);
    stampfile(buf, &thdr);
    Copy(fpath, buf);
    mh_log("log/forward.log", "@_@", buf);
    strcpy(thdr.owner, pmhdr->owner);
    strcpy(thdr.title, pmhdr->title);
    thdr.savemode = 0;
    sethomedir(buf, forward_addr);
    if(append_record(buf, &thdr, sizeof(thdr)) == -1)
    {
      return -1;
    }
  }
  else
  {
    if(mh_bbs_sendmail(fpath, pmhdr->title, forward_addr, userid) == -1)
      return -1;
  }
}

int mh_memoforward(char *holder, char *fpath, fileheader *pmhdr, int hdrsize)
{
  char buf[256];
  FILE *fp;
  mh_userrc tuserrc;
  fileheader thdr;
  int internet_mail = NA;

  sethomefile(buf, holder, ".userrc");
  if((fp = fopen(buf, "rb")) == NULL)
  {
    sprintf(buf, "can't read %s's .userrc", holder);
    log_usies("Autoforward", buf);
    return -2;
  }
  fread(&tuserrc, sizeof(tuserrc), 1, fp);
  fclose(fp);
  
  if(!(tuserrc.autoforward & MH_USERRC_AUTOFORWARD_MEMOFORWARD))
  {
    return 1;
  }
  
  if(mh_do_forward(tuserrc.forward_addr, holder, fpath, pmhdr, hdrsize) == -1)
    return -1;

  if(tuserrc.autoforward & MH_USERRC_AUTOFORWARD_MEMOCOPY)
  {
    return 1;
  }
  else
  {
/*    unlink(pmhdr->filename);*/
  }
  return 0;
}

int mh_autoforward(char *userid, fileheader *pmhdr, int hdrsize, int flag)
{
  char buf[256];
  FILE *fp;
  mh_userrc tuserrc;
  fileheader thdr;
  int internet_mail = NA;

  sethomefile(buf, userid, ".userrc");
  if((fp = fopen(buf, "rb")) == NULL)
  {
    sprintf(buf, "can't read %s's .userrc", userid);
    log_usies("Autoforward", buf);
    return -2;
  }
  fread(&tuserrc, sizeof(tuserrc), 1, fp);
  fclose(fp);
  
  if(!(tuserrc.autoforward & MH_USERRC_AUTOFORWARD_AUTO))
  {
    return 1;
  }

  sethomefile(buf, userid, pmhdr->filename);
  if(mh_do_forward(tuserrc.forward_addr, userid, buf, pmhdr, hdrsize) == -1)
    return -1;

  if(tuserrc.autoforward & MH_USERRC_AUTOFORWARD_COPY && flag)
  {
    return 1;
  }
  else
  {
/*    unlink(pmhdr->filename);*/
  }
  return 0;
}

#if 0
void save_mailmsg(void)
{
  FILE *fp;
  char buf[80];
  char buf2[10];
  
  setuserfile(buf, ".mailmsgrc");
  fp = fopen(buf, "w");
  
  sprintf(buf, "%c", currutmp->mailmsg_type);
  if(currutmp->mailmsg_type == MAILMSG_TYPE_SELECT)
  {
    sprintf(buf2, "%d", currutmp->mailmsg_num);
    strcat(buf, buf2);
  }
  fprintf(fp, "%s\n", buf);
  fprintf(fp, "%-*s\n", MAILMSGLEN, currutmp->mailmsg);
  fclose(fp);
}
#endif

/*
int access_perm(char *filename, char *userid)
{
  char c;
  char *sp, *sp2;
  char buf[MAXSTRLEN], buf2[MAXSTRLEN], buf3[MAXSTRLEN];
  FILE *fp;
  int r = MH_UNKNOWN;

  if((fp = fopen(filename, "r")) == NULL)
  {
    return MH_UNKNOWN;
  }
  
  while(fgets(buf, MAXSTRLEN, fp))
  {
    mh_delete_nl(buf);
    sp = buf;
    if(buf[0] == '+' || buf[0] == '-' && buf[1] == ':')
    {
      sp = buf + 2;
      while(*sp != '\0')
      {
        sp2 = sp;
        while(*sp2 != ' ' && *sp2 != '#' && *sp2 != '\0')
          sp2 ++;
        c = *sp2;
        *sp2 = '\0';
        if(strcasecmp(sp, userid) == 0)
        {
          r = ((buf[0] == '+') ? MH_ALLOW : MH_DENY);
        }
        *sp2 = c;
        sp = sp2 + ((*sp2 == '\0') ? 0 : 1);
      }
    }
  }
  
  fclose(fp);

  return r;
}
*/

int mh_maxproc(void)
{
  FILE *fp;
  char buf1[200];
  
  if((fp = popen("ulimit -u", "r")) == NULL)
  {
    move(10, 0);
    outs("Can't excute!!!");
    return 0;
  }
  
  fgets(buf1, 200, fp);
  move(10, 0);
  outs(buf1);
  pressanykey();
  
  pclose(fp);
  return 0;
}

int mh_belong(char *filename, int mode, char *key)
{
  int result = NA;
  FILE *fp;
  char buf[STRLEN];
  char *sp1;
  
  if((fp = fopen(filename, "r")) == NULL)
  {
    return NA;
  }
  while(fgets(buf, STRLEN, fp) != NULL)
  {
    if((sp1 = strtok(buf, " \t\r\n")) != NULL)
    {
      if(strcasecmp(sp1, "*") == 0)
      {
        result = YEA;
      }
      if(strcasecmp(sp1, (mode == MH_BELONG_BOARD) ? currboard : cuser.userid) == 0)
      {
        result = YEA;
      }
    }
  }
  fclose(fp);
  return result;
}

extern struct UTMPFILE *utmpshm;

void mh_test_list()
{
  int a, b;
  int i, j;
  int ch;
  uschar continue_flag = YEA;
  uschar refresh_flag = YEA;
  int st, end;
  int cur;
  user_info *uentp;
  char buf[256];
  
  st = 0;
  cur = 0;
  end = st + 20;
  do
  {
    if(cur < 0)
      cur = 0;
    if(cur < st || cur >= end)
    {
      st = (cur / 20) * 20;
      end = st + 20;
      refresh_flag = YEA;
    }
    for(a = 0; a < 20; a ++)
    {
      uentp = &(utmpshm->uinfo[a + st]);
      
      sprintf(buf, "  %3d %4d %13s %16s %c", a + st, uentp->uid, uentp->userid,
               uentp->username, (uentp->invisible) ? 'C' : ' ');
      move(a + 3, 0);
      prints(buf);
    }
    ch = cursor_key(cur - st + 3, 0);
    switch(ch)
    {
      case KEY_UP:
        cur --;
        break;
      case KEY_DOWN:
        cur ++;
        break;
      case KEY_PGUP:
        cur -= 20;
        break;
      case KEY_PGDN:
        cur += 20;
        break;
      case KEY_LEFT:
        continue_flag = NA;
        break;
    }
  } while(continue_flag);
}


int mh_edit_lists(int listtype)
{

}


int mh_strtodate(char *str, struct tm *date)
{
  char *sp;
  int a, b;
  
  if((sp = strtok(str, "/")) == NULL)
    return -1;
  if((a = atoi(sp)) <= 0 || a > 12)
    return -1;
  date->tm_mon = a - 1;
  if((sp = strtok(NULL, "/")) == NULL)
    return -2;
  if((a = atoi(sp)) <= 0 || a > 31)
    return -2;
  date->tm_mday = a;
  if((sp = strtok(NULL, "")) == NULL)
    return -3;
  if((a = atoi(sp)) < 0)
    return -3;
  if(strlen(sp) <= 2)
    date->tm_year = a;
  else
    date->tm_year = a - 1900;
  return 0;
}

void mh_form_showhelprim(int lines)
{
  int a;
  
  move(t_lines - (lines + 2) - 1, 0);
  outs("¢z¢w»¡©ú¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{");
  for(a = 0; a < lines; a ++)
  {
    move(t_lines - (lines + 2) - 1 + (a + 1), 0);
    outs("¢x");
    move(t_lines - (lines + 2) - 1 + (a + 1), 78);
    outs("¢x");
  }
  move(t_lines - 2, 0);
  outs("¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}");
}

void mh_form_showhelp(char *discription, int lines)
{
  int a, b, c;
  char *sp;
  char help[512];
  char buf[256];
  
  strncpy(help, discription, 500);
  sp = strtok(help, "\r\n");
  for(a = 0; a < lines; a ++)
  {
    if(sp != NULL)
      strncpy(buf, sp, 255);
    else
      buf[0] = '\0';
    move(t_lines - (lines + 2) - 1 + (a + 1), 2);
    outs(buf);
    getyx(&b, &c);
#if 1
    if(c < 78)
    {
      for(;c < 78; c ++)
        outc(' ');
      outc('|');
    }
#else
    clrtoeol();
    move(t_lines - (lines + 2) - 1 + (a + 1), 78);
    outs("¢x");
#endif
    sp = strtok(NULL, "\r\n");
  }
}

#if 0
void mh_form_showhint(mh_field *fieldp)
{
  move(fieldp->hrow, fieldp->hcol);
  switch(fieldp->type)
  {
    case MH_FIELD_NUM:
    case MH_FIELD_CHOICE:
      prints(fieldp->hint, *(int *)fieldp->valuep);
      break;
    case MH_FIELD_STRING:
      prints(fieldp->hint, fieldp->valuep);
      break;
  }
}
#endif

void mh_form_showfield(mh_field *fieldp)
{
  int a, b;
  char buf[100];
  
  /* show hint */
  move(fieldp->hrow, fieldp->hcol);
  switch(fieldp->type)
  {
    case MH_FIELD_NUM:
    case MH_FIELD_CHOICE:
      prints(fieldp->hint, *(int *)fieldp->valuep);
      break;
    case MH_FIELD_STRING:
      prints(fieldp->hint, fieldp->valuep);
      break;
    case MH_FIELD_DATE:
      prints(fieldp->hint, ((struct tm *)fieldp->valuep)->tm_mon + 1,
              ((struct tm *)fieldp->valuep)->tm_mday,
              ((struct tm *)fieldp->valuep)->tm_year + 1900);
      break;
  }
  /*           */
  if(fieldp->mode & MH_FIELD_USEDEFAULT)
  {
    switch(fieldp->type)
    {
      case MH_FIELD_NUM:
        sprintf(buf, "%d", *(int *)fieldp->valuep);
        break;
      case MH_FIELD_STRING:
        strncpy(buf, (char *)fieldp->valuep, 80);
        break;
      case MH_FIELD_DATE:
        sprintf(buf, "%02d/%02d/%04d", ((struct tm *)fieldp->valuep)->tm_mon + 1,
                ((struct tm *)fieldp->valuep)->tm_mday,
                ((struct tm *)fieldp->valuep)->tm_year + 1900);
        break;
      case MH_FIELD_CHOICE:
      default:
        buf[0] = '\0';
    }
  }
  else
    buf[0] = '\0';
  strncat(buf, SPACE_STRING, fieldp->limit - strlen(buf));
  move(fieldp->frow, fieldp->fcol);
  prints("[0m%s", buf);
}

int mh_form(int field_num, mh_field *fields, int helplines)
{
  int a, b;
  int i, j;
  int cur_stop;
  int cur_field;
  int cur_type;
  mh_field *cur_fieldp;
  int continue_flag = YEA;
  char buf[512];
  
  cur_field = 0;
  for(a = field_num - 1; a >= 0; a --)
  {
    mh_form_showfield(&(fields[a]));
  }
  mh_form_showhelprim(helplines);
  do
  {
    cur_fieldp = &(fields[cur_field]);
    mh_form_showhelp(cur_fieldp->discription, helplines);
    buf[0] = '\0';
    b = 0;
    switch(cur_fieldp->type)
    {
      case MH_FIELD_COMMENT:
        break;
      case MH_FIELD_NUM:
      case MH_FIELD_CHOICE:
        if(cur_fieldp->mode & MH_FIELD_USEDEFAULT && cur_fieldp->type != MH_FIELD_CHOICE)
          sprintf(buf, "%d", *(int *)cur_fieldp->valuep);
        a = mh_getdata(cur_fieldp->frow, cur_fieldp->fcol, "", buf, cur_fieldp->limit, DOECHO, buf, MH_GETDATA_STATE | MH_GETDATA_TAB, &b);
        if(a > 0)
        {
          i = atoi(buf);
          if((i < 0) || (cur_fieldp->mode & MH_FIELD_NLIMIT && i > (int)cur_fieldp->extra_info))
            continue;
          *(int *)cur_fieldp->valuep = i;
        }
        else if(cur_fieldp->mode & MH_FIELD_USEDEFAULT)
          continue;
        break;
      case MH_FIELD_STRING:
        if(cur_fieldp->mode & MH_FIELD_USEDEFAULT)
          strncpy(buf, (char *)cur_fieldp->valuep, cur_fieldp->limit);
        a = mh_getdata(cur_fieldp->frow, cur_fieldp->fcol, "", buf, cur_fieldp->limit, DOECHO, buf, MH_GETDATA_STATE | MH_GETDATA_TAB, &b);
        if(a > 0 || cur_fieldp->mode & MH_FIELD_USEDEFAULT)
          strcpy((char *)cur_fieldp->valuep, buf);
        break;
      case MH_FIELD_DATE:
        if(cur_fieldp->mode & MH_FIELD_USEDEFAULT)
        {
          sprintf(buf, "%02d/%02d/%04d", ((struct tm *)cur_fieldp->valuep)->tm_mon + 1,
                  ((struct tm *)cur_fieldp->valuep)->tm_mday,
                  ((struct tm *)cur_fieldp->valuep)->tm_year + 1900);
        }
        a = mh_getdata(cur_fieldp->frow, cur_fieldp->fcol, "", buf, 11, DOECHO, buf, MH_GETDATA_STATE | MH_GETDATA_TAB, &b);
        {
          struct tm date;
          
          if(a > 0 && mh_strtodate(buf, &date) == 0)
          {
            ((struct tm *)cur_fieldp->valuep)->tm_mday = date.tm_mday;
            ((struct tm *)cur_fieldp->valuep)->tm_mon = date.tm_mon;
            ((struct tm *)cur_fieldp->valuep)->tm_year = date.tm_year;
          }
          else
            continue;
        }
        break;
    }
    mh_form_showfield(cur_fieldp);
#if 0
    if(b == 0)
      cur_field ++;
    else if(b == MH_TAB)
      cur_field = cur_fieldp->tab_next;
    if(cur_field >= field_num)
      continue_flag = NA;
#else
    if(cur_fieldp->tab_next >= 0)
      cur_field = cur_fieldp->tab_next;
    else
      cur_field ++;
    if(cur_field >= field_num)
      if(b == MH_TAB)
        cur_field = 0;
      else
        continue_flag = NA;
#endif
  } while(continue_flag);
}

int mh_test_form()
{
#if 0
  static int a = 0, b = 1;
  static char c[40] = "test";
  static struct tm date = {0, 0, 0, 1, 0, 98, 0, 0, 0, 0, ""};
  mh_field fields[4] = {{MH_FIELD_NUM, &a, 3, 4, "A: ", 3, 0, 3, 3,
                      "½Ð¿é¤J¤@­Ó¤p©óµ¥©ó¤@¦Êªº¼Æ¦r\n«ö[TAB]´`Àô¤Á´«Äæ¦ì, [ENTER]¤Á´«¨ì¤U¤@­ÓÄæ¦ì", (void *)100, -1},
                     {MH_FIELD_NUM, &b, 0, 4, "B[%d]: ", 4, 0, 4, 6,
                      "½Ð¿é¤J1~7ªº¼Æ¦r", (void *)7, -1},
                     {MH_FIELD_STRING, c, 0, 6, "C[%-5s]: ", 5, 0, 5, 10,
                      "½Ð¿é¤J¤@­Óªø«×¤£¶W¹L5ªº¦r¦ê\n«ö[TAB]´`Àô¤Á´«Äæ¦ì, [ENTER]¤Á´«¨ì¤U¤@­ÓÄæ¦ì", NULL, -1},
                     {MH_FIELD_DATE, &date, 1, 0, "D[%02d/%02d/%04d]: ", 6, 0, 6, 15,
                      "½Ð¿é¤J¤@­Ó¦Xªkªº¤é´Á\n«ö[TAB]´`Àô¤Á´«Äæ¦ì, [ENTER]¤Á´«¨ì¤U¤@­ÓÄæ¦ì", NULL, -1}};
  
  clear();
  mh_form(4, fields, 3);
  move(16, 0);
  prints("%d %d |%s|", a, b, c);
#endif
}

int mh_test_scroll()
{
  int a, b;
  
  for(a = 0; a < t_lines; a ++)
  {
    move(a, 0);
    prints("%d:", a + 1);
  }
  igetkey();
  scroll();
  move(t_lines - 1, 0);
  prints("%d:", a + 1);
  a ++;
  igetkey();
  rscroll();
  move(0, 0);
  prints("%d:", 0);
  igetkey();
}

int mh_edit_hotnews()
{
  
}

#if 0
struct mh_class_entry
{
  uschar name[IDLEN + 1];
  uschar title[BTLEN + 1];
  int lstnum;
  int flag;
  struct mh_class_entry **list;
  boardstat *brds;
};

typedef struct mh_class_entry mhc_ent;

#define MH_ADJUST_ENT_SIZE
#define MH_MAX_ENT_NUM 200
#define MH_MAX_ENT_DEPTH 16
#define MH_ENT_BOARD (-1)
#define MH_ENT_COMMENT (-2)

mhc_ent root = {"Root", "®Ú¥Ø¿ý", 0, NULL, NULL};
mhc_ent daily = {"Daily", "Daily", 0, NULL, NULL};

/* a stack for (mhc_ent *) */
int mhc_ent_stack_num = 0;
mhc_ent *mhc_ent_stack[MH_MAX_ENT_DEPTH];

void mhc_ent_stack_flush(void)
{
  mhc_ent_stack_num = 0;
}

int mhc_ent_stack_push(mhc_ent *pent)
{
  if(mhc_ent_stack_num >= MH_MAX_ENT_DEPTH)
  {
    return -1;
  }
  else
  {
    mhc_ent_stack[mhc_ent_stack_num ++] = pent;
    return 0;
  }
}

mhc_ent *mhc_ent_stack_pop(void)
{
  if(mhc_ent_stack_num <= 0)
  {
    return NULL;
  }
  else
  {
    return mhc_ent_stack[-- mhc_ent_stack_num];
  }
}
/*                         */

boardstat *mh_search_board(char *name)
{
  int a;
  
  /* linear search, §ï¦¨ binary search? */
  for(a = 0;a < brdnum;a ++)
  {
    if(strcasecmp(name, nbrd[a].name) == 0)
      return &nbrd[a];
  }
  return NULL;
}

int mh_load_classlist(mhc_ent *root, char *filename)
{
  int a, b;
  FILE *fp;
  mhc_ent *pent;
  mhc_ent tmproot;
  mhc_ent *pcroot;
  mhc_ent **tmplist;
  boardstat *pbrds;
  char buf1[200], buf2[200];
  char *sp1, *sp2, *sp3, *sp4, *sp5;


  if(brdnum <= 0)
  {
    load_boards();
    if(brdnum <= 0)
      return;
    qsort(nbrd, brdnum, sizeof(boardstat), cmpboard);
  }

  if((fp = fopen(filename, "r")) == NULL)
  {
    sprintf(buf1, "can't open file %s", filename);
    log_usies("MH_CLASS ", buf1);
    return -1;
  }

  if((tmproot.list = (mhc_ent **)calloc(MH_MAX_ENT_NUM, sizeof(mhc_ent *))) == NULL)
    /* allocate ¤@¶ô (MH_MAX_ENT_NUM * sizeof(mhc_ent *)) ªºªÅ¶¡, ¶¶«K¶ñ 0 */
  {
    log_usies("MH_CLASS ", "can't allocate memory for tmproot.list");
    return -1;
  }
  tmproot.lstnum = 0;
  pcroot = &tmproot;
  
  while(fgets(buf1, 200, fp) != NULL)
  {
    if((sp1 = strtok(buf1, " \t\r\n")) == NULL || *sp1 == '#')
    {
      continue;
    }
    else if(strcasecmp(sp1, "Directory") == 0)
    {
      if((sp2 = strtok(NULL, " \t\r\n")) == NULL)
      {
        log_usies("MH_CLASS ", "no Directory name");
        return -1;
      }
      if((sp3 = strtok(NULL, "\t\r\n")) == NULL)
      {
        sp3 = sp2;  /* ­Y¨S¦³ title «h¥Î name ¥N´À */
      }
      else
      {
        if(*sp3 == '"')
        {
          sp3 ++;
          if((sp3 = strtok(sp3, "\"")) == NULL)
          {
            sp3 = sp2;
          }
        }
      }
      if((pent = (mhc_ent *)malloc(sizeof(mhc_ent))) == NULL)
      {
        log_usies("MH_CLASS ", "can't allocate memory for pent in D");
        return -1;
      }
      sprintf(buf2, "pcroot->list %p, pcroot->lstnum %d", pcroot->list, pcroot->lstnum);
      pcroot->list[pcroot->lstnum ++] = pent;
      /* initialize *pent(as a directory) */
      strcpy(pent->name, sp2);
      strcpy(pent->title, sp3);
      pent->lstnum = 0;
      pent->flag = 0;
      pent->brds = NULL;
      if((pent->list = (mhc_ent **)calloc(MH_MAX_ENT_NUM, sizeof(mhc_ent *))) == NULL)
        /* allocate ¤@¶ô (MH_MAX_ENT_NUM * sizeof(mhc_ent *)) ªºªÅ¶¡, ¶¶«K¶ñ 0 */
      {
        log_usies("MH_CLASS ", "can't allocate memory for pent->list in D");
        free(pent);
        return -1;
      }
      /*                                 */
      if(mhc_ent_stack_push(pcroot) == -1)
      {
        log_usies("MH_CLASS ", "depth > MH_MAX_ENT_DEPTH in D");
        return -1;
      }
      pcroot = pent;
    }
    else if(strcasecmp(sp1, "Board") == 0)
    {
      if((sp2 = strtok(NULL, " \t\r\n")) == NULL)
      {
        log_usies("MH_CLASS ", "no Board name");
        return -1;
      }
      if((pbrds = mh_search_board(sp2)) == NULL)
      {
        log_usies("MH_CLASS ", "Board doesn't exist");
        continue;
      }
      if((sp3 = strtok(NULL, "\t\r\n")) == NULL)
      {
        sp3 = sp2;  /* ­Y¨S¦³ title «h¥Î name ¥N´À */
      }
      else
      {
        if(*sp3 == '"')
        {
          sp3 ++;
          if((sp3 = strtok(sp3, "\"")) == NULL)
          {
            sp3 = sp2;
          }
        }
      }
      if((pent = (mhc_ent *)malloc(sizeof(mhc_ent))) == NULL)
      {
        log_usies("MH_CLASS ", "can't allocate memory for pent in B");
        return -1;
      }
      pcroot->list[pcroot->lstnum ++] = pent;
      /* initialize *pent(as a board) */
      strcpy(pent->name, sp2);
      strcpy(pent->title, sp3);
      pent->lstnum = MH_ENT_BOARD;
      pent->flag = 0;
      pent->list = NULL;
      pent->brds = pbrds;
      /*                              */
    }
    else if(strcasecmp(sp1, "Comment") == 0)
    {
      if((sp3 = strtok(NULL, "\t\r\n")) == NULL)
      {
        sp3 = sp2;  /* ­Y¨S¦³ title «h¥Î name ¥N´À */
      }
      else
      {
        if(*sp3 == '"')
        {
          sp3 ++;
          if((sp3 = strtok(sp3, "\"")) == NULL)
          {
            sp3 = sp2;
          }
        }
      }
      if((pent = (mhc_ent *)malloc(sizeof(mhc_ent))) == NULL)
      {
        log_usies("MH_CLASS ", "can't allocate memory for pent in C");
        return -1;
      }
      pcroot->list[pcroot->lstnum ++] = pent;
      /* initialize *pent(as a board) */
      pent->name[0] = '\0';
      strcpy(pent->title, sp3);
      pent->lstnum = MH_ENT_COMMENT;
      pent->flag = 0;
      pent->list = NULL;
      pent->brds = NULL;
      /*                              */
    }
    else if(strcasecmp(sp1, "File") == 0)
    {
      if((sp2 = strtok(NULL, " \t\r\n")) == NULL)
      {
        log_usies("MH_CLASS ", "no Directory name");
        return -1;
      }
      if((sp3 = strtok(NULL, "\t\r\n")) == NULL)
      {
        sp3 = sp2;  /* ­Y¨S¦³ title «h¥Î name ¥N´À */
      }
      else
      {
        if(*sp3 == '"')
        {
          sp3 ++;
          if((sp3 = strtok(sp3, "\"")) == NULL)
          {
            sp3 = sp2;
          }
        }
      }
      if((sp4 = strtok(NULL, " \t\r\n")) == NULL)
      {
        log_usies("MH_CLASS ", "no File name");
        return -1;
      }
      if((pent = (mhc_ent *)malloc(sizeof(mhc_ent))) == NULL)
      {
        log_usies("MH_CLASS ", "can't allocate memory for pent in F");
        return -1;
      }
      pcroot->list[pcroot->lstnum ++] = pent;
      pent->lstnum = 0;
      pent->flag = 0;
      pent->list = NULL;
      pent->brds = NULL;

      /* ¬°¤F±N File ¤]ºâ¶i depth, ©Ò¥H¥ý push */
      if(mhc_ent_stack_push(pcroot) == -1)
      {
        log_usies("MH_CLASS ", "depth > MH_MAX_ENT_DEPTH in F");
        return -1;
      }
      mh_load_classlist(pent, sp4);  /* »¼°j */
      if((pcroot = mhc_ent_stack_pop()) == NULL)
      {
        log_usies("MHC_CLASS ", "why the stack is empty???");
        return -1;
      }

      /* initialize *pent(as a directory) */
      strcpy(pent->name, sp2);
      strcpy(pent->title, sp3);
      /*                                 */
    }
    else if(strcasecmp(sp1, "End") == 0)
    {
      if((sp2 = strtok(NULL, " \t\r\n")) == NULL || *sp2 == '#')  /* ¤@¦¸¸Ñ¨M */
      {
        do
        {
#ifdef MH_ADJUST_ENT_LIST_SIZE
          if((tmplist = (mhc_ent **)calloc(pcroot->lstnum, sizeof(mhc_ent *))) == NULL)
            /* allocate ¤@¶ô (pcroot->lstnum * sizeof(mhc_ent *)) ªºªÅ¶¡, ¶¶«K¶ñ 0 */
          {
            log_usies("MH_CLASS ", "can't allocate memory for tmplist in E");
            return -1;
          }
          for(a = 0;a < pcroot->lstnum;a ++)
          {
            tmplist[a] = pcroot->list[a];
          }
          free(pcroot->list);
          pcroot->list = tmplist;
#endif
        } while((pcroot = mhc_ent_stack_pop()) != NULL);
      }
      else if(strcasecmp(sp2, "Directory") == 0)
      {
#ifdef MH_ADJUST_ENT_LIST_SIZE
        if((tmplist = (mhc_ent **)calloc(pcroot->lstnum, sizeof(mhc_ent *))) == NULL)
          /* allocate ¤@¶ô (pcroot->lstnum * sizeof(mhc_ent *)) ªºªÅ¶¡, ¶¶«K¶ñ 0 */
        {
          log_usies("MH_CLASS ", "can't allocate memory for tmplist in ED");
          return -1;
        }
        for(a = 0;a < pcroot->lstnum;a ++)
        {
          tmplist[a] = pcroot->list[a];
        }
        free(pcroot->list);
        pcroot->list = tmplist;
#endif
        if((pcroot = mhc_ent_stack_pop()) == NULL)
        {
          log_usies("MH_CLASS ", "why the stack is empty???");
          return -1;
        }
      }
    }
  };
  
#ifdef MH_ADJUST_ENT_LIST_SIZE
  if((tmplist = (mhc_ent **)calloc(tmproot.lstnum, sizeof(mhc_ent *))) == NULL)
    /* allocate ¤@¶ô (tmproot.lstnum * sizeof(mhc_ent *)) ªºªÅ¶¡, ¶¶«K¶ñ 0 */
  {
    log_usies("MH_CLASS ", "can't allocate memory for tmplist in R");
    return -1;
  }
  for(a = 0;a < tmproot.lstnum;a ++)
  {
    tmplist[a] = tmproot.list[a];
  }
  free(tmproot.list);
  tmproot.list = tmplist;
#endif
  root->list = tmproot.list;
  root->lstnum = tmproot.lstnum;
  root->flag = 0;
  root->brds = NULL;
  
  /* °O±o free mempry (?) */
  
  fclose(fp);
  return 0;
}

void
mh_entlist_foot()
{
  prints("[34;46m  ¿ï¾Ü¬ÝªO  [31;47m  (c)[30m·s¤å³¹¼Ò¦¡  [31m(v/V)[30m¼Ð°O¤wÅª/¥¼Åª  [31m(y)[30m¿z¿ï%s  [31m(z)[30m¤Á´«¿ï¾Ü  [0m",
    yank_flag ? "³¡¥÷" : "¥þ³¡");
}

/* UI...¶â...¦A§ï */
void mh_show_entlist(mhc_ent *root, int clsflag, int head, int newflag)
{
  int a;
  int count = 0;
  mhc_ent *pent;
  boardstat *pbrds;
  char buf1[200];
  
  if(clsflag)
  {
    showtitle("¬ÝªO¦Cªí", BoardName);
    prints("[¡ö]¥D¿ï³æ [¡÷]¾\\Åª [¡ô¡õ]¿ï¾Ü [y]¸ü¤J [S]±Æ§Ç [/]·j´M [TAB]¤åºK¡E¬ÝªO [h]¨D§U\n"
      "[7m%-20s Ãþ  §O %-32s§ë²¼ ªO    ¥D     [0m",
      "  ½s¸¹  ¬Ý  ªO", "¤¤   ¤å   ±Ô   ­z");
    move(b_lines, 0);
    mh_entlist_foot();
  }
  for(a = 0;a < b_lines - 3;a ++)
  {
    pent = root->list[head + a];
    move(a + 3, 0);
/*    sprintf(buf1, "%s%c", root.list[a]->name, (root.list[a]->lstnum == -1) ? ' ' : '/');
    sprintf(buf2, "%3d %%-%ds %%-%ds", IDLEN + 1, BTLEN);
    sprintf(buf3, buf2, buf1, root.list[a]->title);*/
    if(head + a < root->lstnum
      && (pent->lstnum != MH_ENT_BOARD || pent->brds != NULL))
        /* board ¦s¦b¤~¦L */
    {
      count ++;
      if(pent->lstnum == MH_ENT_BOARD)
      {
        /*prints("%5d %-13s %-42s%c %.13s", head + a + 1, buf1, pent->title,
          " VR"[pent->brds->bvote], pent->brds->BM);*/
        pbrds = pent->brds;
        if (yank_flag == 2)
          prints("%5d %c ", head + a + 1, 'A');
        else if (!newflag)
          prints("%5d %c ", head + a + 1, pbrds->zap ? '-' : ' ');
        else if (pbrds->zap)
        {
          pbrds->total = pbrds->unread = 0;
          outs("   ¡ß ¡ß");
        }
        else
        {
          if (pbrds->total == -1)
            check_newpost(pbrds);
          if (newflag)
             prints("%6d%s", pbrds->total, pbrds->unread ? "£¾" : "¡C");
        }
        prints("%-13s%-42s%c %.13s",
          pbrds->name, pbrds->title, " VR"[pbrds->bvote], pbrds->BM);
        
      }
      else
      {
        sprintf(buf1, "%s%c", pent->name,
          (pent->lstnum >= 0) ? '/' : ' ');
        prints("%5d   %-13s %-42s", head + a + 1, buf1, pent->title);
      }
    }
    clrtoeol();
  }
  if(count == 0)
  {
    move(3, 0);
    prints("       No......");
  }
}

void mh_class(mhc_ent *root, char *filename, int newflag)
{
  mhc_ent *pcroot;
  boardstat *pbrds;
  int a, b;
  int c, d;
  uschar cflag;
  int num, head;
  int ch1;
  char buf1[200], buf2[200], buf3[200];
  
  if(root->list == NULL)
  {
    sprintf(buf1, "loading classlist: %s", filename);
    log_usies("MH_CLASS ", buf1);
    mhc_ent_stack_flush();
    if(mh_load_classlist(root, filename) == -1 || mhc_ent_stack_num != 0)
    {
      log_usies("MH_CLASS ", "error loading classlist in mh_class()");
      root = NULL;
      return;
    }
  }
  if(root->lstnum <= 0)
  {
    root->list = NULL;
    return;
  }
  
  setutmpmode(newflag ? READNEW : READBRD);
  if(cuser.userlevel == 0)
    yank_flag = 1;
  
  cflag = YEA;
  pcroot = root;
  num = 0;
  head = -1;

  do
  {
    if(num < 0)
      num = 0;
    else if(num >= pcroot->lstnum)
      num = pcroot->lstnum - 1;
    if(head < 0)
    {
      if(newflag != 0)
      {
        b = num;
        while(num < pcroot->lstnum)
        {
          if(pcroot->list[num]->brds != NULL)
          {
            pbrds = pcroot->list[num]->brds;
            if(pbrds->total == -1)
              check_newpost(pbrds);
            if(pbrds->unread)
              break;
          }
          num ++;
        }
        if(num >= pcroot->lstnum)
          num = b;
      }
      head = (num / p_lines) * p_lines;
      mh_show_entlist(pcroot, YEA, head, newflag);
    }
    else if(num < head || num >= head + p_lines)
    {
      head = (num / p_lines) * p_lines;
      mh_show_entlist(pcroot, NA, head, newflag);
    }
  
    if(pcroot->lstnum > 0)
      ch1 = cursor_key(num - head + 3, 0);
    else
      ch1 = igetkey();
      
    switch(ch1)
    {
      case KEY_UP:
        if(--num < 0)
          num = pcroot->lstnum - 1;
        break;
      case KEY_PGUP:
        num -= p_lines;
        if(num < 0)
          num = pcroot->lstnum - 1;
        break;
      case KEY_DOWN:
        if(++num >= pcroot->lstnum)
          num = 0;
        break;
      case KEY_PGDN:
        if(num == pcroot->lstnum - 1)
          num = 0;
        else
          num += p_lines;
        break;
      case KEY_LEFT:
        if((pcroot = mhc_ent_stack_pop()) == NULL)
        {
          cflag = NA;
        }
        else
        {
          num = (pcroot->flag >> 1);
          pcroot->flag &= 1;
          head = -1;
        }
        break;
      case '\n':
      case KEY_RIGHT:
        if(pcroot->lstnum <= 0)
        {
          /* do nothing */
        }
        else if(pcroot->list[num]->lstnum >= 0)  /* Directory */
        {
          /* Enter directory */
          pcroot->flag |= (num << 1);
          if(mhc_ent_stack_push(pcroot) == -1)
          {
            log_usies("MH_CLASS ", "depth > MH_MAX_ENT_DEPTH in mh_class()");
            return;
          }
          pcroot = pcroot->list[num];
          num = 0;
          head = -1;
        }
        else if(pcroot->list[num]->lstnum == MH_ENT_BOARD)  /* Board */
        {
          /* Read */
          pbrds = pcroot->list[num]->brds;
          brc_initial(pbrds->name);
  
          if (yank_flag == 2)
          {
            setbdir(buf1, currboard);
            b = have_author(currboard) - 1;
            head = b - t_lines / 2;
            getkeep(buf1, head > 1 ? head : 1, -(b + 1));
          }
          else if (newflag)
          {
            setbdir(buf1, currboard);
            b = unread_position(buf1, pbrds);
            head = b - t_lines / 2;
            getkeep(buf1, head > 1 ? head : 1, b + 1);
          }

          board_visit_time = zapbuf[pbrds->pos];
          if (!pbrds->zap)
            time((time_t *) &zapbuf[pbrds->pos]);

          Read();

          pbrds->total = head = -1;
        
          head = -1;
          setutmpmode(newflag ? READNEW : READBRD);
        }
        else if(pcroot->list[num]->lstnum == MH_ENT_COMMENT)  /* Comment */
        {
          /* do nothing */
        }
        break;
      case KEY_HOME:
        num = 0;
        break;
      case KEY_END:
        num = pcroot->lstnum - 1;
        break;
      case 'c':
        if(yank_flag == 2)
        {
          newflag = yank_flag = 0;
          brdnum = -1;
        }
        mh_show_entlist(pcroot, YEA, head, newflag ^= 1);
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
        if((b = search_num(ch1, pcroot->lstnum)) >= 0)
          num = b;
/*        mh_entlist_foot();*/
        break;
      case Ctrl('I'):
        t_idle();
        mh_show_entlist(pcroot, YEA, head, newflag);
        break;
      case Ctrl('U'):
        t_users();
        mh_show_entlist(pcroot, YEA, head, newflag);
        break;
      default:
        cflag = NA;
        break;
    }
  } while(cflag);
  save_zapbuf();
}
#endif

#define MH_CLASS_DEBUG

#define MH_CLASS_DIRECTORY_SIZE (200)

#define MH_CLASS_END (0)
#define MH_CLASS_COMMENT (1)
#define MH_CLASS_BOARD (2)
#define MH_CLASS_DIRECTORY (3)
#define MH_CLASS_LINK (4)

#define MH_CLASS_NONE (0)

struct mh_class_ent
{
  uschar type;
  uschar mode;
  uschar name[IDLEN + 1];
  uschar title[BTLEN + 1];
  struct mh_class_ent *parent, *leftc, *rightc;
  void *ptr;
};
typedef struct mh_class_ent mh_class_ent;

struct mh_class_file_ent
{
  uschar type;
  uschar mode;
  uschar name[IDLEN + 1];
  uschar title[BTLEN + 1];
};
typedef struct mh_class_file_ent mh_class_file_ent;

mh_class_ent root;

int mh_class_add_brother(mh_class_ent *curp, mh_class_ent *brother)
{
  brother->parent = curp->parent;
  brother->rightc = curp->rightc;
  curp->rightc = brother;
}

int mh_class_add_child(mh_class_ent *curp, mh_class_ent *child)
{
  child->parent = curp;
  child->rightc = curp->leftc;
  curp->leftc = child;
}

int mh_class_delete_brother(mh_class_ent *curp)
{
  if(curp->rightc != NULL)
  /* ¤£À³¸Ó¬O NULL */
    curp->rightc = curp->rightc->rightc;
}

int mh_class_delete_child(mh_class_ent *curp)
{
  if(curp->leftc != NULL)
  /* ¤£À³¸Ó¬O NULL */
    curp->leftc = curp->leftc->rightc;
}

boardstat *mh_search_board(char *name)
{
  int a;
  
  /* linear search, §ï¦¨ binary search? */
  for(a = 0;a < brdnum;a ++)
  {
    if(strcasecmp(name, nbrd[a].name) == 0)
      return &nbrd[a];
  }
  return NULL;
}

int mh_class_load_class_list_from_text(mh_class_ent *root, char *filename)
{
  FILE *fp;
  char buf[256];
  char *sp1, *sp2, *sp3;
  mh_class_ent *croot;
  mh_class_ent *curp;
  mh_class_ent *tmp;
  boardstat *pbrd;
  
  if((fp = fopen(filename, "r")) == NULL)
  {
    log_usies("MHClass", "can't open file");
    return -1;
  }
  
  if(root == NULL)
  {
    if((root = malloc(sizeof(mh_class_ent))) == NULL)
    {
      log_usies("MHClass", "can't alloc memory for root");
      return -1;
    }
    root->type = MH_CLASS_DIRECTORY;
    root->mode = MH_CLASS_NONE;
    root->name[0] = '\0';
    root->title[0] = '\0';
    root->ptr = NULL;
    root->parent = NULL;
    root->leftc = NULL;
    root->rightc = NULL;
  }
  
  croot = root;
  curp = NULL;
  
  if(brdnum <= 0)
  {
    load_boards();
    if(brdnum <= 0)
      return;
    qsort(nbrd, brdnum, sizeof(boardstat), cmpboard);
  }
  
  while(fgets(buf, 200, fp) != NULL)
  {
    sp1 = strtok(buf, " ");
    if(sp1[0] == '#')
    /* µù¸Ñ */
      continue;
    if(strcasecmp(sp1, "Board") == 0)
    /* ¬ÝªO("Board") */
    {
#ifdef MH_CLASS_DEBUG
      log_usies("MHClass", "Board");
#endif
      if((sp2 = strtok(NULL, " \t\r\n")) == NULL)
      {
        log_usies("MHClass", "no board name");
        return -1;
      }
      if((pbrd = mh_search_board(sp2)) == NULL)
      {
        log_usies("MHClass", "board doesn't exist");
        continue;
      }
      if((sp3 = strtok(NULL, " \t\r\n")) == NULL)
      {
        sp3 = pbrd->title;
      }

      if((tmp = (mh_class_ent *)malloc(sizeof(mh_class_ent))) == NULL)
      {
        log_usies("MHClass", "can't alloc memory for tmp in Board");
        return -1;
      }
      
      if(curp == NULL)
      /* ¥Ø¿ý¬OªÅªº */
        mh_class_add_child(croot, tmp);
      else
        mh_class_add_brother(curp, tmp);
      tmp->rightc = NULL;
      tmp->leftc = NULL;
      tmp->type = MH_CLASS_BOARD;
      strncpy(tmp->name, sp2, IDLEN);
      strncpy(tmp->title, sp3, BTLEN);
      tmp->ptr = (void *)pbrd;
#ifdef MH_CLASS_DEBUG
      sprintf(buf, "croot:%p curp:%p tmp:%p tmp->parent:%p", croot, curp, tmp, tmp->parent);
      log_usies("MHClass", buf);
#endif
      curp = tmp;
    }
    else if(strcasecmp(sp1, "Directory") == 0)
    /* ¥Ø¿ý("Directory") */
    {
#ifdef MH_CLASS_DEBUG
      log_usies("MHClass", "Directory");
#endif
      if((sp2 = strtok(NULL, " \t\r\n")) == NULL)
      {
        log_usies("MHClass", "no directory name");
        return -1;
      }
      if((sp3 = strtok(NULL, " \t\r\n")) == NULL)
      {
        sp3 = sp2;
      }

      if((tmp = (mh_class_ent *)malloc(sizeof(mh_class_ent))) == NULL)
      {
        log_usies("MHClass", "can't alloc memory for tmp in Directory");
        return -1;
      }
      
      if(curp == NULL)
      /* ¥Ø¿ý¬OªÅªº */
        mh_class_add_child(croot, tmp);
      else
        mh_class_add_brother(curp, tmp);
      tmp->rightc = NULL;
      tmp->leftc = NULL;
      tmp->type = MH_CLASS_DIRECTORY;
      strncpy(tmp->name, sp2, IDLEN);
      strncpy(tmp->title, sp3, BTLEN);
#ifdef MH_CLASS_DEBUG
      sprintf(buf, "croot:%p curp:%p tmp:%p tmp->parent:%p", croot, curp, tmp, tmp->parent);
      log_usies("MHClass", buf);
#endif
      croot = tmp;
      curp = NULL;
    }
    else if(strcasecmp(sp1, "Comment") == 0)
    {
    }
    else if(strcasecmp(sp1, "End") == 0)
    {
#ifdef MH_CLASS_DEBUG
      log_usies("MHClass", "End");
#endif
      if((sp2 = strtok(NULL, " \t\r\n")) == NULL || sp2[0] == '#')
      {
      }
      else if(strcasecmp(sp2, "Directory") == 0)
      {
#ifdef MH_CLASS_DEBUG
        log_usies("MHClass", "End Directory");
        sprintf(buf, "croot:%p curp:%p curp->parent:%p", croot, curp, curp->parent);
        log_usies("MHClass", buf);
#endif
        curp = croot;
        if(croot == NULL)
          log_usies("MHClass", "what?");
        croot = curp->parent;
      }
    }
  }
  
  fclose(fp);
}

int mh_class_load_class_list(mh_class_ent *root, char *filename)
{
  FILE *fp;
  char buf[256];
  char *sp1, *sp2, *sp3;
  mh_class_file_ent tmpcfe;
  mh_class_ent *croot;
  mh_class_ent *curp;
  mh_class_ent *tmp;
  boardstat *pbrd;
  
  if((fp = fopen(filename, "rb")) == NULL)
  {
    log_usies("MHClass", "can't open file");
    return -1;
  }
  
  if(root == NULL)
  {
    if((root = malloc(sizeof(mh_class_ent))) == NULL)
    {
      log_usies("MHClass", "can't alloc memory for root");
      return -1;
    }
    root->type = MH_CLASS_DIRECTORY;
    root->mode = MH_CLASS_NONE;
    root->name[0] = '\0';
    root->title[0] = '\0';
    root->ptr = NULL;
    root->parent = NULL;
    root->leftc = NULL;
    root->rightc = NULL;
  }
  
  croot = root;
  curp = NULL;
  
  if(brdnum <= 0)
  {
    load_boards();
    if(brdnum <= 0)
      return;
    qsort(nbrd, brdnum, sizeof(boardstat), cmpboard);
  }
  
  while(fread(&tmpcfe, sizeof(mh_class_file_ent), 1, fp) != 0)
  {
    if(tmpcfe.type == MH_CLASS_COMMENT)
    /* µù¸Ñ */
      continue;
    if(tmpcfe.type == MH_CLASS_BOARD)
    /* ¬ÝªO("Board") */
    {
#ifdef MH_CLASS_DEBUG
      log_usies("MHClass", "Board");
#endif
      if((pbrd = mh_search_board(tmpcfe.name)) == NULL)
      {
        log_usies("MHClass", "board doesn't exist");
        continue;
      }

      if((tmp = (mh_class_ent *)malloc(sizeof(mh_class_ent))) == NULL)
      {
        log_usies("MHClass", "can't alloc memory for tmp in Board");
        return -1;
      }
      
      if(curp == NULL)
      /* ¥Ø¿ý¬OªÅªº */
        mh_class_add_child(croot, tmp);
      else
        mh_class_add_brother(curp, tmp);
      tmp->rightc = NULL;
      tmp->leftc = NULL;
      memcpy(tmp, &tmpcfe, sizeof(mh_class_file_ent));
      tmp->ptr = (void *)pbrd;
#ifdef MH_CLASS_DEBUG
      sprintf(buf, "croot:%p curp:%p tmp:%p tmp->parent:%p", croot, curp, tmp, tmp->parent);
      log_usies("MHClass", buf);
#endif
      curp = tmp;
    }
    else if(tmpcfe.type == MH_CLASS_DIRECTORY)
    /* ¥Ø¿ý("Directory") */
    {
#ifdef MH_CLASS_DEBUG
      log_usies("MHClass", "Directory");
#endif

      if((tmp = (mh_class_ent *)malloc(sizeof(mh_class_ent))) == NULL)
      {
        log_usies("MHClass", "can't alloc memory for tmp in Directory");
        return -1;
      }
      
      if(curp == NULL)
      /* ¥Ø¿ý¬OªÅªº */
        mh_class_add_child(croot, tmp);
      else
        mh_class_add_brother(curp, tmp);
      tmp->rightc = NULL;
      tmp->leftc = NULL;
      memcpy(tmp, &tmpcfe, sizeof(mh_class_file_ent));
#ifdef MH_CLASS_DEBUG
      sprintf(buf, "croot:%p curp:%p tmp:%p tmp->parent:%p", croot, curp, tmp, tmp->parent);
      log_usies("MHClass", buf);
#endif
      croot = tmp;
      curp = NULL;
    }
    else if(tmpcfe.type == MH_CLASS_COMMENT)
    {
    }
    else if(tmpcfe.type == MH_CLASS_END)
    {
#ifdef MH_CLASS_DEBUG
      log_usies("MHClass", "End Directory");
      sprintf(buf, "croot:%p curp:%p curp->parent:%p", croot, curp, curp->parent);
      log_usies("MHClass", buf);
#endif
      curp = croot;
      if(croot == NULL)
        log_usies("MHClass", "what?");
      croot = curp->parent;
    }
  }
  
  fclose(fp);
}

int mh_class_save_class_list(mh_class_ent *root)
{
  mh_class_file_ent tmpcfe = {MH_CLASS_END, 0, "", ""};
  FILE *fp;
  char buf[256], buf2[256];
  mh_class_ent *curp, *croot;
  int count;
  
  if((fp = fopen("tmp/classlist.bin", "wb")) == NULL)
  {
    return -1;
  }
  
  count = 0;
  croot = root;
  curp = root->leftc;
  
  while(croot != NULL)
  {
    fwrite(curp, sizeof(mh_class_file_ent), 1, fp);
    if(curp->type == MH_CLASS_DIRECTORY)
    {
      croot = curp;
      curp = croot->leftc;
    }
    else
    {
      while(curp != root && curp != NULL && curp->rightc == NULL)
      {
        fwrite(&tmpcfe, sizeof(mh_class_file_ent), 1, fp);
        curp = croot;
        croot = curp->parent;
      }
      if(curp != NULL && curp->rightc != NULL)
        curp = curp->rightc;
    }
  }
  
  fclose(fp);
}

int mh_class_dump_class_list(mh_class_ent *root)
{
  FILE *fp;
  char buf[256], buf2[256];
  mh_class_ent *curp, *croot;
  int a, l;
  
  if((fp = fopen("tmp/classlist.out", "w")) == NULL)
  {
    return -1;
  }
  
  fprintf(fp, "%d\n", sizeof(mh_class_ent));
  
  l = 0;
  croot = root;
  curp = root->leftc;
  
  while(croot != NULL)
  {
    for(a = 0; a < l; a ++)
      buf[a] = ' ';
    buf[a] = '\0';
    sprintf(buf2, "%-10s %-13s %p\n", (curp->type == MH_CLASS_BOARD) ? "Board" : "Directory", curp->name, curp->parent);
    strcat(buf, buf2);
    fprintf(fp, buf);
    if(curp->type == MH_CLASS_DIRECTORY)
    {
      l += 2;
      croot = curp;
      curp = croot->leftc;
    }
    else
    {
      while(curp != root && curp != NULL && curp->rightc == NULL)
      {
        l -= 2;
        curp = croot;
        croot = curp->parent;
      }
      if(curp != NULL && curp->rightc != NULL)
        curp = curp->rightc;
    }
  }
  
  fclose(fp);
}

int mh_pre_class(void)
{
#if 0
  mh_class(&root, MH_CLASS_FILE, 0);
#endif
#if 0
  mh_class_load_class_list_from_text(&root, "etc/classlist");
#else
  mh_class_load_class_list(&root, "tmp/classlist.bin");
#endif
  mh_class_dump_class_list(&root);
  mh_class_save_class_list(&root);
  return 0;
}

int mh_pre_daily(void)
{
#if 0
  mh_class(&daily, MH_DAILY_FILE, 0);
#endif
  return 0;
}

#define MH_LOGINFROM_USER (1)
#define MH_LOGINFROM_ADDR (2)
#define MH_LOGINFROM_ANY (3)

char *mh_strtolower(char str[])
{
  char *sp;
  
  sp = str;
  for(; *sp != '\0'; sp ++)
    *sp = tolower(*sp);
  return str;
}

int mh_loginfrom_cmpaddr(char ostr[], char ostr2[])
{
  int r;
  char str[100], str2[100];
  char *sp;
  
  r = 0;
  strncpy(str, ostr, 99);
  mh_strtolower(str);
  strncpy(str2, ostr2, 99);
  mh_strtolower(str2);
  if(strcasecmp(str, str2) == 0)
    return 1;
  sp = strstr(str, str2);
  return (sp != NULL && (str2[0] == '.' || sp == str) &&
          (str2[strlen(str2) - 1] == '.' || sp - str == strlen(str) - strlen(str2)));
}

void mh_loginfrom_getfields(char str[], char **type, char **key, char **value)
{
  char *sp, *sp2;
  
  sp = str;
  sp2 = strsep(&sp, "#");
  if(sp2 == NULL || *sp2 == '\0')
  {
    *type = *key = *value = NULL;
    return;
  }
  sp = sp2;
  while((*type = strsep(&sp, " \t")) != NULL && **type == '\0')
    ;
  while((*key = strsep(&sp, " \t")) != NULL && **key == '\0')
    ;
  *value = strsep(&sp, "\n");
}

int mh_loginfrom_check(char dst[], char userid[], char from[], int ltype, FILE *fp)
{
  char buf[200];
  char *sp, *sp2, *sp3;
  int type;

  while(fgets(buf, 199, fp) != NULL)
  {
    mh_loginfrom_getfields(buf, &sp, &sp2, &sp3);
    if(sp != NULL && sp2 != NULL && sp3 != NULL)
    {
      if(strcasecmp(sp, "User") == 0)
        type = MH_LOGINFROM_USER;
      else if(strcasecmp(sp, "Addr") == 0)
        type = MH_LOGINFROM_ADDR;
      else
        type = MH_LOGINFROM_ANY;
      type &= ltype;

      if((type & MH_LOGINFROM_USER && strcasecmp(userid, sp2) == 0) ||
         (type & MH_LOGINFROM_ADDR && mh_loginfrom_cmpaddr(from, sp2) != 0))
      {
        strncpy(dst, sp3, 28);
        return 1;
      }
    }
  }
  
  return 0;
}

char *mh_loginfrom(char dst[], char userid[], char from[])
{
  FILE *fp;
  char buf[200];
  int r;
  
  r = 0;
#if 0
  setuserfile(buf, "loginfrom");
  if((fp = fopen(buf, "r")) != NULL)
  {
    if(mh_loginfrom_check(dst, userid, from, MH_LOGINFROM_ADDR, fp))
      r = 1;
    fclose(fp);
  }
#endif

  if(!r && (fp = fopen("etc/loginfrom", "r")) != NULL)
  {
    mh_loginfrom_check(dst, userid, from, MH_LOGINFROM_ANY, fp);
    fclose(fp);
  }
  
  return dst;
}

void mh_welcome(void)
{
  if(cuserrc.welcome & MH_USERRC_WELCOME_NOTE)
    more(fn_note_ans, 2);
  if(cuserrc.welcome & MH_USERRC_WELCOME_DAY)
    x_issue();
  if(cuserrc.welcome & MH_USERRC_WELCOME_WEEK)
    x_week();
  if(cuserrc.welcome & MH_USERRC_WELCOME_TOPUSER)
    x_user();
  if(cuserrc.welcome & MH_USERRC_WELCOME_TODAY)
    x_today();
  /*if(cuserrc.welcome & MH_USERRC_WELCOME_NOTE2)
    more(fn_note_ans2, 2);*/
}

int mh_generic_test(void)
{
  char dst[100];
  char src[] = "Fw: ´ú¸Õ";
  
  move(10,0);
  outs(mh_qp_encode(dst, 100, src, "Big5"));
  pressanykey();
}
