#include<cstdio>
#ifndef LINUX
#define lld "I64d"
#else
#define lld "lld"
#endif
main()
{
    long long i;
    char tmp[1000];
    while(scanf("%s",tmp)==1)
    {
        sscanf(tmp,"%12"lld,&i);
        printf("%"lld"d\n",i);
    }
}
