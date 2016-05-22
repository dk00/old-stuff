#include<cmath>
#include<cstdio>
main()
{
    int T;
    double a,b,s;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lf %lf %lf",&a,&b,&s);
        if(s<=0)s+=0.00000000000001;
        s<?=a*b;
        printf("%lf%%\n",(1-s*(1+log(a*b/s))/a/b)*100);
    }
}
