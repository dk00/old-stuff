#include<cstdio>
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0 -1};
char map[999][999];
int c[999][999], dg[999], s[999], send[999];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, l, x, y, h, w, n, m;
    scanf("%d %d", &h, &w);
    for (i = 0; i < 26; ++i)
      for (j = 0; j < 26; ++j)
        c[i][j] = 0;
    for (i = n = 0; i < h; ++i) {
      scanf("%s", map[i]);
      for (j = 0; j < w; ++j) {
        if (map[i][j] - 'A' + 1 > n)
          n = map[i][j] - 'A' + 1;
      }
    }
    for (i = 0; i < h; ++i)
      for (j = 0; j < w; ++j)
        for (k = 0; k < 4; ++k) {
          x = i + dx[k], y = j + dy[k];
          if (x < 0 || x >= h || y < 0 || y >= w) continue;
          c[map[i][j]-'A'][map[x][y]-'A'] = 1;
          c[map[x][y]-'A'][map[i][j]-'A'] = 1;
        }
    for (i = 0; i < n; ++i) {
      scanf("%d", s+i);
      c[i][i] = 0;
      for (j = 0, dg[i] = 1; j < n; ++j)
        if (c[i][j]) ++dg[i];
      send[i] = s[i]/dg[i];
    }
    scanf("%d", &m);
    for (i = 0; i < n; ++i) {
      for (j = 0; j < n; ++j) {
        if (s[j] < 0) continue;
        for (k = 0, l = s[j]; k < n; ++k) {
          if (s[k] > 0)
            l += c[j][k]*send[k];
        }
        if (m > l) break;
      }
      if (j >= n) break;
      s[j] = -1;
      for (k = 0; k < n; ++k)
        if (c[j][k]) s[k] -= send[k];
    }
    if (i >= n) puts("Saruman");
    else puts("Human");
  }
}
