#include<cstdio>
char tmp[150001];
main()
{
    int i,n,T;
    long long sum,c[256];
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<256;i++)c[i]=0;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%s",tmp);
            scanf("%lld",&c[tmp[0]+128]);
        }
        scanf("%d%c",&n,tmp);
        for(sum=0;n--;)
        {
            gets(tmp);
            for(i=0;tmp[i];i++)
                sum+=c[tmp[i]+128];
        }
        printf("%lld.%02lld$\n",sum/100,sum%100);
    }
}
