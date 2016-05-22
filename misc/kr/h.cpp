#include <stdio.h>
#include <algorithm>
using namespace std;

long long dp[1005][1005];

bool cmp(int x, int y)
{
  return x>y;
}

inline void update(long long *x, long long v)
{
  if(*x==-1 || *x > v)
    *x = v;
}
int a[1005];
int main(void)
{
  int T, i, j;
  scanf("%d", &T);
  while(T--){
    int n, A, B, C;
    scanf("%d%d%d%d", &n, &A, &B, &C);
    for(i=1;i<=n;i++)
      scanf("%d", &a[i]);
    sort(a+1, a+n+1, cmp);
    dp[0][0] = 0;
    for(i=1;i<=n;i++){
      for(j=0;j<=i;j++)
        dp[i][j] = -1;
      for(j=0;j<i;j++){
        update(&dp[i][j+1], dp[i-1][j] + (C*(j) + A*n)*1ll * a[i]);
        update(&dp[i][j], dp[i-1][j] + B*1ll*(i-j)*a[i]);
      }
    }
    long long ans = -1;
    for(i=0;i<=n;i++){
      update(&ans, dp[n][i]);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
