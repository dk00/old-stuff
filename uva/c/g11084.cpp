#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(0));
    puts("10");
    int t;
    for(t=0;t<10;t++)
    {
        printf("%06d %d\n",(rand()*rand())%1000000,rand()%10+1);
    }
}
