#include<cstdio>
const int N = 22, M = 1000000007;
int m;
inline void cp(int a[N][N], int b[N][N]) {
  int i, j;
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      b[i][j] = a[i][j];
}
inline void mul(int s[], int a[N][N]) {
  int i, j, t[N];
  for (i = 0; i < N; ++i)
    t[i] = s[i], s[i] = 0;
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      (s[i] += t[j]*1ll*a[i][j]%M)%=M;
}
inline void sq(int a[N][N], int b[N][N]) {
  int i, j, k;
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j) {
      b[i][j] = 0;
      for (k = 0; k < N; ++k)
        (b[i][j] += a[i][k]*1ll*a[k][j]%M)%= M;
    }
}
void init(int k, int m, int s[], int a[N][N]) {
  int i, j;
  for (i = m; i < N; ++i)
    a[N-1][N-i-1] = 0;
  for (i = m; i < N; ++i) {
    s[i] = 0;
    for (j = 0; j < m; ++j)
      (s[i] += s[i-j-1]*1ll*a[0][j]%M)%= M;
  }
  for (i = 0; i < N; ++i)
    (s[i+k] += s[i])%=M;
  for (i = 0; i < N; ++i)
    a[N-1][i] = 0;
  for (i = 0; i < m; ++i) {
    (a[N-1][N-i-1] += a[0][i])%= M;
    (a[N-1][N-k-i-1] += M - a[0][i])%= M;
  }
  ++a[N-1][N-k] %= M;
  for (i = 0; i+1 < N; ++i)
    for (j = 0; j < N; ++j)
      a[i][j] = 0;
  for (i = 1; i < N; ++i)
    a[i-1][i] = 1;

/*  for (i = 0; i < N; ++i, puts(""))
    for (j = 0; j < N; ++j)
      printf("%d ", a[i][j]);
  for (i = 0; i < N; ++i)
    printf("%d ", s[i]);
  puts("");*/
}
int a[N][N], b[N][N], s[N], t[N];
main() {
  int i, j, k, T;
  long long n;
  scanf("%d", &T);
  while (T--) {
    scanf("%lld %d %d", &n, &m, &k);
    for (i = 0; i < m; ++i)
      scanf("%d", s+i);
    for (i = 0; i < m; ++i)
      scanf("%d", a[0] + i);
    init(k, m, s, a);
    if (--(n *= k) < N) {
      printf("%d\n", s[n]);
      continue;
    }
    n -= N - 1;
    for (i = 0; n > 0; ++i) {
      if (n&(1ll<<i)) {
        n ^= 1ll<<i;
        mul(s, a);
      }
      cp(a, b);
      sq(b, a);
    }
    printf("%d\n", s[N-1]);
  }
}

