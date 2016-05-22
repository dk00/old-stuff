#include<ctime>
#include<cstdio>
#include<cstdlib>
char t[]="01ab";
main()
{
    int i,j;
    srand(time(NULL));
    for(i=0;i<15;i++)
    {
        for(j=1+rand()%30;j--;)
            putchar(t[rand()%4]);
        puts("");
    }
}
