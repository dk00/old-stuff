#include<ctime>
#include<cstdio>
#include<cstdlib>
const int X=5000,Y=4995;
main()
{
    int i,j,t;
    srand(time(NULL));
    puts("10");
    for(t=0;t<10;t++)
    {
        puts("500 500");
        for(i=0;i<500;i++)
        {
            for(j=0;j<500;j++)
                printf("%d ",(rand()%X)>Y);
            puts("");
        }
    }
}
