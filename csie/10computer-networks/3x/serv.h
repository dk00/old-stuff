#ifndef _SERV_H
#define _SERV_H
#include"mysock.h"
#include<vector>
using namespace std;
class Server {
public:
  bool Load(const char file[]);
  bool Send();
  bool Update(unsigned id, unsigned cost);
  bool Refresh();
  void Display();
  bool SetPort(unsigned port);
  void Wait();  
private:
  unsigned id, num_serv, refresh_num;
  MySock serv_sock;
  vector<MySock> serv;
  vector<vector<unsigned> > dv;
  vector<unsigned> dis, cost;
};
#endif
