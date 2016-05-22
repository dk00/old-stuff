#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,t;
    srand(time(NULL));
    for(t=0;t<10;t++)
    {
        printf("%d ",1+rand()%10);
        for(i=0;i<20;i++)
            putchar(rand()%3+'a');
        puts("");
    }
}
