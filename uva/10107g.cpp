#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    for(int n=0;n<20000;n++)
        printf("%d\n",rand()%100);
}
