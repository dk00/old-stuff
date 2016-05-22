#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
main() {
  int s = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in a, to;
	bzero(&a,sizeof(a));
	a.sin_family = AF_INET;  
	a.sin_addr.s_addr = htonl(INADDR_ANY);
	a.sin_port = htons(5002);
  bind(s,(struct sockaddr *)&a,sizeof(a));
  socklen_t to_len = sizeof(to);
  bzero(&to, sizeof(to));
	to.sin_family = AF_INET;  
	to.sin_addr.s_addr = inet_addr("127.0.0.1");
	to.sin_port = htons(5001);  
  char buf[999];
  sendto(s, buf, 999, 0, (struct sockaddr *)&to, to_len);
  printf("%u\n", ntohl(to.sin_port));
}
