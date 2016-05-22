#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1001;
int n, m, s[N][N];
char tmp[N];
inline int sum(int x, int y, int l) {
  return s[x+l][y+l] - (x>0?s[x-1][y+l]:0) - (y>0?s[x+l][y-1]:0)
    + (x>0 && y>0?s[x-1][y-1]:0);
}
int go(int x, int y, int K) {
  int i, j, k, r = 0;
  for (i = 1, j = min(n - x, m - y); i <= j;) {
    k = (i + j)/2;
    if (sum(x, y, k - 1) > K) j = k - 1;
    else r = k, i = k + 1;
  }
  return r;
}
main() {
  int i, j, k, u, x, y, T, K;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d", &n, &m, &K);
    for (i = 0; i < n; ++i) {
      scanf("%s", tmp);
      s[i][0] = tmp[0] - '0';
      for (j = 1; tmp[j]; ++j)
        s[i][j] = s[i][j-1] + tmp[j] - '0';
    }
    for (j = 0; j < m; ++j)
      for (i = 1; i < n; ++i)
        s[i][j] += s[i-1][j];
    for (i = u = 0; i < n; ++i)
      for (j = 0; j < m; ++j)
        if ((k = go(i, j, K)) > u)
          u = k, x = i, y = j;
    printf("%d %d %d\n", x + 1, y + 1, u);
  }
}
