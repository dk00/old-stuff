#include<cstdio>
#include<algorithm>
const long long inf=9223372036854775807ll;
const int V=300;
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
            if(cap[q[i]][k]==1 && d[q[i]]+cost[q[i]][k]<d[k])
            {
                d[k]=d[p[k]=q[i]]+cost[q[i]][k];
                if(u[k])u[q[j++]=k]=0;
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
    return sum;
}
struct pt{int x,y;}s1[200],s2[200];
int dis(pt a,pt b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}
char map[200][200];
main()
{
    int i,j,m,n1,n2,t;
    while(scanf("%d %d",&n,&m)==2 && n+m)
    {
        for(i=n1=n2=0;i<n;i++)
        {
            scanf("%s",map[i]);
            for(j=0;map[i][j];j++)
                if(map[i][j]=='H')
                    s1[n1++]=(pt){i,j};
                else if(map[i][j]=='m')
                    s2[n2++]=(pt){i,j};
        }
        t=n1*2+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                cap[i][j]=cost[i][j]=0;
        for(i=0;i<n1;i++)
            cap[0][i+1]=cap[n1+i+1][t]=1;
        for(i=0;i<n1;i++)
            for(j=0;j<n2;j++)
            {
                cost[i+1][n1+j+1]=dis(s1[i],s2[j]);
                cost[n1+j+1][i+1]=-cost[i+1][n1+j+1];
                cap[i+1][n1+j+1]=1;
            }
        n=t+1;
        printf("%d\n",flow(2000,1));
    }
}
