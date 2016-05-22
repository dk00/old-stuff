#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    puts("10");
    int i,t;
    for(t=0;t<10;t++)
    {
        printf("1 ");
        for(i=0;i<10;i++)
            printf("%c",'a'+rand()%2);
        puts("");
    }
}
