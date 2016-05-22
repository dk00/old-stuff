#include<nds.h>
#include<netdb.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"text.h"
#include"keyboard.h"
extern u32 keysPress();
void getTouch(short &x,short &y);
void iac(int sc,const char *ptr);
void Send(int sd,const char buf[],int n,int f)
{
	for(int i=0;i<n;i+=send(sd,buf+i,n-i,0));
}
const int buflen=128;
u32 getip(const char host[]){return *(unsigned *)gethostbyname(host)->h_addr_list[0];}
int connect(const char host[],u16 port=23)
{
	int sd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in sin;
	sin.sin_addr.s_addr=getip(host);
	sin.sin_family=AF_INET;
	sin.sin_port=htons(port);
	if(connect(sd,(struct sockaddr *)&sin,sizeof(sin))<0)
		return -1;;
	int flags=1;
	ioctl(sd,FIONBIO,&flags);
//	fcntl(sd,F_SETFL,flags|O_NONBLOCK);
	return sd;
}
enum State
{
	Text,IAC
};
void resp(int sd,const char mes[])
{
	printf(Sub,"\x1b[20;3fIAC:");
	for(int i=0;mes[i];i++)
		printf(Sub,"%02X ",mes[i]);
	iac(sd,mes);
}
void sendkey(int sd,char c)
{
	int n=1;
	char buf[32];
	for(int i=0;i<6;i++)buf[i]=0;
	buf[0]=27;
	if(c<=26)
		n=1,buf[0]=c;
	else if(c==BS)
		n=1,buf[0]=0x7f,buf[1]=0;
	else if(c==Up)
		n=3,buf[1]='O',buf[2]='A';
	else if(c==Down)
		n=3,buf[1]='O',buf[2]='B';
	else if(c==Right)
		n=3,buf[1]='O',buf[2]='C';
	else if(c==Left)
		n=3,buf[1]='O',buf[2]='D';
	else if(c==Del)
		n=4,buf[1]='[',buf[2]='3',buf[3]='~';
	else
		buf[0]=c;
	printf(Sub,"\x1b[21;2f[%d]send(%d) : %d %d %d",c,n,buf[0],buf[1],buf[2]);
	send(sd,buf,n,0);
}
const u32 KEY_FUNCS=KEY_LEFT|KEY_RIGHT|KEY_UP|KEY_DOWN;
void run(int sd)
{
	int i,j,len=-1;
	static int m=0;
	static char buf[buflen],mes[buflen];
	buf[0]=255;
	buf[1]=253;
	buf[2]=241;
	send(sd,buf,3,0);
	int stat=Text;
	printf(Main,"\x1b[1;1f\x1b[m ");
	while(len)
	{
		len=buflen+1;
		while(len>=buflen)
		{
			printf(Sub,"\x1b[1;1frecv               ");
			len=recv(sd,buf,128,0);
			printf(Sub,"\x1b[1;1f                   ");
			if(len<1)break;
			printf(Sub,"\x1b[19;3frecv:                                                 \x1b[19;8f");
			for(i=0;i<len;i++)
				printf(Sub," %02X",buf[i]);
			printf(Sub,"\x1b[18;3ftext:");
			for(i=0;i<len;i++)
				putchar(Sub,buf[i]);
			for(i=j=0;j<len;j++)
			{
				if(stat==Text)
				{
					if(buf[j]==255)
					{	
						buf[j]=0;
						printf(Main,buf+i);
						i=j+1;
						stat=IAC;
						mes[0]=255,m=1;
					}
				}
				else 
				{
					mes[m++]=buf[j];
					if(buf[j]==240 ||(m==3 && mes[1]!=250))
					{
						i=j+1;
						resp(sd,mes);
						stat=Text;
					}
				}
			}
			buf[len]=0;
			if(stat==Text && i<len)
				printf(Main,buf+i);
		}
		scanKeys();
		u32 keys=keysDownRepeat();
		u32 keyh=keysHeld();
		if(KEY_L&keyh)	//Scroll right
			Main.scrollH(-2);
		if(KEY_R&keyh)	//Scroll left
			Main.scrollH(2);
		if(KEY_UP&keys)
			sendkey(sd,Up);
		if(KEY_DOWN&keys)
			sendkey(sd,Down);
		if(KEY_LEFT&keys)
			sendkey(sd,Left);
		if(KEY_RIGHT&keys)
			sendkey(sd,Right);
		if(KEY_A&keys)
			sendkey(sd,Enter);
		if(KEY_B&keys)
			sendkey(sd,Left);
		if(KEY_Y&keys)
			sendkey(sd,'y');
		if(KEY_TOUCH&keys)
		{
			char kb_key=kb.press();
			if(kb_key)
				sendkey(sd,kb_key);
		}
		printf(Sub,"\x1b[22;2fscr (%d,%d) %d %d    ",Main.x,Main.y,Main.top,Main.bot);
		swiWaitForVBlank();
	}
}
