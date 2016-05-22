#include<cstdio>
#include<algorithm>
const int N=999,MAXT=505;
struct pt{
    int s,t;
    bool operator<(pt a)const{
	if(s!=a.s)return s<a.s;
	return t<a.t;
    }
}s[N];
int n,C,T,un,u[N][MAXT],r[N][MAXT];
int go(int v,int t)
{
    if(v>=n)return 0;
    if(u[v][t]==un)return r[v][t];
    u[v][t]=un;
    int i,k,ub=0,st=t;
    ub=go(v+1,t);
    for(i=0;i<C && i+v<n;i++){
        if(s[i+v].s>st)st=s[i+v].s;
	if(st+T>s[v].t)break;
	k=i+1+go(i+v+1,st+T);
	if(k>ub)ub=k;
    }
    return r[v][t]=ub;
}
main()
{
    int i,j,k,q,max;
    freopen("pc.in","r",stdin);
    while(scanf("%d %d %d",&n,&C,&T)==3 && n){
	un++;
	for(i=0;i<n;i++){
	    scanf("%d %d",&s[i].s,&s[i].t);
	    if(s[i].s+T>s[i].t)i--,n--;
	}
	std::sort(s,s+n);
	printf("%d\n",go(0,0));
    }
}
