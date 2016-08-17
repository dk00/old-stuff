#include<ctime>
#include<algorithm>
long long Rand()
{
    return rand()*(1ll<<48)+rand()*(1ll<<32)+rand()*(1ll<<16)+rand();
}
main()
{
    srand(time(NULL));
    for(int i=0;i<10000;i++)
        //printf("%I64d\n",Rand()%900000000000000ll+1);
        printf("%I64d\n",i+1);
}
