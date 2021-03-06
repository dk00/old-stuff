/*-------------------------------------------------------*/
/* xchatd.c     ( NTHU CS MapleBBS Ver 2.36 )            */
/*-------------------------------------------------------*/
/* target : super KTV daemon for chat server             */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/


#include "bbs.h"


#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#ifdef LINUX
#include <unistd.h>
#else
#include <sys/uio.h>
#endif

#ifdef AIX
#include <sys/select.h>
#endif

#if !RELIABLE_SELECT_FOR_WRITE
#include <fcntl.h>
#endif

#if USES_SYS_SELECT_H
#include <sys/select.h>
#endif

#if NO_SETPGID
#define setpgid setpgrp
#endif


#define RESTRICTED(u)   (users[(u)].flags == 0) /* guest */
#define SYSOP(u)        (users[(u)].flags & PERM_SYSOP)
#define HIDE(u)     (SYSOP(u) && (users[(u)].flags & PERM_DENYPOST))
#define ROOMOP(u)       (users[(u)].flags & PERM_CHATROOM)

#define ROOM_LOCKED     0x1
#define ROOM_SECRET     0x2

#define LOCKED(r)       (rooms[(r)].flags & ROOM_LOCKED)
#define SECRET(r)       (rooms[(r)].flags & ROOM_SECRET)

#define ROOM_ALL        (-2)

struct chatuser
{
  int sockfd;                   /* socket to bbs server */
  int utent;                    /* utable entry for this user */
  int room;                     /* room: -1 means none, 0 means main */
  int flags;
  char userid[IDLEN + 1];       /* real userid */
  char chatid[9];               /* chat id */
  char ibuf[80];                /* buffer for sending/receiving */
  int ibufsize;                 /* current size of ibuf */
  char host[30];                /* from host */
}        users[MAXACTIVE];


struct chatroom
{
  char name[IDLEN];             /* name of room; room 0 is "main" */
  short occupants;              /* number of users in room */
  short flags;                  /* ROOM_LOCKED, ROOM_SECRET */
  char invites[MAXACTIVE];      /* Keep track of invites to rooms */
  char topic[48];               /* Let the room op to define room topic */
}        rooms[MAXROOM];


struct chatcmd
{
  char *cmdstr;
  void (*cmdfunc) ();
  int exact;
};


int sock = -1;                  /* the socket for listening */
int nfds;                       /* number of sockets to select on */
int num_conns;                  /* current number of connections */
fd_set allfds;                  /* fd set for selecting */
struct timeval zerotv;          /* timeval for selecting */
char chatbuf[256];              /* general purpose buffer */

/* name of the main room (always exists) */

char mainroom[] = "main";
char maintopic[] = "音樂班";

char *msg_not_op = "◆ 您不是這間聊天室的 Op";
char *msg_no_such_id = "◆ 目前沒有人使用 [%s] 這個聊天代號";
char *msg_not_here = "◆ [%s] 不在這間聊天室";


#undef HAVE_REPORT

#ifdef  HAVE_REPORT
report(s)
  char *s;
{
  static int disable = NA;
  int fd;

  if (disable)
    return;
  if ((fd = open("trace.chatd", O_WRONLY, 0644)) != -1)
  {
    char buf[160];

    flock(fd, LOCK_EX);
    lseek(fd, 0, L_XTND);
    sprintf(buf, "%s\n", s);
    write(fd, buf, strlen(buf));
    flock(fd, LOCK_UN);
    close(fd);
    return;
  }
  disable = YEA;
  return;
}
#else
#define report(s)       ;
#endif


is_valid_chatid(id)
  char *id;
{
  int i, ch;

/*
woju
*/
  if (*id == '\0' || *id == '/' || *id == '@' || *id == '>')
    return 0;

  for (i = 0; (i < 8) && (ch = id[i]); i++)
    if (ch == '*' || ch == ':')
      return 0;

  return 1;
}


int
Isspace(ch)
  char ch;
{
  return (ch == ' ' || ch == '\t' || ch == 10);
}


char *
nextword(str)
  char **str;
{
  char *p;

  while (Isspace(**str))
    (*str)++;
  p = *str;
  while (**str && !Isspace(**str))
    (*str)++;
  if (**str)
  {
    **str = '\0';
    (*str)++;
  }
  return p;
}


/* Case Independent strcmp : 1 ==> euqal */

int
ci_strcmp(s1, s2)
  register char *s1, *s2;
{
  register char c1, c2;

  while (1)
  {
    c1 = *s1++;
    if (c1 >= 'A' && c1 <= 'Z')
      c1 |= 32;

    c2 = *s2++;
    if (c2 >= 'A' && c2 <= 'Z')
      c2 |= 32;

    if (c1 != c2)
      return 0;
  }
  return 1;
}


int
chatid_to_indx(chatid)
  char *chatid;
{
  register int i;

  for (i = 0; i < MAXACTIVE; i++)
  {
    if (users[i].sockfd == -1)
      continue;
    if (!strcasecmp(chatid, users[i].chatid))
      return i;
  }
  return -1;
}


int
fuzzy_chatid_to_indx(chatid)
  char *chatid;
{
  register int i, indx = -1;
  int len = strlen(chatid);

  for (i = 0; i < MAXACTIVE; i++)
  {
    if (users[i].sockfd == -1)
      continue;
    if (!strncasecmp(chatid, users[i].chatid, len))
    {
      if (len == strlen(users[i].chatid))
        return i;
      if (indx == -1)
        indx = i;
      else
        return -2;
    }
  }
  return indx;
}


int
roomid_to_indx(roomid)
  char *roomid;
{
  register int i;

  for (i = 0; i < MAXROOM; i++)
  {
    if (i && rooms[i].occupants == 0)
      continue;
    report(roomid);
    report(rooms[i].name);
    if (!strcasecmp(roomid, rooms[i].name))
      return i;
  }
  return -1;
}


void
do_send(writefds, str)
  fd_set *writefds;
  char *str;
{
  register int i;
  int len = strlen(str);

  if (select(nfds, NULL, writefds, NULL, &zerotv) > 0)
  {
    for (i = 0; i < nfds; i++)
      if (FD_ISSET(i, writefds))
        send(i, str, len + 1, 0);
  }
}


