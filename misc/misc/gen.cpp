#include<ctime>
#include<cstdio>
#include<cstdlib>
int main()
{
	srand(time(NULL));
	int i,n=10000,m=100;
	printf("%d %d\n",n,m);
	for(i=0;i<10000;i++)
		printf("%d ",1+rand()%500000);
	puts("");
	for(i=0;i<100;i++)
		printf("%d %d\n",1+rand()%1000,1+rand()%1000);
}
