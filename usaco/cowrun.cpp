/*
TASK:cowrun
LANG:C++
*/
#include<cstdio>
int c[10001],s[10001];
main()
{
    freopen("cowrun.in","r",stdin);
    freopen("cowrun.out","w",stdout);
    int i,j,k,n,m;
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%d",c+i);
    for(i=0;i<n;i++)
        for(j=1,k=c[i+j];j<=m && i+j*2<=n;k+=c[i+(++j)])
            s[i+j*2]>?=s[i]+k;
    printf("%d\n",s[n]>?s[n-1]);
}
