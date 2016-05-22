#include<cstdio>
int s[300],t[300][300],u[300][300],v[300][300],r[32][300];
main()
{
    int i,j,k,n,m;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%d",&s[i]);
    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
        {
            if(j>i)
                v[i][j]=v[i][j-1];
            else v[i][j]=0;
            v[i][j]+=s[j]-s[i];
        }
    for(i=n-1;i>=0;i--)
        for(j=i;j>=0;j--)
        {
            if(j<i)
                u[i][j]=u[i][j+1];
            else u[i][j]=0;
            u[i][j]+=s[i]-s[j];
        }
    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
        {
            t[i][j]=u[i][i]+v[i][j];
            for(k=i;k<=j;k++)
                if(u[i][k]+v[k][j]<t[i][j])
                    t[i][j]=u[i][k]+v[k][j];
        }
    for(i=0;i<n;i++)
        r[1][i]=t[0][i];
    for(k=2;k<=m;k++)
        for(i=0;i<n;i++)
        {
            r[k][i]=2000000000;
            for(j=1;j<i;j++)
                r[k][i]<?=(r[k-1][j-1]+t[j][i]);
        }
    printf("%d\n",r[m][n-1]);
}
