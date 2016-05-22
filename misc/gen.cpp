#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int n=1024;
    printf("%d\n",n);
    for(int i=0;i<n;i++)
        printf("%d ",rand());
}
