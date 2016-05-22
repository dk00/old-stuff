#include<cstdio>
#include<algorithm>
using namespace std;
const int N=51;
struct pt{
    int t,d;
    bool operator<(pt a)const{
	return d<a.d;
    }
}s[N];
int n,t,p[N*3],id[N],c[N*3][N*3];
int go(int v){
    if(v==t)return 1;
    if(p[v])return 0;
    p[v]=1;
    for(int i=0;i<=t;i++)
	if(c[v][i]-- && go(i))
	    return ++c[i][v];
	else
	    c[v][i]++;
    return 0;
}
int flow()
{
    int f=0;
    while(1){
	for(int i=0;i<=t;i++)p[i]=0;
	if(!go(0))break;
	f++;
    }
    return f;
}
int go()
{
    int i,j,ub=-99999999;
    sort(s,s+n);
    for(i=j=0;i<n;i++){
	j+=s[i].t;
	if(j-s[i].d>ub)
	    ub=j-s[i].d;	    
    }
    return ub;
}
main()
{
    int i,j,k;
    freopen("pb.in","r",stdin);
    while(scanf("%d",&n)==1 && n){
	t=n+51;
	for(i=0;i<=t;i++)
	    for(j=0;j<=t;j++)
		c[i][j]=0;
	for(i=0;i<n;i++){
	    scanf("%d %d %d %d: ",id+i,&s[i].t,&s[i].d,&j);
	    while(j--){
		scanf("%d",&k);
		c[id[i]][n+k]=1;
	    }
	}
	for(i=0;i<n;i++)
	    c[0][i+1]=1;
	for(i=0;i<50;i++)
	    c[n+i+1][t]=1;
	if(flow()==n)
	    printf("%d\n",go());
	else
	    puts("NoSolution");
    }
}
