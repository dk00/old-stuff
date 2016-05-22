#include"bigint1.h"
#include<ctime>
#define P3
main()
{
    int i,n,start;
    bigint a,b;
    while(scanf("%d",&n)==1)
    {
        #ifdef P1
        start=clock();
        for(a=1,i=0;i<n;i++)
            a*=2;
        start=clock()-start;
//      puts(a.tostr());
        printf("%d.%03d\n",start/1000,start%1000);
        #endif
        #ifdef P2
        start=clock();
        for(a=1,i=0;i<n;i++)
            a+=2147483647;
        start=clock()-start;
//        puts(a.tostr());
        printf("%d.%03d\n",start/1000,start%1000);
        #endif
        #ifdef P3
        start=clock();
        a=2;
        for(i=0;i<n;i++)
        {
            b=a;
            a*=b;
        }
        puts(a.tostr());
        start=clock()-start;
        printf("%d.%03d\n",start/1000,start%1000);
        #endif
        #ifdef P4
//        start=clock();
        a=1;
        for(i=0;i<n;i++)
        {
            b=a;
            a+=a;
        }
//        puts(a.tostr());
        start=clock()-start;
        printf("%d.%03d\n",start/1000,start%1000);
        #endif
    }
}
