#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,j,n=20,m=n*(n-1)/2,t;
    srand(time(NULL));
    for(t=0;t<10;t++)
    {
        printf("%d\n",m);
        for(j=1;j<n;j++)
            printf("Park %d %d\n",j,1+rand());
        for(i=1;i<n;i++)
            for(j=i+1;j<n;j++)
                printf("%d %d %d\n",i,j,1+rand());
        printf("%d\n",1+rand()%20);
    }
}
