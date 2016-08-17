/*-------------------------------------------------------*/
/* vote.c       ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : boards' vote routines                        */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/

#include "bbs.h"
#include <time.h>

long atol();
extern cmpbnames();
extern int numboards;

static char STR_bv_control[] = "control";
static char STR_bv_desc[] = "desc";
static char STR_bv_ballots[] = "ballots";
static char STR_bv_results[] = "results";
static char STR_bv_flags[] = "flags";
static char STR_bv_tickets[] = "tickets";
static char STR_bv_comments[] = "comments";
static char STR_bv_tmp[] = "tmp";

void
b_suckinfile(fp, fname)
  FILE *fp;
  char *fname;
{
  FILE *sfp;

  if (sfp = fopen(fname, "r"))
  {
    char inbuf[256];

    while (fgets(inbuf, sizeof(inbuf), sfp))
      fputs(inbuf, fp);
    fclose(sfp);
  }
/* MH */
  else
  {
    char buf[100];
    
    sprintf(buf, "errno:%d, fname:%s", errno, fname);
#if 0
    log_usies("MH_DEBUG ", buf);
#else
    mh_log("log/errnolog", "b_suckinfile ", buf);
#endif
  }
/*    */
}



int
b_closepolls()
{
  static char *fn_vote_polling = ".voting";
  boardheader fh;
  struct stat st;
  FILE *cfp;
  char buf[80];
  time_t now;
  int fd, dirty;

  now = time(NULL);

/*  if (stat(fn_vote_polling, &st) == -1 || st.st_mtime > now - 3600)
    return 0;
*/

  if ((cfp = fopen(fn_vote_polling, "w")) == NULL)
    return 0;
  fprintf(cfp, ctime(&now));
  fclose(cfp);

  resolve_boards();
  if ((fd = open(fn_board, O_RDWR)) == -1)
  {
    outs(ERR_BOARD_OPEN);
    return -1;
  }

  flock(fd, LOCK_EX);
  dirty = 0;
  while (read(fd, &fh, sizeof(fh)) == sizeof(fh))
  {
    if (fh.bvote && b_close(&fh))
    {
      lseek(fd, sizeof(fh) * (getbnum(fh.brdname) - 1), SEEK_SET);
      if (write(fd, &fh, sizeof(fh)) != sizeof(fh))
      {
        sprintf(currmsg, "[1;5;37;41mWarning![m");
        kill(currpid, SIGUSR2);
        igetch();
        break;
      }
      dirty = 1;
    }
  }
  if (dirty) /* vote flag changed */
    touch_boards();

  flock(fd, LOCK_UN);
  close(fd);
  return 0;
}

void
vote_report(bname, fname, fpath)
  char *bname, *fname, *fpath;
{
  register char *ip;
  time_t dtime;
  int fd;
  fileheader header;

  ip = fpath;
  while (*(++ip));
  *ip++ = '/';

  /* get a filename by timestamp */

  dtime = time(0);
  for (;;)
  {
    sprintf(ip, "M.%d.A", dtime);
    fd = open(fpath, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd >= 0)
      break;
    dtime++;
  }
  close(fd);

  unlink(fpath);
  link(fname, fpath);

  /* append record to .DIR */

  memset(&header, 0, sizeof(fileheader));
  strcpy(header.owner,"[�����}����]");
  sprintf(header.title, "[%s] �ݪO �ﱡ����", bname);
  {
    register struct tm *ptime = localtime(&dtime);
    sprintf(header.date, "%2d/%02d", ptime->tm_mon + 1, ptime->tm_mday);
  }
  strcpy(header.filename, ip);

  strcpy(ip, ".DIR");
  if ((fd = open(fpath, O_WRONLY | O_CREAT, 0644)) >= 0)
  {
    flock(fd, LOCK_EX);
    lseek(fd, 0, SEEK_END);
    write(fd, &header, sizeof(fileheader));
    flock(fd, LOCK_UN);
    close(fd);
  }
}

