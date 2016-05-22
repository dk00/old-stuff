#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i;
    char s[1006];
    for(i=0;i<=999;i++)
        s[i]='9';
    s[i]=0;
    printf("10 %s 1000 1000\n",s);
    for(i=0;i<=10;i++)
        puts(s);

}
