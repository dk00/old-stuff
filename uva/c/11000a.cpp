#include<cstdio>
long long a[46],b[46],max=1ll<<32;
main()
{
    int i;
    a[0]=0;a[1]=1;
    b[0]=1;b[1]=1;
    for(i=2;i<46;i++)
    {
        a[i]=a[i-2]+a[i-1]+1;
        b[i]=b[i-2]+b[i-1];
    }
    while(scanf("%d",&i) && i>=0)
        printf("%lld %lld\n",a[i],a[i]+b[i]);
}
