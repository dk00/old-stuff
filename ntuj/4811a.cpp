#include<cstdio>
#include<cstring>
const int N = 1000007;
void rsort(int x[], int t0[], int t1[], int n, int m) {
  static int num[N];
  int i;
  for (i = 0; i <= m; ++i) num[i] = 0;
  for (i = 0; i < n; ++i) ++num[x[t0[i]]+1];
  for (i = 1; i <= m; ++i) num[i] += num[i-1];
  for (i = 0; i < n; ++i) t1[num[x[t0[i]]]++] = t0[i];
}
int x[N], t[N], d[N];
void SA(const char text[], int t[], int n, int m) {
  int i, j, k;
  int *tmp = d;
  static int s[N*2];
  for (i = 0; i < n; ++i) s[i] = text[i], t[i] = i;
  for (i = t[n] = n; i < n*2; ++i) s[i] = 0;
  for (i = 1; i < n; i *= 2) {
    rsort(s+i, t ,tmp, n, m);
    rsort(s, tmp, t, n, m);
    for (j = 0; j < n; ++j) tmp[j] = s[j];
    for (j = 0, m = 1; j < n; ++j) {
      s[t[j]] = m;
      if (tmp[t[j]] != tmp[t[j+1]] || tmp[t[j]+i] != tmp[t[j+1]+i]) ++m;
    }
  }
}
void depth(const char s[], const int t[], int d[], int n) {
  int i, j, k;
  for (i = 0; i < n; ++i) x[t[i]] = i;
  for (i = j = 0; i < n; ++i) {
    if (x[i] == n-1) {
      j = d[x[i]] = 0;
      continue;
    }
    k = t[x[i]+1];
    while (s[i+j] == s[k+j]) ++j;
    d[x[i]] = j;
    if (j > 0) --j;
  }
}
char tx[N];
main() {
  int i, n, m;
  while (scanf("%d", &n) == 1 && n) {
    for (i = m = 0; i < n; ++i) {
      scanf("%s", tx + m);
      m += strlen(tx+m);
      tx[m++] = '}';
    }
    tx[m] = 0;
    SA(tx, t, m, 127);
    depth(tx, t, d, m);
    for (i = 0; i < m; ++i)
      printf("%d %s\n", d[i], tx+t[i]);
    
  }
}

