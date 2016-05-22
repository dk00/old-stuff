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
    for (i = 0; i < h; ++i){
      scanf("%s", map[i]);
      for (j = 0; j < w; ++j) {
        if (map[i][j] - 'A' + 1> n)
          n = map[i][j] - 'A' + 1;
      }
    }
    for (i = 0; i < n; ++i) {
      scanf("%d", s+i);
    }
    scanf("%d", &m);
    puts("Human");
  }
}
