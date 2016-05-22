#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,j;
    srand(time(NULL));
    puts("1");
    for(i=0;i<1;i++)
    {
        puts("20");
        for(j=0;j<20;j++)
            printf("%d %d\n",rand()%100,rand()%100);
    }
}
