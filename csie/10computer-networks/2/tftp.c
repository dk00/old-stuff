#include"tftp.h"
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
extern void ProcError(const TftpPacket *p);
// Send a request to server
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
// Send a TFTP packet
int Send(int sd, sockaddr_in dest, const TftpPacket *p) {
	fprintf(stderr, "Send packet (op %d, block %d, len %d)\n",
      p->op, p->block, p->len);
	return sendto(sd, p, p->len, 0, (struct sockaddr *)&dest, sizeof(dest));
}
// Read a TFTP packet without remove it from buffer 
int Peek(int sd, sockaddr_in *sour, TftpPacket *p) {
	socklen_t s_len = sizeof(*sour);
	int len = recvfrom(sd, p, sizeof(*p), MSG_PEEK, (struct sockaddr *)sour, &s_len);
	p->len = len;
	if (p->op == ERROR) {
		ProcError(p);
		return -1;
	}
	return len;
}
// Read a TFTP packet
int Recv(int sd, sockaddr_in *sour, TftpPacket *p) {
	socklen_t s_len = sizeof(*sour);
	int len = recvfrom(sd, p, sizeof(*p), 0, (struct sockaddr *)sour, &s_len);
	p->len = len;
	if (p->op == ERROR) {
		ProcError(p);
		return -1;
	}
	return len;
}
// Send an error packet
int SendError(int sd, sockaddr_in dest, short code, const char mes[]) {
	printf("Send Error Packet %d: %s\n", code, mes);
	int retry = 5, timeout = 200;
	int i = retry;
	TftpPacket err;
	err.op = ERROR;
	err.block = code;
	strcpy(err.buf,mes);
	err.len = 5 + strlen(mes);
	while (i--) {
		Send(sd, dest, &err);
		if(Ready(sd, timeout)) return 0;
	}
	return -1;  
}
// Send a file
int SendFile(int sd, sockaddr_in dest, const char name[]) {
	int timeout = 1500000; //microsecond
	int fd = open(name, O_RDONLY);
	if (fd < 0) return -1;
	int i = 0 , rem,
		num_block = (lseek(fd, 0, SEEK_END) + BLOCK_SIZE)/BLOCK_SIZE;
	rem = num_block;
	char *done = malloc(num_block);
	bzero(done, num_block);
	TftpPacket data, ack;
	data.op = DATA;
	printf("%d blocks\n", num_block);
	Timer(1);             //Reset Timer
	while (rem > 0) {     
		if(i >= num_block) i = 0;
		while (done[i]) 
			if (++i >= num_block) i = 0;
		int num_read = pread(fd, data.buf, BLOCK_SIZE, i*BLOCK_SIZE);
		if (num_read < 0) {
			close(fd);
			return -1;
		}
		data.block = ++i;
		data.len = 4 + num_read;
		printf("Send data %d/%d %d byte(s)\n", data.block, num_block, data.len);
		Send(sd, dest, &data);
		while (Ready(sd, 0)) {
			if (Recv(sd,&dest,&ack) < 0) {
				close(fd);
				return -1;
			}
			Timer(1);
			if (ack.op == ACK) {
				printf("ack #%d\n", ack.block);
				if (ack.block>0 && ack.block <= num_block && !done[ack.block-1]) {
					done[ack.block-1] = 1;
					--rem;
				}
			}
			else if(ack.op == ERROR) {
        close(fd);
        return -1;
      }
		}
		if(Timer(0) >= timeout){
			fprintf(stderr, "Timeout: Already sent %d/%d\n", num_block - rem, num_block);
			// Client Error or Normal Exit
			break;
		}
	}
  printf("Sent \'%s\', %u byte(s)\n", name, lseek(fd, 0, SEEK_END));
	close(fd);
	free(done);
	return 0;
}
#include "nset.h"
// Recieve a file
int RecvFile(int sd, sockaddr_in oris, const char name[]) {
	int fd = open(name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	if (fd < 1){
		SendError(sd, oris, 6, "File already exists.");
		return -1;
	}
	TftpPacket data;
	sockaddr_in sour;
	NaiveSet dataNSet;	
	initNSet(&dataNSet);
	while(!chkDone(&dataNSet) && Ready(sd, 10000)) {
		int size = Recv(sd, &sour, &data);
		int i;
		printf("recv %d %d %d\n", data.op, data.block, data.len);

		if (size < 4 || pwrite(fd, data.buf, size - 4,
          (data.block - 1)*BLOCK_SIZE) < 0) {
			close(fd);
			SendError(sd, sour, 2, "Access violation.");
			return -1;
		}		
		setNSet(&dataNSet, data.block - 1);
    //View as last block of data
		if(data.op == DATA && data.len < BLOCK_SIZE + 4)
			setLastChunk(&dataNSet, data.block - 1);
		data.op = ACK;
		data.len = 4;
    printf("Send ACK #%d\n", data.block);
		Send(sd, sour, &data);
	}
  printf("Recieved \'%s\', %u byte(s).\n", name, lseek(fd, 0, SEEK_END));
	close(fd);
	return 0;
}

