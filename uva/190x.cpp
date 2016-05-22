#include<stdio.h>
double x1,y1,x2,y2,x3,y3,px,py;
double a1,b1,c1,a2,b2,c2;
main(){
while(scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3)!=EOF){
    a1=x1-x2;
    b1=y1-y2;
    px=(x1+x2)/2;
    py=(y1+y2)/2;
    c1=a1*px+b1*py;
    a2=x1-x3;
    b2=y1-y3;
    px=(x1+x3)/2;
    py=(y1+y3)/2;
    c2=a2*px+b2*py;
    px=(c1*b2-c2*b1)/(a1*b2-a2*b1);
    py=(a1*c2-a2*c1)/(a1*b2-a2*b1);
    printf("%.3lf %.3lf\n",px,py);
}
}
/*
| c1 b1
| c2 b2
*/
