#include<cstdio>
const int N = 20;
char s[9][N][N], t[9][N][N];
int n, m, c[9][9], u[9];
int fit(char a[N][N], char b[N][N]) {
  int i, j;
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j)
      if (b[i][j] == '0' && a[i][j] == '1') return 0;
  return 1;
}
int go(int v) {
  if (v >= 3) return 1;
  for (int i = 0; i < 3; ++i) {
    if (u[i]) continue;
    u[i] = 1;
    if (c[v][i] && go(v+1)) {
      u[i] = 0;
      return 1;
    }
    u[i] = 0;
  }
  return 0;
}
main() {
  int T;
  int i, j;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < 3; ++i)
      for (j = 0; j < n; ++j)
        scanf("%s", s[i][j]);
    for (i = 0; i < 3; ++i)
      for (j = 0; j < n; ++j)
        scanf("%s", t[i][j]);
    for (i = 0; i < 3; ++i)
      for (j = 0; j < 3; ++j)
        c[i][j] = fit(s[i], t[j]);
    puts(go(0)?"YES":"NO");
  }
}
