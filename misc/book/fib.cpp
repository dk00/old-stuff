#include"bigint2.h"
bigint a,b,c;
main()
{
    int i,n;
    while(scanf("%d",&n) && n)
    {
        a=1,b=2;
        if(n>=1)
            printf(" 1");
        if(n>=2)
            printf(" 2");
        for(i=2;i<n;i++)
        {
            c=b;
            c+=a;
            printf(" %s",c.tostr());
            if(i%10==9)puts("\n");
            a=b,b=c;
        }
        if(i%10)puts("");
    }
}
