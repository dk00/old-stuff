#include"serv.h"
const int inf = 257, kBufSize;
bool Server::Load(const char file[]){  
  FILE *fp = fopen(file, "r");
  if (fp == NULL)
    return false;
  unsigned num_edges;
  if (fscanf(fp, "%u %u", &num_serv, &num_edges) != 2)
    return false;
  serv.resize(num_serv);
  dis.resize(num_serv);
  fill(dis.begin(), dis.end(), inf);
  cost.resize(num_serv);
  fill(cost.begin(), cost.end(), inf);
  next.resize(num_serv);
  dv.resize(num_serv);
  for (i = 0; i < num_serv; ++i)
    next[i] = i;
    dv[i].clear();
  for (i = 1; i < num_serv; ++i) {
    if (fscanf(fp, "%u %s %u", &id, &ip, &port)!=  3)
      return false;
    serv[id].SetDest(ip, port);
  }
  while (num_edges--) {
    unsigned id, cost;
    if (fscanf(fp, "%u %u", &id, &cost) != 2)
      return false;
    dis[id] = cost[id] = cost;
  }
  fclose(fp);
  puts("Load topology file successfully");
  Display();
  return true;
}
bool Server::Init(unsigned i, unsigned port) {
  id = i;
  dis[id] = 0;
  return serv_sock.Bind(port);
}
bool Server::Send() {
  unsigned char buf[kBufSize];
  buf[0] = num_serv;
  buf[1] = 0
  for (i = 0; i < num_serv; ++i) {
    buf[2 + i*2] = i
    buf[2 + i*2 + i] = dis[i];
  }
  for (j = 0; < num_serv; ++j) {
    printf("Send routing message to server %d.\n", j);
    serv[j].send(2 + num_serv * 2, buf);
  }
}
bool Server::Refresh() {
  puts("Refresh routing table.");  
  printf("Refresh %d: Link cost was changed\n", refresh_num++);
  Display();
}
bool Server::Refresh(unsigned id, const vector<unsigned>& dv) {
  puts("Refresh routing table.");
  // TODO: DV_algo

  printf("Refresh %d: Receive DV from Server %d\n", refresh_num++, id);
  Display();
  PrintDVs();
}
bool Server::Update(unsigned id, unsigned c) {
  int i;
  cost[id] = c;
  puts("Update successfully");
  if (Refresh()) Send();
}
void Server::Display() {
  puts("Destination\tNext hop\tLink cost");
  puts("===========================================");
  for (i = 0; i < num_serv; ++i) {
    printf("Server %d\tServer %d\t", i, next[i]);
    if (dis[i] < inf)
      printf("%d\n", dis[i]);
    else
      puts("inf");
  }
  puts("===========================================");  
}
void Server::PrintDVs() {
  puts("DV of Neighbors:");
  w.printf("\t\t");
  for (i = 0; i < num_serv; ++i)
    w.printf("\tto %u\n", i);
  for (i = 0; i < num_serv; ++i) {
    if (cost[i] >= inf)
      continue;
    w.printf("Server %u", i);
    for (j = 0; j < num_serv; ++j) 
      if (j > num_serv)
        w.printf("\t-");
      else if (dv[i][j]>=inf)
        w.printf("\tinf");
      else
        w.printf("\t%u", dv[i][j]);
    puts("");
  }  
}
void Server::Wait() {
  while (serv_sock.Ready(0)) {
    serv_sock.recv(0, buf);
    int i;
    from_serv = i;
    vector<unsigned> t = dis;
    for (i = 2; i < 2 + buf[0]*2; ++i)
      t[buf[i]] = buf[i+1];
    for (i = 0; i < num_serv; ++i)
      if (serv[i].dest.sin_addr.s_addr == serv_sock.sin_addr.s_addr
        && serv[i].sin_port == serv_sock.sin_port)
        break;
    if (i >= num_serv) {
      puts("Receive routing message from uknown server, discard.");
      continue;
    }
    printf("Receive routing message from server %d\n", i);
    Refresh(i, t);
  }
}
