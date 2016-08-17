#include<cmath>
#include<cstdio>
main()
{
    int i,j;
    while(scanf("%d %d",&i,&j) && i+j)
        printf("%.0lf\n",floor((i-1)/(100.0-j)*100));
}
