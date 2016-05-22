#include<cstdio>
long long s[101][64];
main()
{
    int i,j,n;
    long long k;
    for(i=1;i<=100;i++)
        for(j=1;j<64;j++)
            s[i][j]=s[i-1][j-1]+s[i][j-1]+1;
    while(scanf("%d %lld",&n,&k) && n)
    {
        for(i=1;i<=63;i++)
            if(s[n<?i][i]>=k)
                break;
        if(i>63)
            puts("More than 63 trials needed.");
        else
            printf("%d\n",i);
    }
}