void
send_to_room(room, str)
  int room;
  char *str;
{
  int i;
  fd_set writefds;

  FD_ZERO(&writefds);
  for (i = 0; i < MAXROOM; i++)
  {
    if (users[i].sockfd == -1)
      continue;
    if (room == ROOM_ALL || room == users[i].room)
      /* write(users[i].sockfd, str, strlen(str) + 1); */
      FD_SET(users[i].sockfd, &writefds);
  }
  do_send(&writefds, str);
}

void
send_to_room_hide(room, str1)
  int room;
  char *str1;
{
  int i;
  fd_set writefds;
  char str[200];

  sprintf(str, ">%s", str1);
  FD_ZERO(&writefds);
  for (i = 0; i < MAXROOM; i++)
  {
    if (users[i].sockfd == -1 || !HIDE(i))
       continue;
    if (room == ROOM_ALL || room == users[i].room)
       FD_SET(users[i].sockfd, &writefds);
  }
  do_send(&writefds, str);
}



void
send_to_unum(unum, str)
  int unum;
  char *str;
{
  fd_set writefds;

  FD_ZERO(&writefds);
  FD_SET(users[unum].sockfd, &writefds);
  do_send(&writefds, str);
}


void
exit_room(unum, disp, msg)
  int unum;
  int disp;
  char *msg;
{
  int oldrnum = users[unum].room;

  if (oldrnum != -1)
  {
    if (--rooms[oldrnum].occupants)
    {
      sprintf(chatbuf, "%s EXIT", users[unum].userid);
      send_to_room_hide(users[unum].room, chatbuf);
      switch (disp)
      {
      case EXIT_LOGOUT:
        sprintf(chatbuf, "◆ %s 離開了", users[unum].chatid);
        if (msg && *msg)
        {
          strcat(chatbuf, ": ");
          strncat(chatbuf, msg, 80);
        }
        break;

      case EXIT_LOSTCONN:
        sprintf(chatbuf, "◆ %s 不見了... :~(", users[unum].chatid);
        break;

      case EXIT_KICK:
        sprintf(chatbuf, "◆ 哈哈！%s 被踢出去了", users[unum].chatid);
        break;
      }
      if (!HIDE(unum))
         send_to_room(oldrnum, chatbuf);
    }
  }
  users[unum].flags &= ~PERM_CHATROOM;
  users[unum].room = -1;
}


void
chat_topic(unum, msg)
  int unum;
  char *msg;
{
  int rnum;

  rnum = users[unum].room;

  if (!ROOMOP(unum) && !SYSOP(unum))
  {
    send_to_unum(unum, msg_not_op);
    return;
  }
  if (*msg == '\0')
  {
    send_to_unum(unum, "※ 請指定話題");
    return;
  }


  sprintf(chatbuf, "%s TOPIC", users[unum].userid);
  send_to_room_hide(users[unum].room, chatbuf);
  strncpy(rooms[rnum].topic, msg, 48);
  rooms[rnum].topic[48] = '\0';
  sprintf(chatbuf, "/t%.47s", msg);
  send_to_room(rnum, chatbuf);
  sprintf(chatbuf, "◆ %s 將話題改為 [1;32m%s[0m", users[unum].chatid, msg);
  send_to_room(rnum, chatbuf);
}


enter_room(unum, room, msg)
  int unum;
  char *room;
  char *msg;
{
  int rnum;
  int op = 0;
  register int i;

  rnum = roomid_to_indx(room);
  if (rnum == -1)
  {
    /* new room */
    for (i = 1; i < MAXROOM; i++)
    {
      if (rooms[i].occupants == 0)
      {
        report("new room");
        rnum = i;
        memset(rooms[rnum].invites, 0, MAXACTIVE);
        strcpy(rooms[rnum].topic, maintopic);
        strncpy(rooms[rnum].name, room, IDLEN - 1);
        rooms[rnum].name[IDLEN - 1] = '\0';
        rooms[rnum].flags = 0;
        op++;
        break;
      }
    }
    if (rnum == -1)
    {
      send_to_unum(unum, "※ 無法再新闢包廂了");
      return 0;
    }
  }
  if (!SYSOP(unum))
    if (LOCKED(rnum) && rooms[rnum].invites[unum] == 0)
    {
      send_to_unum(unum, "※ 內有大白鯊，非請莫入");
      return 0;
    }

  exit_room(unum, EXIT_LOGOUT, msg);
  users[unum].room = rnum;
  if (op || SYSOP(unum))
    users[unum].flags |= PERM_CHATROOM;
  rooms[rnum].occupants++;
  rooms[rnum].invites[unum] = 0;
  sprintf(chatbuf, "%s ENTER", users[unum].userid);
  send_to_room_hide(users[unum].room, chatbuf);
  sprintf(chatbuf, "※ [32;1m%s[0m 進入 [33;1m[%s][0m 包廂",
    users[unum].chatid, rooms[rnum].name);
  if (HIDE(unum))
     send_to_unum(unum, chatbuf);
  else
     send_to_room(rnum, chatbuf);
  sprintf(chatbuf, "/r%s", room);
  send_to_unum(unum, chatbuf);
  sprintf(chatbuf, "/t%s", maintopic);
  send_to_unum(unum, chatbuf);
  return 0;
}


void
logout_user(unum)
{
  int i, sockfd = users[unum].sockfd;

  close(sockfd);
  FD_CLR(sockfd, &allfds);
  memset(&users[unum], 0, sizeof(users[unum]));
  users[unum].sockfd = users[unum].utent = users[unum].room = -1;
  for (i = 0; i < MAXROOM; i++)
  {
    if (rooms[i].invites != NULL)
      rooms[i].invites[unum] = 0;
  }
  num_conns--;
}

