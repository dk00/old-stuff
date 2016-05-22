#include<cstdio>
main()
{
    double a,b,c,d,e,f,d1,d2,x,y,a1,a2,b1,b2,c1,c2,px,py;
    while(scanf("%lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f)==6)
    {
        d1=8*a*c*f+2*b*e*d-2*c*d*d-2*b*b*f-2*a*e*e;
        d2=b*b-4*a*c;
        printf("Δ= %lf\n",d1);
        printf("δ= %lf\n",d2);
        a1=2*a,b1=b,c1=d;
        a2=b,b2=2*c,c2=e;
        if(b*b!=4*a*c)
        {
            printf("%lfx+%lfy+%lf=0\n",a1,b1,c1);
            printf("%lfx+%lfy+%lf=0\n",a2,b2,c2);
            px=(c1*b2-c2*b1)/(a1*b2-a2*b1);
            py=(a1*c2-a2*c1)/(a1*b2-a2*b1);
            printf("(%lf,%lf):%lf\n",px,py,
            a*px*px+b*px*py+c*py*py+d*px+e*py+f);
        }
        if(d2>-0.000001 && d2<0.000001)
        {
            if(d1>-0.000001 && d1<0.000001)
                puts("二平行或重合直線");
            else
                puts("拋物線");
        }
        else if(d2<0)
        {
            if(d1>-0.000001 && d1<0.000001)
                puts("點");
            else if(a*d1<0)
                puts("橢圓");
        }
        else
        {
            if(d1>-0.000001 && d1<0.000001)
                puts("二相交直線");
            else
                puts("雙曲線");
        }
    }
}
