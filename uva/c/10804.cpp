#include<math.h>
#include<stdio.h>
struct pt{
    double x,y;
    void get(){
        scanf("%lf %lf",&x,&y);
    }
    double operator-(pt a){
        return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));
    }
}gp[50],hp[50];
int s,t,n,m,p[102],u[102],c[102][102];
double mixd,maxd,dis[102][102];
void start(double max){
    int i,j;
    s=0,t=n+m+1;
    for(i=0;i<=n+m+1;i++)
        for(j=0;j<=n+m+1;j++)
            c[i][j]=0;
    for(i=1;i<=n;i++)
        for(j=n+1;j<=n+m;j++)
            c[i][j]=(dis[i][j]<=max);
    for(i=1;i<=n;i++)
        c[0][i]=1;
    for(i=n+1;i<=n+m;i++)
        c[i][t]=1;
}
int find(int v){
    if(v==t)return 1;
    for(int i=1;i<=t;i++)
        if(c[v][i] && u[i]){
            u[i]=0;
            if(find(i)){
                p[i]=v;
                return 1;
            }
        }
    return 0;
}
void push(int v){
    if(!v)return;
    c[p[v]][v]--;
    c[v][p[v]]++;
    if(mixd<dis[p[v]][v])
		mixd=dis[p[v]][v];
    if(maxd<dis[p[v]][v])
		maxd=dis[p[v]][v];
    push(p[v]);
}
int flow(){
    int i,j,k,f=0;
    while(1){
        for(i=1;i<=t;i++)p[i]=-1,u[i]=1;;
        if(find(s))push(t);
        else break;
        f++;
    }
    return f;
}
int main(){
int i,j,k,t,C=1;
double min,max,mid,find;
scanf("%d",&t);
while(t--){
    scanf("%d %d %d",&n,&m,&k);
    for(i=0;i<n;i++)gp[i].get();
    for(i=0;i<m;i++)hp[i].get();	
    printf("Case #%d:\n",C++);
    if(n-k>m){
        puts("Too bad.");
		if(t)puts("");
        continue;
    }
    for(i=0;i<n;i++)
		for(j=0;j<m;j++)
            dis[i+1][n+j+1]=gp[i]-hp[j];
    for(min=0.0,max=10e10;max-min>1e-5;){
        mid=(min+max)/2;
        start(mid);
        maxd=min;
		mixd=max;
		if(flow()>=n-k)
            find=max=maxd;
        else
            min=mid;
    }
    printf("%.3lf\n",find);
	if(t)puts("");
}
}
