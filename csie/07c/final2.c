#include<stdio.h>
#include<math.h>
main()
{
    double a,b,c,pi;
    pi=acos(-1);
    
    scanf("%lf %lf %lf",&a,&b,&c);
    double x=0,y=0;
    if(c>b)x=c-b;
    if(c>a)y=c-a;
    printf("%e\n",pi*c*c*3.0/4.0+pi*x*x/4+pi*y*y/4);
}
