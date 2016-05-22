#include"tftp.h"
#include"mysock.h"
#include<stdio.h>
void ProcError(const TftpPacket *p) {
  printf("Error %d: %s\n", p->block, p->buf);
}
main(int argc, char **argv) {
  int port;
  if (argc < 2 || sscanf(argv[2], "%d", &port) != 1) return 0;  
  sockaddr_in serv;  
  SetAddr(argv[1], port, &serv);
  char line[256], cmd[64], name[192];
  while(1) {
    printf("> ");
    gets(line);
    sscanf(line, "%s %s", cmd, name);
    if (!strcmp(cmd, "exit")) break;
    if (!strcmp(cmd, "get")) {      
      if (!fork()) {
        int sd = NewSock();
        if (SendRQ(sd, &serv, RRQ, name) == 0) 
          if(RecvFile(sd, name)<0)
            perror("recv");
        close(sd);
        _exit(0);
      }
    }
    if (!strcmp(cmd, "put")) {
      if (!fork()) {
        int sd = NewSock();
        if (SendRQ(sd, &serv, WRQ, name) == 0) SendFile(sd, serv, name);
        close(sd);
        _exit(0);
      }
    }
  }
}
