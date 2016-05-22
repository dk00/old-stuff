#include<queue>
#include<cstdio>
using namespace std;
const int N = 900, formation[][8] = {
  {1, 2, 1, 1, 2, 1, 1, 2},
  {1, 2, 1, 1, 3, 1, 1, 1},
  {1, 2, 1, 1, 3, 0, 0, 3},
  {1, 3, 0, 0, 3, 1, 1, 2},
  {1, 3, 0, 0, 4, 1, 1, 1},
  {1, 3, 1, 1, 3, 0, 0, 2},
  {1, 4, 1, 1, 3, 0, 0, 1}
};
const char label[][6] = {"A", "B", "C", "D", "E", "F", "China"};
int t, p[N], d[N], u[N], cap[N][N], cost[N][N];
void Init() {
  int i, j;
  for (i = 0; i <= t; ++i)
    for (j = 0; j <= t; ++j)
      cost[i][j] = 0;
}
void Init(int n, const int F[]) {
  int i, j;
  for (i = 0; i <= t; ++i)
    for (j = 0; j <= t; ++j)
      cap[i][j] = 0;
  for (i = 0; i < n; ++i) {
    cap[0][i+1] = 1;
    for (j = 0; j < 8; ++j)
      cap[i+1][n+j+1] = 1;
  }
  for (j = 0; j < 8; ++j)
    cap[n+j+1][t] = F[j];
}
inline int Cost(int a, int b) {
  return cost[a][b] - cost[b][a];
}
inline int sp() {
  int i, j, k;
  for (i = 0; i <= t; ++i)
    d[i] = -9999, u[i] = 0;
  d[0] = 0;
  queue<int> Q;
  Q.push(0);
  while (!Q.empty()) {
    i = Q.front(), Q.pop();
    u[i] = 0;
    for (j = 0; j <= t; ++j) {
      if (cap[i][j] < 1) continue;
      k = d[i] + Cost(i, j);
      if (k > d[j]) {
        d[j] = k, p[j] = i;
        if (!u[j])
          u[j] = 1, Q.push(j);
      }
    }
  }
  if (d[t] <= 0) return -1;
  for (i = t; i; i = p[i])
    --cap[p[i]][i], ++cap[i][p[i]];
  return d[t];
}
int flow() {
  int f = 0, tmp;
  while (1) {
    tmp = sp();
    if (tmp < 0) return f;
    f += tmp;
  }
}
int sc[9];
main() {
  int i, j, k, l, n;
  while (scanf("%d", &n) == 1 && n) {
    t = 9 + n;
    Init();
    for (i = 0; i < n; ++i) {
      scanf("%*s");
      for (j = 0; j < 8; ++j)
        scanf("%d", &cost[i+1][n+j+1]);
    }
    for (i = j = 0; i < 7; ++i) {
      Init(n, formation[i]);
      sc[i] = flow();
      if (sc[i] > sc[j]) j = i;
    }
    for (i = 0; i < 7; ++i)
      if (sc[i] == sc[j])
        printf("Formation %s has the highest points %d.\n", label[i], sc[i]);
    puts("");
  }
}
