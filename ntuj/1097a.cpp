#include <stdio.h>
#include <string.h>

long long dp[100005];

int main(void)
{
  int n, m, i, j;
  while(scanf("%d%d", &n, &m)!=EOF) {
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    for(i=0;i<n;i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      if(y <= x) continue;
      y -= x;
      for(j=0;j<=m-x;j++)
        if(dp[j] != -1 && dp[j+x] < dp[j] + y)
          dp[j+x] = dp[j] + y;
    }
    long long ans = 0;
    for(i=0;i<=m;i++)
      if(ans < dp[i] + m-i)
        ans = dp[i] + m-i;
    printf("%lld\n", ans);
  }
  return 0;
}