print_user_counts(unum)
{
  int i, c, userc = 0, suserc = 0, roomc = 0;

  for (i = 0; i < MAXROOM; i++)
  {
    c = rooms[i].occupants;
    if (i > 0 && c > 0)
    {
      if ((!HIDE(i) || HIDE(unum)) && (!SECRET(i) || SYSOP(unum)))
        roomc++;
    }
    c = users[i].room;
    if (users[i].sockfd != -1 && c != -1)
    {
      if (SECRET(c) && !SYSOP(unum))
        suserc++;
      else if (!HIDE(c) || HIDE(unum))
        userc++;
    }
  }
  sprintf(chatbuf,
    "☉ 歡迎光臨【陽光茶坊】，目前開了 [1;31m%d[0m 間包廂", roomc + 1);
  send_to_unum(unum, chatbuf);
  sprintf(chatbuf, "☉ 共有 [1;36m%d[0m 人來擺\龍門陣", userc + 1);
  if (suserc)
    sprintf(chatbuf + strlen(chatbuf), " [%d 人在摸摸茶]", suserc);
  send_to_unum(unum, chatbuf);
  return 0;
}


int
login_user(unum, msg)
  int unum;
  char *msg;
{
  int i, utent, fd = users[unum].sockfd;
  int userlevel;
  char *utentstr;
  char *level;
  char *userid;
  char *chatid;

  utentstr = nextword(&msg);
  level = nextword(&msg);
  userid = nextword(&msg);
  chatid = nextword(&msg);
/*
  if (*chatid == KEY_ESC) {
     strcpy(chatid, chatid + 1);
     if (!strcmp(users[unum].host, MYHOSTNAME))
        userlevel = atoi(level) | PERM_DENYPOST;
     else
        userlevel = 0;
  }
  else
     userlevel = atoi(level) & ~PERM_DENYPOST;
*/
  if (!strcmp(users[unum].host, MYHOSTNAME))
     userlevel = atoi(level) & 1;
  utent = atoi(utentstr);
  for (i = 0; i < MAXACTIVE; i++)
  {
    if (users[i].sockfd != -1 && users[i].utent == utent)
    {
      send_to_unum(unum, CHAT_LOGIN_BOGUS);
      return -1;
    }
  }
  if (!is_valid_chatid(chatid))
  {
    send_to_unum(unum, CHAT_LOGIN_INVALID);
    return 0;
  }
  if (chatid_to_indx(chatid) != -1)
  {
    /* userid in use */
    send_to_unum(unum, CHAT_LOGIN_EXISTS);
    return 0;
  }
  report(level);
  users[unum].utent = utent;
  users[unum].flags = userlevel;
  strcpy(users[unum].userid, userid);
  strncpy(users[unum].chatid, chatid, 8);
  users[unum].chatid[8] = '\0';
  send_to_unum(unum, CHAT_LOGIN_OK);
  print_user_counts(unum);
  enter_room(unum, mainroom, (char *) NULL);
  return 0;
}


void
chat_list_rooms(unum, msg)
  int unum;
  char *msg;
{
  int i, occupants;

  if (RESTRICTED(unum))
  {
    send_to_unum(unum, "※ 您沒有權限列出現有的聊天室");
    return;
  }
  send_to_unum(unum, "[7m 談天室名稱  │人數│話題        [0m");
  for (i = 0; i < MAXROOM; i++)
  {
    occupants = rooms[i].occupants;
    if (occupants > 0)
    {
      if (!SYSOP(unum))
        if ((rooms[i].flags & ROOM_SECRET) && (users[unum].room != i))
          continue;
      sprintf(chatbuf, " %-12s│%4d│%s", rooms[i].name, occupants, rooms[i].topic);
      if (rooms[i].flags & ROOM_LOCKED)
        strcat(chatbuf, " [鎖住]");
      if (rooms[i].flags & ROOM_SECRET)
        strcat(chatbuf, " [秘密]");
      send_to_unum(unum, chatbuf);
    }
  }
}


int
chat_do_user_list(unum, msg, whichroom)
  int unum;
  char *msg;
  int whichroom;
{
  int start, stop, curr = 0;
  int i, rnum, myroom = users[unum].room;

  while (*msg && Isspace(*msg))
    msg++;
  start = atoi(msg);
  while (*msg && isdigit(*msg))
    msg++;
  while (*msg && !isdigit(*msg))
    msg++;
  stop = atoi(msg);
  send_to_unum(unum, "[7m 聊天代號│使用者代號  │聊天室 [0m");
  for (i = 0; i < MAXROOM; i++)
  {
    rnum = users[i].room;
    if (users[i].sockfd != -1 && rnum != -1)
    {
      if (whichroom != -1 && whichroom != rnum)
        continue;
      if (myroom != rnum)
      {
        if (RESTRICTED(unum))
          continue;
        if ((rooms[rnum].flags & ROOM_SECRET) && !SYSOP(unum))
          continue;
      }
      curr++;
      if (curr < start)
        continue;
      else if (stop && (curr > stop))
        break;
      sprintf(chatbuf, " %-8s│%-12s│%-15s %c%c%c%c %30s", users[i].chatid,
        users[i].userid, rooms[rnum].name,
        HIDE(i) ? 'H' : ' ',
        SYSOP(i) ? 'S' : ' ',
        ROOMOP(i) ? 'O' : ' ',
        RESTRICTED(i) ? 'R' : ' ',
        users[i].host);
      if (!HIDE(i) || HIDE(unum))
         send_to_unum(unum, chatbuf);
    }
  }
  return 0;
}


void
chat_list_by_room(unum, msg)
  int unum;
  char *msg;
{
  int whichroom;
  char *roomstr;

  roomstr = nextword(&msg);
  if (*roomstr == '\0')
    whichroom = users[unum].room;
  else
  {
    if ((whichroom = roomid_to_indx(roomstr)) == -1)
    {
      sprintf(chatbuf, "※ 沒有 [%s] 這個聊天室", roomstr);
      send_to_unum(unum, chatbuf);
      return;
    }
    if ((rooms[whichroom].flags & ROOM_SECRET) && !SYSOP(unum))
    {
      send_to_unum(unum, "※ 無法列出在秘密聊天室的使用者");
      return;
    }
  }
  chat_do_user_list(unum, msg, whichroom);
}


void
chat_list_users(unum, msg)
  int unum;
  char *msg;
{
  chat_do_user_list(unum, msg, -1);
}


