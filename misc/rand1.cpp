#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int n;
    srand(time(NULL));
    while(scanf("%d",&n) && n)
    {
        while(n--)
            printf("%d %d\n",rand()&15,rand()&15);
    }
}
