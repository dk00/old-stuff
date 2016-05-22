#include<cstdio>
long long s[21][21][21];
inline long long sum(long long s[21][21],int i,int j,int k,int l)
{
    return s[k][l]-s[i-1][l]-s[k][j-1]+s[i-1][j-1];
}
main()
{
    long long h,i,j,k,l,n,m,o,p,q,r,T;
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld %lld %lld",&n,&m,&o);
        h=-2147483649ll;
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                for(k=1;k<=o;k++)
                {
                    scanf("%lld",&s[i][j][k]);
                    s[i][j][k]+=s[i][j][k-1];
                }
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                for(k=1;k<=o;k++)
                    s[i][j][k]+=s[i][j-1][k];
        for(j=1;j<=m;j++)
            for(p=j;p<=m;p++)
                for(k=1;k<=o;k++)
                    for(q=k;q<=o;q++)
                        for(i=1,r=0;i<=n;i++)
                        {
                            r+=sum(s[i],j,k,p,q);
                            h>?=r;
                            if(r<0)r=0;
                        }
        printf("%lld\n",h);
        if(T)puts("");
    }
}
