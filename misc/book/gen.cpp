#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int i;
    for(i=0;i<150;i++)
        putchar('0'+rand()%10);
    puts("");
    for(i=0;i<150;i++)
        putchar('0'+rand()%10);
}
