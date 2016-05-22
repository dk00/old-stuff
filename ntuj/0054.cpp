#include<cstdio>
int s[101][101];
main()
{
    int i,j,k,n,max,tmp;
    while(scanf("%d",&n)>0 && n)
    {
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                scanf("%d",&s[i][j]),s[i][j]+=s[i][j-1];
        max=s[0][0];
        for(j=1;j<=n;j++)
            for(k=j+1;k<=n;k++)
                for(tmp=0,i=1;i<=n;i++)
                {
                    tmp+=s[i][k]-s[i][j-1];
                    max>?=tmp;
                    tmp>?=0;
                }
        printf("%d\n",max);
    }
}
