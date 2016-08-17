#include<cstdio>
int c[50][50];
void go(int u,int v)
{
    for(int i=0;i<50;i++)
        while(c[v][i])
        {
            c[v][i]--,c[i][v]--;
            go(v,i);
        }
    if(u>=0)printf("%d %d\n",v+1,u+1);
}
int d[50],u[50];
int go(int v)
{
    if(u[v])return 0;
    for(int i=0;i<50;i++)
        if(c[v][i])u[v]+=go(i);
    return ++u[v];
}
main()
{
    int i,j,n,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<50;i++)
            for(j=d[i]=u[i]=0;j<50;j++)
                c[i][j]=0;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d %d",&i,&j);
            d[--i]++,d[--j]++;
            c[i][j]++,c[j][i]++;
        }
        for(i=j=0;i<50;i++)if(d[i])j++;
        if(C>1)puts("");
        printf("Case #%d\n",C++);
        for(n=0;!d[n];n++);
        for(i=j=0;d[i]%2==0 && i<50;i++);
        if(i<50 || go(n)!=j)
        {
            puts("some beads may be lost");
            continue;
        }
        for(i=0;!d[i];i++);
        go(-1,i);
    }
}
