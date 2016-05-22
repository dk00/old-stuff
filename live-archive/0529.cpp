#include<map>
#include<queue>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
const int N=99,Len=99,inf=500000;
int t,d[N],p[N],in[N],c[N][N][4],f[N][N],cap[N][N];
void init(int n)
{
	t=n+1;
	int i,j,k;
	for(i=0;i<=t;i++)
		for(j=0;j<=t;j++)
			f[i][j]=cap[i][j]=0;
}
void add(int u,int v,int l)
{
	c[u][v][cap[u][v]++]=l;
}
void fix()
{
	int i,j;
	for(i=0;i<=t;i++)
		for(j=0;j<=t;j++)
			if(f[i][j]>0)
				sort(c[i][j],c[i][j]+f[i][j]);
}
int Min(int a,int b)
{
	if(f[b][a]>0)
		return -c[b][a][f[b][a]-1];
	if(f[a][b]<cap[a][b])
		return c[a][b][f[a][b]];
	return inf;
}
int proc(int a,int b)
{
	if(f[b][a]>0)
		return -c[b][a][--f[b][a]];
	if(f[a][b]<cap[a][b])
		return c[a][b][f[a][b]++];
	printf("Error: proc %d %d\n",a,b);
	return inf;
}
int sp(int st,int ed)
{
	int i,j,k;
	for(i=0;i<=t;i++)
		d[i]=inf,in[i]=0;
	queue<int> Q;
	d[st]=0;
	Q.push(st);
	while(!Q.empty()){
		i=Q.front(),in[i]=0;
		Q.pop();
		for(j=0;j<=t;j++){
			k=Min(i,j);
			if(d[i]+k<d[j]){
//				printf(">%d ",j);
				d[j]=d[i]+k;
				p[j]=i;
				if(!in[j])
					Q.push(j),in[j]=1;
			}
		}
	}
	if(d[ed]>=inf)return inf;
	for(i=ed,j=0;i!=st;i=p[i])
		j+=proc(p[i],i);
	return j;
}
main()
{
	int n,m;
	map<string,int> h;
	while(scanf("%d %d",&n,&m)==2 && n+m){
		h.clear();
		char tmp0[Len],tmp1[Len];
		int i,j,k;
		for(i=0;i<n;i++){
			scanf("%s",tmp0);
			h[tmp0]=i;
		}
		init(n);
		while(m--){
			scanf("%s %s %d",tmp0,tmp1,&k);
			i=h[tmp0];
			j=h[tmp1];
			add(i+1,j+1,k);
			add(j+1,i+1,k);
		}
		fix();
		for(m=k=0;m<4;m++){
			scanf("%s %s",tmp0,tmp1);
			/*add(0,h[tmp0]+1,0);
			add(h[tmp1]+1,t,0);*/
			k+=sp(h[tmp0]+1,h[tmp1]+1);
		}
		printf("%d\n",k);
	}
}
