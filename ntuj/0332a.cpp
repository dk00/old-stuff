#include<cstdio>
long long s[1000001];
main()
{
    int i,j,a,b,c;
    while(scanf("%d %d",&a,&b)==2)
    {
        c=a<?b;
        for(i=c;i>0;i--)
        {
            s[i]=1ll*a/i*(b/i);
            for(j=i*2;j<=c;j+=i)
                s[i]-=s[j];
        }
        printf("%lld\n",s[1]);
    }
}
