#include<cstdio>
#include<algorithm>
int s[20001];
main()
{
    int i,n,sum,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        std::sort(s,s+n);
        for(i=n-3,sum=0;i>=0;i-=3)
            sum+=s[i];
        printf("%d\n",sum);
    }
}
