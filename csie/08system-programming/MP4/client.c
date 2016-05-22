#include<time.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<setjmp.h>
#include<sys/stat.h>
#include"printinfo.h"
void quit(char mes[])
{
	puts(mes);
	exit(0);
}
jmp_buf jp;
void ph(int signum){longjmp(jp,1);}
main(int m,char **a)
{
	if(m<3)
		quit("Usage: client <FIFO> <times to run>");
	int T=-1;
	sscanf(a[2],"%d",&T);
	if(T<0)
		quit("Invalid argument");
	if(m>3)
		fputs("Warning: too many arguments",stderr);
	signal(SIGPIPE,ph);
	while(T--)
	{
		sleep(1);
		FILE *fp=fopen(a[1],"wb");
		if(!fp)
			quit("The filename of well-known FIFO is not specified or invalid");
		char client[99];
		pid_t pid[2]={0,getpid()};
		sprintf(client,"%d",pid[1]);
		if(mkfifo(client,0666))
		{
			puts("Can't create client specific FIFO");
			continue;
		}
		if(setjmp(jp))
		{
			printinfo(3);
			unlink(client);
			continue;
		}
		fwrite(pid+1,sizeof(*pid),1,fp);
		fclose(fp);
		fp=fopen(client,"rb");
		if(!fp)
		{
			puts("Can't open clinet specific FIFO");
			continue;
		}
		if(fread(pid,sizeof(*pid),2,fp)<sizeof(*pid)*2)
			if(feof(fp))
			{
				printinfo(4);
				unlink(client);
				exit(0);
			}
		fclose(fp);
		unlink(client);
	}
}
