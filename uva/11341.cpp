#include<cstdio>
const int inf=1000;
int s[13][101];
main()
{
    int i,j,k,a,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<=n;i++)
            for(j=0;j<=m;j++)
                s[i][j]=-inf;
        s[0][0]=0;
        for(i=0;i<n;i++)
            for(j=1;j<=m;j++)
            {
                scanf("%d",&a);
                if(a<5)continue;
                for(k=0;k+j<=m;k++)
                    s[i+1][k+j]>?=s[i][k]+a;
            }
        if(s[n][m]>0)
            printf("Maximal possible average mark - %.2lf.\n",s[n][m]/1.0/n+1e-9);
        else
            puts("Peter, you shouldn't have played billiard that much.");
    }
}
