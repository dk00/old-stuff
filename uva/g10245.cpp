#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int i,j,n=10000;
    for(i=0;i<5;i++)
    {
        printf("%d\n",n);
        for(j=0;j<n;j++)
            printf("%d %d\n",rand()%40000,rand()%40000);
    }
    puts("0");
}
