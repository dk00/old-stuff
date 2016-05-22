#include<cmath>
#include<cstdio>
main()
{
    double i,j;
    while(scanf("%lf %lf",&i,&j)==2)
        printf("%.3lf 0.000 %.3lf\n",
        (i+j-sqrt(i*i-i*j+j*j))/6.0+1e-7,(i<?j)/2.0+1e-7);
}