int
b_close(fh)
  boardheader *fh;
{
  FILE *cfp, *tfp, *frp;
  char *bname = fh->brdname;
  char buf[STRLEN];
  char inchar, inbuf[80];
  int counts[31], fd;
  int total, num ,bid, person, grades;
  char b_control[64];
  char b_newresults[64];
  char b_report[64];
  time_t now;
  struct stat st;

  now = time(NULL);

  if (fh->bvote == 2)
  {
    if (fh->vtime < now - 7 * 86400)
    {
      fh->bvote = 0;
      return 1;
    }
    else
      return 0;
  }

  if (fh->vtime > now)
    return 0;

  fh->bvote = 2;
  setbfile(b_control, bname, STR_bv_control);
  if (stat(b_control, &st) == -1)
  {
    fh->bvote = 0;
    return 1;
  }

  memset(counts, 0, sizeof(counts));
  setbfile(buf, bname, STR_bv_flags);
  unlink(buf);
  setbfile(buf, bname, STR_bv_tickets);
  unlink(buf);
  setbfile(buf, bname, STR_bv_ballots);
  if ((fd = open(buf, O_RDONLY)) != -1)
  {
    while (read(fd, &inchar, 1) == 1)
      counts[(int) (inchar - 'A')]++;
    close(fd);
  }
  person = counts['_' - 'A'];
  unlink(buf);

  setbfile(b_newresults, bname, "newresults");
  if ((tfp = fopen(b_newresults, "w")) == NULL)
    return 1;

  fprintf(tfp, "%s\n�� �}���ɶ�: %s\n�� �벼���e:\n",
    msg_seperator, ctime(&fh->vtime));

  setbfile(buf, bname, STR_bv_desc);
  b_suckinfile(tfp, buf);
  unlink(buf);

  fprintf(tfp, "\n�� �벼���G:\n");
  total = 0;
  if (cfp = fopen(b_control, "r"))
  {
    fgets(inbuf, sizeof(inbuf), cfp);
    fgets(inbuf, sizeof(inbuf), cfp);
    grades = (int) atoi(inbuf);
    while (fgets(inbuf, sizeof(inbuf), cfp))
    {
      inbuf[(strlen(inbuf) - 1)] = '\0';
      inbuf[43] = '\0';         /* truncate */
      num = counts[inbuf[0] - 'A'];
      /* Tzu */
      if (person)
        fprintf(tfp, "    %-42s%3d �� (%4.2f %%)\n", inbuf + 3, num, (float)num * 100 / person);
      else
        fprintf(tfp, "    %-42s%3d �� (0.00 %%)\n", inbuf + 3, num);
      if (grades == 1 && num)
        grades = num * (100 - (inbuf[0] - 'A') * 10);
      else if (grades)
        grades += num * (100 - (inbuf[0] - 'A') * 10);
      /*     */
      total += num;
    }
    fclose(cfp);
  }
  unlink(b_control);
  

  if (grades && person)
    fprintf(tfp, "\n�� �������� = %4.2f ��\n", (float) grades / person);  
  else if (grades)
    fprintf(tfp, "\n�� �������� = 0.00 ��\n");  
  else
    fprintf(tfp, "\n�� �X�p���� = %d ��\n", total);  
  fprintf(tfp, "�� �벼�H�� = %d �H\n", person); /* Tzu */

  fprintf(tfp, "\n�� �ϥΪ̫�ĳ�G\n");
  setbfile(buf, bname, STR_bv_comments);
  b_suckinfile(tfp, buf);
  unlink(buf);

  
  fclose(tfp);

  setbfile(b_report, bname, "report");
  if(frp = fopen(b_report, "w")){
  b_suckinfile(frp, b_newresults);
  fclose(frp);
  }
  sprintf(inbuf,"boards/%s",bname);
  vote_report(bname, b_report, inbuf);
  /*sprintf(inbuf,"boards/%s","Record");
  vote_report(bname, b_report, inbuf);*/
  unlink(b_report);

  tfp = fopen(b_newresults, "a");
  setbfile(buf, bname, STR_bv_results);
  b_suckinfile(tfp, buf);
  fclose(tfp);
  Rename(b_newresults, buf);
  return 1;
}


