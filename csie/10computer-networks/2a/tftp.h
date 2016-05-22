#ifndef _TFTP_H
#define _TFTP_H
#include"mysock.h"
#define BLOCK_SIZE 512
enum Operations {RRQ = 1, WRQ, DATA, ACK, ERROR};
typedef struct {
  short op, block;
  char buf[512];
  int len;
} TftpPacket;
int SendRQ(int sd, sockaddr_in *dest, short op, const char name[]);
int Send(int sd, sockaddr_in dest, const TftpPacket *p);
int SendError(int sd, sockaddr_in dest, short code, const char mes[]);
int SendFile(int sd, sockaddr_in dest, const char name[]);
int RecvFile(int sd, const char name[]);
#endif

