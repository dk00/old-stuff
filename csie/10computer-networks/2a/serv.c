#include"tftp.h"
#include"mysock.h"
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#define Message printf
typedef struct {
  unsigned ip,port,pid;
}Client;
int qn = 0;
Client q[1024];
int Inqueue(sockaddr_in a) {
  printf("%u %u\n",a.sin_port,a.sin_addr.s_addr);
  if (qn > 1024 || !a.sin_port || !a.sin_addr.s_addr) return 1;
  int i;
  for (i = 0; i < qn; ++i)
    if (a.sin_port == q[i].port && a.sin_addr.s_addr == q[i].ip)
      return 1;
  return 0;
}
void Enqueue(sockaddr_in a,unsigned pid) {
  q[qn].pid = pid;
  q[qn].ip = a.sin_addr.s_addr;
  q[qn++].port = a.sin_port;
}
void Dequeue(unsigned pid) {
  printf("Remove %u\n", pid);
  int i;
  for (i = 0; i < qn; ++i)
    if (q[i].pid == pid) break;
  if (i > qn) return;
  q[i] = q[--qn];
}

void ShowInfo(sockaddr_in client,short op) {
  char ip[16];
  inet_ntop(AF_INET, &(client.sin_addr), ip, INET_ADDRSTRLEN);
  printf("[%s:%d]\tOP %d\n", ip, ntohs(client.sin_port), op);
  fflush(stdout);
}
void ProcError(const TftpPacket *p) {}
int Serve(const char mes[], sockaddr_in client) {
  short op = *(short *)mes,name_len;
  ShowInfo(client, op);  
  if (op == ERROR)
    return 0;
  int sd = NewSock(), error = 0;
  if (sd < 0) return -1;  
  if (op != RRQ && op != WRQ) {
    SendError(sd, client, 4, "Illegal TFTP operation.");
    close(sd);
    return -1;
  }
  const char *name = mes + 2;
  name_len = strlen(name);
  const char *mode = name + name_len;
  if (op == RRQ) {
    Message("RRQ %s\n", name);
    if (SendFile(sd, client, name) < 0) error = 1;
  }
  else if (op == WRQ) {
    Message("WRQ %s\n", name);
    TftpPacket p;
    p.op = ACK;
    p.block = 0;
    p.len = 4;
    while(!Ready(sd,100)) Send(sd, client, &p);
    if (RecvFile(sd, name) < 0) error = 1;
  }
  if (!error) {
    close(sd);
    return 0;
  }

  if (errno == ENOENT)
    SendError(sd, client, 1, "File not found.");
  else if (errno == EEXIST)
    SendError(sd, client, 6, "File already exists.");
  else if (errno == EACCES)
    SendError(sd, client, 2, "Access violation.");  
  else if (errno == ENOSPC || errno == EMFILE || errno == ENOMEM 
      || errno == ENFILE)
    SendError(sd, client, 3, "Disk full or allocation exceeded.");
  else SendError(sd, client, 0,"Client or Undefined Error"); // TODO: Other errors
  close(sd);
  return -1;
}
main(int argc,char **argv) {  
  if (argc < 2) return 0;
  int port;
  if (sscanf(argv[1],"%d",&port) != 1) return 0;
  sockaddr_in serv;
  int sd = NewSock();
  if (sd < 0 || Bind(sd, port) < 0) return -1;
  while(1) {
    if (!Ready(sd,-1))
      continue;
    char mes[512];
    sockaddr_in client;
    socklen_t c_len;
    int l = recvfrom(sd,mes,512,0,(struct sockaddr *)&client,&c_len), stat;
    pid_t sub;
    while (qn > 0 && (sub = waitpid(-1, &stat, WNOHANG))) Dequeue(sub);
    if (Inqueue(client)) continue;
    sub = fork();
    if (!sub) {
      Serve(mes, client);
      _exit(0);
    }
//    Enqueue(client, sub);
  }
}
