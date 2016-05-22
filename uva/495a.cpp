#define Size 320
#include"bigint0.h"
bigint f[5001];
main(){
int i;
f[1]=1;
f[2]=1;
for(i=3;i<=5000;i++){
    f[i]+=f[i-1];
    f[i]+=f[i-2];
}
while(scanf("%d",&i)!=EOF){
    printf("The Fibonacci number for %d is ",i);
    f[i].show();
}
}
