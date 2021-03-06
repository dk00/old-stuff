/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* buggy.c                                                         */
/*                                                                 */
/* SOB verison 3.0 的更正與補強(?)                                 */
/*                                                                 */
/*                                                by buggy, Izero  */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* TEST */

#include "bbs.h"
#include "modes.h"
#include <stdio.h>
#include <time.h>

/*extern static struct commands adminlist;*/
int board();
int secret;



/* the following are added by buggy */
int get_max_ever_login()                /* 記錄同時最高上線人數 */
{
   int num;

   FILE *f=fopen("etc/max_ever_login.log","r");
   fscanf(f,"%d",&num);
   fclose(f);
   return(num);
}

void set_max_ever_login(int num)
{
   time_t now;
   struct tm *ptime;
   struct stat st;

   FILE *f1=fopen("etc/max_ever_login.log","w");
   FILE *f2=fopen("etc/history","a");

   now = time(NULL) - 6 * 60;     /* back to ancent */
   ptime = localtime(&now);

   fprintf(f1,"%d",num);

   fprintf(f2,"不良牛牧場在[%d/%d/%d]時,",ptime->tm_year, ptime->tm_mon + 1, ptime->tm_mday);
   fprintf(f2,"創下最高同時上線人數為%d人\n\n",num);

   fclose(f1);
   fclose(f2);
}



char *where(char *from)           /* 更改UserList上的故鄉 */
{                                 /* 用where做判斷再回傳  */

   #define NUM_HOSTS1 28    /* 更動資料記得要改這裡 */
   char compare1[NUM_HOSTS1][2][30]={
         /* 目前狀態 */
        {"reading",             "啃書中..."     },
        {"eating",              "吃飯中..."     },
         /* 站長群的電腦 */
        {"localhost",           "牧場管理處"    },
        {"zoo.m3.ntu.edu.tw",   "牧場管理處"    },
        {"Atlantis.m3.ntu.t",   "亞特蘭提斯之謎"},
        {"IAN.m3.ntu.edu.tw",   "來自魔界"    },
        {"Pahn.m1.ntu.edu",     "牧場售票口"    },
        {"140.112.213.207",     "波特多之家"    },
         /* 好友的電腦 */
        {"kk.f2.ntu.edu.tw",    "貓貓貓貓貓貓"  },
        {"Luzern.m3.ntu.edu",   "白癡白痴白癡"  },
        {"Elfstone.m1.ntu",     "小遠的家"      },
        {"Turtle.m1.ntu.edu",   "忍者龜的下水道"},
        {"KYO.m1.ntu.edu.tw",   "龍域"          },
        {"Dolphin.m3.ntu.edu",  "海豚樂園"      },
        {"140.112.169.187",     "萱萱的窩"      },
        {"polymer.m1.ntu.ed",   "臥龍居"        },
        {"140.112.169.223",     "粉色水晶內"    },
        {"x.m1.ntu.edu.tw",     "小花貓"        },
        {"ccstudent.ee.ntu",    "台大電機工作站"},
        {"m7070.m7.ntu.edu.",   "Unknown"       },
        {"WZ.m1.ntu.edu.tw",    "wz的家"        },
        {"140.112.213.176",     "雁鳥的故鄉"    },
        {"m7201.m7.ntu.edu.",   "邪惡小小容的家"},
        {"140.119.138.28",      "文山區牧場"    },
        {"140.112.169.233",     "風有故鄉嗎？"  },
         /* 大大們的主機 */
        {"freebsd.ee.ntu.edu",  "神祕深奧的地方"},
        {"woju.g1.ntu.edu.tw",  "詭異之域"      },
        {"Power.m7.ntu.edu.t",  "既magic又Power"}
               };

   #define NUM_HOSTS2 25    /* 更動資料記得要改這裡 */
   char compare2[NUM_HOSTS2][2][30]={
        {".m1.ntu.edu",         "台大男一舍"    },
        {".m3.ntu.edu",         "台大男三舍"    },
        {"140.112.213.",        "台大男三舍"    },
        {"140.112.217",         "台大男七舍"    },
        {".m7.ntu.e",           "台大男七舍"    },
        {"140.112.171.",        "台大男八舍"    },
        {"140.112.172.",        "台大男八舍"    },
        {".m8.ntu.ed",          "台大男八舍"    },
        {"140.112.222.",        "台大女二舍"    },
        {"140.112.225",         "台大女五舍"    },
        {"140.112.169.",        "台大研二舍"    },
        {".cc.ntu.edu.",        "台大計中"      },
        {".ee.ntu.ed",          "台大電機系"    },
        {"140.112.20.",         "台大電機系"    },
        {"140.112.52.",         "台大物理系"    },
        {"140.112.145",         "台大普通大樓"  },
        {"168.95.100.",         "HiNet "        },
        {"168.95.101.",         "HiNet "        },
        {"140.112.8.",          "台大計中工作站"},
        {"dialup.ntu",          "台大撥接專線"  },
        {".nctu.",              "國立交通大學"  },
        {".ncku.ed",            "國立成功\大學" },
        {"140.116.",            "國立成功\大學" },
        {"203.64.52.",          "北一女中"      },
        {"168.95.99.",          "HiNet"}
               };


   int i;

   for(i=0;i<NUM_HOSTS1;i++)
   if(strncmp(compare1[i][0],from,15)==0)
   {
        char *local=(char *)malloc(sizeof(char)*17);
        strcpy(local,compare1[i][1]);
        return local;
    }
   for(i=0;i<NUM_HOSTS2;i++)
   if(strstr(from,compare2[i][0]))
   {
        char *local=(char *)malloc(sizeof(char)*17);
        strcpy(local,compare2[i][1]);
        return local;
    }
    return from;
}




