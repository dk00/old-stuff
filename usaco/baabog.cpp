#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,n;
    srand(time(NULL));
    printf("%d\n",n=900);
    for(i=0;i<n;i++)
        printf("%d ",rand()%1000+1);
    puts("");
    for(i=0;i<n;i++)
        printf("%d ",rand()%1000+1);
}
