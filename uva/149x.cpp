/*
sin@ = r/d
sin@ > sin0.01
r/d > sin0.01
d sin0.01 < 0.1
10d sin0.01 < 1

10d sin0.01 = 1
d sin0.01 = 0.1
*/
#include<math.h>
#include<stdio.h>
using namespace std;
const double pi=acos(-1);
double x,y,r;
int sum;
void find(double s1,double s2,int h,int y1,int y2){
double d3=sqrt((x-h)*(x-h)+(y1-y)*(y1-y)),
       d4=sqrt((x-h)*(x-h)+(y2-y)*(y2-y))
       s3=asin(r/d3)+asin((x-h)/d3);
       s4=pi/2-asin(r/d4)+asin((x-h)/d4);
       

}
main(){
while(scanf("%lf %lf %lf",&r,&x,&y) && r+x+y>0.0){
    r/=2;
    sum=0;
    find(pi/4,3*pi/4,0,0,1);
    printf("%d\n",sum);
}
}
