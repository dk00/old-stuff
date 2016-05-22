#include<cstdio>
#include<algorithm>
int s[10000];
main()
{
    freopen("in_2.txt","r",stdin);
    int i,n;
    long long sum;
    s[0]=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&s[i]);
    std::sort(s,s+n+1);
    for(sum=i=0;i<n;i++)
        sum+=(s[i]-s[i+1])*(s[i]-s[i+1]);
    printf("%I64d\n",sum);
}
