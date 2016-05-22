#include<cmath>
#include<cstdio>
main()
{
    int t;
    double aa,bb,cc,pi;
    pi=2.0*acos(0.0);
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lf %lf",&cc,&aa);
        cc/=2,aa/=2;
        bb=sqrt(aa*aa-cc*cc);
        printf("%.3lf\n",pi*aa*bb);
    }
}
