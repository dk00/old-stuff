#include<cstdio>
int s[102][102][102];
int lcs(char a[],char b[],char c[])
{
    int i,j,k;
    for(i=1;a[i];i++)
        for(j=1;b[j];j++)
            for(k=1;c[k];k++)
                if(a[i]==b[j] && b[j]==c[k])
                    s[i][j][k]=s[i-1][j-1][k-1]+1;
                else s[i][j][k]=s[i-1][j][k]>?s[i][j-1][k]>?s[i][j][k-1]>?
                s[i-1][j-1][k]>?s[i-1][j][k-1]>?s[i][j-1][k-1];
    return s[i-1][j-1][k-1];
}
char x[20][200];
main()
{
    int i,j,k,n,max;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            scanf("%s",x[i]+1);
        for(i=max=0;i<n;i++)
            for(j=i+1;j<n;j++)
                for(k=j+1;k<n;k++)
                    max>?=lcs(x[i],x[j],x[k]);
        printf("%d\n",max);
    }
}