void
chat_map_chatids(unum, whichroom)
  int unum;
  int whichroom;
{
  int i, c, myroom, rnum;

  myroom = users[unum].room;
  send_to_unum(unum,
    "[7m 聊天代號 使用者代號  │ 聊天代號 使用者代號  │ 聊天代號 使用者代號 [0m");
  for (i = 0, c = 0; i < MAXROOM; i++)
  {
    rnum = users[i].room;
    if (users[i].sockfd != -1 && rnum != -1)
    {
      if (whichroom != -1 && whichroom != rnum)
        continue;
      if (myroom != rnum)
      {
        if (RESTRICTED(unum))
          continue;
        if ((rooms[rnum].flags & ROOM_SECRET) && !SYSOP(unum))
          continue;
      }
      if (!HIDE(unum) && HIDE(i))
         continue;
      sprintf(chatbuf + (c * 24), " %-8s%c%-12s%s",
        users[i].chatid, (ROOMOP(i)) ? '*' : ' ', users[i].userid,
        (c < 2 ? "│" : "  "));
      if (++c == 3)
      {
        send_to_unum(unum, chatbuf);
        c = 0;
      }
    }
  }
  if (c > 0)
    send_to_unum(unum, chatbuf);
}


void
chat_map_chatids_thisroom(unum, msg)
  int unum;
  char *msg;
{
  chat_map_chatids(unum, users[unum].room);
}


void
chat_setroom(unum, msg)
  int unum;
  char *msg;
{
  char *modestr;
  int rnum = users[unum].room;
  int sign = 1;
  int flag;
  char *fstr;

  modestr = nextword(&msg);
  if (!ROOMOP(unum))
  {
    send_to_unum(unum, msg_not_op);
    return;
  }
  if (*modestr == '+')
    modestr++;
  else if (*modestr == '-')
  {
    modestr++;
    sign = 0;
  }
  if (*modestr == '\0')
  {
    send_to_unum(unum,
      "※ 請指定狀態指標: {[+(設定)][-(取消)]}{[l(鎖住)][s(秘密)]}");
    return;
  }

  while (*modestr)
  {
    flag = 0;
    switch (*modestr)
    {
    case 'l':
    case 'L':
      flag = ROOM_LOCKED;
      fstr = "鎖住";
      break;

    case 's':
    case 'S':
      flag = ROOM_SECRET;
      fstr = "秘密";
      break;

    default:
      sprintf(chatbuf, "※ 狀態指標錯誤：[%c]", *modestr);
      send_to_unum(unum, chatbuf);
    }

    if (flag && ((rooms[rnum].flags & flag) != sign * flag))
    {
      rooms[rnum].flags ^= flag;
      sprintf(chatbuf, "%s SETROOM", users[unum].userid);
      send_to_room_hide(users[unum].room, chatbuf);
      sprintf(chatbuf, "※ 本聊天室被 %s %s%s狀態",
        users[unum].chatid, sign ? "設定為" : "取消", fstr);
      send_to_room(rnum, chatbuf);
    }
    modestr++;
  }
}


void
chat_nick(unum, msg)
  int unum;
  char *msg;
{
  char *chatid;
  int othernum;

  chatid = nextword(&msg);
  if (!is_valid_chatid(chatid))
  {
    send_to_unum(unum, "※ 這個聊天代號是不正確的");
    return;
  }
  othernum = chatid_to_indx(chatid);
  if (othernum != -1 && othernum != unum)
  {
    send_to_unum(unum, "※ 已經有人捷足先登囉");
    return;
  }
  chatid[8] = '\0';

  sprintf(chatbuf, "%s NICK", users[unum].userid);
  send_to_room_hide(users[unum].room, chatbuf);
  sprintf(chatbuf, "※ %s 將聊天代號改為 [1;33m%s[0m",
    users[unum].chatid, chatid);
  if (!HIDE(unum))
     send_to_room(users[unum].room, chatbuf);
  strcpy(users[unum].chatid, chatid);
  sprintf(chatbuf, "/n%s", users[unum].chatid);
  send_to_unum(unum, chatbuf);
}


void
chat_private(unum, msg)
  int unum;
  char *msg;
{
  char *recipient;
  int recunum;

  recipient = nextword(&msg);
  recunum = fuzzy_chatid_to_indx(recipient);
  if (recunum < 0)
  {
    /* no such user, or ambiguous */
    if (recunum == -1)
/*
woju
      sprintf(chatbuf, msg_no_such_id, recipient);
*/
      sprintf(chatbuf, "@%s@%s", recipient, msg);
    else
      sprintf(chatbuf, "※ 請指明聊天代號", recipient);
    send_to_unum(unum, chatbuf);
    return;
  }
  if (*msg)
  {
    sprintf(chatbuf, "*%s* ", users[unum].chatid);
    strncat(chatbuf, msg, 80);
    send_to_unum(recunum, chatbuf);
    sprintf(chatbuf, "%s> ", users[recunum].chatid);
    strncat(chatbuf, msg, 80);
    send_to_unum(unum, chatbuf);
  }
}


put_chatid(unum, str)
  int unum;
  char *str;
{
  int i;
  char *chatid = users[unum].chatid;

  memset(str, ' ', 10);
  for (i = 0; chatid[i]; i++)
    str[i] = chatid[i];
  str[i] = ':';
  str[10] = '\0';
}


void
chat_allmsg(unum, msg)
  int unum;
  char *msg;
{
  if (*msg)
  {
    sprintf(chatbuf, "%s ALLMSG", users[unum].userid);
    send_to_room_hide(users[unum].room, chatbuf);
    put_chatid(unum, chatbuf);
    strcat(chatbuf, msg);
    send_to_room(users[unum].room, chatbuf);
  }
}


void
chat_act(unum, msg)
  int unum;
  char *msg;
{
  if (*msg)
  {
    sprintf(chatbuf, "%s ACT", users[unum].userid);
    send_to_room_hide(users[unum].room, chatbuf);
    sprintf(chatbuf, "%s [36m%s[m", users[unum].chatid, msg);
    send_to_room(users[unum].room, chatbuf);
  }
}


void
chat_join(unum, msg)
  int unum;
  char *msg;
{
  if (RESTRICTED(unum))
  {
    send_to_unum(unum, "※ 您沒有加入其他聊天室的權限");
  }
  else
  {
    char *roomid = nextword(&msg);

    if (*roomid)
      enter_room(unum, roomid, msg);
    else
      send_to_unum(unum, "※ 請指定聊天室的名字");
  }
}


