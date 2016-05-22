#include"mysock.h"
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
int NewSock() {
  int sd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sd < 0)
    perror("socket");
  return sd;
}
int Bind(int sd,int port) {
  sockaddr_in addr;
  bzero(&addr,sizeof(addr));
  addr.sin_family = AF_INET;  
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(port);
  int r = bind(sd,(struct sockaddr *)&addr,sizeof(addr));
  if (r < 0)
    perror("bind");
  return r;
}
void SetAddr(const char ip[],int port,sockaddr_in *addr) {
    bzero(addr,sizeof(*addr));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(ip);
    addr->sin_port = htons(port);
}
int Ready(int sd,int t) {
  struct timeval tv;
  struct timeval *ptv = &tv;
  if (t < 0) {
    ptv = NULL;
  } else {
    tv.tv_sec = t/1000;
    tv.tv_usec = t%1000*1000;
  }
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(sd, &fds);
  if (select(sd + 1, &fds, NULL, NULL, ptv) > 0)
    return FD_ISSET(sd, &fds);
  return 0;
}
inline long long Wait(long long t){
  static long long last = 0;
	struct timespec tp;
	if (clock_gettime(CLOCK_REALTIME, &tp)) {
		perror("clock_gettime()");
    return -1;
	}
  long long rt = t - (tp.tv_sec * 1000000000ll + tp.tv_nsec - last)/1000;
  last = tp.tv_sec * 1000000000ll + tp.tv_nsec;  
  if (rt > 0) usleep(rt);
  return 0;
}
