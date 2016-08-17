#define VACATION
/*-------------------------------------------------------*/
/* register.c   ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : user register routines                       */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


/* ------------------- */
/* password encryption */
/* ------------------- */

char *crypt();
static char pwbuf[14];


char *
genpasswd(pw)
  char *pw;
{
  if (pw[0])
  {
    char saltc[2], c;
    int i;

    i = 9 * getpid();
    saltc[0] = i & 077;
    saltc[1] = (i >> 6) & 077;

    for (i = 0; i < 2; i++)
    {
      c = saltc[i] + '.';
      if (c > '9')
        c += 7;
      if (c > 'Z')
        c += 6;
      saltc[i] = c;
    }
    strcpy(pwbuf, pw);
    return crypt(pwbuf, saltc);
  }
  return "";
}


int
checkpasswd(passwd, test)
  char *passwd, *test;
{
  char *pw;

  strncpy(pwbuf, test, 14);
  pw = crypt(pwbuf, passwd);
  return (!strncmp(pw, passwd, 14));
}


/* ------------------ */
/* �ˬd user ���U���p */
/* ------------------ */


static int
bad_user_id(userid)
  char *userid;
{
  register char ch;

  if (strlen(userid) < 2)
    return 1;

  if (not_alpha(*userid))
    return 1;

  if (!ci_strcmp(userid, str_new))
    return 1;

  while (ch = *(++userid))
  {
    if (not_alnum(ch))
      return 1;
  }
  return 0;
}


/* -------------------------------- */
/* New policy for allocate new user */
/* (a) is the worst user currently  */
/* (b) is the object to be compared */
/* -------------------------------- */


static int
compute_user_value(urec, clock)
  userec *urec;
  time_t clock;
{
  int value;

  /* if (urec) has XEMPT permission, don't kick it */
  if ((urec->userid[0] == '\0') || (urec->userlevel & PERM_XEMPT))
    return 9999;

  value = (clock - urec->lastlogin) / 60;       /* minutes */

  /* new user should register in 30 mins */
/*  if (strcmp(urec->userid, str_new) == 0)
    return (30 - value);*/ /* MH */ /* �ȮɧR�� */

#ifdef  VACATION
  return 120 * 24 * 60 - value; /* �H�����O�s�b�� 120 �� */
#else
  if (!urec->numlogins)         /* �� login ���\�̡A���O�d */
    return -1;
  if (urec->numlogins <= 3)     /* #login �֩�T�̡A�O�d 30 �� */
    return 30 * 24 * 60 - value;

  /* ���������U�̡A�O�d 45 �� */
  /* �@�뱡�p�A�O�d 90 �� */
  return (urec->userlevel & PERM_LOGINOK ? 90 : 45) * 24 * 60 - value;
#endif
}


