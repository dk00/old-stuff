#include<vector>
#include<cstdio>
const int N = 201*201, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int n, m, t, p[N], c[N][6], dummy;
std::vector<int> to[N];
inline int& C(int a, int b) {
  if (b == 0 || a == t)
    return dummy = 0;
  if (a == 0) return c[b][4];
  if (b == t) return c[a][5];
  int i, x = (a-1)/m, y = (a-1)%m, nx, ny;
  for (i = 0; i < 4; ++i) {
    nx = x + dx[i], ny = y + dy[i];
    if (nx*m + ny + 1 == b) break;
  }
  if (i >= 4) return dummy = 0;
  return c[a][i];
}
int go(int v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  int sum = 0;
  for (int j = 0; j < to[v].size(); ++j) {
    int i = to[v][j];
    if (C(v, i)-- && go(i)) {
      if (v) return ++C(i, v);
      ++C(i, v);
      ++sum;
    }
    else ++C(v, i);
  }
  return sum;
}
int flow() {
  int i, x, f = 0;
  while (1) {
    for (i = 0; i <= t; ++i)
      p[i] = 0;
    x = go(0);
    if (!x) return f;
    f += x;
  }
  return f;
}
main() {
  int i, j, k;
  while (scanf("%d %d %d", &n, &m, &k) == 3 && n+m+k) {
    if (k == 0) {
      printf("%d\n", n*m/2);
      continue;
    }
    t = n*m + 1;
    for (i = 0; i <= t; ++i) {
      to[i].clear();
      for (j = 0; j < 6; ++j)
        c[i][j] = 0;
    }
    for (i = 0; i < n; ++i)
      for (j = 0; j < m; ++j) {
        if ((i+j)%2) {
          c[i*m+j+1][5] = 1;
          to[i*m+j+1].push_back(t);
          continue;
        }
        to[0].push_back(i*m+j+1);
        c[i*m+j+1][4] = 1;
        for (int l = 0; l < 4; ++l) {
          int x = i + dx[l], y = j + dy[l];
          if (x < 0 || x >= n || y < 0 || y >= m) continue;
          c[i*m+j+1][l] = 1;
          to[i*m+j+1].push_back(x*m+y+1);
          to[x*m+y+1].push_back(i*m+j+1);
        }
      }
    while (k--) {
      scanf("%d %d", &i, &j);
      if ((i+j)%2) c[i*m+j+1][5] = 0;
      else c[i*m+j+1][4] = 0;
    }
    printf("%d\n", flow());
  }
}
