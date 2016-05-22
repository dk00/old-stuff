#include<stdio.h>
int coin[]={1,2,4,10,20,40},num[6],dp[201];
main(){
int i,j,k;
while(1){
    for(i=k=0;i<6;i++)
        scanf("%d",&num[i]),k+=num[i];
    if(!k)break;
    scanf("%d.%d",&j,&k);
    k=j*20+k/5;
    for(i=1,dp[0]=0;i<=200;i++)dp[i]=100000;
    for(i=0;i<6;i++)
        while(num[i]--)
            for(j=200;j>=coin[i];j--)
                dp[j]<?=(dp[j-coin[i]]+1);
    for(i=0;i<6;i++)
        for(j=200-coin[i];j>=0;j--)
            dp[j]<?=(dp[j+coin[i]]+1);
    printf("%3d\n",dp[k]);
}
}
