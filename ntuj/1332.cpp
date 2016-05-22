#include<cstdio>
const int N = 4022;
char s[N], t[N];
main() {
  int i, j, k, n, m;
  while (scanf("%d %d", &n, &m) && n+m) {
    for (i = 0; i < n; ++i) {
      scanf("%d", &k);
      s[i] = k;
    }
    for (j = 0; j < m; ++j) {
      scanf("%d", &k);
      t[j] = k;
    }
    for (i = 0; i < n * 2; ++i) {
      if (s[i%n] == 0) continue;
      for (j = 0; j < m; ++j)
        s[(i+j)%n] ^= t[j];
    }
    for (i = 0; i < n; ++i)
      if (s[i] > 0) break;
    if (i < n) puts("NO");
    else puts("YES");
    for (i = 0; i < n; ++i)
      printf("%d ", s[i]);
    puts("");
  }
}
/*
 0 1 0 1 1 0 1 0 1 1

 1
 
 
 
 
 
 */
