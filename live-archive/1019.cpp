#include<cstdio>
long long abs(long long a){return a<0?-a:a;}
int d[1001];
long long s[1001];
main()
{
    int i,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d",d+i);
        s[0]=0;
        s[1]=abs(1ll*d[0]-d[1]);
        for(i=2;i<n;i++)
            s[i]=(s[i-1]+abs(1ll*d[i]-d[i-1]))<?
            (s[i-2]+abs(1ll*d[i]-d[i-2]));
        printf("%I64d\n",s[n-1]);
    }
}
