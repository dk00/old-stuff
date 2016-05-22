#include<cstdio>
const int N=1001;
int n,t,p[N],c[N][N];
int go(int v)
{
    if(v==t)return 1;
    if(p[v])return 0;
    p[v]=1;
    for(int i=0;i<=t;i++)
        if(c[v][i]-- && go(i))
            return ++c[i][v];
        else c[v][i]++;
    return 0;
}
int flow()
{
    int i,f=-1;
    do for(i=0,f++;i<=t;i++)p[i]=0;
    while(go(0));
    return f;
}
main()
{
    int i,j,m;
    while(scanf("%d %d",&n,&m)>0)
    {
        t=n*2+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        for(i=0;i<n;i++)
            c[0][i+1]=c[i+n+1][t]=1;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][j+n]=1;
        }
        printf("%d\n",flow());
    }
}
