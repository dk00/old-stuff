#include<cstdio>
long long s[40];
main()
{
    freopen("subset.in","r",stdin);
    freopen("subset.out","w",stdout);
    int i,j,n;
    scanf("%d",&n);
    if(n*(n+1)/2%2)
    {
        puts("0");
        return 0;
    }
    s[0]=1;
    for(i=1;i<=n;i++)
        for(j=n*(n+1)/4;j>=i;j--)
            s[j]+=s[j-i];
    printf("%lld\n",s[n*(n+1)/4]/2);
}
/*
PROB:subset
LANG:C++
*/
