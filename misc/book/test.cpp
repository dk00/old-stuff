#include"bigint2.h"
char a[300000],b[300000];
bigint x;
main()
{
    while(scanf("%s %s",a,b)==2)
    {
        x=a;
        x*=b;
        puts(x.tostr());
    }
}