static int
getnewuserid(char *newuserid)
{
  static char *fn_fresh = ".fresh";
  extern struct UCACHE *uidshm;
  userec utmp, zerorec;
  time_t clock;
  struct stat st;
  int fd, val, i;
  char genbuf[200];
  char genbuf2[200];

  memset(&zerorec, 0, sizeof(zerorec));
  clock = time(NULL);

/*
woju: reload shm before searchnewuser ("resolve"_ucache)
*/
  reload_ucache();

  /* -------------------------------------- */
  /* Lazy method : ����M�w�g�M�����L���b�� */
  /* -------------------------------------- */

  if ((i = searchnewuser(0)) == 0)
  {

    /* ------------------------------- */
    /* �C 1 �Ӥp�ɡA�M�z user �b���@�� */
    /* ------------------------------- */

    if ((stat(fn_fresh, &st) == -1) || (st.st_mtime < clock - 3600))
    {
      if ((fd = open(fn_fresh, O_RDWR | O_CREAT, 0600)) == -1)
        return -1;
      write(fd, ctime(&clock), 25);
      close(fd);
      log_usies("CLEAN", "dated users");

      printf("�M��s�b����, �еy�ݤ���...\n\r");
      if ((fd = open(fn_passwd, O_RDWR | O_CREAT, 0600)) == -1)
        return -1;
      i = 0;
      while (i < MAXUSERS)
      {
        i++;
        if (read(fd, &utmp, sizeof(userec)) != sizeof(userec))
          break;
/*
woju
*/
        if ((val = compute_user_value(&utmp, clock)) < 0 &&
            !belong("etc/anonymous", utmp.userid)) {
           sprintf(genbuf, "#%d %-12s %15.15s %d %d %d",
             i, utmp.userid, ctime(&(utmp.lastlogin)) + 4,
             utmp.numlogins, utmp.numposts, val);
           if (val > -1 * 60 * 24 * 365)
           {
             log_usies("CLEAN", genbuf);
             sprintf(genbuf, "home/%s", utmp.userid);
             sprintf(genbuf2, "tmp/%s", utmp.userid);
             sweep(utmp.userid);
             if (dashd(genbuf) && Rename(genbuf, genbuf2))
             {
               sprintf(genbuf, "/bin/rm -fr home/%s", utmp.userid);
               system(genbuf);
             }
             if (lseek(fd, (i - 1) * sizeof(userec), SEEK_SET) != -1)
                write(fd, &zerorec, sizeof(utmp));
           }
           else
              log_usies("DATED", genbuf);
        }
      }
      close(fd);
      time(&(uidshm->touchtime));
    }
  }
  if ((fd = open(fn_passwd, O_RDWR | O_CREAT, 0600)) == -1)
    return -1;
  flock(fd, LOCK_EX);

  i = searchnewuser(1);
  if ((i <= 0) || (i > MAXUSERS))
  {
    flock(fd, LOCK_UN);
    close(fd);
    if (more("etc/user_full", NA) == -1)
      printf("��p�A�ϥΪ̱b���w�g���F�A�L�k���U�s���b��\n\r");
    val = (st.st_mtime - clock + 3660) / 60;
    printf("�е��� %d ������A�դ@���A���A�n�B\n\r", val);
    sleep(2);
    exit(1);
  }

  sprintf(genbuf, "uid %d, %s", i, newuserid);
  log_usies("APPLY", genbuf);
  sprintf(genbuf, "home/%s", newuserid);
  if (stat(genbuf, &st) != -1) {
    sprintf(genbuf, "uid %d, %s", i, newuserid);
    log_usies("COLLISION", genbuf);
    exit(1);
  }

  strcpy(zerorec.userid, str_new);
  zerorec.lastlogin = clock;
  if (lseek(fd, sizeof(zerorec) * (i - 1), SEEK_SET) == -1)
  {
    flock(fd, LOCK_UN);
    close(fd);
    return -1;
  }
  write(fd, &zerorec, sizeof(zerorec));
  setuserid(i, zerorec.userid);
  flock(fd, LOCK_UN);
  close(fd);
  return i;
}



