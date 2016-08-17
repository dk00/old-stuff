/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* buggy.c                                                         */
/*                                                                 */
/* SOB verison 3.0 ���󥿻P�ɱj(?)                                 */
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
int get_max_ever_login()                /* �O���P�ɳ̰��W�u�H�� */
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

   fprintf(f2,"���}�������b[%d/%d/%d]��,",ptime->tm_year, ptime->tm_mon + 1, ptime->tm_mday);
   fprintf(f2,"�ФU�̰��P�ɤW�u�H�Ƭ�%d�H\n\n",num);

   fclose(f1);
   fclose(f2);
}



char *where(char *from)           /* ���UserList�W���G�m */
{                                 /* ��where���P�_�A�^��  */

   #define NUM_HOSTS1 28    /* ��ʸ�ưO�o�n��o�� */
   char compare1[NUM_HOSTS1][2][30]={
         /* �ثe���A */
        {"reading",             "�ٮѤ�..."     },
        {"eating",              "�Y����..."     },
         /* �����s���q�� */
        {"localhost",           "�����޲z�B"    },
        {"zoo.m3.ntu.edu.tw",   "�����޲z�B"    },
        {"Atlantis.m3.ntu.t",   "�ȯS����������"},
        {"IAN.m3.ntu.edu.tw",   "�Ӧ��]��"    },
        {"Pahn.m1.ntu.edu",     "�����Ⲽ�f"    },
        {"140.112.213.207",     "�i�S�h���a"    },
         /* �n�ͪ��q�� */
        {"kk.f2.ntu.edu.tw",    "�߿߿߿߿߿�"  },
        {"Luzern.m3.ntu.edu",   "��è�շ���è"  },
        {"Elfstone.m1.ntu",     "�p�����a"      },
        {"Turtle.m1.ntu.edu",   "�Ԫ��t���U���D"},
        {"KYO.m1.ntu.edu.tw",   "�s��"          },
        {"Dolphin.m3.ntu.edu",  "���b�ֶ�"      },
        {"140.112.169.187",     "��������"      },
        {"polymer.m1.ntu.ed",   "���s�~"        },
        {"140.112.169.223",     "���������"    },
        {"x.m1.ntu.edu.tw",     "�p���"        },
        {"ccstudent.ee.ntu",    "�x�j�q���u�@��"},
        {"m7070.m7.ntu.edu.",   "Unknown"       },
        {"WZ.m1.ntu.edu.tw",    "wz���a"        },
        {"140.112.213.176",     "�������G�m"    },
        {"m7201.m7.ntu.edu.",   "���c�p�p�e���a"},
        {"140.119.138.28",      "��s�Ϫ���"    },
        {"140.112.169.233",     "�����G�m�ܡH"  },
         /* �j�j�̪��D�� */
        {"freebsd.ee.ntu.edu",  "�����`�����a��"},
        {"woju.g1.ntu.edu.tw",  "�޲�����"      },
        {"Power.m7.ntu.edu.t",  "�Jmagic�SPower"}
               };

   #define NUM_HOSTS2 25    /* ��ʸ�ưO�o�n��o�� */
   char compare2[NUM_HOSTS2][2][30]={
        {".m1.ntu.edu",         "�x�j�k�@��"    },
        {".m3.ntu.edu",         "�x�j�k�T��"    },
        {"140.112.213.",        "�x�j�k�T��"    },
        {"140.112.217",         "�x�j�k�C��"    },
        {".m7.ntu.e",           "�x�j�k�C��"    },
        {"140.112.171.",        "�x�j�k�K��"    },
        {"140.112.172.",        "�x�j�k�K��"    },
        {".m8.ntu.ed",          "�x�j�k�K��"    },
        {"140.112.222.",        "�x�j�k�G��"    },
        {"140.112.225",         "�x�j�k����"    },
        {"140.112.169.",        "�x�j��G��"    },
        {".cc.ntu.edu.",        "�x�j�p��"      },
        {".ee.ntu.ed",          "�x�j�q���t"    },
        {"140.112.20.",         "�x�j�q���t"    },
        {"140.112.52.",         "�x�j���z�t"    },
        {"140.112.145",         "�x�j���q�j��"  },
        {"168.95.100.",         "HiNet "        },
        {"168.95.101.",         "HiNet "        },
        {"140.112.8.",          "�x�j�p���u�@��"},
        {"dialup.ntu",          "�x�j�����M�u"  },
        {".nctu.",              "��ߥ�q�j��"  },
        {".ncku.ed",            "��ߦ��\\�j��" },
        {"140.116.",            "��ߦ��\\�j��" },
        {"203.64.52.",          "�_�@�k��"      },
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


/* �C������ by Izero */
game_introduce()
{
clear();
secret=1;
more("/bbs1/home/bbs/etc/game_introduce",YEA);
secret=0;
return;
}

/* �±N by Izero */
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
    outs("\n�w����{�i���}�������j�ϥ� ARCHIE �\\��\n");
    outs("���\\��N���z�C�X�b���� FTP ���s���z���M�䪺�ɮ�.\n");
    outs("�п�J���j�M���r��, �Ϊ����� <ENTER> �����C\n");
    outs("                                                         coder by Harimau\n");
    outs("                                                      provided by Leeym\n");
    outs("                                                     modifided by Izero\n");
    getdata(15,0,"�п�J�j�M�r��G",buf,20,DOECHO,0);
    if (buf[0]=='\0')
      {
      prints("\n�����j�M.....\n");
      pressanykey();
      return;
      }
    for(s=buf;*s != '\0';s++)
        {
        if(isspace(*s))
            {
            prints("\n�@���u��j�M�@�Ӧr���, ����ӳg�߳�!!");
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
       getdata(0, 0, "�n�N���G�H�^�H�c��(Y/N)�H[N]", ans, 3, DOECHO,0);
       if (*ans == 'y')
        {
          fileheader mhdr;
          char title[128], buf1[80];
          FILE* fp;

          sethomepath(buf1, cuser.userid);
          stampfile(buf1, &mhdr);
          strcpy(mhdr.owner, cuser.userid);
          sprintf(genbuf2, "Archie �j�M�ɮ�: %s ���G", genbuf1);
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
       outs("\n�w����{�i���}�������j�ϥ� [�^�~�r��] �\\��\n");
       outs("�п�J���d����r, �Ϊ����� <ENTER> �����C\n");
       getdata(16,0,"�п�J��r�G",buf,20,DOECHO,0);
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
/* �±N by Izero */
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
  outs("�w��i�J ��[31m[1;33m���}������[0m�� �Ӫ�[1;37m�������P[0m\n");
  outs("[1;35mKaede[37m:[0m �����P���ν��,\n");
  outs("       �٥i�H�M�j�a�s��,�h�����q���d��!! *^_^*\n\n");
  outs("[1;34mRaw[37m:[0m ���..�٥i�H�w���ѤHè�b�g!!\n");
  outs("     (�O���۫H,�o���ھڪ�!!)\n\n");
  outs("p.s: �Ĥ@��W�u�̱N�۰ʦ��� Server!\n");
  outs("\n");
  outs("�S�O�P��Kaede & Raw���Ѩ�U\n");

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
  prints("���� [1;33m%s[0m �����{!!\n", cuser.userid);
  outs("�w��U���A�Ӫ����P��!! ^o^\n");
  pressanykey();

  clear();
  return 0;
}

/* �P�_����Υͤ�  Izero */
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

int get_max_users()                 /* �������U�H�� */
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
   fprintf(f1,"���}�������b[%d/%d/%d]��,",ptime->tm_year, ptime->tm_mon + 1, ptime->tm_mday);
   fprintf(f1,"���U�H�Ʀ����� %d �H\n\n",num);
   fclose(f1);
   fclose(f2);
}


/* �q�X���v���� by Izero */
history()
{
clear();
more("etc/history",YEA);
return;
}

/* ���n�ƶ� by Izero */
x_announce()
{
clear();
more("etc/announce",NA);
pressanykey();
return;
}


static struct commands tree_menu[] = {

  board, 0, "00Club         [1;32;40m���٪��αM��[0m",
  board, 0, "11Tainan       [1;33;40m�x�n�M�ݰ�[0m",
  board, 0, "22Liming       [1;34;40m�������ǱM��[0m",
  board, 0, "33NTUEE        [1;31;40m�x�j�q���M��[0m",
  board, 0, "44Kaohsiung    [1;35;40m�����M��->�����H���ѤU[0m",
  board, 0, "55CSIE         [1;36;40m�x�j��T�a�U��[0m",
  board, 0, "66CK           [1;31;40m�x�_���߫ؤ��M��[0m",

NULL, 0, NULL};

tree()
{

secret=1;
domenu(CLASS,"�����̪���L",'0',tree_menu);
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
             return 1; /* �S���D */
           }
         }
         fclose(fp);
         return 0;  /* �W�Ӫ�host���b�\�i�W�椺 */
      }
    }
    fclose(fp);
  }
  return 1; /* �S���D */
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
  outs("�w����{\n");
  outs("�Цh�Q�θ�Ƭd�ߨt��!\n");

  outs("�� Enter ��i�J�x�j Gopher �d�ߨt��");
  if (!getdata(13, 0, "�п�J Gopher ���}�G", buf, 30, DOECHO, 0))
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
