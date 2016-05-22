#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,t;
    srand(time(NULL));
    for(t=0;t<100;t++)
    {
        puts("10000");
        for(i=0;i<10000;i++)
            printf("%d ",rand()%10000);
        puts("");
    }
    puts("0");
}
