#include<cstdio>
const int M=1000000007;
int pow(long long n,int k)
{
    if(!k)return 1;
    if(k%2)return pow(n,k-1)*n%M;
    n=pow(n,k/2);
    return n*n%M;
}
main()
{
    int n,T,C=1;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        printf("Case #%d: %lld\n",C++,pow(2,n-1)*1ll*n%M);
    }
}
