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
void printerr(){printf(strerror(errno));}
jmp_buf pt;
void ph(int signum){longjmp(pt,1);}
main(int m,char **a)
{
	FILE *fp=NULL;
	if(m>1)
	{
		unlink(a[1]);
		mkfifo(a[1],0666);
		fp=fopen(a[1],"rb");
	}
	else quit("Usage: server <FIFO>");
	if(!fp)
		quit("The filename of FIFO is not specified or invalid");
	if(m>2)
		fprintf(stderr,"Warning: too many arguments\n");
	signal(SIGPIPE,ph);
	int C=0;
	while(1)
	{
		usleep(1);
		pid_t pid[2];
		pid[0]=getpid();
		if(fread(pid+1,sizeof(*pid),1,fp)<1)
		{
			if(feof(fp) && !C)
				printinfo(2),C=1;
			continue;
		}
		char client[99];
		sprintf(client,"%d",pid[1]);
		struct stat a;
		if(stat(client,&a))
		{
			printf("Can't read attributes of client-specific FIFO %s (",client);
			printerr();
			printf(").\n");
			continue;
		}
		if(!S_ISFIFO(a.st_mode))
		{
			printf("Client-sepcific FIFO %s is not a FIFO\n",client);
			continue;
		}
		FILE *rp=fopen(client,"wb");
		if(!rp)
		{
			printf("Can't open client specific FIFO %s(",client);
			printerr();
			puts(")\n");
			continue;
		}
		if(setjmp(pt))
		{
			printinfo(1);
			continue;
		}
		fwrite(pid,sizeof(*pid),2,rp);
		fclose(rp);
	}
}
