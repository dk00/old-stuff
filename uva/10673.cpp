#include<stdio.h>
main(){
int t,x,k;
scanf("%d",&t);
while(t--){
    scanf("%d %d",&x,&k);
    if(x%k)printf("%d %d\n",k-x%k,x%k);
    else printf("0 %d\n",k);
}
}
