#include<queue>
#include<cstdio>
using namespace std;
const int N=1300,inf=-2000000000;
int n,t,d[N],p[N],c[N][N],cost[N][N];
char u[N];
inline int Cost(int a,int b){return cost[a][b]-cost[b][a];}
int sp()
{
    int i,j;
    queue<int> Q;
    for(i=0;i<=t;i++)
        d[i]=inf,p[i]=i,u[i]=1;
    d[0]=0;
    Q.push(0);
    while(!Q.empty()){
        i=Q.front(),Q.pop();
        u[i]=1;
        for(j=1;j<=t;j++){
            if(c[i][j] && d[i]+Cost(i,j)>d[j]){
                d[j]=d[i]+Cost(i,j);
                p[j]=i;
                if(u[j])u[j]=0,Q.push(j);
            }
        }        
    }
    for(i=t;i>0;i=p[i])
        c[p[i]][i]--,c[i][p[i]]++;
    return d[t];
}
int flow()
{
    int i,sum=0;
    for(i=0;i<n;i++)sum+=sp();
    return sum;
}
main()
{
    int i,j,k,T;
    freopen("pc.in","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        t=n*2+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=cost[i][j]=0;
        for(k=0;k<n*n;k++){
            scanf("%d %d",&i,&j);
            c[i][j]=1;
            scanf("%d",&cost[i][j]);
        }
        scanf("%*d");
        for(i=0;i<n;i++)
            c[0][i+1]=c[i+n+1][t]=1;
        printf("%d\n",flow());
    }
}
