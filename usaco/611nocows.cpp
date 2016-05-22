/*
ID: s0000151
PROG: nocows
LANG: C++
*/
#include<stdio.h>
int dp[201][101],cut[201][101];
int inline tree(int n,int d){
    if(cut[n][d])return dp[n][d];
    if(!d)return 0;
    if(n%2==0)return 0;
int i,left,right,sum=0;
    for(i=1;i<n;i++,i++){
        left=tree(i,(d-1)<?(i/2+1))%9901;
        right=tree(n-i-1,(d-1)<?((n-i-1)/2+1))%9901;
        dp[n][d]+=left*right;
        dp[n][d]%=9901;
    }
    cut[n][d]=1;
    return dp[n][d];
}
main(){
freopen("nocows.in","r",stdin);
freopen("nocows.out","w",stdout);
int n,k,ans;
cut[1][1]=cut[3][2]=dp[1][1]=dp[3][2]=1;
scanf("%d %d",&n,&k);
ans=tree(n,k)-(k?tree(n,k-1):0);
printf("%d\n",(ans+(ans<0?9901:0))%9901);
}
