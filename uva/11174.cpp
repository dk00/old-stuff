#include<cstdio>
const int D=1000000007;
struct pt
{
    int a,b;
}s[50000];
int p[50000],q[50000],c[50000];
int C(int n,int k)
{
    return f[n]/f[k]/f[n-k];
}
int count(int v)
{
    int i;
    for(i=p[v],q[v]=1;i<p[v+1];i++)
        q[v]+=count(c[i]);
    return q[v];
}
int go(int v)
{

}
main()
{
    int i,j,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=1;i<=n+1;i++)
            p[i]=q[i]=0,c[i-1]=i;
        p[1]=n;
        for(i=0;i<m;i++)
        {
            scanf("%d %d",&s[i].a,&s[i].b);
            p[s[i].a+1]++;
        }
        for(i=1;i<=n+1;i++)
            p[i]+=p[i-1];
        for(i=0;i<m;i++)
            c[p[s[i].a]+q[s[i].a]++]=s[i].b;
        count(0);
        printf("%d\n",go(0));
    }
}
