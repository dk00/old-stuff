#include<cstdio>
long long s[10001];
main()
{
    freopen("money.in","r",stdin);
    freopen("money.out","w",stdout);
    int i,j,n,m;
    s[0]=1;
    scanf("%d %d",&n,&m);
    while(n--)
    {
        scanf("%d",&j);
        for(i=0;i+j<=m;i++)
            s[i+j]+=s[i];
    }
    printf("%lld\n",s[m]);
}
/*
PROB:money
LANG:C++
*/
