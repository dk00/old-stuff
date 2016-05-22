/* 
PROB: surround
LANG: C++ 
*/
#include<cstdio>
const int N=501,inf=2009;
short p[N],d[N],c[N][N];
int find(int v)
{
	if(v==p[v])return v;
	return p[v]=find(p[v]);
}
void uni(int a,int b)
{
	a=find(a),b=find(b);
	if(d[a]<d[b])p[a]=b;
	else p[b]=a;
	if(d[a]==d[b])d[a]++;
}
main()
{
	freopen("surround.in","r",stdin);
	freopen("surround.out","w",stdout);
	int i,j,k,n,min=inf;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		p[i]=i;
	for(i=0;i<n;i++)
	{
		scanf("%d %d",&j,&k);
		uni(j-1,k-1);
		for(j=0;j<n;j++)
			c[i][j]=inf;
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			scanf("%d",&k);
			c[find(i)][find(j)]<?=k;
		}
	for(i=0;i<n;i++)
	{
		for(j=k=0;j<n;j++)
			if(find(j)==j && find(j)!=find(i))
				k+=c[find(i)][find(j)];
		min<?=k;
	}
	printf("%d\n",min*2);
}
