#include<cmath>
#include<cstdio>
const double pi=acos(-1.0);
main()
{
    double n,r;
    while(scanf("%lf %lf",&r,&n)==2)
        printf("%.3lf\n",n*(cos(pi/n)*sin(pi/n)*r*r));
}
