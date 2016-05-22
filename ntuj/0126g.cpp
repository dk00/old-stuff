#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    freopen("0126.in","w",stdout);
    int i,n,T=100;
    while(T--)
    {
        n=5+rand()%5;
        printf("%d",n);
        for(i=0;i<6;i++)
            printf(" %d",rand()%n);
        puts("");
    }
    puts("0 0 0 0 0 0 0");
}
