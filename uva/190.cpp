#include<math.h>
#include<stdio.h>
double x1,y_1,x2,y2,x3,y3,px,py;
double a1,b1,c1,a2,b2,c2,r;
main(){
while(scanf("%lf %lf %lf %lf %lf %lf",&x1,&y_1,&x2,&y2,&x3,&y3)!=EOF){
    a1=x1-x2;
    b1=y_1-y2;
    px=(x1+x2)/2;
    py=(y_1+y2)/2;
    c1=a1*px+b1*py;
    a2=x1-x3;
    b2=y_1-y3;
    px=(x1+x3)/2;
    py=(y_1+y3)/2;
    c2=a2*px+b2*py;
    px=(c1*b2-c2*b1)/(a1*b2-a2*b1);
    py=(a1*c2-a2*c1)/(a1*b2-a2*b1);
    printf("(x");
    if(px>0.0)printf(" - %.3lf",px);
    else if(px<0.0)printf(" + %.3lf",-px);
    printf(")^2 + (y");
    if(py>0.0)printf(" - %.3lf",py);
    else if(py<0.0)printf(" + %.3lf",-py);
    r=sqrt((px-x1)*(px-x1)+(py-y_1)*(py-y_1));
    printf(")^2 = %.3lf^2\n",r);
    printf("x^2 + y^2");
    if(px>0.0)printf("  - %.3lfx",px*2);
    else if(px<0.0)printf(" + %.3lfx",px*-2);
    if(py>0.0)printf(" - %.3lfy",py*2);
    else if(py<0.0)printf(" + %.3lfy",py*-2);
    r=(px-x1)*(px-x1)+(py-y_1)*(py-y_1);
    if(px*px+py*py-r>0.0)printf(" + %.3lf",px*px+py*py-r);
    else if(px*px+py*py-r<0.0)printf(" - %.3lf",-(px*px+py*py-r));
    puts(" = 0\n");
}
}
/*
| c1 b1
| c2 b2
*/
