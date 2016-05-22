/*
PROB:numtri
LANG:C++
*/
#include<cstdio>
int s[1001][1001];
main()
{
    freopen("numtri.in","r",stdin);
    freopen("numtri.out","w",stdout);
    int i,j,n;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=i;j++)
        {
            scanf("%d",&s[i][j]);
            s[i][j]+=(s[i-1][j-1]>?s[i-1][j]);
        }
    for(i=0,j=1;j<=n;j++)i>?=s[n][j];
    printf("%d\n",i);
    scanf(" ");
}
