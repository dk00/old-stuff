#include<cstdio>
const int V=1024,inf=2147483647;
int t,c[V][V],p[V],d[V],u[V],q[V];
int sp()
{
    int i,j,k;
    for(i=0;i<=t;i++)
        d[i]=inf;
    d[q[0]=t]=0;
    for(i=0,j=1;d[0]>=inf && i<j;i++)
        for(k=0;k<=t;k++)
            if(c[k][q[i]] && d[k]>=inf)
                d[q[j++]=k]=d[q[i]]+1;
    return d[0];
}
int go(int v)
{
    if(v==t)return 1;
    int sum=0;
    for(;u[v]<=t;u[v]++)
        if(d[v]==d[u[v]]+1)
        {
            if(c[v][u[v]]-- && go(u[v]))
            {
                c[u[v]][v]++;
                if(v)return 1;
                sum++;
            }
            else c[v][u[v]]++;
        }
    return sum;
}
int flow()
{
    int i,sum=0;
    while(sp()>=inf)
    {
        for(i=0;i<=t;i++)u[i]=0;
        sum+=go(0);
    }
    return sum;
}
main()
{
    int i,j,n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        t=n+m+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        for(i=1;i<=n;i++)c[0][i]=1;
        for(i=1;i<=m;i++)c[n+i][t]=1;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                scanf("%d",&c[i][n+j]);
        printf("Case %d: a maximum of %d nuts and bolts can be fitted together\n",
        C++,flow());
    }
}
