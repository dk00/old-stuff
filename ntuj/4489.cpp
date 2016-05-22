#include<cstdio>
const int N = 305;
int p[N], h[N], c[N], s[1<<17];
inline int& S(int k, int c, int a, int b) {
  return s[((k&1)<<16)|(c<<15)|(a<<6)|b];
}
inline void S(int k, int c, int a, int b, int v) {
  int &x = s[((k&1)<<16)|(c<<15)|(a<<6)|b];
  if (v > x) x = v;
}
main() {
  int i, j, k, n, v0, v1, C = 1;
  while (scanf("%d %d %d", &v0, &v1, &n) == 3 && v0+v1+n) {
    for (i = 0; i < n; ++i)
      scanf("%d %d %d", p+i, h+i, c+i);
    for (i = 0; i <= v0; ++i)
      for (j = 0; j <= v1; ++j)
        S(0, 0, i, j) = S(0, 1, i, j) = 0;
    for (k = 0; k < n; ++k) {
      if (c[k])
        for (i = 0; i <= v0; ++i)
          for (j = 0; j <= v1; ++j)
            S(k+1, 0, i, j) = S(k+1, 1, i, j) = -1;
      else
        for (i = 0; i <= v0; ++i)
          for (j = 0; j <= v1; ++j) {
            S(k+1, 0, i, j) = S(k, 0, i, j);
            S(k+1, 1, i, j) = S(k, 1, i, j);
          }
      for (i = 0; i <= v0; ++i)
        for (j = 0; j <= v1; ++j) {
          int a = S(k, 0, i, j);
          if (a >= 0) {
            a += h[k];
            S(k+1, 1, i, j, a);
            if (i+p[k] <= v0) S(k+1, 0, i+p[k], j, a);
            if (j+p[k] <= v1) S(k+1, 0, i, j+p[k], a);
          }
          a = S(k, 1, i, j);
          if (a >= 0) {
            a += h[k];
            if (i+p[k] <= v0) S(k+1, 1, i+v0, j, a);
            if (j+p[k] <= v1) S(k+1, 1, i, j+v1, a);
          }
        }
    }
    for (k = -1, i = 0; i <= v0; ++i)
      for (j = 0; j <= v1; ++j)
        if (S(n, 1, i, j) > k)
          k = S(n, 1, i, j);
    printf("Case %d: %d\n", C++, k);
  }
}
