#include<cstdio>
int s1[1001][1001],s2[1001][1001],s3[1001][1001];
main()
{
    int i,j,k,n,m,C=1;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                s1[i][j]=s2[i][j]=s3[i][j]=0;
        for(i=0;i<n;i++)
            for(j=1;j<m;j++)
                scanf("%d",&s1[i][j]);
        for(i=1;i<n;i++)
            for(j=1;j<m;j++)
                scanf("%d",&s3[i][j]);
        for(i=1;i<n;i++)
            for(j=0;j<m;j++)
                scanf("%d",&s2[i][j]);
        for(i=0;i<n;i++)
            for(j=(i==0);j<m;j++)
            {
                k=s1[i][j]+s2[i][j]+s3[i][j];
                s1[i][j+1]<?=k;
                s2[i+1][j]<?=k;
                s3[i+1][j+1]<?=k;
            }
        printf("Case %d: Minimum = %d\n",
        C++,s1[n-1][m-1]+s2[n-1][m-1]+s3[n-1][m-1]);
    }
}
