#include<cstdio>
const int N = 1111;
int m, s[N], t[N];
void go(int v) {
  if (v > t[m-1]) {
    t[m++] = v;
    return;
  }
  int i, j, k;
  i = 0, j = m - 1;
  while (i <= j) {
    k = (i + j)/2;
    if (v <= t[k] && (k == 0 || v > t[k - 1])) break;
    if (v > t[k]) i = k + 1;
    else j = k - 1;
  }
  t[k] = v;
}
main() {
  int i, j, k, n, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0;i < n; ++i) {
      scanf("%d", s + i);
      t[i] = -1;
    }
    t[0] = s[0];
    m = !!n;
    for (i = 1; i < n; ++i)
      go(s[i]);
    printf("%d\n", m);
  }
}
