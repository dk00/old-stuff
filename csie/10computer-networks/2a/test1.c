#include"tftp.h"
#include"mysock.h"
main()
{
  char mes[] = "abcd";
  short i = *(short *)mes;
	int sd = NewSock();
  printf("%d\n", i);
  TftpPacket p;
	p.op = 12;
  p.len = 2;
	sockaddr_in serv;
	SetAddr("127.0.0.1",6666,&serv);
	while(1) {
		Wait(0);
    puts("Sending");
		Send(sd,serv,&p);
		Wait(1000000);
	}
}
