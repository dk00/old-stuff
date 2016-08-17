#include<stdio.h>
int dp[27][361][27];
main(){
int i,j,k,l,s;
for(i=1;i<=26;i++)
    dp[1][i][i]=1;
for(i=1;i<26;i++)
    for(j=0;j<=360;j++)
        for(k=1;k<=26;k++)
            for(l=k+1;l<=26 && j+l<361;l++)
                dp[i+1][j+l][l]+=dp[i][j][k];
for(i=1;i<=26;i++)
    for(j=0;j<=361;j++)
        for(k=1;k<=26;k++)
            dp[i][j][k]+=dp[i][j][k-1];
s=1;
while(scanf("%d %d",&i,&j) && i+j){
    printf("Case %d: ",s++);
    if(i<=26 && j<361)
        printf("%d\n",dp[i][j][26]);
    else puts("0");
}
}

