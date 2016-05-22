#include<cstdio>
#include<algorithm>
main()
{
    int i,j,n,s[100];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        std::sort(s,s+n);
        printf("%d\n",s[n-2]+s[n-1]-2*s[n-3]);
    }
}
