#include<cstdio>
char go(int n,int m)
{
	int i,j,k,a,b,s[99];
	for(i=0;i<n;i++)
		s[i]=1;
	for(;i<n*2;i++)
		s[i]=-1;
	a=1,b=n;
	int x=n*2;

	for(j=0;x>0;)
	{
		k=m%x+x;
		x--;
		while(1)
		{
//			printf("%d:%d\n",j,s[j]);
			if(s[j]!=0)k--;
			if(k<=0)break;
			j=(j+1)%(2*n);
		}
		if(s[j]>0)a--;
		if(s[j]<0)b--;
//		printf("%d ",j);
		s[j]=0;
		if(b<=0)return 0;
		if(a<=0)return 1;
	}
	puts("!!");
	return 1;
}
main()
{
	int n,m;
	while(scanf("%d",&n)==1)
	{
		for(m=1;go(n,m);m++);
		printf("%d\n",m);
	}
}
