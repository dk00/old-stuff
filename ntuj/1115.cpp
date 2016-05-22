#include<cstdio>
const int N = 11, M = 1<<16, inf = 100, dx[] = {-1, -1, 0, 1, 1, 1, 0, -1, 0}, 
      dy[] = {0, 1, 1, 1, 0, -1, -1, -1, 0};
int un, n, u[M], s[M], t[M];
char a[N][N];
inline int count(int x) {
  int r = 0;
  while (x > 0) r += x%2, x /= 2;
  return r;
}
int go(int v) {
  if (u[v] == un) return s[v];
  u[v] = un;
  s[v] = inf;
  int i, j;
  for (i = 0; i < n; ++i)
    if (v&t[i]) {
      j = 1 + go(v&~t[i]);
      if (j < s[v]) s[v] = j;
    }
  return s[v];
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, l, m;
    for (i = m = 0; i < 10; ++i) {
      scanf("%s", a[i]);
      for (j = 0; j < 10; ++j)
        if (a[i][j] == 'e')
          a[i][j] = m++;
    }
    for (n = 0, i = 0; i < 10; ++i)
      for (j = 0; j < 10; ++j) {
        for (k = l = 0; k < 9; ++k) {
          int nx = i + dx[k], ny = j + dy[k];
          if (nx < 0 || nx > 9 || ny < 0 || ny > 9)
            continue;
          if (a[nx][ny] == 'g') break;
          if (a[nx][ny] != '.') l |= (1<<a[nx][ny]);
        }
        if (k >= 9 && l) t[n++] = l;
      }
    s[0] = 0;
    u[0] = ++un;
    for (j = 0, i = (1<<m) - 1; i >= 0; --i) {
      go(i);
      if (s[i] >= inf) continue;
      if (count(i) > count(j) || (count(i) == count(j) && s[i] < s[j]))
        j = i;
    }
    printf("%d %d\n", count(j), s[j]);
  }
}
