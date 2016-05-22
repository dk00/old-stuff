#include<cstdio>
int s[5000][5000];
main()
{
    freopen("pf.in","r",stdin);
    freopen("pf.out","w",stdout);
    int i,j,n,m,max;
    while(scanf("%d %d",&n,&m)==2 && n+m)
    {
        for(i=max=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                scanf("%d",&s[i][j]);
                if(s[i][j]==2)s[i][j]=0;
                else max=s[i][j]=1;
            }
        for(i=1;i<n;i++)
            for(j=1;j<m;j++)
                if(s[i][j])
                    max>?=(s[i][j]=((s[i-1][j]<?s[i][j-1])<?s[i-1][j-1])+1);
        printf("%d\n",max*max);
    }
}
