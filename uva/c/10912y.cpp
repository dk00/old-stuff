#include <stdio.h>
int dp[27][10001],min[27],max[27];
main(){
int i,j,k;
dp[0][0]=1,max[1]=26;
for(i=1;i<=26;i++)dp[1][i]=1;
for(i=25;i>=1;i--)max[27-i]=max[26-i]+i;
for(i=1;i<=26;i++)min[i]=min[i-1]+i;
for(i=1;i<26;i++)
    for(j=min[i];j<=max[i];j++)
        for(k=j+i+1;k<=max[i+1];k++)
            dp[i+1][k]+=dp[i][j];
while(scanf("%d %d",&i,&j)){
    if(i<=26)printf("%d\n",dp[i][j]);
    else puts("0");
}
}
