#include"tftp.h"
#include"mysock.h"
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
void ProcError(const TftpPacket *p) {
  printf("Error %d: %s\n", p->block, p->buf);
}
main(int argc, char **argv) {
  int port;
  if (argc < 3 || sscanf(argv[2], "%d", &port) != 1) return 0;  
  sockaddr_in serv;  
  SetAddr(argv[1], port, &serv);
  char line[256], cmd[64], name[192];
  while(1) {
    printf("> ");
    gets(line);
    int num_arg;
    if ( (num_arg = sscanf(line, "%s %s", cmd, name)) < 1) continue;
    if (!strcmp(cmd, "exit")) break;
    else if (num_arg > 1 && !strcmp(cmd, "get")) {
      if (!access(name,F_OK)) {
        int fd = open(name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
        if (fd < 0) {
          puts("Can't open the file for write");
          continue;
        }
        close(fd);
      }      
      if (!fork()) {
        int sd = NewSock();
        if (SendRQ(sd, &serv, RRQ, name) == 0) 
          if (RecvFile(sd, serv, name) < 0)
            perror("recv");
        close(sd);
        _exit(0);
      }
    }
    else if (num_arg > 1 && !strcmp(cmd, "put")){
      int fd = open(name, O_RDONLY);
      if (fd < 0) {
        puts("Can't open the file for read (not found or no permission)");
        continue;
      }
      close(fd);
      if (!fork()) {
        int sd = NewSock();
        if (SendRQ(sd, &serv, WRQ, name) == 0)
          SendFile(sd, serv, name);
        close(sd);
        _exit(0);
      }
    }
    else puts("Unknown command.");
  }
}
