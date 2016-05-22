#include<cstdio>
const int N = 20000, M = 100001;
int n, m, s[N];
int go(int l, int st) {
  int i, j, k, v, r;
  for (j = -M, k = M; j <= k;) {
    v = (j + k)/2;
    for (i = 0; i < m; ++i)
      if (l + v*(i + 1) < s[st + i]) break;
    if (i < m) j = v + 1;
    else r = v, k = v - 1;
  }
  return r;
}
int main () {
  int i, j, k;
  while (scanf("%d %d", &n, &m) == 2) {
    for (i = 0; i < n + m - 1; ++i)
      scanf("%d", s + i);
    for (i = j = 0; i < n; ++i) {
      if (i > 0) printf(" ");
      j += (k = go(j, i));
      printf("%d", k);
    }
    puts("");
  }
} 
