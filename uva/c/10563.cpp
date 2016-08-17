#include<cstdio>
char map[101][101];
int s1[101][101],s2[101][101];
main()
{
    int i,j,n,m,first=1;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(i=1;i<=n;i++)
        {
            scanf("%s",map[i]);
            for(j=1;j<=m;j++)
                s1[i][j]=s2[i][j]=(map[i][j]=='?');
        }
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                s2[i][j]+=s2[i][j-1];
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                s2[i][j]+=s2[i-1][j];
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                if(s1[i][j])
                {
                    for(k=1;i+k<n && j+k<m;k++)
                        if(s2[i-1][j-1]+s2[i+k][j+k]
                        -s2[i-1][j+k]-s2[i+k][j-1]<(k+1)*(k+1))
                            break;
                    for(l=0;l*l<k;l++)
                        map[
                }
        if(first)first=0;
        else puts("");
        for(i=1;i<=n;i++)
            puts(map[i]);
    }
}
