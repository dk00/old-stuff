#include<cstdio>
#include<algorithm>
using namespace std;
struct edge
{
	int a,b,c;
	bool operator<(edge x)const
	{
		if(a!=x.a)return a<x.a;
		return b<x.b;
	}
}s[20008];
int num1[20008],st[20008];
char u[10001];
int go(int v)
{
	if(u[v])return -1;
	u[v]=1;
	int i,sum=1;
	for(i=st[v];i<st[v+1];i++)
	{
		num1[i]=go(s[i].b);
		if(num1[i]>=0)
			sum+=num1[i];
	}
	return sum;
}
main()
{
	int i,j,n,m,T;
	long long sum;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i=0;i<n;i++)u[i]=0;
		for(i=0;i<n-1;i++)
		{
			scanf("%d %d %d",&s[i].a,&s[i].b,&s[i].c);
			s[i+n-1]=s[i];
			swap(s[i].a,s[i].b);
		}
		m=n*2-2;
		sort(s,s+m);
		for(i=j=0;i<n;i++)
		{
			while(i!=s[j].a)j++;
			st[i]=j;
		}
		st[i]=m;
		go(0);
		for(sum=i=j=0;i<m;i++)
		{
			if(num1[i]>=0)
				j++,sum+=1ll*num1[i]*(n-num1[i])*s[i].c;
		}
		printf("%lf\n",(((double)sum)/(1ll*n*(n-1)/2))+1e-11);
	}
}
