#include<stdio.h>
main(){
double a,b;
while(scanf("%lf %lf",&a,&b)!=EOF)printf("%.0lf\n",a>b?a-b:b-a);
}
