/* @JUDGE_ID:  58589NF  686  C++  "Goldbach's Conjecture(II)"*/
#include<stdio.h>
main(){
long i,n,j,gc[32769];
long prime[3512],isP,p;
prime[p=0]=2;prime[++p]=3;
for(i=5;i<=32767;i+=2){
    for(j=1,isP=1;prime[j]*prime[j]<=i;j++){
        if(i%prime[j]==0){
            isP=0;
            break;
        }
    }
    if(isP) prime[++p]=i;
}
for(i=0;i<=32768;i++) gc[i]=0;
for(i=1;i<=3511;i++){
    for(j=i;prime[i]+prime[j]<=32768 && j<=3511;j++)
        gc[prime[i]+prime[j]]++;
}
gc[4]=1;
while(1){
    scanf("%ld",&n);
    if(n<=0)break;
    printf("%ld\n",gc[n]);
}
}
/*@END_OF_SOURCE_CODE*/
