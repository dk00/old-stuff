#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,n,m;
    srand(time(NULL));
    freopen("10986.in","w",stdout);
    puts("100");
    for(i=0;i<100;i++)
    {
        n=5+rand()%5;
        m=10+rand()%10;
        printf("%d %d %d %d\n",n,m,rand()%n,rand()%n);
        while(m--)
            printf("%d %d %d\n",rand()%n,rand()%n,1+rand()%100);
    }
}