int
vote_maintain(bname)
  char *bname;
{
  FILE *fp, *tick;
  char inbuf[STRLEN], buf[STRLEN];
  int num = 0, aborted, tickets, grades;
  time_t closetime, now; 
  int pos;
  boardheader fh;
  char genbuf[4];


  if (!(currmode & MODE_BOARD))
    return 0;

  stand_title("�|��벼");

  setbfile(buf, bname, STR_bv_control);
  if ((fp = fopen(buf, "r")))
  {
    int counts[31], fd, total, count = 0, person;
    char inchar;

    fgets(inbuf, sizeof(inbuf), fp);
    closetime = (time_t) atol(inbuf);
    fgets(inbuf, sizeof(inbuf), fp);
    grades = (int) atoi(inbuf);
    prints("�P�ɶ����L�k�|���ӥH�W���벼�C\n�����벼�w�p������: %s",
      ctime(&closetime));

    memset(counts, 0, sizeof(counts));
    setbfile(buf, bname, STR_bv_ballots);
    if ((fd = open(buf, O_RDONLY)) != -1)
    {
      while (read(fd, &inchar, 1) == 1)
        counts[(int) (inchar - 'A')]++;
      close(fd);
    }
    person = counts['_' - 'A'];

    outs("\n�� �w���벼����:\n\n");
    total = 0;
    while (fgets(inbuf, sizeof(inbuf), fp))
    {
      inbuf[(strlen(inbuf) - 1)] = '\0';
      inbuf[31] = '\0';         /* truncate */ /* Tzu */
      num = counts[inbuf[0] - 'A'];
      count++;
      move(((count-1)%15)+4,((count-1)/15)*40);
      if (grades)
        prints( " %3d��> %-31s%3d ��", 100 - (count - 1) * 10, inbuf, num);
      else
        prints(" %-31s%3d ��", inbuf, num);
      if (grades == 1 && num)
        grades = num * (100 - (inbuf[0] - 'A') * 10);
      else if (grades)
        grades += num * (100 - (inbuf[0] - 'A') * 10);
      total += num;
    }
    fclose(fp);

    move(b_lines-3, 0);

    if (grades && person)
      prints("�� �ثe���� = %4.2f ��\n", (float) grades / person);  
    else if (grades)
      prints("�� �ثe���� = 0.00 ��\n");
    else
      prints("�� �ثe���� = %d ��\n", total);
    prints("�� �ثe�H�� = %d �H\n", person); /* Tzu */

    getdata(b_lines - 1, 0, "(A)�����벼 (B)�����}�� (C)�~�� (E)�s��벼�H[C] ", genbuf, 4, LCECHO, 0);
    if (genbuf[0] == 'a')
    {
      setbfile(buf, bname, STR_bv_tickets);
      unlink(buf);
      setbfile(buf, bname, STR_bv_control);
      unlink(buf);
      setbfile(buf, bname, STR_bv_flags);
      unlink(buf);
      setbfile(buf, bname, STR_bv_ballots);
      unlink(buf);
      setbfile(buf, bname, STR_bv_desc);
      unlink(buf);
      setbfile(buf, bname, STR_bv_comments);
      unlink(buf);
      
      pos = search_record(fn_board, &fh, sizeof(fh), cmpbnames, (int) bname);
      fh.bvote = 0;
      if (substitute_record(fn_board, &fh, sizeof(fh), pos) == -1)
        outs(err_board_update);
      touch_boards();           /* vote flag changed */
      resolve_boards();
    }
    else if (genbuf[0] == 'b')
    {
      char b_newresults[80];
      char b_report[80];
      FILE *tfp, *frp;

      setbfile(b_newresults, bname, "newresults");
      tfp = fopen(b_newresults, "w");
      
      /* Tzu */
      now = time(NULL); 
      fprintf(tfp, "%s\n�� �}���ɶ�: %s\n�� �벼���e:\n",
        msg_seperator, ctime(&now));
      /*     */

      setbfile(buf, bname, STR_bv_tickets);
      unlink(buf);
      setbfile(buf, bname, STR_bv_flags);
      unlink(buf);
      setbfile(buf, bname, STR_bv_ballots);
      unlink(buf);
      setbfile(buf, bname, STR_bv_desc);
      b_suckinfile(tfp, buf);
      unlink(buf);

      fprintf(tfp, "\n�� �벼���G:\n");
      total = 0;
      setbfile(buf, bname, STR_bv_control);
      if (fp = fopen(buf, "r"))
      {
        fgets(inbuf, sizeof(inbuf), fp);
        fgets(inbuf, sizeof(inbuf), fp);
        grades = (int) atoi(inbuf);
        while (fgets(inbuf, sizeof(inbuf), fp))
        {
          inbuf[(strlen(inbuf) - 1)] = '\0';
          inbuf[43] = '\0';     /* truncate */
          num = counts[inbuf[0] - 'A'];
          /* Tzu */
          if (person)
            fprintf(tfp, "    %-42s%3d �� (%4.2f %%)\n", inbuf + 3, num, (float)num * 100 / person);
          else
            fprintf(tfp, "    %-42s%3d �� (0.00 %%)\n", inbuf + 3, num);
          if (grades == 1 && num)
            grades = num * (100 - (inbuf[0] - 'A') * 10);
          else if (grades)
            grades += num * (100 - (inbuf[0] - 'A') * 10);
          /*     */
          total += num;
        }
        fclose(fp);
      }
      unlink(buf);
      
      if (grades && person)
        fprintf(tfp, "\n�� �������� = %4.2f ��\n", (float) grades / person);  
      else if (grades)
        fprintf(tfp, "\n�� �������� = 0.00 ��\n");  
      else
        fprintf(tfp, "\n�� �X�p���� = %d ��\n", total);  
      fprintf(tfp, "�� �벼�H�� = %d �H\n", person); /* Tzu */
      
      fprintf(tfp, "\n�� �ϥΪ̫�ĳ�G\n");
      setbfile(buf, bname, STR_bv_comments);
      b_suckinfile(tfp, buf);
      unlink(buf);
      

      fclose(tfp);
      setbfile(b_report, bname, "report");
      if(frp = fopen(b_report, "w"))
      {
        b_suckinfile(frp, b_newresults);
        fclose(frp);
      }
      sprintf(inbuf,"boards/%s",bname);
      vote_report(bname, b_report, inbuf);
      /*sprintf(inbuf,"boards/%s","Result");
      vote_report(bname, b_report, inbuf);*/
      unlink(b_report);

      tfp = fopen(b_newresults, "a");
      setbfile(buf, bname, STR_bv_results);
      b_suckinfile(tfp, buf);
      fclose(tfp);
      Rename(b_newresults, buf);

      pos = search_record(fn_board, &fh, sizeof(fh), cmpbnames, (int) bname);
      fh.bvote = 2;
      if (substitute_record(fn_board, &fh, sizeof(fh), pos) == -1)
        outs(err_board_update);
      touch_boards();           /* vote flag changed */
      resolve_boards();
    }
    /* Tzu */
    else if (genbuf[0] == 'e')
    {
      FILE *tmpfp;
      char *prestr;
      
      mh_pressanykey("�������䭫�s�s�覹�� [�벼�v��]");
      setbfile(buf, bname, STR_bv_desc);
      aborted = vedit(buf, NA);
      if (aborted)
      {
        clear();
        outs("�������s�s��벼");
        pressanykey();
        return FULLUPDATE;
      }
      setbfile(buf, bname, STR_bv_control);
      setbfile(inbuf, bname, STR_bv_tmp);
      if ((fp = fopen(buf, "r")) && (tmpfp = fopen(inbuf, "w")))
      {
        fgets(inbuf, sizeof(inbuf), fp);
        fprintf(tmpfp, "%s", inbuf);
        fgets(inbuf, sizeof(inbuf), fp);
        strcpy(buf, (grades = (int) atoi(inbuf)) ? "Y" : "N");
        do 
          getdata(2, 0, "�����벼�H(y/n)", genbuf, 3, DOECHO, buf);
        while (*genbuf == '\0');
        fprintf(tmpfp, "%d\n", (genbuf[0]=='Y' || genbuf[0]=='y') ? YEA : NA);
        grades = (genbuf[0]=='Y' || genbuf[0]=='y') ? YEA : NA;
        clear();
        outs("\n�Ш̧ǭ��s�s��ﶵ");
        num = 0;
        while (fgets(inbuf, sizeof(inbuf), fp) && !aborted)
        {
          inbuf[(strlen(inbuf) - 1)] = '\0';
          if (grades)
            sprintf(buf, "%3d��> %c)", 100 - num * 10, num + 'A');
          else
            sprintf(buf, "%c) ", num + 'A');
          prestr = strchr(inbuf, ' ');
          if (prestr)
            strcpy(inbuf, prestr + 1);
          do  
            getdata( (num%15) + 2,(num/15)*40, buf, inbuf, 36, DOECHO, inbuf);
          while (*inbuf == '\0');
          fprintf(tmpfp, "%1c) %s\n", (num+'A'), inbuf);
          num++;
          if (num == 30 || grades && num == 11)
            aborted = 1;            
        }
        if (!aborted)
        {
          getdata((num%15) + 2,(num/15)*40, "�W�[�ﶵ�H(y/n)[N]"  , genbuf, 3, DOECHO, 0);
          if(genbuf[0]=='Y' || genbuf[0]=='y')
          while (!aborted)
          {
            sprintf(buf, "%c) ", num + 'A');
            getdata( (num%15) + 2,(num/15)*40, buf, inbuf, 36, DOECHO, 0);
            if (*inbuf)
            {
              fprintf(tmpfp, "%1c) %s\n", (num+'A'), inbuf);
              num++;
            }
            if (*inbuf == '\0' || num == 30 || grades && num == 11)
              aborted = 1;
          } 
        }
      }
      fclose(fp);
      fclose(tmpfp);
      setbfile(buf, bname, STR_bv_control);
      setbfile(inbuf, bname, STR_bv_tmp);
      unlink(buf);
      Rename(inbuf, buf);
      clear();
      outs("���s�s��벼����");
      pressanykey();
    }
    /*     */
    return FULLUPDATE;
  }

  mh_pressanykey("��������}�l�s�覹�� [�벼�v��]"); /* Tzu */
  setbfile(buf, bname, STR_bv_desc);
  aborted = vedit(buf, NA);
  if (aborted)
  {
    clear();
    outs("���������벼");
    pressanykey();
    return FULLUPDATE;
  }
  setbfile(buf, bname, STR_bv_flags);
  unlink(buf);

  clear();
  getdata(0, 0, "�����벼�i��X�� (�ܤ֢���)�H", inbuf, 4, DOECHO, 0);

  if (*inbuf == '\n' || !strcmp(inbuf, "0") || *inbuf == '\0')
    strcpy(inbuf, "1");

  time(&closetime);
  closetime += atol(inbuf) * 86400;
  setbfile(buf, bname, STR_bv_control);
  fp = fopen(buf, "w");
  fprintf(fp, "%lu\n", closetime);
  fflush(fp);
  getdata(2, 0, "�����벼�H(y/n)[N]"  , genbuf, 3, DOECHO, 0);
  fprintf(fp, "%d\n", (genbuf[0]=='Y' || genbuf[0]=='y') ? YEA : NA);
  grades = (genbuf[0]=='Y' || genbuf[0]=='y') ? YEA : NA;

  clear();
  outs("\n�Ш̧ǿ�J�ﶵ, �� ENTER �����]�w");
  num = 0;
  while (!aborted)
  {
    if (grades)
      sprintf(buf, "%3d��> %c)", 100 - num * 10, num + 'A');
    else  
      sprintf(buf, "%c) ", num + 'A');
      
    getdata( (num%15) + 2,(num/15)*40, buf, inbuf, 36, DOECHO, 0);
    if (*inbuf)
    {
      fprintf(fp, "%1c) %s\n", (num+'A'), inbuf);
      num++;
    }
    if (*inbuf == '\0' || num == 30 || grades && num == 11)
      aborted = 1;
  }
  fclose(fp);

  if(num==0)
  {
    clear();
    setbfile(buf, bname, STR_bv_control);
    unlink(buf);
    prints( "���������벼\n" );
    pressanykey();
    return FULLUPDATE;
  }
  else
  {

    pos = search_record(fn_board, &fh, sizeof(fh), cmpbnames, (int) bname);
    fh.bvote = 1;
    fh.vtime = closetime;
    if (substitute_record(fn_board, &fh, sizeof(fh), pos) == -1)
      outs(err_board_update);
    touch_boards();             /* vote flag changed */

#ifdef  HAVE_REPORT
    b_report("OPEN");
#endif

    while(1)
    {
      move( t_lines - 3, 0);
      if (grades)
        strcpy(inbuf, "1");
      else
      {
        sprintf(buf,"�аݥi�H��X�� (1~%1d): ",num);
        getdata(t_lines-3, 0, buf , inbuf, 3, DOECHO, 0);
        if(atoi(inbuf)<=0 || atoi(inbuf)>num)
          continue;
      }
      setbfile( buf, bname, "tickets" );
      if((tick= fopen(buf, "w")) == NULL)
        break;
      fprintf(tick,"%s\n",inbuf);
      fclose(tick);
      break;
    }
    move( t_lines - 2, 0);
    outs("�}�l�벼�F�I");
  }
  pressanykey();
  return FULLUPDATE;
}


