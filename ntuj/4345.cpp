#include<cstdio>
#include<cstring>
const int N = 1005;
int s[101][N], t[N];
char tmp[N];
inline int Sum(int a, int b) {return t[b] - (a?t[a-1]:0) + (b-a > 0?b-a:0); }
inline int tri(int v) {return v*v*v; }
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, l, n, m;
    scanf("%d %d", &l, &m);
    gets(tmp);
    for (n = 0; gets(tmp) && tmp[0];) {
      char *p = strtok(tmp, " ");
      while (p) {
        t[n++] = strlen(p);
        p = strtok(NULL, " ");
      }
    }
    for (i = 1; i < n; ++i)
      t[i] += t[i-1];
    for (i = 0; i < n; ++i) {
      if (Sum(0, i) <= m) s[0][i] = tri(m - Sum(0, i));
      else s[0][i] = -1;
    }
    for (i = 1; i < l; ++i)
      for (j = 0; j < n; ++j) {
        s[i][j] = -1;
        for (k = 0; k <= j; ++k) {
          if (s[i-1][k] < 0) continue;
          int tmp = Sum(k+1, j);
          if (tmp > m) continue;
          tmp = tri(m - tmp);
          if (s[i-1][k] + tmp < s[i][j] || s[i][j] < 0)
            s[i][j] = s[i-1][k] + tmp;
        }
      }
    for (i = 0; i < l; ++i, puts(""))
      for (j = 0; j < n; ++j)
        printf("%d ", s[i][j]);
    printf("%d\n", s[i-1][n-1]);
  }
}
