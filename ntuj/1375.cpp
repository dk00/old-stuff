#include<vector>
#include<cstdio>
const int N = 201*201, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int t, n, m, to[N][6], c[N][6], p[N], dummy;
inline int& C(int a, int b) {
  int i;
  if (a == t) return dummy = 0;
  for (i = 0; i < 4; ++i)
    if (to[a][i] == b) break;
  if (i >= 4) {
    printf("%d %d\n", a, b);
    i/= 0;
  }
  return c[a][i];
}
int go(int v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  if (v) {
    for (int j = 0; j < 6; ++j) {
      if (to[v][j] < 0 || c[v][j] < 1) continue;
      if (c[v][j]-- && go(to[v][j]))
        return ++C(to[v][j], v);
      ++c[v][j];
    }
    return 0;
  }
  int sum = 0;
  for (int i = 1; i < t; ++i) {
    if (c[i][4]-- && go(i)) ++sum;
    else ++c[i][4];
  }
  return sum;
}
int flow() {
  int i, x, f = 0;
  while (1) {
    for (i = 0; i <= t; ++i) p[i] = 0;
    x = go(0);
    f += x;
    if (x < 1) break;
  }
  return f;
}
main() {
  int i, j, k, x, y;
  while (scanf("%d %d", &n, &m) == 2 && n + m) {
    t = n*m + 1;
    for (i = 0; i <= t; ++i)
      for (j = 0; j < 6; ++j)
        to[i][j] = -1, c[i][j] = 0;
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j) {
        k = i*m + j + 1;
        for (int l = 0; l < 4; ++l) {
          x = i + dx[l],  y = j + dy[l];
          if (x < 0 || x >= n || y < 0 || y >=m) continue;
          to[k][l] = x*m + y + 1;
        }
        if ((i+j)%2) {
          to[k][5] = t;
          c[k][5] = 1;
          continue;
        }
        c[k][4] = 1;
        for (int l = 0; l < 4; ++l)
          if (to[k][l] >= 0) c[k][l] = 1;
      }
   scanf("%d", &k);
   if (n+m+k == 0) break;
   while (k--) {
      scanf("%d %d", &i, &j);
      if ((i+j)%2) c[i*m+j+1][5] = 0;
      else c[i*m+j+1][4] = 0;
    }
    printf("%d\n", flow());
  }
}
