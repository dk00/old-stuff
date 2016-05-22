#include<cstdio>
int u[5], dx[][2] = {{0, 0}, {1, 1}, {0, 1}, {1, 2}, {0, 1}, {0, -1}},
    dy[][2] = {{1, 2}, {0, 1}, {1, 1}, {0, 0}, {1, 0}, {1, 1}};
void Init(int v) {
  for (int i = 0; i < 5; ++i) {
    u[i] = v % 3;
    v /= 3;
    u[i] += u[i]/2;
  }
}
int Valid(int d, int i) {
  int x = d + dx[i][0], y = dy[i][0];
  if (!(0 <= x && x < 5 && ((1<<y)&~u[x])))
    return 0;
  x = d + dx[i][1], y = dy[i][1];
  return (0 <= x && x < 5 && ((1<<y)&~u[x]));
}
void Fill(int d, int i) {
  u[d] |= 1;
  int x = d + dx[i][0], y = dy[i][0];
  u[x] |= 1<<y;
  x = d + dx[i][1], y = dy[i][1];
  u[x] |= 1<<y;
}
const int N = 243, M = 123456789;
int count[N];
void go(int d) {
  if (d >= 5) {
    int i, j;
    for (i = 4, j = 0; i >= 0; --i)
      j = j*3 + u[i]/3;
    ++count[j];
    return;
  }
  if (u[d]&1) {
    go(d+1);
    return;
  }
  int i, j, t[5];
  for (i = 0; i < 5; ++i)
    t[i] = u[i];
  for (i = 0; i < 6; ++i)
    if (Valid(d, i)) {
      Fill(d, i);
      go(d+1);
      for (j = 0; j < 5; ++j)
        u[j] = t[j];      
    }
}
void Copy (int c0[N][N], const int c1[N][N]) {
  int i, j;
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      c0[i][j] = c1[i][j];
}
int r[N][N];
void Mul(int c0[N][N], const int c1[N][N]) {
  int i, j, k;
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      r[i][j] = 0;  
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      for (k = 0; k < N; ++k)
        r[i][k] = (r[i][k] + c0[i][j]*1ll*c1[j][k]) % M;
  Copy(c0, r);
}
void Mul0(int c0[N][N], const int c1[N][N]) {
  int i, j, k;
  for (i = 0; i < N; ++i)
    for (j = 0; j < N; ++j)
      r[i][j] = 0;  
  for (i = 0; i < 1; ++i)
    for (j = 0; j < N; ++j)
      for (k = 0; k < N; ++k)
        r[i][k] = (r[i][k] + c0[i][j]*1ll*c1[j][k]) % M;
  Copy(c0, r);
}
int c[50][N][N], a[N][N];
main() {
  int i, j, n, T;
  for (i = 0; i < N; ++i) {
    Init(i);
    go(0);
    for (j = 0; j < N; ++j)
      c[0][i][j] = count[j], count[j] = 0;
  }
  for (i = 1; i < 50; ++i) {
    Copy(c[i], c[i-1]);
    Mul(c[i], c[i-1]);
  }
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    if (n % 3) {
      puts("0");
      continue;
    }
    for (i = 0; i < N; ++i)
      for (j = 0; j < N; ++j)
        a[i][j] = 0;
    a[0][0] = 1;
    for (i = 0; (1<<i) <= n; ++i)
      if ((1<<i)&n)
        Mul0(a, c[i]);
    printf("%d\n", a[0][0]);
  }
}
