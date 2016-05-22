#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int n,m;
    srand(time(NULL));
    n=4,m=10;//scanf("%d %d",&n,&m);
    freopen("11183.in","w",stdout);
    puts("15");
    for(int x=0;x<15;x++)
    {
    printf("%d %d\n",n+=rand()%2,m+=rand()%5);
    int i,j,k;
    for(i=0;i<m;i++)
    {
        j=rand()%n,k=rand()%n;
        while(j==k)k=rand()%n;
        printf("%d %d %d\n",j,k,rand()%10);
    }
    }
}