void
new_register()
{
  userec newuser;
  char passbuf[STRLEN];
  int allocid, try;
  char genbuf[200];

#if 0
  time_t now;

  /* ------------------ */
  /* ���w�P���X������U */
  /* ------------------ */

  now = time(0);
  sprintf(genbuf, "etc/no_register_%3.3s", ctime(&now));
  if (more(genbuf, NA) != -1)
  {
    pressanykey();
    exit(1);
  }
#endif

  memset(&newuser, 0, sizeof(newuser));

  more("etc/register", NA);
  try = 0;
  while (1)
  {
    if (++try >= 6)
    {
      outs("\n�z���տ��~����J�Ӧh�A�ФU���A�ӧa\n");
      refresh();

      pressanykey();
      oflush();
      exit(1);
    }
    getdata(0, 0, msg_uid, newuser.userid, IDLEN + 1, DOECHO, 0);

    if (bad_user_id(newuser.userid))
      outs("�L�k�����o�ӥN���A�Шϥέ^��r���A�åB���n�]�t�Ů�\n");
    else if (searchuser(newuser.userid))
      outs("���N���w�g���H�ϥ�\n");
    /* Prince: �t�ηl�a�ƥ�Ȯɩʪ��B�z */
    else if (belong("etc/fixlist",newuser.userid))
    {
      char ans[4];
      outs("[ĵ�i]��ID�b�����t�ηl�a�O�ަW�椤!!�Y�D��Ҧ��H���U,����N���v�R��!!\n");
      getdata(0, 0, "�T�w�n�H��ID���U(Y/N)[N]?", ans, 4, DOECHO, 0);
      if ( *ans == 'y' )
        break;
    }
    /* Prince: ���ƥ�L��i�N���q�R�� */
    else
      break;
  }


    try = 0;
  while (1)
  {
    if (++try >= 6)
    {
      outs("\n�z���տ��~����J�Ӧh�A�ФU���A�ӧa\n");
      refresh();

      pressanykey();
      oflush();
      exit(1);

      /*
      return;
      */
/*longjmp(byebye, -1);*/
    }
    if ((getdata(0, 0, "�г]�w�K�X�G", passbuf, PASSLEN, NOECHO, 0) < 3) ||
      !strcmp(passbuf, newuser.userid))
    {
      outs("�K�X��²��A���D�J�I�A�ܤ֭n 4 �Ӧr�A�Э��s��J\n");
      continue;
    }
    strncpy(newuser.passwd, passbuf, PASSLEN);
    getdata(0, 0, "���ˬd�K�X�G", passbuf, PASSLEN, NOECHO, 0);
    if (strncmp(passbuf, newuser.passwd, PASSLEN))
    {
      outs("�K�X��J���~, �Э��s��J�K�X.\n");
      continue;
    }
    passbuf[8] = '\0';
    strncpy(newuser.passwd, genpasswd(passbuf), PASSLEN);
    break;
  }
/*
  getdata(0, 0, "�׺ݾ��κA [vt100]�G", newuser.termtype, 8, ECHO);
  if (newuser.termtype[0] == '\0')
  strcpy(newuser.termtype, "vt100");
*/
  newuser.userlevel = PERM_DEFAULT;
  newuser.uflag = COLOR_FLAG | BRDSORT_FLAG | MOVIE_FLAG;
  newuser.firstlogin = newuser.lastlogin = time(NULL);
  newuser.year = newuser.month = newuser.day = 0;
/*  newuser.sex = 17;*/ /* Tzu */
  newuser.sex = MAX_SEXS;  /* MH */
  
  allocid = getnewuserid(newuser.userid);
  if (allocid > MAXUSERS || allocid <= 0)
  {
    fprintf(stderr, "�����H�f�w�F���M�I\n");
    exit(1);
  }

  if (substitute_record(fn_passwd, &newuser, sizeof(newuser), allocid) == -1)
  {
    fprintf(stderr, "�Ⱥ��F�A�A���I\n");
    exit(1);
  }
  setuserid(allocid, newuser.userid);
  if (!dosearchuser(newuser.userid))
  {
    fprintf(stderr, "�L�k�إ߱b��\n");
    exit(1);
  }
}


