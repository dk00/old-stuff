#include<cstdio>
const long long inf=9223372036854775807ll;
const int V=100;
char u[V];
int n,p[V],q[V*V],cap[V][V],cost[V][V];
long long d[V+1];
long long sp()
{
    int i,j,k;
    for(i=0;i<n;i++)d[i]=inf,u[i]=1;
    q[0]=d[0]=u[0]=0;
    for(i=0,j=1;i<j;i++)
    {
        u[q[i]]=1;
        for(k=0;k<n;k++)
        {
            if(cap[q[i]][k]==2 && d[q[i]]-cost[k][q[i]]<d[k])
            {
                d[k]=d[p[k]=q[i]]-cost[k][q[i]];
                if(u[k])u[q[j++]=k]=0;
            }
            if(cap[q[i]][k]==1 && d[q[i]]+cost[q[i]][k]<d[k])
            {
                d[k]=d[p[k]=q[i]]+cost[q[i]][k];
                if(u[k])u[q[j++]=k]=0;
            }
        }
    }
    if(d[n-1]<inf)return d[n-1];
    return 0;
}
long long flow(int dem,int one)
{
    long long tmp,sum=0;
    while(dem>0 && (tmp=sp()))
    {
        sum+=tmp*(dem<?one);
        dem-=one;
        for(int i=n-1;i>0;i=p[i])
            cap[p[i]][i]--,cap[i][p[i]]++;
    }
    if(dem<=0)return sum;
    return -1;
}
main()
{
    int i,j,k,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                cap[i][j]=0;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k),i--,j--;
            cost[i][j]=cost[j][i]=k;
            cap[i][j]=cap[j][i]=1;
        }
        scanf("%d %d",&k,&m);
        long long ll=flow(k,m);
        if(ll>=0)printf("%lld\n",ll);
        else puts("Impossible.");
    }
}
