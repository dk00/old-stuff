#include<cmath>
#include<cstdio>
main()
{
    double k,n;
    int a,b;
    while(scanf("%lf %lf %d %d",&k,&n,&a,&b) && k+n+a+b>0)
        printf("%.3lf\n",-log10(a*(-k+sqrt(k*k+4*a*b*n*k))/2/a/b));
}
