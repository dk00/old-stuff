#include<queue>
#include<cstdio>
#include<vector>
using namespace std;
const int N=10000,inf=200000000;
struct ed{
	int t,c;
	ed(int nt,int nc){t=nt,c=nc;};
};
vector<ed> c[N+1],r[N+1];
int d0[N+1],d1[N+1];
char u[N+1];
int sp(vector<ed> c[],int d[],int st)
{
	queue<int> q;
	int i,j,k,x;
	for(i=0;i<N;i++)u[i]=0;
	q.push(st);
	d[st]=0;
	while(q.size())
	{
		u[x=q.front()]=0;
		q.pop();
		for(i=0;i<c[x].size();i++)
		{
			j=c[x][i].t;
			k=c[x][i].c;
			if(d[x]+k<d[j])
			{
				d[j]=d[x]+k;
				if(!u[j])q.push(j),u[j]=1;
			}
		}
	}
}
main()
{
	int i,j,m,T,C=1;
	scanf("%d",&T);
	while(T--)
	{
		r[0].clear();
		c[N].clear();
		for(i=0;i<N+2;i++)
		{
			c[i].clear();
			r[i+1].clear();
			if(i+1<N){
				c[i].push_back(ed(i+1,1));
				r[i+1].push_back(ed(i,1));
			}
		}
		scanf("%d",&m);
		while(m--)
		{
			scanf("%d %d",&i,&j);
			if(i==j)continue;
			if(i<j)
			{
				c[i].push_back(ed(j,(j-i)/2));
				r[j].push_back(ed(i,(j-i)/2));
			}
			else
			{
				c[i].push_back(ed(j,-(i-j)/4));
				r[j].push_back(ed(i,-(i-j)/4));
			}
		}
		for(i=0;i<N;i++)
			d0[i]=d1[i]=inf;
		scanf("%d",&i);
		sp(c,d0,i);
		sp(r,d1,i);
		scanf("%d",&m);
		printf("DATA SET #%d\n",C++);
		while(m--)
		{
			scanf("%d",&i);
			if(d0[i]>=inf || d1[i]>=inf)
				puts("IMPOSSIBLE");
			else
				printf("%d\n",d0[i]+d1[i]);
		}
	}
}
