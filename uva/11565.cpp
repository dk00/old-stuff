#include<cstdio>
int n,m;
char go(int x,int y)
{
	int a,b;
	if(x<n)a=n-1-x;
	else a=x-n+1;
	if(y<n)b=n-1-y;
	else b=y-n+1;
	if(a+b>n-1)return '.';
	return 'a'+(a+b)%26;
}
main()
{
	int C=1,x1,y1,x2,y2,i,j;
	while(scanf("%d %d %d %d %d",&n,&x1,&y1,&x2,&y2)==5 && n)
	{
		m=2*n-1;
		printf("Case %d:\n",C++);
		for(i=x1;i<=x2;i++,puts(""))
			for(j=y1;j<=y2;j++)
				putchar(go(i%m,j%m));
	}
}
