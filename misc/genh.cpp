#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    int t,T=100,M=10000,N=11,a=1001,b=1001;
    srand(time(NULL));
    printf("%d\n",T);
    for(t=0;t<T;t++)
        printf("%d %d %d %d\n",1+rand()%M,rand()%N,rand()%a,rand()%b);
}
