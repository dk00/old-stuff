#include<cstdio>
const int N = 55555, M = 10007;
int n, a[N], s[2][N];
int go(int lim) {
  int i, j, k;
  for (i = j = k = 0; i < n; ++i) {
    if (j + a[i] > lim) {
      ++k;
      j = 0;
    }
    j += a[i];
  }
  return k + 1;
}
inline int& S(int x, int y) {
  static int null = 0;
  if (y < 0) return null;
  return s[(x)%2][y];
}
main() {
  int i, j, k, l, m, max;
  while (scanf("%d %d", &n, &m) == 2) {
    for (i = j = k = 0; i < n; ++i) {
      scanf("%d", a+i);
      j += a[i];
      if (a[i] > k) k = a[i];
      s[0][i] = s[1][i] = 0;
    }
    max = j;
    for (i = k; i <= j;) {
      k = (i + j)/2;
      l = go(k);
      if (l > m) i = k + 1;
      else {
        max = k;
        j = k - 1;
      }
    }
    for (i = l = 0; i < n; ++i) {
      if ((l += a[i]) > max) break;
      s[0][i] = 1;
    }
#define Add(a, b) ((a) += (M + (b))) %= M
    int tmp, sum = s[0][n-1];
    for (k = 1; k < m; ++k) {
      for (i = 0 ;i < n; ++i)
        S(k, i) = 0;
      for (i = j = l = tmp = 0; j < n; ++j) {
        l += a[j];
        Add(tmp, S(k-1, j-1));
        while (l > max) {
          Add(tmp, -S(k-1, i-1));
          l -= a[i++];
        }
        Add(S(k, j), tmp);
      }
      Add(sum, S(k, n-1));
    }
    printf("%d %d\n", max, sum);
  }
}
