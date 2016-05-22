#include<stdio.h>
main(){
int i,k,n;
while(scanf("%d",&n)-EOF){
    for(i=0,k=n;k;i++,k/=10)
        while(k%10-1)k+=n;
    printf("%d\n",i);
}
}
