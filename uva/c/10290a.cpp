#include<stdio.h>
main(){
long long n;
int i,j;
while(scanf("%I64d",&n)!=EOF){
    while((~n)&1)n>>=1;
    if(n<=1){
        puts("1");
        continue;
    }
    for(i=1,j=0;i<n/i;i++,i++){
        if(n%i==0)j++,j++;
    }
    if(n%i==0)j++;
    printf("%d\n",j);
}
}
