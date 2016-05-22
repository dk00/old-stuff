#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,t;
    srand(time(NULL));
    for(t=0;t<10;t++)
    {
        puts("5");
        for(int i=0;i<5;i++)
            printf("%d ",270+rand()%30+1);
        puts("");
    }
    puts("0");
}
