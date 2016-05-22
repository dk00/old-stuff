#include<cstdio>
const int inf=2147483647;
long long b[505],t[505],s[505][505],p[505][505];
long long max(long long a,long long b){return a>?b;}
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(j=1;j<=n;j++)scanf("%lld",&b[j]);
        for(j=1;j<=n;j++)
            t[j]=0,s[1][j]=s[1][j-1]+b[j];
        for(i=2;i<=m;i++)
            for(j=i,k=i-1;j<=n;j++)
            {
                p[i][j]=k,s[i][j]=max(s[i-1][k],s[1][j]-s[1][k]);
                while(k+1<j && max(s[i-1][k+1],s[1][j]-s[1][k+1])<s[i][j])
                    p[i][j]=++k,s[i][j]=max(s[i-1][k],s[1][j]-s[1][k]);
            }
        for(i=m,j=n;i>0;j=p[i--][j])t[j]=1;
        for(j=1;j<n;j++)
        {
            printf("%lld ",b[j]);
            if(t[j])printf("/ ");
        }
        printf("%lld\n",b[n]);
    }
}
