#include<cstdio>
const int N = 102;
int s[N][N], t[N][N];
main() {
  int i, j, k, l, n, m, x, T, C = 1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        scanf("%d", &s[i][j]);
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        scanf("%d", &t[i][j]);
    printf("Case %d: ", C++);
    for (i = k = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        if (s[i][j] != t[i][j]) ++k;

    if (k == 0) {
      puts("0");
      continue;
    }
    for (i = k = 0; i < n; ++i)
      for (j = i + 1; j < n; ++j)
        if (t[j][i] != t[i][j]) ++k;
    if (k == 0) {
      puts("-1");
      continue;
    }/*
    for (i = k = 0; i < n; ++i)
      for (j = i + 1; j < n; ++j)
        if (s[i][j] != s[j][i]) ++k;
    if (k == 0) {
      puts("-1");
      continue;
    }*/
    for (i = l = 0; i < n; ++i)
      for (j = i + 1; j < n; ++j)
        if (s[i][j] != t[i][j] && s[j][i] != t[j][i] && t[i][j] == s[j][i] && t[j][i] == s[i][j])
          ++l;
    if (k == 1 && l == 1) {
      x = 1;
      if (m == 2) {
        if (n <= 2) {
          puts("-1");
          continue;
        }
        x = 2;
      }
    }
    else x = 0;
    for (i = k = 0; i < n; ++i)
      for (j = 0; j < n; ++j)
        if (s[i][j] != t[i][j]) ++k;
    printf("%d\n", k + x);
  }
}
