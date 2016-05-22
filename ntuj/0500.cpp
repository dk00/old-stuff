#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001;
vector<int> c[N],len[N];
int n,m,dep[N],low[N];
int go(int v,int d)
{
	if(dep[v]>0)
		return 0;
	if(v==0)
		return d;
	dep[v]=d+1;
	int i,j=0,k=0;
	for(i=0;i<c[v].size();i++)
	{
		len[v][i]=go(c[v][i],d+1);
		if(len[v][i]>len[v][k])
			k=i,j=k;
		else if(len[v][i]>len[v][j])
			j=i;		
	}

}
main()
{
	int i,j,k;
	while(scanf("%d %d",&n,&m)==2)
	{
		for(i=0;i<n;i++)c[i].clear();
		for(i=0;i<n+m;i++)
		{
			scanf("%d %d",&j,&k);
			c[j-1].push_back(k-1);
			c[k-1].push_back(j-1);
			dg[j-1]++;
			dg[k-1]++;
		}
		for(i=0;i<n;i++)
			len.resize(c[i].size());
		sort(c[0].begin(),c[0].end());
		for(i=0;i<n;i++)
		{
			low[i]=n+1;
			dep[i]=0;
			go(0,0);
		}
	}
}
