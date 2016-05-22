#include<cstdio>
int a[1001],b[1001],t[1001],s[1001][1001];
main()
{
    int i,j,k,n;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        t[i]=t[i-1]+a[i];
        s[i][0]=-t[i]*t[i];
    }
    for(i=1;i<=n;i++)
        scanf("%d",b+i);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            for(k=0;k<i;k++)
                s[i][j]>?=s[k][j-1]-(t[i-1]-t[k])*(t[i-1]-t[k])+a[i]*b[j];
            s[i][j]>?=s[i][j-1];
        }
    for(i=0;i<=n;i++)
    {
        for(j=0;j<=n;j++)
            printf("%d ",s[i][j]);
        puts("");
    }
    scanf(" ");
}
