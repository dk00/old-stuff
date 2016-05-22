#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int i,j,t;
    for(t=0;t<50;t++)
    {
        puts("10 5");
        for(i=0;i<100;i++)
        {
            j=rand()%51;
            printf("%d %d\n",j,rand()%(j+1));
        }
        for(i=0;i<50;i++)
        {
            j=rand()%41;
            printf("%d %d\n",j,rand()%(j+1));
        }
    }
}
