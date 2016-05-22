#include<queue>
#include<cstdio>
using namespace std;
const int N = 1005, inf = 2000000000;
int n, n0, t, sum, p[N], d[N], u[N], cap[N][N], cost[N][N], c[N][N];
inline int Cost(int a, int b) {
  return cost[a][b] - cost[b][a];
}
inline int sp() {
  int i, j, k;
  for (i = 0; i <= t; ++i)
    d[i] = inf, u[i] = 0;
  d[0] = 0;
  queue<int> Q;
  Q.push(0);
  while (!Q.empty()) {
    i = Q.front(), Q.pop();
    u[i] = 0;
    for (j = 0; j <= t; ++j) {
      if (cap[i][j] < 1) continue;
      k = d[i] + Cost(i, j);
      if (k < d[j]) {
        d[j] = k, p[j] = i;
        if (!u[j])
          u[j] = 1, Q.push(j);
      }
    }
  }
  if (d[t] >= inf) return -1;
  for (i = t; i; i = p[i])
    --cap[p[i]][i], ++cap[i][p[i]];
  return d[t];
}
int flow() {
  int i, j, f = 0;
  for (i = 0; i < n0; ++i) {
    j = sp();
    if (j < 0) return -1;
    f += j;
  }
  return sum - f;
}
int s[8], g[8];
void Init() {
  int i, j;
  for (i = 0; i <= t; ++i)
    for (j = 0; j <= t; ++j)
      cap[i][j] = 0;
  for (i = 0; i < n; ++i) {
    cap[i+1][i+n+1] = 1;
    for (j = 0; j < n; ++j)
      if (c[i][j])
        cap[i+n+1][j+1] = 1;
  }
  for (i = 0; i < n0*2; ++i) {
    if (s[i]) cap[0][g[i]+1] = 1;
    else cap[g[i]+n+1][t] = 1;
  }
}
int go(int r, int i) {
  if (r >= n0) {
    Init();
    return flow();
  }
  int j, k = -1;
  for (; i+1 < n0*2; ++i) {
    s[i] = 1;
    j = go(r+1, i+1);
    if (j > k) k = j;
    s[i] = 0;
  }
  return k;
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, m;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        c[i][j] = 0;
    while (m--) {
      scanf("%d %d", &i, &j);
      c[i][j] = c[j][i] = 1;
    }
    scanf("%d", &n0);
    for (i = 0; i < n0*2; ++i)
      scanf("%d", &g[i]);
    t = n*2 + 1;
    for (i = 0; i <= t; ++i)
      for (j = 0; j <= t; ++j)
        cost[i][j] = 0;
    for (i = sum = 0; i < n; ++i) {
      scanf("%d", &cost[i+1][i+n+1]);
      sum += cost[i+1][i+n+1];
    }
    s[0] = 1;
    printf("%d\n", go(1, 1));
  }
}
