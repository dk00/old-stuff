#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int i,j,k,n=6;
    srand(time(NULL));
    puts("10");
    for(i=0;i<10;i++)
    {
        printf("%d\n",n);
        for(j=0;j<n;j++)
        {
            for(k=0;k<n;k++)
            {
                if(rand()%3==0)
                    putchar('-');
                printf("%d ",rand()%20);
            }
            puts("");
        }
        puts("");
    }
}
