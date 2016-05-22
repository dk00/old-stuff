#include<stdio.h>
main(){
int i,h,d,t1,t2;
double n,u,f;
while(scanf("%d %d %d %d",&h,&t2,&d,&t1) && h+t1+d+t2){
    f=t1/100.0;
    u=t2*1.0;
    for(n=0.0,i=1;n>=0 && n<=h;i++){
        n+=u;
        if(n>h)break;
        n-=d;
        u-=f*t2;
        u>?=0.0;
    }
    if(n<0.0)printf("failure on day %d\n",i-1);
    else printf("success on day %d\n",i);
}
}
