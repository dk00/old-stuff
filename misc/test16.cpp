#include<cmath>
#include<cstdio>
main()
{
    double v;
    for(v=1;v<1e7;v*=10)
        printf("%lf %lf\n",v,pow(log(v),3));
    scanf("%lf",&v);
}
