#include<stdio.h>
__int64 n,k;
main(){
while(scanf("%I64d %I64d",&n,&k)!=EOF)printf("%I64d\n",n+(n-1)/(k-1));
}
