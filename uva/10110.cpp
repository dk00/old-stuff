#include<stdio.h>
#include<math.h>
main(){
unsigned long i;
double q;
while(scanf("%lu",&i) && i){
    if((q=sqrt(i))-floor(q)==0.00)puts("yes");
    else puts("no");
}
}
