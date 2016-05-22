/* 
PROB: lepr
LANG: C++ 
*/
#include<cstdio>
const int N=201,dx[]={0,1,1,1},dy[]={1,1,0,-1};
int go(int n,int s[])
{
	int i,j,sum,min,max,s0,s1;
	min=max=s[0];
	for(i=j=s0=s1=sum=0;i<n;i++)
	{
		sum+=s[i];
		s0+=s[i];
		s1+=s[i];
		max>?=s0;
		min<?=s1;
		if(s0<0)s0=0;
		if(s1>0)s1=0;
		if(s[i]>0)j=1;
	}
	if(j>0)max>?=(sum-min);
	return max;
}
int s[N][N],tmp[N];
main()
{
	freopen("lepr.in","r",stdin);
	freopen("lepr.out","w",stdout);
	int i,j,k,x,y,n,max;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&s[i][j]);
	max=s[0][0];
	for(i=0;i<n;i++)
		for(j=0;j<4;j++)
		{
			for(k=y=0,x=i;k<n;k++)
			{
				tmp[k]=s[x][y];
				x+=dx[j],y+=dy[j];
				if(x>=n)x-=n;
				if(x<0)x+=n;
				if(y>=n)y-=n;
				if(y<0)y+=n;
			}
			max>?=go(n,tmp);
		}
	printf("%d\n",max);
}
