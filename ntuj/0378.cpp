#include<cstdio>
const int V=999;
char c[V][V],p[V];
int t;
char go(int v)
{
    if(v==t)return 1;
    if(p[v])return 0;
    p[v]=1;
    for(int i=1;i<=t;i++)
        if(c[v][i]-- && go(i))
            return ++c[i][v];
        else c[v][i]++;
    return 0;
}
int flow()
{
    int i,f=0;
    while(1)
    {
        for(i=0;i<=t;i++)
            p[i]=0;
        if(go(0))f++;
        else break;
    }
    return f;
}
main()
{
    int i,j,k,n;
    while(scanf("%d %d %d",&n,&j,&k) && n)
    {
        t=n+j+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        while(k--)
        {
            scanf("%d",&i);
            scanf("%d %d",&i,&j);
            if(i && j)
                c[i][j+n]=1;
        }
        for(i=1;i<=n;i++)
            c[0][i]=1;
        for(;i<t;i++)
            c[i][t]=1;
        printf("%d\n",flow());
    }
}
