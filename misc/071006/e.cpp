#include<cstdio>
short p[101][101][101];
int lcs(char a[],char b[],char c[])
{
    int i,j,k;
    for(i=1;a[i];i++)
        for(j=1;b[j];j++)
            for(k=1;c[k];k++)
            {
                if(a[i]==b[j] && b[j]==c[k])
                    p[i][j][k]=p[i-1][j-1][k-1]+1;
                else
                    p[i][j][k]=p[i-1][j][k]>?p[i][j-1][k]>?p[i][j][k-1]>?
                    p[i-1][j-1][k]>?p[i-1][j][k-1]>?p[i][j-1][k-1];
            }
    return p[i-1][j-1][k-1];
}
char s[15][102];
main()
{
    int i,j,k,n,max;
    while(scanf("%d",&n)==1)
    {
    for(i=0;i<n;i++)
        scanf("%s",s[i]+1);
    for(i=max=0;i<n;i++)
        for(j=i+1;j<n;j++)
            for(k=j+1;k<n;k++)
                max>?=lcs(s[i],s[j],s[k]);
    printf("%d\n",max);
    }
}
