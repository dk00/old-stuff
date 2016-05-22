#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    puts("1000");
    int i,j,k;
    for(i=0;i<1000;i++)
    {
        for(j=0;j<5;j++)
        {
            for(k=0;k<5;k++)
                printf("%d ",(rand()%4)>2);
            puts("");
        }
    }
}
