#include<cmath>
#include<cstdio>
main()
{
    int i,n,T,s[21];
    long long j,k,d,sum;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<=n;i++)
            scanf("%d",&s[i]);
        scanf("%lld %lld",&d,&k);
        k=ceil((sqrt(d*d+8*d*k)-d)/2/d);
        for(sum=d=i=0,j=1;i<=n;i++,j*=k)
            sum+=j*s[i];
        printf("%lld\n",sum);
    }
}
