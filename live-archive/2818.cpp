#include<cstdio>
const int inf=200000000;
char u[99];
int n,c[99][99];
void go(int a,int b)
{
    u[a]=1;
    if(a==b)return;
    for(int i=0;i<n;i++)
        if(c[i][a]==1 && c[i][b]==c[a][b]-1)
            go(i,b);
}
main()
{
    int i,j,k,m;
    char tmp[3],s[99];
    scanf("%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=inf;
    for(i=0;i<n;i++)
    {
        c[i][i]=0;
        while(scanf("%d%c",&j,tmp) && tmp[0]!='\n')
            c[i][j-1]=c[j-1][i]=1;
        c[i][j-1]=c[j-1][i]=1;
    }
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]<?=c[i][k]+c[k][j];
    scanf("%d",&m);
    while(m--)
    {
        for(i=0;i<n;i++)u[i]=0;
        for(k=0;scanf("%d%c",s+k,tmp) && tmp[0]!='\n';k++);
        for(i=0;i<=k;i++)
            for(j=0;j<i;j++)
                go(s[i]-1,s[j]-1);
        for(i=0;u[i] && i<n;i++);
        if(i<n)puts("no");
        else puts("yes");
    }
}
