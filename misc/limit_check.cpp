#include<cmath>
#include<cstdio>
double f(double x)
{
    return x*sin(x);
}
main()
{
    int i;
    double x;
    for(i=0,x=1;i<12;i++,x/=10)
        printf("%lf\n",f(1.570796-x));
    for(i=0;i<12;i++,x*=10)
        printf("%lf\n",f(1.570796+x));
}