/* the following part are patched by Izero               */

/* BBS NET by Izero */
bbs_net()
{
  int save_pager;

  clear();
  save_pager = currutmp->pager;
  currutmp->pager = NA;
  setutmpmode(BBSNET);
  reset_tty();
  do_exec("/bbsnet.sh",NULL);
  restore_tty();
  currutmp->pager = save_pager;

  clear();
  return 0;
}


/* 遊戲介紹 by Izero */
game_introduce()
{
clear();
secret=1;
more("/bbs1/home/bbs/etc/game_introduce",YEA);
secret=0;
return;
}

/* 麻將 by Izero */
x_qkmj()
{
  char buf[64];
  int save_pager;

  clear();
  more("/bbs1/home/bbs/etc/qkmj",YEA);
  save_pager = currutmp->pager;
  currutmp->pager = NA;
  setutmpmode(QKMJ);
  reset_tty();
  do_exec("/qkmj.sh", NULL);
  restore_tty();
  currutmp->pager = save_pager;
  clear();
  return 0;
}

/* archie by Izero */
x_archie()
{
    char buf[STRLEN], ans[4];
    char genbuf1[100], genbuf2[200];
    char *s;
    setutmpmode(ARCHIE);
    clear();
    movie(0);
    move(8,0);
    outs("\n歡迎光臨【不良牛牧場】使用 ARCHIE 功\能\n");
    outs("本功\能將為您列出在哪個 FTP 站存有您欲尋找的檔案.\n");
    outs("請輸入欲搜尋的字串, 或直接按 <ENTER> 取消。\n");
    outs("                                                         coder by Harimau\n");
    outs("                                                      provided by Leeym\n");
    outs("                                                     modifided by Izero\n");
    getdata(15,0,"請輸入搜尋字串：",buf,20,DOECHO,0);
    if (buf[0]=='\0')
      {
      prints("\n取消搜尋.....\n");
      pressanykey();
      return;
      }
    for(s=buf;*s != '\0';s++)
        {
        if(isspace(*s))
            {
            prints("\n一次只能搜尋一個字串啦, 不能太貪心喔!!");
            pressanykey();
            return;
            }
        }
    bbssetenv("ARCHIESTRING",buf);
    do_exec( "/archie.sh", NULL);
    log_usies("ARCHIE","");
    strcpy(genbuf1, buf);
    sprintf(buf,"bin/usr/tmp/archie.%s",cuser.userid);
    if (dashf(buf))
       {
       getdata(0, 0, "要將結果寄回信箱嗎(Y/N)？[N]", ans, 3, DOECHO,0);
       if (*ans == 'y')
        {
          fileheader mhdr;
          char title[128], buf1[80];
          FILE* fp;

          sethomepath(buf1, cuser.userid);
          stampfile(buf1, &mhdr);
          strcpy(mhdr.owner, cuser.userid);
          sprintf(genbuf2, "Archie 搜尋檔案: %s 結果", genbuf1);
          strcpy(mhdr.title, genbuf2);
          mhdr.savemode = 0;
          mhdr.filemode = 0;
          sethomedir(title, cuser.userid);
          append_record(title, &mhdr, sizeof(mhdr));
          Link(buf, buf1);
          }
       more( buf, YEA);
       unlink (buf);
       }
}