void
chat_kick(unum, msg)
  int unum;
  char *msg;
{
  char *twit;
  int rnum = users[unum].room;
  int recunum;

  twit = nextword(&msg);
  if (!ROOMOP(unum) && !SYSOP(unum))
  {
    send_to_unum(unum, msg_not_op);
    return;
  }
  if ((recunum = chatid_to_indx(twit)) == -1 || HIDE(recunum))
  {
    sprintf(chatbuf, msg_no_such_id, twit);
    send_to_unum(unum, chatbuf);
    return;
  }
  if (rnum != users[recunum].room)
  {
    sprintf(chatbuf, msg_not_here, users[recunum].chatid);
    send_to_unum(unum, chatbuf);
    return;
  }
  sprintf(chatbuf, "%s KICK %s", users[unum].userid, users[recunum].userid);
  send_to_room_hide(users[unum].room, chatbuf);
  exit_room(recunum, EXIT_KICK, (char *) NULL);

  if (rnum == 0)
    logout_user(recunum);
  else
    enter_room(recunum, mainroom, (char *) NULL);
}


void
chat_makeop(unum, msg)
  int unum;
  char *msg;
{
  char *newop = nextword(&msg);
  int rnum = users[unum].room;
  int recunum;

  if (!ROOMOP(unum))
  {
    send_to_unum(unum, msg_not_op);
    return;
  }
  if ((recunum = chatid_to_indx(newop)) == -1)
  {
    /* no such user */
    sprintf(chatbuf, msg_no_such_id, newop);
    send_to_unum(unum, chatbuf);
    return;
  }
  if (unum == recunum)
  {
    sprintf(chatbuf, "※ 您早就已經是 Op 了啊");
    send_to_unum(unum, chatbuf);
    return;
  }
  if (rnum != users[recunum].room)
  {
    sprintf(chatbuf, msg_not_here, users[recunum].chatid);
    send_to_unum(unum, chatbuf);
    return;
  }
  users[unum].flags &= ~PERM_CHATROOM;
  users[recunum].flags |= PERM_CHATROOM;
  sprintf(chatbuf, "%s MAKEOP %s", users[unum].userid, users[recunum].userid);
  send_to_room_hide(users[unum].room, chatbuf);
  sprintf(chatbuf, "※ %s 將 Op 權力轉移給 %s", users[unum].chatid,
    users[recunum].chatid);
  send_to_room(rnum, chatbuf);
}


void
chat_invite(unum, msg)
  int unum;
  char *msg;
{
  char *invitee = nextword(&msg);
  int rnum = users[unum].room;
  int recunum;

  if (!ROOMOP(unum))
  {
    send_to_unum(unum, msg_not_op);
    return;
  }
  if ((recunum = chatid_to_indx(invitee)) == -1)
  {
    sprintf(chatbuf, msg_not_here, invitee);
    send_to_unum(unum, chatbuf);
    return;
  }
  if (rooms[rnum].invites[recunum] == 1)
  {
    sprintf(chatbuf, "※ %s 已經接受過邀請了", users[recunum].chatid);
    send_to_unum(unum, chatbuf);
    return;
  }
  rooms[rnum].invites[recunum] = 1;
  sprintf(chatbuf, "※ %s 邀請您到 [%s] 聊天室",
    users[unum].chatid, rooms[rnum].name);
  send_to_unum(recunum, chatbuf);
  sprintf(chatbuf, "※ %s 收到您的邀請了", users[recunum].chatid);
  send_to_unum(unum, chatbuf);
}


void
chat_broadcast(unum, msg)
  int unum;
  char *msg;
{
  if (!SYSOP(unum))
  {
    send_to_unum(unum, "※ 您沒有在聊天室廣播的權力!");
    return;
  }
  if (*msg == '\0')
  {
    send_to_unum(unum, "※ 請指定廣播內容");
    return;
  }
  sprintf(chatbuf, "%s BROADCAST", users[unum].userid);
  send_to_room_hide(ROOM_ALL, chatbuf);
  sprintf(chatbuf, "*※ " BOARDNAME "談天室廣播中 [%s].....",
    users[unum].chatid);
  send_to_room(ROOM_ALL, chatbuf);
  sprintf(chatbuf, "◆ %s", msg);
  send_to_room(ROOM_ALL, chatbuf);
}


void
chat_goodbye(unum, msg)
  int unum;
  char *msg;
{
  exit_room(unum, EXIT_LOGOUT, msg);
}


/* -------------------------------------------- */
/* MUD-like social commands : action             */
/* -------------------------------------------- */


struct action
{
  char *verb;                   /* 動詞 */
  char *part1_msg;              /* 介詞 */
  char *part2_msg;              /* 動作 */
  char *keyword ;
};


