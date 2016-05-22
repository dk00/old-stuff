#include<cstdio>
char p[1005],c[1005][1005];
int t;
int node,phase;
char go(int v)
{
    ++node;
    if(p[v])return 0;
    if(v==t)return 1;
    p[v]=1;
    for(int i=1;i<=t;i++)
        if(c[v][i]-- && go(i))
            return ++c[i][v];
        else c[v][i]++;
    return 0;
}
int go()
{
    int i,j=0;
    while(++phase,go(0))
        for(j++,i=0;i<=t;i++)p[i]=0;
    return j;
}
main()
{
    int i,j,n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        node=phase=0;
        scanf("%d %d",&n,&m);
        t=n+m+1;
        for(i=0;i<=t;i++)
            for(j=p[i]=0;j<=t;j++)
                c[i][j]=0;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                scanf("%d",&c[i+1][n+j+1]);
        for(i=1;i<=n;i++)c[0][i]=1;
        for(j=1;j<=m;j++)c[n+j][t]=1;
        printf("Case %d: a maximum of %d nuts and bolts can be fitted together\n",
        C++,go());
        printf("%d/%d\n",phase,node);
    }
}
