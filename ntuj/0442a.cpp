#include<cstdio>
main()
{
    int n;
    while(scanf("%d %*d",&n)>0)
    {
        while(n--)if(scanf("%*d")==EOF)break;
    }
    if(n)n/=0;
}
