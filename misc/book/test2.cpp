int pow(long long n,int k,int m)
{
    if(k==0)return 1;
    if(k%2)return pow(n,k-1,m)*n%m;
    n=pow(n,k/2,m);
    return n*n%m;
}
#include<cstdio>
const long long p=1107296257;
main()
{
    int r;
    for(r=10;r!=1;r=(1ll*r*r)%p)
    {
        if(pow(r,p/2,p)!=1 && pow(r,p/3,p)!=1 && pow(r,p/11,p)!=1)
        {
            printf("%d",r);
            getchar();
        }
    }
}
