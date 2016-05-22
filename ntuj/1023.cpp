#include<cmath>
#include<cstdio>
const int N = 2, M = 1000001;
int st, len, un, m, u[M], p[M];
inline void Init(int r[][N]) {
  r[0][0] = 0;
  r[0][1] = r[1][0] = r[1][1] = 1;
}
int Pow(int n, int k) {
  if (k <= 0) return 1;
  if (k%2) return n*1ll*Pow(n, k-1)%m;
  n = Pow(n, k/2);
  return n*1ll*n%m;
}
void Getlen(int a, int m) {
  ++un;
  int i, j, k, b;
  k = (int)ceil(sqrt(m));
  b = Pow(a, k);
  for (i = 0, j = 1 % m; i < k; ++i) {
    if (u[j] == un) break;
    u[j] = un;
    p[j] = i;
    j = j*1ll*a % m;
  }
  if (i < k && u[j] == un) {
    st = p[j];
    len = i - p[j];
    return;
  }
  for (; i < m*2; i += k) {
    if (u[j] == un) break;
    j = j*1ll*b % m;
  }
  if (i < m*2 && u[j] == un) {
    st = p[j];
    len = i - p[j];
    return;
  }
  for (i = k, j = b; i < m; ++i) {
    if (u[j] == un) break;
    u[j] = un;
    p[j] = i;
    j = j*1ll*a % m;
  }
  st = p[j];
  len = i - p[j];  
}
inline int fix(long long x) {
  if (x <= st) return x;
  return st + (x - st) % len;
}
void Mul(int a[][N], int b[][N]) {
  int i, j, k, tmp[N][N];
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      tmp[i][j] = 0;  
  for (i = 0; i < N; ++i)
    for (k = 0; k < N; ++k)
      for (j = 0; j < N; ++j) 
        tmp[i][j] = fix(tmp[i][j] + a[i][k]*1ll*b[k][j]);
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      a[i][j] = tmp[i][j];
}
void calc(int x, int n, int q[][N]) {
  Getlen(x, m);
  int r[N][N];
  Init(r);
  q[0][0] = q[1][1] = 1;
  q[0][1] = q[1][0] = 0;
  for (int i = 1; i <= n; i <<= 1) {
    if (n&i) Mul(q, r);
    Mul(r, r);
  }
}
main() {
  int T, C = 1;
  scanf("%d", &T);
  while (T--) {
    int i, a, b, n, q[N][N];
    scanf("%d %d %d %d", &a, &b, &m, &n);
    --n;
    calc(a, n, q);
    a = Pow(a, q[0][0]);
    calc(b, n, q);
    b = Pow(b, q[0][1]);
    printf("Case #%d: %d\n", C++, a*1ll*b % m);
  }
}
