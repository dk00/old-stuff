#include<stdio.h>
main(){
long long x;
while(scanf("%lld",&x)!=EOF)printf("%lld\n",x*x*(x+1)*(x+1)/4);
}
