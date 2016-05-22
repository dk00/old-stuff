#include<cstdio>
main()
{
    char tmp[99];
    long long i,x;
    while(scanf("%s",tmp)==1 && (tmp[0]!='0' || tmp[1]))
    {
        for(i=x=0;tmp[i];i++)
            x=x*9+(tmp[i]-'0'-(tmp[i]>='6'));
        printf("%I64d\n",x);
    }
}
