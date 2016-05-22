#include<cstdio>
main()
{
    int i,n,C=1;
    long long a,b,c,d,max;
    while(scanf("%d",&n)==1)
    {
        a=b=1,max=0;
        while(n--)
        {
            scanf("%d",&i);
            c=a*i;
            d=b*i;
            max>?=(a=(c>?d))>?(b=(c<?d));
            if(a<=0)a=1;
            if(b>=0)b=1;
        }
        printf("Case #%d: The maximum product is %lld.\n\n",C++,max);
    }
}
