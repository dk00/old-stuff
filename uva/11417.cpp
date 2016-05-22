#include<cstdio>
const int N=2000000;
int ph[N+1];
long long s[N+1];
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
main()
{
    int i,j,k;
    for(i=1;i<=N;i++)
        ph[i]=i;
    for(i=1;i<=N;i++)
        for(j=i*2,k=ph[i];j<=N;j+=i)
        {
            ph[j]-=ph[i];
            s[j]+=k;
            k+=ph[i];
        }
    for(i=1;i<=N;i++)
        s[i]+=s[i-1];
    while(scanf("%d",&i) && i)
        printf("%lld\n",s[i]);
}
