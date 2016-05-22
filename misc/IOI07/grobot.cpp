#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int i,j,n,m;
    n=37,m=37;
    printf("%d %d\n",n,m);
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            if(!i || !j || i==n-1 || j==m-1 || rand()%5==2)
                putchar('#');
            else
                putchar('.');
        puts("");
    }
}
