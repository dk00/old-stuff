#include<math.h>
#include<time.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
char **arg;
extern char **environ;
double *stt;
inline long long gettime();
inline int exec()
{
	int pid,tmp;
	if(!(pid=fork()))
	{
		*stt=gettime();
		execve("./hello",arg,environ);
	}
	wait(&tmp);
	return pid;
}
inline long long gettime()
{
	struct timespec tp;
	if(clock_gettime(CLOCK_REALTIME,&tp))
	{
		printf("clock_gettime() error: %s\n",strerror(errno));
		exit(0);
	}
	return tp.tv_nsec;
}
double s[100001];
main(int m,char *a[])
{
	int n=1000;
	char *op;
	int (*func)();
	arg=malloc(sizeof(arg[0]));
	arg[0]=NULL;
	if(m<2)
	{
		puts("fbench [number_of_samples] fork|vfork|exec");
		return 0;
	}
	if(m==2)
		op=a[1];
	else
	{
		if(sscanf(a[1],"%d",&n)!=1)
			printf("%s is not a valid number\n",a[1]);
		op=a[2];
	}
	if(!strcmp(op,"fork"))
		func=fork;
	else if(!strcmp(op,"vfork"))
		func=vfork;
	else if(!strcmp(op,"exec"))
	{
		FILE *fp=fopen("hello.c","r");
		if(!fp)
		{
			puts("can't access hello.c");
			return 0;
		}
		fclose(fp);
		system("gcc hello.c -o hello");
		fp=fopen("hello","rb");
		if(!fp)
		{
			puts("compile error");
			return 0;
		}
		func=exec;
		strcpy(op,"fork+exec");
	}
	else
	{
		printf("unknown function: %s\n",op);
		return 0;
	}
	if(n>100000)n=100000;
	
	int i,stat,pid;
	double st,sum=0;
	stt=&st;
	struct timespec tp;
	for(i=0;i<n;i++)
	{
		st=gettime()/1000;
		if(!(pid=func()))exit(0);
		s[i]=(gettime()/1000-st);		
		if(pid<0)
		{
			printf("fork error: %s\n",strerror(errno));
			exit(0);
		}
		kill(pid,SIGKILL);
		if(s[i]<0)s[i]+=1000000;
		sum+=s[i];
		wait(&stat);
	}
	sum/=n;
	printf("%s: %.4lf",op,sum);
	for(i=0;i<n;i++)
		s[i]=abs(s[i]-sum);
	for(sum=i=0;i<n;i++)
		sum+=s[i]*s[i];
	printf(" +- %.4lf usecs\n",1.96*sqrt(sum/n));
}
