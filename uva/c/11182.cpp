/*
t=n-xi
    n/x
1/2 Sum (1+t)(2+t)
    i=1
    
    n/x
1/2 Sum [(n-xi)^2 + 3(n-xi)] + n/x
    i=1
    
    n/x
1/2 Sum [n^2 + 3n - 2nxi + x^2i^2 - 3xi] + n/x
    i=1

u=n/x
     u
1/2 Sum [x^2i^2 - (2nx+3x)i] + (n^2+3n+2)u/2
    i=1

[(x^2) u(u+1)(2u+1)/6
-(2nx+3x) u(u+1)/2]/2

*/
#include"d:\a\algorithm\ita.h"
#include<algorithm>
long long m2(long long x,long long n)
{
    long long sum,u=n/x;
    sum=(n+1)*(n+2)*u/2+(x*x*u*(u+1)*(2*u+1)/6-(2*n*x+3*x)*u*(u+1)/2)/2;
    return sum;
}
long long m1(int x,int n)
{
    long long sum=0;
    int i,k;
    for(i=0,k=x;k<=n;i++,k*=x)
        sum+=m2(k,n);
    return sum;
}
main()
{
    int i,j,n,m,b,s[70];
    long long min;
    while(scanf("%d %d",&n,&b) && n+b)
    {
        m=0;
        factor(b,m,s);
        std::sort(s,s+m);
        min=1ll<<62;
        for(i=0;i<m;i=j)
        {
            for(j=i+1;j<m && s[j]==s[i];j++);
            min<?=m1(s[i],n)/(j-i);
        }
        printf("%lld\n",min);
    }
}
