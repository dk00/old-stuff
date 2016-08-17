#include<cstdio>
long long phi[200001];
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
main()
{
    int i,j,k;
    long long n;
    for(i=1;i<=200000;i++)phi[i]=i+1;
    for(i=1;i<=200000;i++)
        for(j=i*2;j<=200000;j+=i)
            phi[j]-=phi[i];
    for(i=2;i<=200000;i++)
        phi[i]+=phi[i-1];
    while(scanf("%lld",&n) && n)
    {
        if(n<=2)
        {
            printf("%lld/%lld\n",n-1,n/n);
            continue;
        }
        for(i=1,j=200000;i<=j;)
        {
            k=(i+j)/2;
            if((!k || phi[k-1]<n) && n<=phi[k])
                break;
            if(n>phi[k])i=k+1;
            else j=k;
        }
        n-=phi[k-1];
        for(i=1;n;i++)
            if(gcd(k,i)==1)n--;
        printf("%d/%d\n",i-1,k);
    }
}
