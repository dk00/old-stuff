#include<cstdio>
const int m=2000000011;
long long pow(long long n,int k)
{
    if(k<=0)return 1;
    if(k%2)return(n*pow(n*n%m,k/2))%m;
    return pow(n*n%m,k/2);
}
main()
{
    int n,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("Case #%d: %lld\n",C++,pow(n,n-2));
    }
}
