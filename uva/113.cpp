#include<stdio.h>
#include<math.h>
main(){
double p,n;
while(scanf("%lf %lf",&n,&p)!=EOF) printf("%.0lf\n",pow(p,1/n));
}
