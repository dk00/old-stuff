//s(0)=1,s(1)=1,s(2)=3,s(n) = s(n-1) + s(n-2) + s(n-2) + s(n-2)
#include<stdio.h>
const long long  D=1000000000000000000ll;
long long dp[251][10];
int d[251];
main(){
int i,j;
dp[0][0]=1,dp[1][0]=1,dp[2][0]=3;
d[0]=d[1]=d[2]=1;
for(i=3;i<251;i++){
    for(j=0;j<d[i-2];j++){
        dp[i][j]+=dp[i-2][j];
        while(dp[i][j]>=D){
            dp[i][j]-=D;
            dp[i][j+1]++;
        }
        dp[i][j]+=dp[i-2][j];
        while(dp[i][j]>=D){
            dp[i][j]-=D;
            dp[i][j+1]++;
        }
    }
    for(j=0;j<d[i-1];j++){
        dp[i][j]+=dp[i-1][j];
        while(dp[i][j]>=D){
            dp[i][j]-=D;
            dp[i][j+1]++;
        }
    }
    for(d[i]=9;!dp[i][d[i]];d[i]--);
    d[i]++;
}
while(scanf("%d",&i)!=EOF){
    printf("%lld",dp[i][d[i]-1]);
    for(j=d[i]-2;j>=0;j--)
        printf("%018lld",dp[i][j]);
    puts("");
}
}
