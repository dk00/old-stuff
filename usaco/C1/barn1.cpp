/*
PROB:barn1
LANG:C++
*/
#include<cstdio>
#include<algorithm>
main()
{
    freopen("barn1.in","r",stdin);
    freopen("barn1.out","w",stdout);
    int i,n,m,sum,s[500];
    scanf("%d %d %d",&m,&i,&n);
    for(i=0;i<n;i++)
        scanf("%d",s+i);
    std::sort(s,s+n);
    sum=s[--n]-s[0]+1;
    for(i=0;i<n;i++)
        s[i]=s[i+1]-s[i]-1;
    std::sort(s,s+n);
    for(i=0>?(n-m+1);i<n;i++)
        sum-=s[i];
    printf("%d\n",sum);
}