struct action party_data[] =
{
  {"1", "拿出電鋸，朝", "的那裡鋸了下去...", "１號"},
  {"2", "開始對", "猛打手槍！", "２號"},
  {"3", "碰了一聲，", "啊~~了一聲！", "３號"},
  {"4", "挺起機槍，把", "打成蜂窩", "４號"},
  {"5", "駕著卡車，然後突然對", "右轉...", "５號"},
  {"6", "bon quey 了！拿起六號衝向", "", "６號"},
  {"7", "對", "拋了一個媚眼，把他看死了...", "７號"},
  {"8", "按了 pause，然後開始對", "破口大罵", "８號"},
  {"bearhug", "熱情的擁抱", "", "熱情擁抱"},
  {"bless", "祝福", "心想事成", "祝福"},
  {"bow", "畢躬畢敬的向", "鞠躬", "鞠躬"},
  {"caress", "輕輕的撫摸著", "", "輕撫"},
  {"cry", "向", "嚎啕大哭", "大哭"},
  {"comfort", "溫言安慰", "", "安慰"},
  {"clap", "向", "熱烈鼓掌", "鼓掌"},
  {"dance", "拉了", "的手翩翩起舞", "跳舞"},
  {"dogleg", "對", "狗腿", "狗腿"},
  {"drivel", "對著", "流口水", "流唾液"},
  {"french", "給", "一個法國式的吻", "法國的吻"},
  {"giggle", "對著", "傻傻的呆笑", "傻笑"},
  {"grin", "對", "露出邪惡的笑容", "奸笑"},
  {"growl", "對", "咆哮不已", "咆哮"},
  {"hand", "跟", "握手", "握手"},
  {"hug", "輕輕地擁抱", "", "擁抱"},
  {"jab", "溫柔的戳著", "", "戳人"},
  {"kick", "把", "踢的死去活來", "踢人"},
  {"kiss", "給", "一個溫柔的吻", "溫柔的吻"},
  {"laugh", "大聲嘲笑", "", "嘲笑"},
  {"marry", "捧著九百九十九朵玫瑰向", "求婚", "求婚"},
  {"nod", "向", "點頭稱是", "同意"},
  {"nudge", "用手肘頂", "的肥肚子", "攻擊"},
  {"pad", "輕拍", "的肩膀", "拍肩"},
  {"pinch", "用力的把", "擰的黑青", "用力擰人"},
  {"punch", "狠狠揍了", "一頓", "揍人"},
  {"shrug", "無奈地向", "聳了聳肩膀", "聳肩"},
  {"sigh", "對", "歎了一口氣", "歎氣"},
  {"slap", "啪啪的巴了", "一頓耳光", "打耳光"},
  {"smooch", "擁吻著", "", "擁吻"},
  {"snicker", "嘿嘿嘿..的對", "竊笑", "竊笑"},
  {"sniff", "對", "嗤之以鼻", "不屑"},
  {"sob", "對", "憤憤的說 You S...un Of B...each！", "陽光沙灘"},
  {"spank", "用巴掌打", "的臀部", "打屁屁"},
  {"squeeze", "緊緊地擁抱著", "", "緊緊擁抱"},
  {"thank", "向", "道謝", "道謝"},
  {"tickle", "咕嘰!咕嘰!搔", "的癢", "搔癢"},
  {"wave", "對著", "拼命的揮手", "揮手"},
  {"wink", "對", "神秘的眨眨眼睛", "眨眼"},
  {"zap", "對", "瘋狂的攻擊", "猛攻"},
  {NULL, NULL, NULL, NULL}
};


int
party_action(unum, cmd, party)
  int unum;
  char *cmd;
  char *party;
{
  int i;

  for (i = 0; party_data[i].verb; i++)
  {
    if (!strcmp(cmd, party_data[i].verb))
    {
      if (*party == '\0')
      {
        party = "大家";
      }
      else
      {
        int recunum = fuzzy_chatid_to_indx(party);

        if (recunum < 0)
        {
          /* no such user, or ambiguous */
          if (recunum == -1)
            sprintf(chatbuf, msg_no_such_id, party);
          else
            sprintf(chatbuf, "※ 請指明聊天代號", party);
          send_to_unum(unum, chatbuf);
          return 0;
        }
        party = users[recunum].chatid;
      }
      sprintf(chatbuf, "%s PARTY_ACTION", users[unum].userid);
      send_to_room_hide(users[unum].room, chatbuf);
      sprintf(chatbuf, "[1;32m%s [31m%s[33m %s [31m%s[37;0m",
        users[unum].chatid,
        party_data[i].part1_msg, party, party_data[i].part2_msg);
      send_to_room(users[unum].room, chatbuf);
      return 0;
    }
  }
  return 1;
}


/* -------------------------------------------- */
/* MUD-like social commands : speak              */
/* -------------------------------------------- */


struct action speak_data[] =
{
  {"ask", "詢問", NULL, "詢問"},
  {"chant", "歌頌", NULL, "歌頌"},
  {"cheer", "喝采", NULL, "喝采"},
  {"curse", "咒罵", NULL, "咒罵"},
  {"demand", "要求", NULL, "要求"},
  {"frown", "蹙眉", NULL, "蹙眉"},
  {"groan", "呻吟", NULL, "呻吟"},
  {"grumble", "發牢騷", NULL, "發牢騷"},
  {"helpme", "大聲呼救", NULL, "大聲呼救"},
  {"hum", "喃喃自語", NULL, "喃喃自語"},
  {"moan", "悲嘆", NULL, "悲嘆"},
  {"notice", "注意", NULL, "注意"},
  {"order", "命令", NULL, "命令"},
  {"ponder", "沈思", NULL, "沈思"},
  {"pout", "噘著嘴說", NULL, "噘著嘴說"},
  {"pray", "祈禱", NULL, "祈禱"},
  {"request", "懇求", NULL, "懇求"},
  {"shout", "大叫", NULL, "大叫"},
  {"sing", "唱歌", NULL, "唱歌"},
  {"smile", "微笑", NULL, "微笑"},
  {"smirk", "假笑", NULL, "假笑"},
  {"swear", "發誓", NULL, "發誓"},
  {"tease", "嘲笑", NULL, "嘲笑"},
  {"whimper", "嗚咽的說", NULL, "鳴咽的說"},
  {"yell", "大喊", NULL, "大喊"},
  {NULL, NULL, NULL, NULL}
};



int
speak_action(unum, cmd, msg)
  int unum;
  char *cmd;
  char *msg;
{
  int i;

  for (i = 0; speak_data[i].verb; i++)
  {
    if (!strcmp(cmd, speak_data[i].verb))
    {
      sprintf(chatbuf, "%s SPEAK_ACTION", users[unum].userid);
      send_to_room_hide(users[unum].room, chatbuf);
      if (msg[0])
        sprintf(chatbuf, "[1;32m%s [31m%s：[33m %s[37;0m",
                users[unum].chatid, speak_data[i].part1_msg, msg);
      else
        sprintf(chatbuf, "[1;32m%s [31m%s[33m[37;0m",
                users[unum].chatid, speak_data[i].part1_msg);
      send_to_room(users[unum].room, chatbuf);
      return 0;
    }
  }
  return 1;
}


/* -------------------------------------------- */
/* MUD-like social commands : condition          */
/* -------------------------------------------- */


