#include<cstdio>
main()
{
    long long k;
    while(scanf("%lld",&k) && k)
        if(k%9)
            printf("%lld\n",k/9*10+k%9);
        else
            printf("%lld %lld\n",k/9*10-1,k/9*10);
}
