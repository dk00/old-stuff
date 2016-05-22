#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int i,j,k,n,m,T;
    for(T=0;T<100;T++)
    {
        n=101+rand()%100;
        m=n+rand()%(n/2);
        printf("%d %d %d %d\n",n,m,1+rand()%n,1+rand()%n);
        for(i=0;i<m;i++)
            printf("%d %d %d\n",1+rand()%n,1+rand()%n,1+rand()%10);
    }
    puts("0");
}
