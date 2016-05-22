/* @JUDGE_ID:  58589NF  568  C++  "Just the facts"*/
#include<stdio.h>
int main(){
long fact,n,i;
while(scanf("%ld",&n)!=EOF){
    for(i=1,fact=1;i<=n;i++){
        fact*=i;
        while(fact%10==0) fact/=10;
        fact%=100000;
    }
    while(fact%10==0) fact/=10;
    printf("%5ld -> %ld\n",n,fact%10);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
