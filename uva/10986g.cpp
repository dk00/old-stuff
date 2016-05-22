#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,s,t,n,m;
    freopen("10986.in","w",stdout);
    puts("10");
    for(i=0;i<10;i++)
    {
        n=15000+rand()%5000;
        m=40000+rand()%10000;
        s=rand()%n;
        do t=rand()%n; while(t==s);
        printf("%d %d %d %d\n",n,m,s,t);
        while(m--)
            printf("%d %d %d\n",rand()%n,rand()%n,rand()%10001);
    }
}
