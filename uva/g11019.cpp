#include<ctime>
#include<cstdio>
#include<cstdlib>
int n[]={5,10,10,10,10,100,100,1000,1000,1000},
    m[]={2, 1,10, 1,10,  1,100,1000,1,1000},
    x[]={1, 1, 3, 3, 5,  2, 10, 20,20,100},
    y[]={2, 5, 3, 1, 1, 30, 10, 50, 1,100};
main()
{
    srand(time(0));
    int i,j,k;
    puts("10");
    for(i=0;i<10;i++)
    {
        printf("%d %d\n",n[i],m[i]);
        for(j=0;j<n[i];j++)
        {
            for(k=0;k<m[i];k++)
                putchar(rand()%2+'a');
            puts("");
        }
        printf("%d %d\n",x[i],y[i]);
        for(j=0;j<x[i];j++)
        {
            for(k=0;k<y[i];k++)
                putchar(rand()%2+'a');
            puts("");
        }
    }
}
