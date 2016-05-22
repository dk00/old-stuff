#include<math.h>
#include<stdio.h>
double x1,y_1,x2,y2,x3,y3,px,py,a1,b1,c1,a2,b2,c2;
main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lf %lf %lf %lf %lf %lf",&x1,&y_1,&x2,&y2,&x3,&y3);
        a1=x1-x2;
        b1=y_1-y2;
        px=x3;
        py=y3;
        c1=a1*px+b1*py;
        a2=x1-x3;
        b2=y_1-y3;
        px=x2;
        py=y2;
        c2=a2*px+b2*py;
        px=(c1*b2-c2*b1)/(a1*b2-a2*b1);
        py=(a1*c2-a2*c1)/(a1*b2-a2*b1);
        printf("%.4lf %.4lf\n",px+1e-7,py+1e-7);
    }
}
