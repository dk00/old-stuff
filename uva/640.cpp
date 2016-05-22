#include<stdio.h>
int self[1000001];
long k;
void d(long n){
    if(n>1000000 || self[n])return;
    self[n]=1;
    for(k=n;k>0;k/=10)n+=k%10;
    d(n);
}
main(){
long i;
for(i=1;i<=1000000;i++){
    if(!self[i]){
        d(i);
        printf("%ld\n",i);
    }
}
}