int
vote_flag(bname, val)
  char *bname, val;
{
  char buf[256], flag;
  int fd, num, size;

  num = usernum - 1;
  setbfile(buf, bname, STR_bv_flags);
  if ((fd = open(buf, O_RDWR | O_CREAT, 0600)) == -1)
  {
    return -1;
  }
  size = lseek(fd, 0, SEEK_END);
  memset(buf, 0, sizeof(buf));
  while (size <= num)
  {
    write(fd, buf, sizeof(buf));
    size += sizeof(buf);
  }
  lseek(fd, num, SEEK_SET);
  read(fd, &flag, 1);
  if (flag == 0 && val != 0)
  {
    lseek(fd, num, SEEK_SET);
    write(fd, &val, 1);
  }
  close(fd);
  return flag;
}


int
same(compare, list, num)
  char compare;
  char list[];
  int num;
{
  int n;
  int rep = 0;

  for(n = 0; n < num; n++)
  {
    if(compare == list[n])
      rep = 1;
    if(rep == 1)
      list[n] = list[n+1];
  }
  return rep;
}


int
user_vote(bname)
  char *bname;
{
  FILE *cfp, *fcm;
  char buf[STRLEN];
  char inbuf[80], choices[31], vote[2], bufvote[31];
  int i = 0, tickets, grades;
  int fd, count = 0;
  time_t closetime;

  setbfile( buf, bname, STR_bv_tickets);
  if((cfp= fopen(buf, "r")) == NULL)
    tickets=1;
  else
  {
    fgets( inbuf, sizeof(inbuf), cfp );
    tickets = atoi(inbuf);
    fclose(cfp);
  }


  setbfile(buf, bname, STR_bv_control);
  move(3, 0);
  clrtobot();
  if ((cfp = fopen(buf, "r")) == NULL)
  {
/*
woju

    boardheader bh;
    int bid = getbnum(bname);
    if (get_record(fn_board, &bh, sizeof(bh), bid) != -1 && bh.bvote == 1) {
       bh.bvote = 2;
       substitute_record(fn_board, &bh, sizeof(bh), bid);
       touch_boards();
       resolve_boards();
    }
*/
    outs("\n�ثe�èS������벼�|��C");
    pressanykey();
    return FULLUPDATE;
  }
  
/* 2003/08/30 by Terry */
  if (!HAS_PERM(PERM_LOGINOK))
/*		       */
  {
    outs("\n�藍�_! �z�٨S���벼�v��!");
    fclose(cfp);
    pressanykey();
    return FULLUPDATE;
  }

  setutmpmode(VOTING);
  setbfile(buf, bname, STR_bv_desc);
  more(buf, YEA);


  fgets(inbuf, sizeof(inbuf), cfp);
  closetime = (time_t) atol(inbuf);
  fgets(inbuf, sizeof(inbuf), cfp);
  grades = (int) atoi(inbuf);
  stand_title(grades ? "�����벼�c" : "���q�벼�c");

  prints("�벼�覡�G�T�w�n�z����ܫ�A��J��N�X(A, B, C...)�Y�i�C\n"
    "�����벼�A�i�H�� %1d ���C"
    "[1;30;41m �� 0 �����벼 [m [1;37;42m �� 1 �����벼 [m\n"
    "�}���ɶ��w�p�b�G%s \n",
    tickets, ctime(&closetime));
  move(5, 0);
  memset(choices, 0, sizeof(choices));
  while (fgets(inbuf, sizeof(inbuf), cfp))
  {
    choices[count++] = inbuf[0];
    move(((count-1)%15)+5,((count-1)/15)*40);
    if (grades)
      prints( " %3d��> %s", 100 - (count - 1) * 10, strtok(inbuf,"\n\0"));
    else
      prints( " %s", strtok(inbuf,"\n\0"));
  }
  fclose(cfp);

  if (vote_flag(bname, '\0'))
  {
    move(21, 0);
    outs("�����벼�A�A�w��L�F�I�@�H�@���A�j�a�����C");
    pressanykey();
    return FULLUPDATE;
  }

  while(1)
  {
    vote[0] = vote[1] = '\0';
    move(t_lines-2, 0);
    prints("�A�٥i�H�� %2d ��", tickets-i);
    sprintf(buf, "%s��J�z�����: ", grades ? "�o�O�����벼�A�Ш̤���" : "");
    getdata(t_lines-4, 0, buf, vote, 3, DOECHO, 0);
    move(t_lines - 2, 0);
    *vote = toupper(*vote);
    if (vote[0] == '0' || (!vote[0] && !i))
    {
      clrtoeol();
      prints("[5m�O�o�A�ӧ��!!      [m");
      refresh();
      break;
    }
    else if (vote[0] == '1' && i)
       bufvote[i] = '_'; /* Tzu */
    else if (!vote[0])
       continue;
    else if (index(choices, vote[0]) == NULL) /* �L�� */
      continue;
    else if (same(vote[0], bufvote, i))
    {
      move(((vote[0]-'A')%15)+5, (((vote[0]-'A'))/15)*40);
      prints(" ");
      i--;
      continue;
    }
    else
    {
      if (i == tickets)
         continue;
      bufvote[i] = vote[0];
      move(((vote[0]-'A')%15)+5, (((vote[0]-'A'))/15)*40);
      prints("*");
      i++;
      continue;
    }
    

    if (vote_flag(bname, vote[0]) != 0)
      prints("���Ч벼! �����p���C");
    else
    {
      setbfile(buf, bname, STR_bv_ballots);
      if ((fd = open(buf, O_WRONLY | O_CREAT | O_APPEND, 0600)) == 0)
        outs("�L�k��J���o\n");
      else
      {
        struct stat statb;
        char buf[3], mycomments[3][74], b_comments[80];
        flock(fd, LOCK_EX);
        write(fd, bufvote, i+1);
        flock(fd, LOCK_UN);
        fstat(fd, &statb);
        close(fd);
        move(0,0);
        clrtobot();
        getdata(b_lines - 2, 0,"�z��o���벼�������_�Q���N���ܡH(y/n)[N]",
                buf,3,DOECHO,0);
        if(buf[0]=='Y' || buf[0]=='y')
        {
          do
          {
            clear();
            move(5,0);
            for(i=0; i<3;i++) strcpy(mycomments[i],"");
            outs("�аݱz��o���벼�������_�Q���N���H�̦h�T��A��[Enter]����");
            for (i = 0; (i < 3) &&
                getdata(7 + i, 0, "�G", mycomments[i], 64, DOECHO, 0); i++);
/*        for(i = 0; i < 3; i++)
         strip_ansi(mycomments[i], mycomments[i]); */
            getdata(b_lines-2,0,"(S)�x�s (E)���s�ӹL (Q)�����H[S]",buf,3,LCECHO,0);
          } while(buf[0] == 'e');
          if(buf[0] != 'q')
          {
            setbfile(b_comments, bname, STR_bv_comments);
            if (i)
              if (fcm = fopen(b_comments, "a"))
              {
                fprintf(fcm, "%-12s�G", cuser.userid);
                for(i = 0; i < 3; i++)
                {
                  /* Tzu */
                  if (strcmp(mycomments[i], ""))
                  {
                    if (i != 0)
                      fprintf(fcm, "              "); 
                    fprintf(fcm, "%s\n", mycomments[i]);
                  }
                /*     */
                }
                fclose(fcm);
              }
            }
        }
        move(b_lines -1 ,0);
        prints("�w�����벼�I(�ثe�w�벼��: %d)\n", statb.st_size);
      }
    }
    break;
  }
  pressanykey();
  return FULLUPDATE;
}


