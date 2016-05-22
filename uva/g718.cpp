#include<ctime>
#include<cstdio>
#include<cstdlib>
int Rand()
{
    return(rand()<<16)^(rand()<<8)^rand();
}
main()
{
    srand(time(NULL));
    puts("10");
    int i,j;
    for(i=0;i<10;i++)
    {
        printf("50000000 100 %d %d\n",Rand()%50000000,Rand()%50000000);
        for(j=0;j<100;j++)
            printf("%d %d\n",Rand()%50000000,Rand()%50000000+1);
    }
}
