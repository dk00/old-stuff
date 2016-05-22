#include<stdio.h>
#include<stdlib.h>
long long n;
main(){
long long i;
while(scanf("%lld",&n) && n>=0){
    if(!n)abort();
    while(!(n&1) && n){
        n>>=1;
        puts("    2");
    }
    for(i=3;n>1 && i*i<=n;i++,i++){
        while(n%i==0){
            n/=i;
            printf("    %lld\n",i);
        }
    }
    if(n-1)printf("    %lld\n",n);
    puts("");
}
}
