#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
main() {
  int s = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in a, from;
	bzero(&a,sizeof(a));
	a.sin_family = AF_INET;  
	a.sin_addr.s_addr = htonl(INADDR_ANY);
	a.sin_port = htons(5001);
  int x = bind(s,(struct sockaddr *)&a,sizeof(a));
  printf("%d\n", x);
  socklen_t from_len = sizeof(from);
  bzero(&from, sizeof(from));
  char buf[999];
  recvfrom(s, buf, 999, 0, (struct sockaddr *)&from, &from_len);  
  printf("%u\n", ntohs(from.sin_port));
}
