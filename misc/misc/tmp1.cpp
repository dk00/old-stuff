#include<cstdio>
main()
{
    char tmp[99];
    while(gets(tmp))
    {
        printf("%d\n",16+(tmp[0]+tmp[1]+tmp[2]+tmp[3])%16);
    }
    
}
