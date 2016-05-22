#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
void fib(int n)
{
	int a=0,b=1;
	while(n--)
	{
		printf("%d ",a);
		b+=a;
		a=b-a;
	}
	puts("");
}
main(int m,char *a[])
{
	int n=5,stat;
	if(m>1)
		sscanf(a[1],"%d",&n);
	if(fork()==0)fib(n);
	else if(fork()==-1)
		printf("fork error: %s\n",strerror(errno));
	else wait(&stat);
}
