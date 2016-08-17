#include<cstdio>
int pow(long long n,int k,int m)
{
    if(!k)return 1;
    if(k%2)return n*pow(n,k-1,m)%m;
    n=pow(n,k/2,m);
    return n*n%m;
}
main()
{
    int n;
    while(scanf("%d",&n) && n>=0)
    {
        printf("%d ",n);
        if(pow(2,n-1,n)==1)
            puts("is a Jimmy-number");
        else
            puts("is not a Jimmy-number");
    }
}
