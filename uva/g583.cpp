#include<ctime>
#include<algorithm>
long long Rand()
{
    return rand()*(1ll<<48)+rand()*(1ll<<32)+rand()*(1ll<<16)+rand();
}
main()
{
    for(int i=0;i<1000;i++)
        printf("%d\n",int(Rand()%2147483647+1));
    puts("0");
}
