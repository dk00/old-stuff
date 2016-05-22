#include<cstdio>
int abs(int n){return n<0?-n:n;}
int n,v[2007],s[2007],u[2007];
bool go(int d)
{
    int i;
    if(d==0)
    {
        for(i=1;i<=n;i++)
            v[i]=0;
        for(i=1;i<=n;i++)
            if(v[abs(s[i]-s[i%n+1])]++)return 0;
        for(i=n;i>=1;i--)
            printf("%d ",s[i]);
        return 1;
    }
    for(i=1;i<=n+1;i++)
        if(u[i])
        {
            u[i]--;
            s[d]=i;
            if(go(d-1))
                return 1;
            u[i]++;
        }
    return 0;
}
main()
{
    int i;
    while(scanf("%d",&n) && n)
    {
        for(i=1;i<=n+1;i++)
            u[i]=1;
        s[n]=1,s[n-1]=n+1;
        u[1]=u[n+1]=0;
        go(n-2);
        puts("");
    }
}
