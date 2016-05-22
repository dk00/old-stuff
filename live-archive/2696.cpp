#include<cstdio>
int t;
char c[250][250],u[250];
char go(int v)
{
    if(v==t)return 1;
    if(u[v])return 0;
    u[v]=1;
    for(int i=0;i<=t;i++)
        if(c[v][i])
        {
            c[v][i]--;
            if(go(i))
            {
                c[i][v]++;
                return 1;
            }
            c[v][i]++;
        }
    return 0;
}
int flow()
{
    int sum=0;
    while(1)
    {
        for(int i=0;i<=t;i++)u[i]=0;
        if(!go(0))break;
        sum++;
    }
    return sum;
}
main()
{
    int i,j,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        t=n*2+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][n+j]=1;
        }
        for(i=1;i<=n;i++)
            c[0][i]=c[n+i][t]=1;
        printf("%d\n",n-flow());
    }
}
