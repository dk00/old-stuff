#include<stdio.h>
int n,dp[100],num[100],winlose[100][100],cut[100][100],sum[100][100];
#define Sum(l,r) dp[r]-(l?dp[l-1]:0)
inline int play(int l,int r){
    if(l==r)return num[l];
    if(cut[l][r])return winlose[l][r];
int i;
    winlose[l][r]=sum[l][r];
    for(i=l;i<r;i++)
        winlose[l][r]>?=(sum[l][r]-play(l,i));
    for(i=r;i>l;i--)
        winlose[l][r]>?=(sum[l][r]-play(i,r));
    cut[l][r]=1;
    return winlose[l][r];
}
main(){
int i,j;
while(scanf("%d",&n) && n){
    scanf("%d",&num[0]);
    dp[0]=num[0];
    for(i=1;i<n;i++){
        scanf("%d",&num[i]);
        dp[i]=dp[i-1]+num[i];
    }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            cut[i][j]=0,sum[i][j]=Sum(i,j);
    printf("%d\n",2*play(0,n-1)-dp[n-1]);
}
}
