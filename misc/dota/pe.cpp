#include<stdio.h>
int dp[10010],i,j,k,n,p;
main(){
  while(scanf("%d %d %d",&n,&p,&k)&&n+p+k){
    for(i=1;;i++){
      dp[1]=1;
      for(j=2;j<=n;j++){
        dp[j]=(i+dp[j-1]-1)%j+1;
      }
      if(dp[n]==p)k--;
      if(k==0)break;
    }
    printf("%d\n",i);
  }
}
