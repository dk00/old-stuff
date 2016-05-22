/* @JUDGE_ID:  58589NF  543  C++  "Goldbach's Conjecture"*/
#include<stdio.h>
main(){
long i,n,j,h,e;
long prime[78498],isP,p;
prime[p=0]=2;prime[++p]=3;
for(i=5;i<=99999999;i+=2){
    for(j=1,isP=1;prime[j]*prime[j]<=i;j++){
        if(i%prime[j]==0){
            isP=0;
            break;
        }
    }
    if(isP) prime[++p]=i;
}
printf("%d",p);
scanf("%d");
while(1){
    scanf("%ld",&n);
    if(n<=0)break;
    if(n==4){
        printf("4 = 2 + 2\n");
        continue;
    }
    for(i=1;i<=78498 && 2*prime[i]<=n;i++){
        for(h=i,e=78498;h<=e;){
            j=(h+e)/2;
            if(prime[i]+prime[j]==n) break;
            else if(prime[i]+prime[j]>n) e=j-1;
            else h=j+1;
        }
        if(prime[i]+prime[j]==n) break;
    }
    printf("%ld =  %ld + %ld\n",n,prime[i],prime[j]);
}
}
/*@END_OF_SOURCE_CODE*/
