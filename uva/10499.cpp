#include<cstdio>
main()
{
    int n;
    while(scanf("%d",&n) && n>0)
        if(n==1)puts("0%");
        else printf("%lld%%\n",n*25ll);
}
