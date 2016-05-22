#include<queue>
#include<cstdio>
using namespace std;
const int N=30*2;
const long long inf=1ll<<62;
const char suit[]="SHDC",rank[]="1234567890JQKLMNOPRSTUVWX";
long long cost[N][N],sn[256],d[N];
int n,t,rn[256],p[N],u[N],c[N][N];
char su[N][N];
inline long long Cost(int a,int b){return cost[a][b]-cost[b][a];}
int go(int st=0)
{
    int i,v;
    long long tmp;
    for(i=0;i<=t;i++)
        u[i]=1,d[i]=inf;
    d[st]=0;
    queue<int> Q;
    Q.push(st);
    while(!Q.empty()){
        u[v=Q.front()]=1,Q.pop();
        for(i=1;i<=t;i++){
            if(c[v][i]>0)
                tmp=d[v]+Cost(v,i);
            else continue;
            if(tmp<d[i]){
                p[i]=v;
                d[i]=tmp;
                if(u[i])Q.push(i),u[i]=0;
            }
        }
    }
    if(d[t]>=inf)return 0;
    for(i=t;i!=0;i=p[i]){
        c[p[i]][i]--;
        c[i][p[i]]++;
    }
    return 1;
}
int flow()
{
    int i,sum=0;
    while(go()>0)sum++;
    return sum;
}
inline long long pow(int n,int k)
{
    long long i;
    for(i=1;k--;i*=n);
    return i;
}
void add(int i,int x)
{
    c[i][x/4+n+1]=1;
    long long tmp=x%4*pow(4,25-x/4);
    if(tmp<cost[i][x/4]){
        cost[i][x/4+n+1]=tmp;
        su[x/4+n+1][i]=suit[x%4];
    }
}
main()
{
    freopen("pa.in","r",stdin);
    int i,j,k,m,T;
    char tmp[20];
    for(i=0;suit[i];i++)
        sn[suit[i]]=i;
    for(i=0;rank[i];i++)
        rn[rank[i]]=i;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        t=n*2+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                su[i][j]=c[i][j]=0,cost[i][j]=inf;
        for(i=0;i<n;i++)
            cost[0][i+1]=0,c[0][i+1]=1;
        for(i=0;i<n;i++)
            cost[n+i+1][t]=0,c[n+i+1][t]=1;
        for(i=0;i<n;i++){
            scanf("%d",&m);
            while(m--){
                scanf("%s",tmp);
                if(rn[tmp[1]]<n)
                    add(i+1,sn[tmp[0]]+rn[tmp[1]]*4);
            }
        }
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                if(cost[i][j]>=inf)cost[i][j]=0;
        if(flow()<n){
            puts("no solution");
            continue;
        }
        char s0[20];
        for(i=0;i<n;i++){
            for(j=0;!c[n+j+1][i+1];j++);
            s0[j]=su[n+j+1][i+1];
        }
        printf("%c1",s0[0]);
        for(i=1;i<n;i++)
            printf(" %c%c",s0[i],rank[i]);
        puts("");
    }
}
