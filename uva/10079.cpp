#include<stdio.h>
main(){
long long n;
while(scanf("%lld",&n) && n>=0)printf("%lld\n",n*(n+1)/2+1);
}
