/*
ID: s0000151
PROG: subset
LANG: C++
*/
#include<stdio.h>
int s[40];
long long dp[400];
main(){
freopen("subset.in","r",stdin);
freopen("subset.out","w",stdout);
int i,k,n,max;
for(i=1;i<40;i++)s[i]=s[i-1]+i;
scanf("%d",&n);
if(s[n]%2){
    puts("0");
    return 0;
}
for(max=s[n]/2,dp[0]=i=1;i<=n;i++)
    for(k=max;k>=i;k--)
        dp[k]+=dp[k-i];
printf("%lld\n",dp[max]>>1);
}
