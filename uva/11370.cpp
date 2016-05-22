#include<cstdio>
int sum[201][201],t[201][201],s[201],c[201][201];
int print(int s[201][201],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%2d ",s[i][j]);
        puts("");
    }
}
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        for(i=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
                sum[i][j]=sum[i][j-1]+s[j]-s[i];
            for(j=i-1;j>=0;j--)
                sum[i][j]=sum[i][j+1]+s[i]-s[j];
        }
        print(sum,n);
        for(i=0;i<n;i++)
        {
            k=i+1;
            for(j=i+2;j<n;j++)
            {
                while(s[j]-s[k]>s[k]-s[i])k++;
                c[i][j]=sum[i][j-1]-sum[i][k-1]*2+sum[j][i+1]-sum[j][k]*2;
            }
        }
        print(c,n);
        for(j=0;j<n;j++)
            t[2][j]=c[0][j];
        for(i=3;i<m;i++)
            for(j=k=0;j<n;j++)
            {
                while(k<j && t[i-1][k+1]+c[k+1][j]<t[i-1][k]+c[k][j])k++;
                t[i][j]=t[i-1][k]+c[k][j];
            }
        printf("%d\n",t[m][n-1]);
        printf("%.4lf\n",t[m][n-1]/(n-m));
    }
}
