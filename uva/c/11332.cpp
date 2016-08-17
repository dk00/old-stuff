#include<cstdio>
main()
{
    int i,n;
    while(scanf("%d",&n)==1 && n)
    {
        while(n>=10)
            for(i=n,n=0;i;i/=10)
                n+=i%10;
        printf("%d\n",n);
    }
}
