#include<cstdio>
const int inf=2000000000;
int map[80][80],s1[7][80][80],s2[7][80][80];
main()
{
    int i,j,k,l,n,m,C=1;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
            {
                scanf("%d",&map[i][j]);
                for(k=0;k<=m;k++)
                    s1[k][i][j]=s2[k][i][j]=-inf;
            }
        l=(map[0][0]<0);
        s1[l][0][0]=s2[l][0][0]=map[0][0];
        for(k=0;k<=m;k++)
            for(i=0;i<n;i++)
            {
                for(j=1;j<n;j++)
                {
                    l=k-(map[i][j]<0);
                    if(l>=0 && s1[l][i][j-1]>-inf)
                        s1[k][i][j]>?=(map[i][j]+s1[l][i][j-1]);
                }
                for(j=n-2;j>=0;j--)
                {
                    l=k-(map[i][j]<0);
                    if(l>=0 && s2[l][i][j+1]>-inf)
                        s2[k][i][j]>?=(map[i][j]+s2[l][i][j+1]);
                }
                for(j=0;j<n;j++)
                {
                    l=k+(map[i+1][j]<0);
                    if((s1[k][i][j]>?s2[k][i][j])<=-inf)
                        continue;
                    s1[l][i+1][j]>?=(s1[k][i][j]>?s2[k][i][j])
                                    +map[i+1][j];
                    s2[l][i+1][j]=s1[l][i+1][j];
                }
            }
        for(k=0,j=s1[k][n-1][n-1];k<=m;k++)
            j>?=(s1[k][n-1][n-1]>?s2[k][n-1][n-1]);
        printf("Case %d: ",C++);
        if(j>-inf)
            printf("%d\n",j);
        else puts("impossible");
    }
}
