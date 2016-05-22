#include<vector>
#include<cstdio>
const int N=1001;
int n,m,p[N];
std::vector<int> c[N];
int go(int v)
{
	if(p[v]==m)return 0;
	p[v]=m;
	int i,sum=1;
	for(i=0;i<c[v].size();i++)
	    sum+=go(c[v][i]);
	return sum;
}
main()
{
	int i,j;
	while(scanf("%d %d",&n,&m)>0)
	{
        
		for(i=0;i<n;i++)p[i]=n,c[i].clear();
		while(m--)
		{
			scanf("%d %d",&i,&j);
			c[i-1].push_back(j-1);
		}
		for(m=j=0;m<n;m++)
			j+=(i=go(m));
		printf("%d\n",n*(n+1)/2-j);
	}
}
