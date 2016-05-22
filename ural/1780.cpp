#include <stdio.h>
#include <string.h>

char a[100005];
char b[100005];
int dp[100005][2];

int main(void)
{
  scanf("%s%s", a, b);
  if(strlen(a) != strlen(b)) {
    printf("Impossible\n");
    return 0;
  }
  int n = strlen(a), i;
  dp[n][0] = dp[n][1] = 1;
  for(i=n-1;i>=0;i--) {
    if((a[i]=='0' || a[i]=='?') && (b[i]=='0' || b[i]=='?'))
      dp[i][0] += dp[i+1][0];
    if((a[i]=='1' || a[i]=='?') && (b[i]=='1' || b[i]=='?'))
      dp[i][0] += dp[i+1][1];
    if((a[i]=='0' || a[i]=='?') && (b[i]=='1' || b[i]=='?'))
      dp[i][1] += dp[i+1][0];
    if((a[i]=='1' || a[i]=='?') && (b[i]=='0' || b[i]=='?'))
      dp[i][1] += dp[i+1][1];
    if(dp[i][0] >= 2) dp[i][0] = 2;
    if(dp[i][1] >= 2) dp[i][1] = 2;
  }
  if(dp[0][0] + dp[0][1] == 0)
    printf("Impossible\n");
  else if(dp[0][0] + dp[0][1] > 1)
    printf("Ambiguity\n");
  else{
    int st = 0;
    for(i=0;i<n;i++){
      if(st == 0 && (a[i]=='0' || a[i]=='?') && (b[i]=='0' || b[i]=='?') && dp[i+1][0]==1)
        a[i]='0', b[i]='0', st=0;
      if(st == 0 && (a[i]=='1' || a[i]=='?') && (b[i]=='1' || b[i]=='?') && dp[i+1][1]==1)
        a[i]='0', b[i]='1', st=0;
      if(st == 1 && (a[i]=='0' || a[i]=='?') && (b[i]=='1' || b[i]=='?') && dp[i+1][0]==1)
        a[i]='1', b[i]='1', st=1;
      if(st == 1 && (a[i]=='1' || a[i]=='?') && (b[i]=='0' || b[i]=='?') && dp[i+1][1]==1)
        a[i]='1', b[i]='0', st=1;
    }
    printf("%s\n%s\n", a, b);
  }
  return 0;
}
