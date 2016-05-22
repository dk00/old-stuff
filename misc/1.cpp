#include<stdio.h>
main(){
double x,y,max=-1.0,px,py;
scanf("%lf %lf",&x,&y);
if(x*x+y*y>max){
    px=x;
    py=y;
    max=x*x+y*y;
}
scanf("%lf %lf",&x,&y);
if(x*x+y*y>max){
    px=x;
    py=y;
    max=x*x+y*y;
}
scanf("%lf %lf",&x,&y);
if(x*x+y*y>max){
    px=x;
    py=y;
    max=x*x+y*y;
}
printf("%.0lf %.0lf\n",px,py);
scanf(" ");
}
