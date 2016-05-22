#include<cstdio>
long long s[1000001];
main()
{
    int i;
    long long j;
    for(i=4,j=0;i<=1000000;i++)
    {
        j+=(i-3);
        s[i]=s[i-1]+j;
        j-=(i-2)/2;
    }
    while(scanf("%d",&i) && i>=3)
        printf("%lld\n",s[i]);
}
