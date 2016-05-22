#include<cstdio>
const int N = 1005;
int n, m, h, w, s[N][N], t[N][N];
inline int Sum(int x, int y) {
  return t[x][y] - ((x>=h)?t[x-h][y]:0) - ((y>=w)?t[x][y-w]:0) 
    + ((x>=h && y>=w)?t[x-h][y-w]:0);
}
int Test(int q) {
  int i, j;
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
      if (s[i][j] < q)
        t[i][j] = -1;
      else if (s[i][j] > q)
        t[i][j] = 1;
      else t[i][j] = 0;
  for (i = 0; i < n; ++i)
    for (j = 1; j < m; ++j)
      t[i][j] += t[i][j-1];
  for (j = 0; j < m; ++j)
    for (i = 1; i < n; ++i)
      t[i][j] += t[i-1][j];
  for (i = h - 1; i < n; ++i)
    for (j = w - 1; j < m; ++j)
      if (Sum(i, j) <= 0)
        return 1;
  return 0;
}
int main() {
  int T, C = 1;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, a;
    scanf("%d %d %d %d", &n, &m, &h, &w);
    k = 1;
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j) {
        scanf("%d", &s[i][j]);
        if (s[i][j] > k) k = s[i][j];
      }
    for (i = 0, j = k; i <= j; ) {
      k = (i + j)/2;
      if (Test(k)) a = k, j = k - 1;
      else i = k + 1;
    }
    printf("Case #%d: %d\n", C++, a);
  }
}
