#include"mysock.h"
#include<ctime>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<sys/time.h>

MySock::MySock() {}

bool MySock::Init() {
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		perror("socket");
    return false;
  }
	return true;
}

bool MySock::Bind(int port) {
	sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;  
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	int r = bind(sd,(struct sockaddr *)&addr,sizeof(addr));
	if (r < 0) {
		perror("bind");
    return false;
  }
	return true;
}

bool MySock::SetDest(const char ip[],int port) {
	bzero(addr,sizeof(*dest));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = inet_addr(ip);
	addr->sin_port = htons(dest);
}

bool MySock::Ready(int t) {
	fd_set fds;
	FD_ZERO(&fds);
 	FD_SET(sd, &fds);
  FD_SET(0, &fds);
 	select(sd + 1, &fds, NULL, NULL, NULL);
 	return FD_ISSET(sd, &fds);
}

int MySock::Send(int len, const char buf[]) {
  sendto(sd, buf, len, 0, addr, sizeof(addr));
}

int MySock::Recv(int len, char buf[]) {
  socklen_t addr_len = sizeof(from);
  return recvform(sd, buf, len, 0, from, &from_len);
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

inline long long Timer(int type){
	static long long last = 0;
	struct timespec tp;
	if (clock_gettime(CLOCK_REALTIME, &tp)) {
		perror("clock_gettime()");
		return -1;
	}
	long long rt = (tp.tv_sec * 1000000000ll + tp.tv_nsec - last)/1000;
	if(type == 1)
		last = tp.tv_sec * 1000000000ll + tp.tv_nsec;
	return rt;
}
