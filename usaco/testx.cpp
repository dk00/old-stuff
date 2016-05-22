#include<cstdio>
#include<cstdlib>
main()
{
    freopen("telewire.in","w",stdout);
    puts("10000 100");
    for(int i=0;i<10000;i++)
        printf("%d\n",rand()%100);
}