/* archie by Izero */
x_cdict()
{
    char buf[STRLEN], ans[4];
    char genbuf1[100], genbuf2[200];
    char *s;
    setutmpmode(ARCHIE);
    while (1) {
       clear();
       movie(0);
       move(14,0);
       outs("\n歡迎光臨【不良牛牧場】使用 [英漢字典] 功\能\n");
       outs("請輸入欲查的單字, 或直接按 <ENTER> 取消。\n");
       getdata(16,0,"請輸入單字：",buf,20,DOECHO,0);
       if (buf[0]=='\0')
          return;
       bbssetenv("WORD",buf);
       do_exec( "/cdict.sh", NULL);
       log_usies("CDICT","");
       strcpy(genbuf1, buf);
       sprintf(buf,"bin/usr/tmp/cdict.%s",cuser.userid);
       more(buf, YEA);
    }
}



/* qkmj2 */
/* 麻將 by Izero */
x_qkmj2()
{
  char buf[64];
  int save_pager;

  clear();
  more("bbs1/home/bbs/etc/qkmj",YEA);
  save_pager = currutmp->pager;
  currutmp->pager = NA;
  setutmpmode(QKMJ);
  reset_tty();
  do_exec("/qkmj2.sh", NULL);
  restore_tty();
  currutmp->pager = save_pager;
  clear();
  return 0;
}











x_okbridge()
{
  char buf[64];
  int save_pager;

  clear();
  outs("歡迎進入 ●[31m[1;33m不良牛牧場[0m● 來玩[1;37m網路橋牌[0m\n");
  outs("[1;35mKaede[37m:[0m 玩橋牌不用賭錢,\n");
  outs("       還可以和大家連誼,多玩有益健康喔!! *^_^*\n\n");
  outs("[1;34mRaw[37m:[0m 嗯嗯..還可以預防老人癡呆症!!\n");
  outs("     (別不相信,這有根據的!!)\n\n");
  outs("p.s: 第一位上線者將自動成為 Server!\n");
  outs("\n");
  outs("特別感謝Kaede & Raw提供協助\n");

  pressanykey();

  save_pager = currutmp->pager;
  currutmp->pager = NA;
  setutmpmode(BRIDGE);
  reset_tty();

  sprintf(buf, "/bbs1/home/bbs/bin/okbridge -n %s -s sob", cuser.userid);
  if (!mbbsd)
     do_exec(buf, NULL);

  restore_tty();
  currutmp->pager = save_pager;

  clear();
  prints("謝謝 [1;33m%s[0m 的光臨!!\n", cuser.userid);
  outs("歡迎下次再來玩橋牌啊!! ^o^\n");
  pressanykey();

  clear();
  return 0;
}

/* 判斷假日及生日  Izero */
holiday()
{
  struct tm *ptime;
  time_t now;
  time(&now);
  ptime = localtime(&now);
  if((cuser.year==0) && (cuser.userlevel))
  more("etc/check_birthday", YEA);
  else
  if ((cuser.month==ptime->tm_mon+1)&(cuser.day==ptime->tm_mday))
     {
     more("etc/birthday",YEA);
     }
}

