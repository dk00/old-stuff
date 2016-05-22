#include<queue>
#include<cstdio>
using namespace std;
const int N = 11111, M = 27;
int n, m, p[N], s[N][M], t[M][M], t1[M][M], u[N];
char a[N][M];
void go(int i) {
  int j, tmp[M];
  for (j = 0; j < m; ++j) tmp[j] = 0;
  for (j = 0; j < m; ++j)
    if (tmp[a[i][j]-'A'] < s[i][j] + 1)
      tmp[a[i][j]-'A'] = s[i][j] + 1;
  for (j = 0; j < m; ++j) s[p[i]][j] += tmp[j];  
}
void next(int v) {
  int i, j, k;
  for (i = 0; i < m; ++i)
    for (j = 0; j < m; ++j)
      t1[i][j] = t[i][j], t[i][j] = 0;
  for (i = 0; i < m; ++i)
    for (j = 0; j < m; ++j) {
      if (t1[i][j] < 0) continue;
      for (k = 0; k < m; ++k)
        if (t[i][k] < t1[i][j] + (k == a[v][j] - 'A')) {
          printf("%d %d %d %d\n", i, j, k, t1[i][j]);
          t[i][k] = t1[i][j] + (k == a[v][j] - 'A');
        }
    }
  for (i = 0; i < m; ++i)
    for (j = 0; j < m; ++j)
      t[i][j] += s[v][j];
  for (i = 0; i < m; ++i, puts(""))
    for (j = 0; j < m; ++j)
      printf("%d ", t[i][j]);
  puts("");
  u[v] = 0;
}
main() {
  int T, i, j, k, sum;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i) u[i] = 0;
    for (i = 0; i < n; ++i) {
      scanf("%d %s", p+i, a[i]);
      ++u[--p[i]];
    }
    queue<int> Q;
    for (i = 0; i < n; ++i) {
      for (j = 0; j < m; ++j) s[i][j] = 0;
      if (u[i] == 0) Q.push(i);
    }
    while (!Q.empty()) {
      i = Q.front(), Q.pop();
      go(i);
      if (!--u[p[i]]) Q.push(p[i]);
    }
    for (i = sum = 0; i < n; ++i) {
      if (!u[i]) continue;
      for (j = 0; j < m; ++j)
        for (k = 0; k < m; ++k)
          t[j][k] = -1 + (j == k);
/*      for (j = 0; j < m; ++j)
        t[j][a[i][j]-'A'] = 1;*/
      for (k = p[i]; k != i; k = p[k])
        next(k);
      next(i);
      for (j = k = 0; j < m; ++j)
        if (t[j][j] > t[k][k]) k = j;
      printf("%d\n", t[k][k]);
      sum += t[k][k];
    }
    printf("%d\n", sum);
  }
}
