#include<cstdio>
const int M = 10005;
int s[M];
main() {
  int i, j, k, l, n, m, a, T, C = 1;
  for (i = 1; i < M; ++i)
    for (j = i*2; j < M; j += i)
      if (s[i] + 1 > s[j]) s[j] = s[i] + 1;
  scanf("%d", &T);
  while (T--) {  
    scanf("%d %d", &n, &m);
    for (i = a = 0; i < n; ++i) {
      for (j = k = 0; j < m; ++j) {
        scanf("%d", &l);
        k += s[l];
      }
      a ^= k;
    }
    printf("Case #%d: %s\n", C++, a?"YES":"NO");
  }
}
