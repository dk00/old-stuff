#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,t;
    srand(time(NULL));
    puts("7");
    for(t=0;t<7;t++)
    {
        puts("10");
        for(i=0;i<10;i++)
            printf("%d ",rand()%10);
        puts("");
    }
}
