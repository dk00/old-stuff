#include<cstdio>
long long s[51][51];
main()
{
    int i,j,k,n,l,m;
    s[0][0]=1;
    while(scanf("%d %d %d",&n,&l,&m)!=EOF)
    {
        for(i=1;i<=l;i++)
            for(j=0;j<=n;j++)
                s[i][j]=0;
        for(i=0;i<l;i++)
            for(j=1;j<=m;j++)
                for(k=0;j+k<=n;k++)
                    s[i+1][k+j]+=s[i][k];
        printf("%lld\n",s[l][n]);
    }
}
