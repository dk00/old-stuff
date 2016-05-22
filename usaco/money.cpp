/*
PROB: money
LANG: C++
*/
#include<cstdio>
long long s[10001];
main()
{
    int i,j,n,m;
    freopen("money.in","r",stdin);
    freopen("money.out","w",stdout);
    while(scanf("%d %d",&m,&n)==2)
    {
        s[0]=1;
        while(m--)
        {
            scanf("%d",&j);
            for(i=0;i+j<=n;i++)
                s[i+j]+=s[i];
        }
        printf("%lld\n",s[n]);
    }
}
