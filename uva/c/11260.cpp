#include<cmath>
#include<cstdio>
const int M=100000000;
main()
{
    int i;
    long long a,b,c,k,n,m,sum;
    while(scanf("%lld",&n) && n)
    {
        m=floor(sqrt(n));
        sum=((n/2+n%2)%M*m)%M;
        k=m/2;
        a=k,b=k+1,c=2*k+1;
        if(k%3==0)a/=3;
        else if(k%3==2)b/=3;
        else c/=3;
        (sum+=M-((a*b)%M*c)%M)%=M;
        k=m-k-1;
        a=k,b=k+1,c=2*k+4;
        if(k%3==0)a/=3;
        else if(k%3==2)b/=3;
        else c/=3;
        (sum+=M-((a*b)%M*c)%M)%=M;
        printf("%lld\n",sum);
    }
}
