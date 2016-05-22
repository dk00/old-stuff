#ifndef _MYSOCK_H
#define _MYSOCK_H
#include<netinet/in.h>
class MySock {
public:
  MySock();
  bool SetDest(const char ip[],int port);
  bool Bind(int port);
  unsigned Send(int len, const char buf[]);
  unsigned Recv(char buf[]);
  bool Ready(int t);
  sockaddr_in from
private:
  int sd;
  sockaddr_in dest;
};

inline long long Wait(long long t);
inline long long Timer(int type);
#endif
