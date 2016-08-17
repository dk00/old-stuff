#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,n=20,t;
    puts("10");
    for(t=0;t<10;t++)
    {
        printf("%d\n",n);
        for(i=0;i<n;i++)
            printf("%d ",rand()%30);
        puts("");
    }
}
