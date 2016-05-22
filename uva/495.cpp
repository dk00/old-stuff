#include<stdio.h>
#include<malloc.h>
#define Max 118
#define U 1000000000
main(){
long *fib[5001],i,j,d[5001];
for(i=0;i<=5000;i++) fib[i]=(long *)malloc(sizeof(long)*(Max+1));
fib[0][Max]=0;d[0]=Max;
fib[1][Max]=1;d[1]=Max;
for(i=2;i<=5000;i++){
    d[i]=d[i-1];
    for(j=d[i];j<=Max;j++)
        fib[i][j]=fib[i-1][j]+fib[i-2][j];
    for(j=Max;j>d[i];j--){
        if(fib[i][j]>U){
            fib[i][j-1]+=fib[i][j]/U;
            fib[i][j]%=U;
        }
    }
    if(fib[i][d[i]]>U){
        fib[i][d[i]-1]=fib[i][d[i]]/U;
        fib[i][d[i]--]%=U;
    }
}
while(scanf("%ld",&i)!=EOF){
    printf("The Fibonacci number for %ld is ",i);
    printf("%ld",fib[i][d[i]]);
    for(j=d[i]+1;j<=Max;j++)
        printf("%09ld",fib[i][j]);
    printf("\n");
}
}
