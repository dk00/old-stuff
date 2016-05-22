#include<cstdio>
#include<algorithm>
main()
{
    int a,b;
    while(scanf("%d %d",&a,&b)==2 && a+b)
    {
        if(a>b)std::swap(a,b);
        printf("%I64d\n",1ll*a*(a+1)/2*((2*a+1)/3+b-a));
    }
}