int get_max_users()                 /* 紀錄註冊人數 */
{
   int num;
   FILE *f=fopen("etc/max_users.log","r");
   fscanf(f,"%d",&num);
   fclose(f);
   return(num);

}

void set_max_users(int num)
{
   time_t now;
   struct tm *ptime;
   struct stat st;
   FILE *f1=fopen("etc/history","a");
   FILE *f2=fopen("etc/max_users.log","w");

   now = time(NULL) - 6 * 60;     /* back to ancent */
   ptime = localtime(&now);
   fprintf(f2,"%d",num);
   fprintf(f1,"不良牛牧場在[%d/%d/%d]時,",ptime->tm_year, ptime->tm_mon + 1, ptime->tm_mday);
   fprintf(f1,"註冊人數成長到 %d 人\n\n",num);
   fclose(f1);
   fclose(f2);
}


/* 秀出歷史紀錄 by Izero */
history()
{
clear();
more("etc/history",YEA);
return;
}

/* 重要事項 by Izero */
x_announce()
{
clear();
more("etc/announce",NA);
pressanykey();
return;
}


static struct commands tree_menu[] = {

  board, 0, "00Club         [1;32;40m全省社團專區[0m",
  board, 0, "11Tainan       [1;33;40m台南專屬區[0m",
  board, 0, "22Liming       [1;34;40m黎明中學專區[0m",
  board, 0, "33NTUEE        [1;31;40m台大電機專區[0m",
  board, 0, "44Kaohsiung    [1;35;40m高雄專區->打狗人的天下[0m",
  board, 0, "55CSIE         [1;36;40m台大資訊地下室[0m",
  board, 0, "66CK           [1;31;40m台北市立建中專區[0m",

NULL, 0, NULL};

tree()
{

secret=1;
domenu(CLASS,"牧場裡的樹林",'0',tree_menu);
clear();
secret=0;
return;

}


int
check_host()
{
  FILE *fp;
  char id[15],host[5][50];
  char buf[20];
  char buf1[20];
  int i;

  strncpy(buf1,fromhost,16);
  if (fp=fopen("etc/checkhost","r"))
  {
    while((fscanf(fp,"%s %s %s %s %s",id,host[1],host[2],host[3],host[4]))!=EOF)
    {

      if (!strcmp(cuser.userid,id))
      {
         for (i=1;i<=4;i++)
         {
           strncpy(buf,host[i],16);
           if (!strcmp(buf1,buf))
           {
             fclose(fp);
             return 1; /* 沒問題 */
           }
         }
         fclose(fp);
         return 0;  /* 上來的host不在許可名單內 */
      }
    }
    fclose(fp);
  }
  return 1; /* 沒問題 */
}




#ifdef HAVE_GOPHER
/* by Izero */

x_gopher()
{
  char buf[80];
  int save_pager;

  clear();
  save_pager = currutmp->pager;
  currutmp->pager = NA;
  movie(0);
  move(12,0);
  outs("歡迎光臨\n");
  outs("請多利用資料查詢系統!\n");

  outs("按 Enter 鍵進入台大 Gopher 查詢系統");
  if (!getdata(13, 0, "請輸入 Gopher 網址：", buf, 30, DOECHO, 0))
  strcpy(buf, "gopher.ntu.edu.tw");
  strcpy(buf,strtok(buf, "<>|;[]"));
  reset_tty();
  bbssetenv("GOPHER_SITE",buf);
  do_exec("/gopher.sh",NULL);
  restore_tty();
  currutmp->pager = save_pager;
 return 0;
}


#endif




x_dc()
{
  int save_pager;
  clear();
  save_pager = currutmp->pager;
  currutmp->pager = NA;
  pressanykey();
  clear();
  reset_tty();
  do_exec("/dc.sh",NULL);
  restore_tty();
  currutmp->pager = save_pager;
 return 0;
}