int
vote_results(bname)
  char *bname;
{
  char buf[STRLEN];

  setbfile(buf, bname, STR_bv_results);
  if (more(buf, YEA) == -1)
  {
/*
woju

    boardheader bh;
    int bid = getbnum(bname);

    if (get_record(fn_board, &bh, sizeof(bh), bid) != -1
        && bh.bvote == 2) {
       bh.bvote = 0;
       substitute_record(fn_board, &bh, sizeof(bh), bid);
       touch_boards();
       resolve_boards();
    }
*/
    move(3, 0);
    clrtobot();
    outs("\n�ثe�S������벼�����G�C");
    pressanykey();
  }
/*
woju

  else {
    boardheader bh;
    int bid = getbnum(bname);
    if (get_record(fn_board, &bh, sizeof(bh), bid) != -1
        && bh.vtime < time(NULL) - 7 * 86400
        && bh.bvote == 2) {
       bh.bvote = 0;
       substitute_record(fn_board, &bh, sizeof(bh), bid);
       touch_boards();
       resolve_boards();
    }
  }
*/
  return FULLUPDATE;
}


int
b_vote_maintain()
{
  return vote_maintain(currboard);
}


int
b_vote()
{
  return user_vote(currboard);
}


int
b_results()
{
  return vote_results(currboard);
}


#ifdef  SYS_VOTE
int
m_vote()
{
  return vote_maintain(DEFAULT_BOARD);
}


int
x_vote()
{
  return user_vote(DEFAULT_BOARD);
}


int
x_results()
{
  return vote_results(DEFAULT_BOARD);
}
#endif                          /* SYS_VOTE */



#ifdef  HAVE_REPORT
b_report(s)
  char *s;
{
  static int disable = NA;
  int fd;

  if (disable)
    return;
  if ((fd = open("trace.bvote", O_WRONLY, 0644)) != -1)
  {
    char buf[512];
    char timestr[18], *thetime;
    time_t dtime;

    time(&dtime);
    thetime = ctime(&dtime);
    strncpy(timestr, &(thetime[4]), 15);
    timestr[15] = '\0';
    flock(fd, LOCK_EX);
    lseek(fd, 0, L_XTND);
    sprintf(buf, "%s %-12s %-20s %s\n", timestr, cuser.userid, currboard, s);
    write(fd, buf, strlen(buf));
    flock(fd, LOCK_UN);
    close(fd);
    return;
  }
  disable = YEA;
  return;
}
#endif                          /* HAVE_REPORT */
