#include<math.h>
#include<stdio.h>
inline double cot(double a){return(1/tan(a));}
const double pi=acos(-1);
double r,x,y;
int sum;
void find(double s1,double s2,int w){
    if(s1-s2<=pi/100)return;
double s3,s4,d1,d2;
int i,x1,x2;
    x1=floor((w-y)*cot(s1)+x);
    x2=ceil((w-y)*cot(s2)+x);
    d1=sqrt((x1-x)*(x1-x)+(w-y)*(w-y));
    s3=asin((x1-x)/d1);
    if(s3+asin(r/d1)<=s1){
        sum++;
        find(s1,s3+asin(r/d1),w+1);
    }
    s4=s3;
    d2=d1;
    for(x1++;x1<x2;x1++,sum++){
        s3=s4-asin(d2/r);
        d1=d2;
        d2=sqrt((x1-x)*(x1-x)+(w-y)*(w-y));
        s4=asin((x1-x)/d2);
        find(s3,s4,w+1);
    }
    d1=sqrt((x2-x)*(x2-x)+(w-y)*(w-y));
    s3=asin((x1-x)/d1);
    if(s3+asin(d1/r)>=s2){
        sum++;
        find(s3+asin(d1/r),s2,w+1);
    }
}
main(){
double d1,d2;
while(scanf("%lf %lf %lf",&r,&x,&y) && r+x+y>0){
    sum=0;
    d1=sqrt(x*x+(1-y)*(1-y));
    d2=sqrt((1-x)*(1-x)+(1-y)*(1-y));
    find(asin(x/d1),asin((x-1)/d2),1);
    printf("%d\n",sum);
}
}
