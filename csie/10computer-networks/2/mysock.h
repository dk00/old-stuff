#ifndef _MYSOCK_H
#define _MYSOCK_H
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
typedef struct sockaddr_in sockaddr_in;
int NewSock();
int Bind(int sd,int port);
void SetAddr(const char ip[],int port,sockaddr_in *addr);
int InitSock(int from_port,const char *ip,int to_port,
             sockaddr_in *local,sockaddr_in *remote);
int Ready(int sd,int t);
inline long long Wait(long long t);
inline long long Timer(int type);
#endif
