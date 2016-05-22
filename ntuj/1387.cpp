#include<cstdio>
const int N = 111;
int m, c[N][11], u[N], s[111][11];
inline int create() {
  for (int i = 0; i < 10; ++i)
    c[m][i] = 0;
  u[m] = 1;
  return m++;
}
void go(char a[]) {
  int i, j;
  for (i = j = 0; a[i]; ++i) {
    if (!c[j][a[i]-'0'])
      c[j][a[i]-'0'] = create();
    j = c[j][a[i]-'0'];
  }
  for (i = 0; i < 10; ++i)
    c[j][i] = j;
  u[j] = 0;
}
void link(char a[]) {
  int i, j, k, l, p;
  for (i = j = 0; a[i]; ++i) {
    j = c[j][a[i]-'0'];
    for (k = 1; k - 1 <= i; ++k) {
      for (p = l = 0; l + k <= i; ++l)
        p = c[p][a[l+k]-'0'];
      for (l = 0; l < 10; ++l)
        if (!c[j][l] && c[p][l])
          c[j][l] = c[p][l];
    }
  }
}
int calc(int i, int n) {
  int j, k, sum = 0;
  for (k = i; k < n; ++k)
    for (j = 0; j < m; ++j)
      s[k][j] = 0;
  for (; i < n; ++i) {
    for (j = 0; j < m; ++j)
      for (k = 0; k < 10; ++k)
        s[i][c[j][k]] += s[i-1][j];
  }
  for (j = 0; j < m; ++j)
    sum += u[j]*s[n-1][j];
  return sum;
}
void get(int a) {
  int i, j, k, n, sum, prev;
  for (i = 0; i < 100; ++i)
    for (j = 0; j < 10; ++j)
      s[i][j] = 0;
  for (i = 1; i < 10; ++i)
    ++s[1][c[0][i]];

  for (i = 1; ; ++i) {
    sum = 0;
    for (j = 0; j < m; ++j)
      sum += s[i][j]*u[j];
    if (sum >= a) break;
    a -= sum;
    for (j = 0; j < m; ++j)
      for (k = 0; k < 10; ++k)
        s[i+1][c[j][k]] += s[i][j];
  }
  n = i;
  for (j = 0; j < m; ++j)
    s[0][j] = 0;
  char tmp[111];
  for (i = 0; i < n; ++i) {
    for (j = !i; j < 10; ++j) {
      ++s[i][c[0][j]];
      k = calc(i+1, n);
      if (k >= a) break;
      prev = k;
    }
    a -= prev;
    tmp[i] = '0' + j;
  }
  tmp[i] = 0;
  printf(tmp);
}
char op[11][11];
main() {
  int i, j, n, T;
  char tmp[11];
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    m = 1;
    for (i = 0; i < 10; ++i)
      c[0][i] = 0;
    u[0] = 1;
    for (i = 0; i < n; ++i) {
      scanf("%s", op[i]);
      go(op[i]);
    }
    for (i = 0; i < n; ++i)
      link(op[i]);
    scanf("%d", &j);
    while (j--) {
      scanf("%d", &i);
      get(i);
      /*if (j) printf(" ");
      else */puts("");
    }
  }
}