struct action condition_data[] =
{
  {"applaud", "啪啪啪啪啪啪啪....", NULL, "鼓掌"},
  {"back", "回來坐正繼續奮戰", NULL, "回來"},
  {"blood", "倒在血泊之中", NULL, "失血"},
  {"blush", "臉都紅了", NULL, "臉紅"},
  {"bokan", "Bo Kan! Bo Kan!", NULL, "氣功\"},
  {"cough", "咳了幾聲", NULL, "咳嗽"},
  {"die", "暴斃", NULL, "死亡"},
  {"faint", "當場昏倒", NULL, "昏倒"},
  {"haha", "哇哈哈哈哈哈哈哈哈~~~~!!!!!", NULL, "哈哈哈"},
  {"happy", "ＹＡ！ *^_^*", NULL, "口耶"},
  {"hurricane", "Ｈｏ---Ｒｙｕ--Ｋａｎ！！！", NULL, "昇龍拳"},
  {"idle", "呆住了", NULL, "呆住"},
  {"lag", "lllllllaaaaaaaaaaaagggggggggggggg.................", NULL, "腳"},
  {"puke", "嘔吐中", NULL, "嘔吐"},
  {"room", "r-o-O-m-r-O-Ｏ-Mmm-rRＲ........", NULL, "房間"},
  {"shake", "搖了搖頭", NULL, "搖頭"},
  {"sleep", "趴在鍵盤上睡著了，口水流進鍵盤，造成當機！", NULL, "睡著"},
  {"so", "就醬子!!", NULL, "如此"},
/*{"strut", "大搖大擺\地走", NULL},*/
  {"tongue", "吐了吐舌頭", NULL, "吐舌"},
  {"think", "歪著頭想了一下", NULL, "思考"},
  {"wawa", "哇哇哇~~~~~!!!!!  ~~~>_<~~~", NULL, "哇哇哇"},
  {"www", "汪汪汪!!!", NULL, "全球網頁"},
  {NULL, NULL, NULL, NULL}
};



int
condition_action(unum, cmd)
  int unum;
  char *cmd;
{
  int i;

  for (i = 0; condition_data[i].verb; i++)
  {
    if (!strcmp(cmd, condition_data[i].verb))
    {
      sprintf(chatbuf, "%s CONDITION_ACTION", users[unum].userid);
      send_to_room_hide(users[unum].room, chatbuf);
      sprintf(chatbuf, "[1;32m%s [31m%s[0m",
        users[unum].chatid, condition_data[i].part1_msg);
      send_to_room(users[unum].room, chatbuf);
      return 1;
    }
  }
  return 0;
}


/* -------------------------------------------- */
/* MUD-like social commands : help               */
/* -------------------------------------------- */

char *dscrb[] = {
  "[1m【 Verb + Nick：   動詞 + 對方名字 】[36m   例：//french Kaede[0m",
  "[1m【 Verb + Message：動詞 + 要說的話 】[36m   例：//sing I swear...[0m",
"[1m【 Verb：動詞 】    ↑↓：舊話重提[0m", NULL};
struct action *verbs[] = {party_data, speak_data, condition_data, NULL};


#define SCREEN_WIDTH    80
#define MAX_VERB_LEN    10
#define VERB_NO         8


void
view_action_verb(unum, c)
  int unum,
      c;        /* view verbs of class c */
{
  int i, j;
  char *p;
  char *q;

  if(c==0) {
    send_to_unum(unum, "  [//]help 1 - 列出第一類動詞");
    send_to_unum(unum, "  [//]help 2 - 列出第二類動詞");
    send_to_unum(unum, "  [//]help 3 - 列出第三類動詞");
    send_to_unum(unum, "");
    return ;
  }

  c -- ;
/*  send_to_unum(unum, "/c"); */
  send_to_unum(unum, dscrb[c]);
  chatbuf[0] = '\0';
  i = j = 0;

  p = verbs[0][0].verb ;

  while(p) {
    chatbuf[0] = '\0' ;
    while (p = verbs[c][j].verb)
    {
      j++;
      strcat(chatbuf, p);
      if ((j % VERB_NO) == 0)
      {
        send_to_unum(unum, chatbuf);
        chatbuf[0] = '\0';
        break ;
      }
      else
      {
        strncat(chatbuf, "         ", MAX_VERB_LEN - strlen(p));
      }
    }

    if (j % VERB_NO)
      send_to_unum(unum, chatbuf);

    chatbuf[0] = '\0' ;
    while (p = verbs[c][i].keyword) {
      i ++ ;
      strcat(chatbuf, p);
      if((i % VERB_NO) == 0)
      {
        send_to_unum(unum, chatbuf) ;
        chatbuf[0] = '\0' ;
        break ;
      }
      else
        strncat(chatbuf, "         ", MAX_VERB_LEN - strlen(p));
    }

    if (i % VERB_NO)
      send_to_unum(unum, chatbuf);
  }

  send_to_unum(unum, " ");
}




struct chatcmd chatcmdlist[] =
{
  "act", chat_act, 0,
  "bye", chat_goodbye, 0,
  "flags", chat_setroom, 0,
  "invite", chat_invite, 0,
  "join", chat_join, 0,
  "kick", chat_kick, 0,
  "msg", chat_private, 0,
  "nick", chat_nick, 0,
  "operator", chat_makeop, 0,
  "rooms", chat_list_rooms, 0,
  "whoin", chat_list_by_room, 1,
  "wall", chat_broadcast, 1,

  "who", chat_map_chatids_thisroom, 0,
  "list", chat_list_users, 0,
  "topic", chat_topic, 0,

