/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* buggy.c                                                         */
/*                                                                 */
/* SOB verison 3.0 ªº§ó¥¿»P¸É±j(?)                                 */
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
int get_max_ever_login()                /* °O¿ý¦P®É³Ì°ª¤W½u¤H¼Æ */
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

   fprintf(f2,"¤£¨}¤ûªª³õ¦b[%d/%d/%d]®É,",ptime->tm_year, ptime->tm_mon + 1, ptime->tm_mday);
   fprintf(f2,"³Ð¤U³Ì°ª¦P®É¤W½u¤H¼Æ¬°%d¤H\n\n",num);

   fclose(f1);
   fclose(f2);
}



char *where(char *from)           /* §ó§ïUserList¤Wªº¬G¶m */
{                                 /* ¥Îwhere°µ§PÂ_¦A¦^¶Ç  */

   #define NUM_HOSTS1 28    /* §ó°Ê¸ê®Æ°O±o­n§ï³o¸Ì */
   char compare1[NUM_HOSTS1][2][30]={
         /* ¥Ø«eª¬ºA */
        {"reading",             "°Ù®Ñ¤¤..."     },
        {"eating",              "¦Y¶º¤¤..."     },
         /* ¯¸ªø¸sªº¹q¸£ */
        {"localhost",           "ªª³õºÞ²z³B"    },
        {"zoo.m3.ntu.edu.tw",   "ªª³õºÞ²z³B"    },
        {"Atlantis.m3.ntu.t",   "¨È¯SÄõ´£´µ¤§Á¼"},
        {"IAN.m3.ntu.edu.tw",   "¨Ó¦ÛÅ]¬É"    },
        {"Pahn.m1.ntu.edu",     "ªª³õ°â²¼¤f"    },
        {"140.112.213.207",     "ªi¯S¦h¤§®a"    },
         /* ¦n¤Íªº¹q¸£ */
        {"kk.f2.ntu.edu.tw",    "¿ß¿ß¿ß¿ß¿ß¿ß"  },
        {"Luzern.m3.ntu.edu",   "¥ÕÃ¨¥Õ·ö¥ÕÃ¨"  },
        {"Elfstone.m1.ntu",     "¤p»·ªº®a"      },
        {"Turtle.m1.ntu.edu",   "§ÔªÌÀtªº¤U¤ô¹D"},
        {"KYO.m1.ntu.edu.tw",   "Às°ì"          },
        {"Dolphin.m3.ntu.edu",  "®ü³b¼Ö¶é"      },
        {"140.112.169.187",     "¸©¸©ªººÛ"      },
        {"polymer.m1.ntu.ed",   "ª×Às©~"        },
        {"140.112.169.223",     "¯»¦â¤ô´¹¤º"    },
        {"x.m1.ntu.edu.tw",     "¤pªá¿ß"        },
        {"ccstudent.ee.ntu",    "¥x¤j¹q¾÷¤u§@¯¸"},
        {"m7070.m7.ntu.edu.",   "Unknown"       },
        {"WZ.m1.ntu.edu.tw",    "wzªº®a"        },
        {"140.112.213.176",     "¶­³¾ªº¬G¶m"    },
        {"m7201.m7.ntu.edu.",   "¨¸´c¤p¤p®eªº®a"},
        {"140.119.138.28",      "¤å¤s°Ïªª³õ"    },
        {"140.112.169.233",     "­·¦³¬G¶m¶Ü¡H"  },
         /* ¤j¤j­Ìªº¥D¾÷ */
        {"freebsd.ee.ntu.edu",  "¯«¯¦²`¶øªº¦a¤è"},
        {"woju.g1.ntu.edu.tw",  "¸Þ²§¤§°ì"      },
        {"Power.m7.ntu.edu.t",  "¬Jmagic¤SPower"}
               };

   #define NUM_HOSTS2 25    /* §ó°Ê¸ê®Æ°O±o­n§ï³o¸Ì */
   char compare2[NUM_HOSTS2][2][30]={
        {".m1.ntu.edu",         "¥x¤j¨k¤@ªÙ"    },
        {".m3.ntu.edu",         "¥x¤j¨k¤TªÙ"    },
        {"140.112.213.",        "¥x¤j¨k¤TªÙ"    },
        {"140.112.217",         "¥x¤j¨k¤CªÙ"    },
        {".m7.ntu.e",           "¥x¤j¨k¤CªÙ"    },
        {"140.112.171.",        "¥x¤j¨k¤KªÙ"    },
        {"140.112.172.",        "¥x¤j¨k¤KªÙ"    },
        {".m8.ntu.ed",          "¥x¤j¨k¤KªÙ"    },
        {"140.112.222.",        "¥x¤j¤k¤GªÙ"    },
        {"140.112.225",         "¥x¤j¤k¤­ªÙ"    },
        {"140.112.169.",        "¥x¤j¬ã¤GªÙ"    },
        {".cc.ntu.edu.",        "¥x¤j­p¤¤"      },
        {".ee.ntu.ed",          "¥x¤j¹q¾÷¨t"    },
        {"140.112.20.",         "¥x¤j¹q¾÷¨t"    },
        {"140.112.52.",         "¥x¤jª«²z¨t"    },
        {"140.112.145",         "¥x¤j´¶³q¤j¼Ó"  },
        {"168.95.100.",         "HiNet "        },
        {"168.95.101.",         "HiNet "        },
        {"140.112.8.",          "¥x¤j­p¤¤¤u§@¯¸"},
        {"dialup.ntu",          "¥x¤j¼·±µ±M½u"  },
        {".nctu.",              "°ê¥ß¥æ³q¤j¾Ç"  },
        {".ncku.ed",            "°ê¥ß¦¨¥\\¤j¾Ç" },
        {"140.116.",            "°ê¥ß¦¨¥\\¤j¾Ç" },
        {"203.64.52.",          "¥_¤@¤k¤¤"      },
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


/* ¹CÀ¸¤¶²Ð by Izero */
game_introduce()
{
clear();
secret=1;
more("/bbs1/home/bbs/etc/game_introduce",YEA);
secret=0;
return;
}

/* ³Â±N by Izero */
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
    outs("\nÅwªï¥úÁ{¡i¤£¨}¤ûªª³õ¡j¨Ï¥Î ARCHIE ¥\\¯à\n");
    outs("¥»¥\\¯à±N¬°±z¦C¥X¦b­þ­Ó FTP ¯¸¦s¦³±z±ý´M§äªºÀÉ®×.\n");
    outs("½Ð¿é¤J±ý·j´Mªº¦r¦ê, ©Îª½±µ«ö <ENTER> ¨ú®ø¡C\n");
    outs("                                                         coder by Harimau\n");
    outs("                                                      provided by Leeym\n");
    outs("                                                     modifided by Izero\n");
    getdata(15,0,"½Ð¿é¤J·j´M¦r¦ê¡G",buf,20,DOECHO,0);
    if (buf[0]=='\0')
      {
      prints("\n¨ú®ø·j´M.....\n");
      pressanykey();
      return;
      }
    for(s=buf;*s != '\0';s++)
        {
        if(isspace(*s))
            {
            prints("\n¤@¦¸¥u¯à·j´M¤@­Ó¦r¦ê°Õ, ¤£¯à¤Ó³g¤ß³á!!");
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
       getdata(0, 0, "­n±Nµ²ªG±H¦^«H½c¶Ü(Y/N)¡H[N]", ans, 3, DOECHO,0);
       if (*ans == 'y')
        {
          fileheader mhdr;
          char title[128], buf1[80];
          FILE* fp;

          sethomepath(buf1, cuser.userid);
          stampfile(buf1, &mhdr);
          strcpy(mhdr.owner, cuser.userid);
          sprintf(genbuf2, "Archie ·j´MÀÉ®×: %s µ²ªG", genbuf1);
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
       outs("\nÅwªï¥úÁ{¡i¤£¨}¤ûªª³õ¡j¨Ï¥Î [­^º~¦r¨å] ¥\\¯à\n");
       outs("½Ð¿é¤J±ý¬dªº³æ¦r, ©Îª½±µ«ö <ENTER> ¨ú®ø¡C\n");
       getdata(16,0,"½Ð¿é¤J³æ¦r¡G",buf,20,DOECHO,0);
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
/* ³Â±N by Izero */
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
  outs("Åwªï¶i¤J ¡´[31m[1;33m¤£¨}¤ûªª³õ[0m¡´ ¨Óª±[1;37mºô¸ô¾ôµP[0m\n");
  outs("[1;35mKaede[37m:[0m ª±¾ôµP¤£¥Î½ä¿ú,\n");
  outs("       ÁÙ¥i¥H©M¤j®a³s½Ë,¦hª±¦³¯q°·±d³á!! *^_^*\n\n");
  outs("[1;34mRaw[37m:[0m ¶â¶â..ÁÙ¥i¥H¹w¨¾¦Ñ¤HÃ¨§b¯g!!\n");
  outs("     (§O¤£¬Û«H,³o¦³®Ú¾Úªº!!)\n\n");
  outs("p.s: ²Ä¤@¦ì¤W½uªÌ±N¦Û°Ê¦¨¬° Server!\n");
  outs("\n");
  outs("¯S§O·PÁÂKaede & Raw´£¨Ñ¨ó§U\n");

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
  prints("ÁÂÁÂ [1;33m%s[0m ªº¥úÁ{!!\n", cuser.userid);
  outs("Åwªï¤U¦¸¦A¨Óª±¾ôµP°Ú!! ^o^\n");
  pressanykey();

  clear();
  return 0;
}

/* §PÂ_°²¤é¤Î¥Í¤é  Izero */
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

int get_max_users()                 /* ¬ö¿ýµù¥U¤H¼Æ */
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
   fprintf(f1,"¤£¨}¤ûªª³õ¦b[%d/%d/%d]®É,",ptime->tm_year, ptime->tm_mon + 1, ptime->tm_mday);
   fprintf(f1,"µù¥U¤H¼Æ¦¨ªø¨ì %d ¤H\n\n",num);
   fclose(f1);
   fclose(f2);
}


/* ¨q¥X¾ú¥v¬ö¿ý by Izero */
history()
{
clear();
more("etc/history",YEA);
return;
}

/* ­«­n¨Æ¶µ by Izero */
x_announce()
{
clear();
more("etc/announce",NA);
pressanykey();
return;
}


static struct commands tree_menu[] = {

  board, 0, "00Club         [1;32;40m¥þ¬ÙªÀ¹Î±M°Ï[0m",
  board, 0, "11Tainan       [1;33;40m¥x«n±MÄÝ°Ï[0m",
  board, 0, "22Liming       [1;34;40m¾¤©ú¤¤¾Ç±M°Ï[0m",
  board, 0, "33NTUEE        [1;31;40m¥x¤j¹q¾÷±M°Ï[0m",
  board, 0, "44Kaohsiung    [1;35;40m°ª¶¯±M°Ï->¥´ª¯¤Hªº¤Ñ¤U[0m",
  board, 0, "55CSIE         [1;36;40m¥x¤j¸ê°T¦a¤U«Ç[0m",
  board, 0, "66CK           [1;31;40m¥x¥_¥«¥ß«Ø¤¤±M°Ï[0m",

NULL, 0, NULL};

tree()
{

secret=1;
domenu(CLASS,"ªª³õ¸Ìªº¾ðªL",'0',tree_menu);
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
             return 1; /* ¨S°ÝÃD */
           }
         }
         fclose(fp);
         return 0;  /* ¤W¨Óªºhost¤£¦b³\¥i¦W³æ¤º */
      }
    }
    fclose(fp);
  }
  return 1; /* ¨S°ÝÃD */
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
  outs("Åwªï¥úÁ{\n");
  outs("½Ð¦h§Q¥Î¸ê®Æ¬d¸ß¨t²Î!\n");

  outs("«ö Enter Áä¶i¤J¥x¤j Gopher ¬d¸ß¨t²Î");
  if (!getdata(13, 0, "½Ð¿é¤J Gopher ºô§}¡G", buf, 30, DOECHO, 0))
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
