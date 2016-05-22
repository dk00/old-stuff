#include<cstdio>
const int N=101,inf=2000000000;
int n,d[N],p[N],xd[N],cost[N][N];
char u[N],c[N][N];
int sp()
{
    int i,j;
    for(i=0;i<n;i++)
        p[i]=-1,d[i]=inf,u[i]=1;
    d[0]=0;
    while(1)
    {
        for(i=0;(!u[i] || d[i]>=inf)&& i<n;i++);
        if(i>=n)break;
        u[i]=0;
        for(j=0;j<n;j++)
        {
            if(c[i][j]==1 && d[i]+cost[i][j]+xd[i]-xd[j]<d[j])
                d[j]=d[i]+cost[p[j]=i][j]+xd[i]-xd[j];
            if(c[i][j]==2 && d[i]-cost[j][i]+xd[i]-xd[j]<d[j])
                d[j]=d[i]-cost[j][p[j]=i]+xd[i]-xd[j];
        }
    }
    return d[n-1];
}
long long flow(int dem,int one)
{
    int i,j;
    long long cc=0,sum=0;
    while(dem>0 && (j=sp())<inf)
    {
        for(i=0;i<n;i++)xd[i]+=d[i];
        sum+=(dem<?one)*xd[n-1];
        dem-=one;
        for(i=n-1;i!=0;i=p[i])
            c[p[i]][i]--,c[i][p[i]]++;
    }
    if(dem>0)return -1;
    return sum;
}
main()
{
    int i,j,k,m;
    long long tmp;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k),i--,j--;
            if(i==j)continue;
            c[i][j]=c[j][i]=1,cost[i][j]=cost[j][i]=k;
        }
        scanf("%d %d",&j,&k);
        tmp=flow(j,k);
        if(tmp<0)puts("Impossible.");
        else printf("%lld\n",tmp);
    }
}
