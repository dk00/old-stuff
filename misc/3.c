#include<stdio.h>
long max=0,dw[3],dh[3];
void cut(long w,long h,long earn){
    long i;
    for(i=0;i<3;i++)
        if(w>=dw[i] && h>=dh[i]){
            if(w-dw[i])cut(w-dw[i],dh[i],earn+dw[i]*dh[i]);
            if(h-dh[i])cut(dw[i],h-dh[i],earn+dw[i]*dh[i]);
            if(w-dw[i] && h-dh[i])
                cut(w-dw[i],h-dh[i],earn+dw[i]*dh[i]);
            if(max<earn+dw[i]*dh[i])max=earn+dw[i]*dh[i];
        }
}
int main(){
long i,w,h;
long t1;
scanf("%ld %ld",&w,&h);
for(i=0;i<3;i++)scanf("%ld %ld",&dw[i],&dh[i]);
cut(w,h,0);
t1=w;
printf("%ld\n",max);
return t1;
}

