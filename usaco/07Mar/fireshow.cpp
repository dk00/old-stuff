/*
PROG: fireshow
LANG: C++
ID: s0000151
*/
#include<cstdio>
#include<algorithm>
char s[2000001];
main()
{
    freopen("fireshow.in","r",stdin);
    freopen("fireshow.out","w",stdout);
    int i,j,n,m,c[300];
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%d",&c[i]);
    std::sort(s,s+n);
    for(i=0;i<n;i++)
    {
        if(i && c[i]==c[i-1])continue;
        for(j=c[i];j<=m;j+=c[i])s[j]=1;
    }
    for(i=1,j=0;i<=m;i++)j+=s[i];
    printf("%d\n",j);
    scanf(" ");
}
