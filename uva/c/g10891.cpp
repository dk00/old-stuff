#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int i,n,t;
    for(t=0;t<10;t++)
    {
        printf("%d\n",5);
        for(i=0;i<5;i++)
        {
            if(rand()%3)
                printf("%d ",rand()%10);
            else
                printf("-%d ",rand()%10);
        }
        puts("");
    }
    puts("0");
}
