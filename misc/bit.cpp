#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    char tmp[100];
    int i;
    for(i=0;i<10;i++)
    {
        printf("%08s\n",itoa(rand()%255,tmp,2));
    }
    scanf(" ");
}
