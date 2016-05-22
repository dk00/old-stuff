#include<queue>
#include<cstdio>
using namespace std;
const int N=1001,inf=2147483647;
int n,c[N][N],d[N];
int sp(int lim)
{
	int i,j;
	for(i=0;i<n;i++)d[i]=inf;
	queue<int> q0,q1;
	d[0]=0;
	q0.push(0);
	while(q0.size() || q1.size())
	{
		if(q0.size())j=q0.front(),q0.pop();
		else j=q1.front(),q1.pop();
		for(i=0;i<n;i++)
		{
			if(c[j][i]<=lim && d[j]<d[i])
				d[i]=d[j],q0.push(i);
			if(c[j][i]<inf && c[j][i]>lim && d[j]+1<d[i])
				d[i]=d[j]+1,q1.push(i);
		}
	}
	return d[n-1];
}
main()
{
	int i,j,k,m,z,ub;
	while(scanf("%d %d %d",&n,&m,&z)==3)
	{
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				c[i][j]=inf;
		ub=0;
		while(m--)
		{
			scanf("%d %d %d",&i,&j,&k);
			i--,j--;
			c[i][j]=c[j][i]=k;
			if(k>ub)ub=k;
		}
		for(i=0,j=ub;i<j;)
		{
			k=(i+j)/2;
			if(sp(k)<=z)j=k;
			else i=k+1;
		}
		printf("%d\n",i);
	}
}
