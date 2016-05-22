#include<cstdio>
struct mx
{
    long long p,q,r,s;
    mx operator*(mx a)
    {
        return (mx){p*a.p+q*a.r,p*a.q+q*a.s,r*a.p+s*a.r,r*a.q+s*a.s};
    }
    mx operator*=(mx a){*this=*this*a;}
};
long long calc(int n)
{
    int i;
    mx s,r;
    s=(mx){0,1,1,2};
    for(i=1;!(n&i);i<<=1,s*=s);
    r=s*s;
    for(i<<=1;i<=n;i<<=1,r*=r)
        if(n&i)
            s*=r;
    return s.s;
}
main()
{
    int n;
    while(scanf("%d",&n) && n)
    {
        
    }
}
