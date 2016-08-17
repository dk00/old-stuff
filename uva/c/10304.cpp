#include<cstdio>
int f[300],t[300],s[300][300],p[300][300];
main()
{
    int i,j,k,c,n;
    while(scanf("%d",&n)==1)
    {
        for(i=1;i<=n;i++)
        {
            for(j=i+1;j<=n;j++)
                s[i][j]=-1;
            scanf("%d",&f[i]);
            t[i]=t[i-1]+f[i];
            p[i][i]=i;
        }
        for(j=1;j<n;j++)
            for(i=1;i+j<=n;i++)
                for(k=p[i][i+j-1];k<=p[i+1][i+j];k++)
                {
                    c=s[i][k-1]+s[k+1][i+j]+t[i+j]-t[i-1]-f[k];
                    if(s[i][i+j]<0 || c<s[i][i+j])
                        s[i][i+j]=c,p[i][i+j]=k;
                }
        printf("%d\n",s[1][n]);
    }
}
