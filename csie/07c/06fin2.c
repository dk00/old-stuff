#include<math.h>
#include<stdio.h>
double f(double x)
{
    return x*x+4*sin(x)+7;
}
main()
{
    int n;
    double x,dx;
    scanf("%d %lf %lf",&n,&x,&dx);
    while(n--)
    {
        printf("%lf %lf %lf\n",dx,(f(x+dx) - f(x)) / dx,(f(x+dx) - f(x- dx)) /(2 *dx));
        dx/=2;
    }
}
