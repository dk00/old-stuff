#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(0));
    freopen("10304.in","w",stdout);
    int i,j,n;
    for(i=0;i<5;i++)
    {
        printf("%d\n",n=1+rand()%50);
        for(j=0;j<n;j++)
            printf(" %d",1+rand()%99);
        puts("");
    }
}
