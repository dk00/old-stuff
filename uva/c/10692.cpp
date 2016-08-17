#include<cstdio>
struct sint
{
    int n,m,k;
    sint(int a=0):n(a){}
    void operator*=(sint a)
    {
        n*=a.n;
        if(n>k)n=k+(n-k)%m;
    }
    bool operator==(sint a){return n==a.n;}
}s[100];
int n,m[10],u[20000];
int go(int d)
{
    if(d>=n)return 1;
    int i,j;
    sint x=s[d];
    x.n=1,x*=s[d];
    for(j=0;j<=x.k+x.m;j++)u[j]=-1;
    for(i=1;;i++)
    {
        if(u[x.n]>=0)break;
        u[x.n]=i;
        x*=s[d];
    }
    s[d+1].k=u[x.n];
    s[d+1].m=i-u[x.n];
    j=go(d+1);
    for(x.n=1;j--;x*=s[d]);
    return x.n;
}
main()
{
    int i,C=1;
    while(scanf("%d %d",&s[0].m,&n)==2)
    {
        s[0].k=0;
        for(i=0;i<n;i++)
            scanf("%d",&s[i].n);
        printf("Case #%d: %d\n",C++,go(0));
    }
}
