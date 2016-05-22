#include<stdio.h>
main(){
int n,k,sum;
while(scanf("%d",&n) && n){
    sum=0;
    while(n-- && scanf("%d",&k)){
        sum+=k;
        if(k)printf("%d",k);
        if(n)printf(" ");
    }
    if(!sum)puts("0");
    else puts("");
}
}
