#include"tftp.h"
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
extern void ProcError(const TftpPacket *p);
int SendRQ(int sd, sockaddr_in *dest, short op, const char name[]) {
  int retry = 50, timeout = 1500;
  char buf[512];
  *(short *)buf = op;
  strcpy(buf + 2,name);
  int len = strlen(buf + 2);
  strcpy(buf + len + 3, "octet");
  len += 9;
  int i;
  while(1) {
    puts("Sending request...");
    sendto(sd, buf, len, 0, (struct sockaddr *)dest, sizeof(*dest));
    if(Ready(sd, timeout)) {
      TftpPacket ack;
      if (Peek(sd, &dest, &ack) < 0) return -1;      
      if (op == RRQ) break;      
      if (ack.op == ACK && ack.block == 0) {
        Recv(sd, &dest, &ack);
        break;
      }
    }
  }
  return 0;
}
int Send(int sd, sockaddr_in dest, const TftpPacket *p) {
  return sendto(sd, p, p->len, 0, (struct sockaddr *)&dest, sizeof(dest));
}
int Peek(int sd, sockaddr_in *sour, TftpPacket *p) {
  socklen_t s_len;
  int len = recvfrom(sd, p, sizeof(p), MSG_PEEK, (struct sockaddr *)sour, &s_len);
  p->len = len;
  if (p->op == ERROR) {
    ProcError(p);
    return -1;
  }
  return len;
}
int Recv(int sd, sockaddr_in *sour, TftpPacket *p) {
  socklen_t s_len;
  int len = recvfrom(sd, p, sizeof(p), 0, (struct sockaddr *)sour, &s_len);
  p->len = len;
  if (p->op == ERROR) {
    ProcError(p);
    return -1;
  }
  return len;
}
int SendError(int sd, sockaddr_in dest, short code, const char mes[]) {
  printf("%d %s\n", code, mes);
  int retry = 500, timeout = 250;
  int i = retry;
  TftpPacket err;
  err.op = ERROR;
  err.block = code;
  strcpy(err.buf,mes);
  err.len = 4 + strlen(mes);
  while (i--) {
    Send(sd, dest, &err);
    if(Ready(sd, timeout))
      return 0;
  }
  return -1;  
}

int SendFile(int sd, sockaddr_in dest, const char name[]) {
  int fd = open(name, O_RDONLY);
  if (fd < 0) return -1;
  int i = 0 , rem,
      num_block = (lseek(fd, 0, SEEK_END) + BLOCK_SIZE)/BLOCK_SIZE;
  rem = num_block;
  //TODO: bit compression
  char *done = malloc(num_block);
  bzero(done,num_block);
  TftpPacket data, ack;
  data.op = DATA;
  printf("%d blocks\n", num_block);
  while (rem > 0) {     // TODO: timeout
    while (done[i++]) 
      if (i >= num_block) i = 0;
    if (i >= num_block) i = 0;
    int num_read = pread(fd, data.buf, BLOCK_SIZE, i*BLOCK_SIZE);
    if (num_read < 0) {
      close(fd);
      return -1;
    }
    data.block = i + 1;
    data.len = 4 + num_read;
    printf("Send data %d/%d %d\n", data.block, num_block, data.len);
    Send(sd, dest, &data);
    while (Ready(sd, 0)) {
      if (Recv(sd,&dest,&ack) < 0) {
        close(fd);
        return -1;
      }
      if (ack.op == ACK) {
        printf("ack %d\n", ack.block);
        if (ack.block>0 && ack.block <= num_block && !done[ack.block]) {          
          done[ack.block] = 1;
          --rem;
        }
      }
      else if(ack.op == ERROR) break;
      else {
        // TODO: Errors handling
      }
    }
  }
  close(fd);
  free(done);  
  return 0;
}
int RecvFile(int sd, const char name[]) {
  int fd = open(name, O_WRONLY|O_CREAT|S_IRUSR|S_IWUSR);
  if (fd < 1) return -1;
  TftpPacket data;
  sockaddr_in sour;
  while(Ready(sd, -1)) {                  // TODO: timeout
    int size = Recv(sd, &sour, &data);    // TODO: last block?
    printf("recv %d %d\n", data.block, data.len);
    if (size < 0 /*|| pwrite(fd, data.buf, size, data.block*BLOCK_SIZE) < 0*/) {
      close(fd);
      return -1;
    }
    data.op = ACK;
    data.len = 4;
    Send(sd, sour, &data);
  }
  close(fd);
  return 0;
}

