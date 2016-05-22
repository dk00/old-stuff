#include<queue>
#include<cstdio>
using namespace std;
const int N=2009,inf=200000000;
int t,slot[N],p[N],d[N],u[N],c[N][N],bid[N][N];
int val(int x,int y){
    if(c[x][y]>0)
        return bid[x][y]-bid[y][x];
    return -inf;
}
int sp()
{
    int i,j,k;
    queue<int> Q;
    Q.push(0);
    for(i=0;i<=t;i++)d[i]=-inf,u[i]=0;
    d[0]=0;
    while(!Q.empty()){
        i=Q.front();
        Q.pop();
        for(j=0;j<=t;j++){
            if((k=val(i,j))<=-inf)
                continue;
            k+=d[i];
            if(d[j]<=-inf || k>d[j]){
                p[j]=i;
                d[j]=k;
                if(!u[j])u[j]=1,Q.push(j);
            }
        }
    }
    if(d[t]<=-inf)return d[t];
    for(i=t;i;i=p[i]){
        c[p[i]][i]--;
        c[i][p[i]]++;
    }
    return d[t];
}
int flow()
{
    int sum,tmp;
    for(sum=0;(tmp=sp())>0;sum+=tmp);
    return sum;
}
main()
{
    int i,j,k,l,T,n,m;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d %d",&k,&n,&m);
        t=k+n*10+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=bid[i][j]=0;
        for(i=0;i<10*n;i++)
            c[0][i+1]=1;
        for(i=0;i<k;i++)
            scanf("%d %d",slot+i,&c[10*n+i+1][t]);
        while(m--){
            scanf("%d %d %d",&i,&j,&k);
            bid[(i-1)*10+slot[j-1]][10*n+j]=k;
            c[(i-1)*10+slot[j-1]][10*n+j]=1;
        }
        /*for(i=0;i<=t;i++,puts(""))
            for(j=0;j<=t;j++)
                printf("%d ",c[i][j]);
        puts("--");
        for(i=0;i<=t;i++,puts(""))
            for(j=0;j<=t;j++)
                printf("%d ",bid[i][j]);*/
        printf("%d\n",flow());
    }
}
