#include<stdio.h>
#include<algorithm>
#include<string.h>
int tt,n,i,j,k,l,dp[160][900],a[5][900][900],t,an,ma;
char c[5],s[200];
main(){
  freopen("pb.in","r",stdin);
  scanf("%d",&t);
  while(t--){
    memset(dp,0,sizeof(dp));
    tt++;
    scanf("%d",&n);
    ma=0;
    for(i=0;i<n;i++){
      scanf("%d %s %d",&j,c,&k);
      a[c[0]-'A'][j][k]=tt;
      ma>?=j;
      ma>?=k;
    }
    scanf("%s",s+1);
    l=strlen(s+1);
    dp[0][1]=1;
    for(i=1;i<=l;i++){
      for(j=1;j<=ma;j++){
        for(k=1;k<=ma;k++){
          if(dp[i-1][k]>0&&a[s[i]-'A'][k][j]==tt){
            dp[i][j]>?=dp[i-1][k]+j;
          }
        }
      }
    }
    an=0;
    for(i=1;i<=800;i++){
      an>?=dp[l][i];
    }
    printf("%d\n",an-1);
  }
}
