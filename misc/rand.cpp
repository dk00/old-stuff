#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int n,k;
    while(scanf("%d %d",&n,&k)==2)
    {
        while(n--)
            printf("%d ",rand()%k);
        puts("");
    }
}
