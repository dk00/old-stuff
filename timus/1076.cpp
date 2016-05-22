#include<cstdio>
const int inf=2147483647;
const int V=310;
char u[V];
int n,p[V],q[V*V],cap[V][V],cost[V][V];
int d[V+1];
int sp()
{
    int i,j,k;
    for(i=0;i<n;i++)d[i]=inf,u[i]=1;
    q[0]=d[0]=u[0]=0;
    for(i=0,j=1;i<j;i++)
    {
        u[q[i]]=1;
        for(k=0;k<n;k++)
        {
            if(cap[q[i]][k]==1 && d[q[i]]+cost[q[i]][k]<d[k])
            {
                d[k]=d[p[k]=q[i]]+cost[q[i]][k];
                if(u[k])u[q[j++]=k]=0;
            }
        }
    }
    if(d[n-1]<inf)return d[n-1];
    return -1;
}
int flow(int m)
{
    int tmp,sum=0;
    while(m-- && (tmp=sp())>=0)
    {
        sum+=tmp;
        for(int i=n-1;i>0;i=p[i])
            cap[p[i]][i]--,cap[i][p[i]]++;
    }
    return sum;
}
main()
{
    int i,j,k,t;
    while(scanf("%d",&n)==1)
    {
        t=2*n+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                cap[i][j]=cost[i][j]=0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                scanf("%d",&cost[i+1][j+n+1]);
                cap[i+1][j+n+1]=1;
            }
        for(j=0;j<n;j++)
        {
            for(i=k=0;i<n;i++)
                k+=cost[i+1][j+n+1];
            for(i=0;i<n;i++)
            {
                cost[i+1][j+n+1]=k-cost[i+1][j+n+1];
                cost[j+n+1][i+1]=-cost[i+1][j+n+1];
            }
            cap[0][j+1]=cap[j+n+1][t]=1;
        }
        t=n,n=2*n+2;
        printf("%d\n",flow(t));
    }
}
