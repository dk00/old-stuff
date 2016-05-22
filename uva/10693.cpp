#include<stdio.h>
#include<math.h>
main(){
int f,l;
double v;
while(scanf("%d %d",&l,&f) && f+l){
    v=sqrt(f*l*2.0);
    printf("%.8lf %.8lf\n",v,1800*v/l);
}
}
