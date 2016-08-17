#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int n,m;
    srand(time(NULL));
    n=10,m=40;//scanf("%d %d",&n,&m);
    freopen("11183.in","w",stdout);
    puts("10");
    for(int x=0;x<100;x++)
    {
        n=50+rand()%100,m=100+rand()%(n*(n+1)/3);
    printf("%d %d\n",n,m);
    int i,j,k;
    for(i=0;i<m;i++)
    {
        j=rand()%n,k=rand()%n;
        while(j==k ||k==0)k=rand()%n;
        printf("%d %d %d\n",j,k,rand()%10);
    }
    }
    fclose(stdout);
    system("q11183<11183.in>1.out");
    system("q11183a<11183.in>2.out");
    //system("fc 1.out 2.out");
}
