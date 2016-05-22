#include<stdio.h>
#define Max 320
#define U 1000000000
main(){
long fib[3][Max+1],i,j,d[5001];
fib[0][Max]=1;d[0]=Max;
fib[1][Max]=1;d[1]=Max;
for(i=2;i<=5000;i++){
    d[i]=d[i-1];
    for(j=d[i];j<=Max;j++)
        fib[i%3][j]=fib[(i-1)%3][j]+fib[(i-2)%3][j];
    for(j=Max;j>d[i];j--){
        if(fib[i%3][j]>U){
            fib[i%3][j-1]+=fib[i%3][j]/U;
            fib[i%3][j]%=U;
        }
    }
    if(fib[i%3][d[i]]>U){
        fib[i%3][d[i]-1]=fib[i%3][d[i]]/U;
        fib[i%3][d[i]--]%=U;
    }
}
printf("%ld\n",d[5000]);
while(scanf("%ld",&i)!=EOF){
    printf("The Fibonacci number for %ld is ",i);
    printf("%ld",fib[i%3][d[i]]);
    for(j=d[i]+1;j<=Max;j++)
        printf("%09ld",fib[i%3][j]);
    printf("\n");
}
}
