#include<queue>
#include<cstdio>
using namespace std;
const int N = 11111, M = 27;
int n, m, p[N], s[N][M], t[N][M], u[N];
char a[N][M];
inline void go(int i, int x) {
  int j, k, tmp[M];
  k = x;
  if (x < 0)
    for (j = 0, k = 0; j < m; ++j)
      if (s[i][k] < s[i][j]) k = j;
  for (j = 0; j < m; ++j) tmp[j] = s[i][k];
  for (j = 0; j < m; ++j)
    if ((x < 0 || j == x) && tmp[a[i][j]-'A'] < s[i][j] + 1)
      tmp[a[i][j]-'A'] = s[i][j] + 1;
  for (j = 0; j < m; ++j) s[p[i]][j] += tmp[j];  
}

main() {
  int T, i, j, k, l, sum, Max;
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
      go(i, -1);
      if (!--u[p[i]]) Q.push(p[i]);
    }
    for (i = sum = 0; i < n; ++i) {
      if (!u[i]) continue;
      for (k = p[i]; k != i; k = p[k])
        for (l = 0; l < m; ++l)
          t[k][l] = s[k][l];
      for (j = Max = 0; j < m; ++j) {
        for (k = p[i]; k != i; k = p[k])
          for (l = 0; l < m; ++l)
            s[k][l] = t[k][l];
        for (k = i; p[k] != i; k = p[k])
          go(k, k == i?j: -1);
        if (k == i) {
          if (Max < s[k][j] + (j == a[k][j] - 'A'))
            Max = s[k][j] + (j == a[k][j] - 'A');
          continue;
        }
        for (l = 0; l < m; ++l)
          if (Max < s[k][l] + (j == a[k][l] - 'A'))
            Max = s[k][l] + (j == a[k][l] - 'A');
      }
      for (k = p[i]; k != i; k = p[k]) u[k] = 0;
      u[i] = 0;
      sum += Max;
    }
    printf("%d\n", sum);
  }
}
