#include<cstdio>
main()
{
    int i,j,k;
    while(scanf("%d %d %d",&i,&j,&k) && i+j+k)
        printf("%d\n",((i-7)*(j-7)+k)/2);
}
