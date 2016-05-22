#include<queue>
#include<cstdio>
using namespace std;
const int N = 2012, M = 2012;
char map[M][M];
int t, n, m, un, u[M][M], id[M][M], c[N][N], p[N], d[N];
void draw(const char a[],int x, int y, int dx, int dy, int z) {
  int i;
  for (i = 0; a[i]; ++i, x += dx, y += dy) {
    if (u[x][y] != un) {
      u[x][y] = un;
      id[x][y] = z;
      map[x][y] = a[i];
      continue;
    }
    if (map[x][y] != a[i])
      c[id[x][y]+1][z+n+1] = 1;
  }
}
void sp() {
  int i, j;
  for (i = 0; i <= t; ++i)
    d[i] = t+1;
  queue<int> Q;
  Q.push(0);
  d[0] = 0;
  while (!Q.empty() && d[t] >= t+1) {
    i = Q.front();
    Q.pop();
    for (j = 1; j <= t; ++j)
      if (c[i][j] && d[i] + 1 < d[j]) {
        d[j] = d[i] + 1;
        Q.push(j);
      }
  }
}
int go(int v) {
  if (v == t) return 1;
  if (p[v]) return 0;
  p[v] = 1;
  int i, sum = 0;
  for (i = 1; i <= t; ++i)
    if (c[v][i]-- && go(i)) {
      ++c[i][v];
      ++sum;
      if(v) break;
    }
    else ++c[v][i];
  return sum;
}
int flow() {
  int i, f = 0;
  while (1) {
    sp();
    if (d[t] >= t+1) break;
    for (i = 0; i <= t; ++i) p[i] = 0;
    f += go(0);
  }
  return f;
}
char tmp[M];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, x, y;
    scanf("%d %d", &n, &m);
    t = n + m + 1;
    for (i = 0; i <= t; ++i)
      for (j = 0; j <= t; ++j)
        c[i][j] = 0;
    ++un;
    for (i = 0; i < n; ++i) {
      c[0][i+1] = 1;
      scanf("%d %d", &x, &y);
      scanf("%s", tmp);
      draw(tmp, x, y, 1, 0, i);
    }
    for (j = 0; j < m; ++j) {
      c[j+n+1][t] = 1;
      scanf("%d %d", &x, &y);
      scanf("%s", tmp);
      draw(tmp, x, y, 0, 1, j);
    }
    printf("%d\n", n + m - flow());
  }
}
