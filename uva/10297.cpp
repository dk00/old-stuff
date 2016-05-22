#include<math.h>
#include<stdio.h>
const double pi=acos(-1.0);
main(){
int d,v;
while(scanf("%d %d",&d,&v) && d+v)
    printf("%.3lf\n",pow(d*d*d-6*v/pi,1/3.0));
}
