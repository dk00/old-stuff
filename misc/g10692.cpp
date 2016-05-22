#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int i,j;
    for(i=0;i<10;i++)
    {
        printf("5000");
        for(j=0;j<5000;j++)
            printf(" %d",rand()*rand()+1);
        printf(" %d\n",1+rand()*rand()%1000000);
    }
}
