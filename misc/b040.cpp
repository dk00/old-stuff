#include<cstdio>
#include<cstdlib>
const int V=2008,inf=2020;
int t,p[V],d[V],u[V],q[V],num[V];
char c0[V][V];
short e[720000],*c[V];
inline int sp()
{
    int i,j,k;
    for(i=0;i<=t;i++)
        d[i]=inf;
    q[0]=d[0]=0;
    for(i=0,j=1;d[t]>=inf && i<j;i++)
        for(k=0;k<num[q[i]];k++)
            if(c0[q[i]][c[q[i]][k]] && d[c[q[i]][k]]>=inf)
                d[q[j++]=c[q[i]][k]]=d[q[i]]+1;
    return d[t];
}
inline int go(int v)
{
    if(v==t)return 1;
    int sum=0;
    for(;u[v]<num[v];u[v]++)
        if(d[v]+1==d[c[v][u[v]]])
        {
            if(c0[v][c[v][u[v]]]-- && go(c[v][u[v]]))
            {
                c0[c[v][u[v]]][v]++;
                if(v)return 1;
                sum++;
            }
            else c0[v][c[v][u[v]]]++;
        }
    return sum;
}
inline int flow()
{
    int i,sum=0;
    while(sp()<inf)
    {
        for(i=0;i<=t;i++)u[i]=0;
        sum+=go(0);
    }
    return sum;
}
int x[V],y[V],z[V];
main()
{
    int i,j,n,dis,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        t=n*2+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c0[i][j]=0;
        c[0]=e;
        for(i=0;i<n;i++)
        {
            c0[0][i+1]=c0[n+i+1][t]=1;
            c[0][num[0]++]=i+1;
            scanf("%d %d %d",z+i,x+i,y+i);
        }
        int sum;
        for(i=sum=0;i<n;i++)
        {
            c[i+1]=c[i]+num[i];
            num[i+1]=0;
            for(j=0;j<n;j++)
            {
                dis=abs(x[i]-x[j])+abs(y[i]-y[j]);
                if(i!=j && dis<=z[j]-z[i])
                    sum++,c[i+1][num[i+1]++]=n+j+1,c0[i+1][n+j+1]=1;
            }
        }
        for(i=0;i<n;i++)
        {
            int u=n+i+1;
            c[u]=c[n+i]+num[n+i];
            num[u]=0;
            c[u][num[u]++]=t;
            c0[u][t]=1;
            for(j=0;j<n;j++)
            {
                dis=abs(x[i]-x[j])+abs(y[i]-y[j]);
                if(i!=j && dis<=z[i]-z[j])
                    c[u][num[u]++]=j+1;
            }
        }
        printf("%d\n",n-flow());
    }
}
