#include<cmath>
#include<cstdio>
main()
{
    int T;
    double ha,hb,a,b,c,d,t;
    scanf("%d %lf %lf",&T,&ha,&hb);
    while(T--)
    {
        scanf("%lf %lf %lf %lf",&a,&b,&c,&d);
        t=100*tan(d)/tan(c)/cos(c);
        printf("%lf\n",t/tan(a)+ha);
    }
}