void
check_register()
{
  char *ptr;
  char genbuf[200];

  stand_title("�иԲӶ�g�ӤH���");

  while (strlen(cuser.username) < 2)
    getdata(2, 0, "�︹�ʺ١G", cuser.username, 24, DOECHO, 0);

  for (ptr = cuser.username; *ptr; ptr++)
  {
    if (*ptr == 9)              /* TAB convert */
      *ptr == ' ';
  }

  while (strlen(cuser.realname) < 4)
    getdata(4, 0, "�u��m�W�G", cuser.realname, 20, DOECHO, 0);

  while (strlen(cuser.address) < 8)
    getdata(6, 0, "�p���a�}�G", cuser.address, 50, DOECHO, 0);
  
  if (!strchr(cuser.email, '@'))
  {
    bell();
    move(b_lines - 4, 0);
    prints("\
�� ���F�z���v�q�A�ж�g�u�ꪺ E-mail address�A �H��T�{�դU�����A\n\
   �榡�� [44muser@domain_name[0m �� [44muser@\\[ip_number\\][0m�C\n\n\
�� �p�G�z�u���S�� E-mail�A�Ъ����� [return] �Y�i�C");

    do
    {
      getdata(8, 0, "�q�l�H�c�G", cuser.email, 50, DOECHO, 0);
      if (!cuser.email[0])
        sprintf(cuser.email, "%s%s", cuser.userid, str_mail_address);
    } while (!strchr(cuser.email, '@'));

#ifdef  EMAIL_JUSTIFY
    mail_justify(cuser);
#endif
  }

  while (cuser.month > 12 || cuser.month < 1 ||
    cuser.day > 31 || cuser.day < 1 || cuser.year > 90 || cuser.year < 40)
  {
    int len;
    sprintf(genbuf, "%02i/%02i/%02i",
    cuser.month, cuser.day, cuser.year);
    len = getdata(10, 0, "�ͤ� ���/���/�褸�G", genbuf, 9, DOECHO, 0);
    if (len && len != 8)
      continue;
    if (!len)
      continue;
    else if (len == 8)
    {
      cuser.month = (genbuf[0] - '0') * 10 + (genbuf[1] - '0');
      cuser.day   = (genbuf[3] - '0') * 10 + (genbuf[4] - '0');
      cuser.year  = (genbuf[6] - '0') * 10 + (genbuf[7] - '0');
    }
    else
      continue;
  }
  
/* MH */
  while (cuser.sex >= MAX_SEXS){
    if(HAS_PERM(PERM_SYSOP))
    {
      strcpy(genbuf,
        "�ʧO (1)���� (2)�j�� (3)���} (4)���� (5)���� (6)���� (7)�Ӫ� (8)�q��"
        "\n     (9)�ծ�H (10)�˪֤H (11)�����H (12)�J�L�^�H (13)���~��"
        "\n     (14)Ada Augusta Byron"
        "[?]�G");
    }
    else
    {
      strcpy(genbuf,
        "�ʧO (1)���� (2)�j�� (3)���} (4)���� (5)���� (6)���� (7)�Ӫ� (8)�q��"
        "[?]�G");
    }
    getdata(12, 0, genbuf, genbuf, 3, DOECHO, 0);
/*    if (genbuf[0] >= '1' && genbuf[0] <= '9')
      cuser.sex = genbuf[0] - '1';*/
    {
      int mhtmp1;
      
      mhtmp1 = atoi(genbuf);
      if(mhtmp1 >= 1 && mhtmp1 <= MAX_SEXS)
        cuser.sex = mhtmp1 - 1;
    }
/*    */      
  }

  cuser.userlevel |= PERM_DEFAULT;
  if (!HAS_PERM(PERM_SYSOP) && !(cuser.userlevel & PERM_LOGINOK))
  {
    /* �^�йL�����{�ҫH��A�δ��g E-mail post �L */

    setuserfile(genbuf, "email");
    if (dashf(genbuf))
    {
/*
Leeym
*/
      cuser.userlevel |= ( PERM_POST | PERM_LOGINOK );
        /* �����v���U���Ш̦ۤv�W�w.�������Y��{��.���T�{���o post */
/*
comment out by woju (already done by mailpost)
      strcpy(cuser.justify, cuser.email);
      ��i��� emailreply �T�{��T�{��Ƥ��ť�
*/
      unlink(genbuf);
        /* �����T�{���\��o�@�ʫH�i���w�����T�{ */
        {
          fileheader mhdr;
          char title[128], buf1[80];
          FILE* fp;
          sethomepath(buf1, cuser.userid);
          stampfile(buf1, &mhdr);
          strcpy(mhdr.owner, "����");
          strncpy(mhdr.title, "[���U���\\]", TTLEN);
          mhdr.savemode = 0;
          mhdr.filemode = 0;
          sethomedir(title, cuser.userid);
          append_record(title, &mhdr, sizeof(mhdr));
          Link("etc/registered", buf1);
        }
    }

#ifdef  STRICT
    else
    {
      cuser.userlevel &= ~PERM_POST;
      more("etc/justify", YEA);
    }
#endif
  }

#ifdef  NEWUSER_LIMIT
  /*if (cuser.lastlogin - cuser.firstlogin < 3 * 86400 && ...)*/
  if (!(cuser.userlevel & PERM_LOGINOK) && !HAS_PERM(PERM_SYSOP))
  {
    if (cuser.lastlogin - cuser.firstlogin < 3 * 86400)
      cuser.userlevel &= ~PERM_POST;
    more("etc/newuser", YEA);
  }
#endif

  if (HAS_PERM(PERM_DENYPOST) && !HAS_PERM(PERM_SYSOP))
    cuser.userlevel &= ~PERM_POST;
}
