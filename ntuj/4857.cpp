#include <stdio.h>
#include <string.h>

int last[105];
int c[105];
int a[105];
int dp[105][105];

inline void update(int *x, int v) {
  if(*x > v) *x = v;
}

int dfs(int L, int R) {
  if(dp[L][R] != -1)
    return dp[L][R];
  //printf("L=%d, R=%d\n", L, R);
  if(L==R) {
    dp[L][R] = 1;
    return 1;
  }
  if(a[L] == a[L+1]) {
    dp[L][R] = dfs(L+1, R);
    return dp[L][R];
  }
  if(a[L] != a[R]) {
    int ret = dfs(L, R-1) + 1, x = last[R];
    while(x > L) {
      update(&ret, dfs(L, x-1) + dfs(x, R));
      x = last[x];
    }
    dp[L][R] = ret;
    return dp[L][R];
  }

  int ret = dfs(L+1, R-1) + 1, x = last[R];
  while(x > L) {
    update(&ret, dfs(L+1, x-1) + dfs(x, R));
    x = last[x];
  }
  dp[L][R] = ret;
  return dp[L][R];
}

int main(void)
{
  int T, cs=0, i, n, m, x;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &m);
    memset(c, -1, sizeof(c));
    memset(dp, -1, sizeof(dp));
    for(i=0;i<n;i++) {
      scanf("%d", &x);
      a[i] = x;
      last[i] = c[x];
      c[x] = i;
    }
    int ans = dfs(0, n-1);
    printf("Case %d: %d\n", ++cs, ans);
  }
  return 0;
}