  NULL, NULL, 0
};


int
command_execute(unum)
  int unum;
{
  char *msg = users[unum].ibuf;
  char *cmd;
  struct chatcmd *cmdrec;
  int match = 0;

  /* Validation routine */
  if (users[unum].room == -1)
  {
    /* MUST give special /! command if not in the room yet */
    if (msg[0] != '/' || msg[1] != '!')
      return -1;
    else
      return (login_user(unum, msg + 2));
  }

  /* If not a /-command, it goes to the room. */
  if (msg[0] != '/')
  {
    chat_allmsg(unum, msg);
    return 0;
  }

  msg++;
  cmd = nextword(&msg);

  if (cmd[0] == '/')
  {

    if ( !strcmp(cmd + 1, "help") || cmd[1]=='\0')
    {
      int c ;

      c = atoi(msg) ;

      switch(c) {
      case 1:
        view_action_verb(unum, 1) ;
        match = 1 ;
        break ;
      case 2:
        view_action_verb(unum, 2) ;
        match = 1;
        break ;
      case 3:
        view_action_verb(unum, 3) ;
        match = 1;
        break ;
      default:
        view_action_verb(unum, 0) ;
        match = 1 ;
      }
    }
    else if (party_action(unum, cmd + 1, msg) == 0)
      match = 1;
    else if (speak_action(unum, cmd + 1, msg) == 0)
      match = 1;
    else
      match = condition_action(unum, cmd + 1);
  }
  else
  {
    for (cmdrec = chatcmdlist; !match && cmdrec->cmdstr; cmdrec++)
    {
      if (cmdrec->exact)
        match = !strcasecmp(cmd, cmdrec->cmdstr);
      else
        match = !strncasecmp(cmd, cmdrec->cmdstr, strlen(cmd));
      if (match)
        cmdrec->cmdfunc(unum, msg);
    }
  }

  if (!match)
  {
    sprintf(chatbuf, "◆ 指令錯誤：/%s", cmd);
    send_to_unum(unum, chatbuf);
  }
  memset(users[unum].ibuf, 0, sizeof users[unum].ibuf);
  return 0;
}


int
process_chat_command(unum)
  int unum;
{
  register int i;
  int rc, ibufsize;

  if ((rc = recv(users[unum].sockfd, chatbuf, sizeof chatbuf, 0)) <= 0)
  {
    /* disconnected */
    exit_room(unum, EXIT_LOSTCONN, (char *) NULL);
    return -1;
  }
  ibufsize = users[unum].ibufsize;
  for (i = 0; i < rc; i++)
  {
    /* if newline is two characters, throw out the first */
    if (chatbuf[i] == '\r')
      continue;

    /* carriage return signals end of line */
    else if (chatbuf[i] == '\n')
    {
      users[unum].ibuf[ibufsize] = chatbuf[i] = '\0';
      if (command_execute(unum) == -1)
        return -1;
      ibufsize = 0;
    }

    /* add other chars to input buffer unless size limit exceeded */
    else
    {
      if (ibufsize < 79)
        users[unum].ibuf[ibufsize++] = chatbuf[i];
    }
  }
  users[unum].ibufsize = ibufsize;
  return 0;
}


int
main()
{
  struct sockaddr_in sin;
  register int i;
  int pid, sr, newsock, sinsize;
  fd_set readfds;
  struct timeval tv;

  setgid(BBSGID);
  setuid(BBSUID);

  /* ----------------------------- */
  /* init variable : rooms & users */
  /* ----------------------------- */

  strcpy(rooms[0].name, mainroom);
  strcpy(rooms[0].topic, maintopic);

  for (i = 0; i < MAXACTIVE; i++)
  {
    users[i].chatid[0] = '\0';
    users[i].sockfd = users[i].utent = -1;
  }

  /* ------------------------------ */
  /* bind chat server to port       */
  /* ------------------------------ */

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    return -1;
  }

  sin.sin_family = AF_INET;
  sin.sin_port = CHATPORT;
  sin.sin_addr.s_addr = INADDR_ANY;

  if (bind(sock, (struct sockaddr *) & sin, sizeof(sin)) < 0)
  {
    return -1;
  }

  sinsize = sizeof sin;
  if (getsockname(sock, (struct sockaddr *) & sin, &sinsize) == -1)
  {
    perror("getsockname");
    exit(1);
  }

  if (listen(sock, 5) == -1)
  {
    perror("listen");
    exit(1);
  }

  if (fork())
  {
    exit(0);
  }
  setpgid(0, 0);

  /* ------------------------------ */
  /* trap signals                   */
  /* ------------------------------ */

  signal(SIGHUP, SIG_IGN);
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGPIPE, SIG_IGN);
  signal(SIGALRM, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  signal(SIGURG, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);


  FD_ZERO(&allfds);
  FD_SET(sock, &allfds);
  nfds = sock + 1;

  while (1)
  {
    memcpy(&readfds, &allfds, sizeof readfds);

    tv.tv_sec = 60 * 30;
    tv.tv_usec = 0;
    if ((sr = select(nfds, &readfds, NULL, NULL, &tv)) < 0)
    {
      if (errno != EINTR)
        sleep(5);
      continue;
    }
    else if (!sr)
      continue;

#if 0
    if (sr == 0)
    {
      exit(0);                  /* normal chat server shutdown */
    }
    if (tvptr)
      tvptr = NULL;
#endif

    if (FD_ISSET(sock, &readfds))
    {
      sinsize = sizeof sin;
      newsock = accept(sock, (struct sockaddr *) & sin, &sinsize);
      if (newsock == -1)
      {
        continue;
      }
      for (i = 0; i < MAXACTIVE; i++)
      {
        if (users[i].sockfd == -1)
        {
          struct hostent *hp;
          char *s = users[i].host;

          hp = gethostbyaddr((char *) &sin.sin_addr, sizeof(struct in_addr),
            sin.sin_family);
          strncpy(s, hp ? hp->h_name : (char *) inet_ntoa(sin.sin_addr), 30);
          s[29] = 0;
          users[i].sockfd = newsock;
          users[i].room = -1;
          break;
        }
      }

      if (i >= MAXACTIVE)
      {
        /* full -- no more chat users */
        close(newsock);
      }
      else
      {

#if !RELIABLE_SELECT_FOR_WRITE
        int flags = fcntl(newsock, F_GETFL, 0);

        flags |= O_NDELAY;
        fcntl(newsock, F_SETFL, flags);
#endif

        FD_SET(newsock, &allfds);
        if (newsock >= nfds)
          nfds = newsock + 1;
        num_conns++;
      }
    }

    for (i = 0; i < MAXACTIVE; i++)
    {
      /* we are done with newsock, so re-use the variable */
      newsock = users[i].sockfd;
      if (newsock != -1 && FD_ISSET(newsock, &readfds))
      {
        if (process_chat_command(i) == -1)
        {
          logout_user(i);
        }
      }
    }

#if 0
    if (num_conns <= 0)
    {
      /* one more pass at select, then we go bye-bye */
      tvptr = &zerotv;
    }
#endif
  }
  /* NOTREACHED */
}
