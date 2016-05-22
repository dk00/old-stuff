#include<stdio.h>
main(){
long unsigned d1,d2,p;
int i,n;
scanf("%d",&n);
for(;n>0;n--){
    scanf("%lu",&d1);
    for(p=d1,d2=0;p>0;p/=10)
        d2=d2*10+p%10;
    for(i=1;;i++){
        d1+=d2;
        for(p=d1,d2=0;p>0;p/=10)
            d2=d2*10+p%10;
        if(d1==d2)break;
    }
    printf("%d %lu\n",i,d1);
}
}
