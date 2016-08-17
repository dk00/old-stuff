#include<cstdio>
long long p1[20],p2[20];
long long zero(long long n)
{
    if(n<0)return 0;
    if(n==0)return 1;
    if(n%10)return zero(n-n%10);
    int r;
    long long k;
    for(k=10,r=1;k*10<n && n%(k*10)==0;k*=10,r++);
    if(k*10==n)return p2[r+1];
    if((n/k)%10==1)
        return p1[r]+zero(n-k);
    return p1[r]+zero(n-k);
}
main()
{
    long long i,j;
    p2[0]=1;
    for(i=j=1;i<12;i++,j*=10)
    {
        p1[i]=p1[i-1]*10+j;
        p2[i]=p2[i-1]+j/10*(i-1)*9+1;
    }
    while(scanf("%I64d %I64d",&i,&j)==2)
        printf("%I64d\n",zero(j)-zero(i-1));
}
