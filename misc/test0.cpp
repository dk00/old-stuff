#include<ctime>
#include<cstdio>
#include<cstdlib>
char s[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
main()
{
    srand(time(NULL));
    int i,n;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            putchar(s[rand()%62]);
        puts("");
    }
}
