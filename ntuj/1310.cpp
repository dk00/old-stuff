#include<cstdio>
const long long D = 1000000000ll;
const int N = 2222;
int m, s[N];
long long t[N];
void mul(int v) {
  int i;
  for (i = 0; i < m; ++i)
    t[i] *= v;
  for (i = 0; i < m; ++i) {    
    t[i+1] += t[i]/D;
    t[i] %= D;
  }
  if (t[m] > 0) ++m;
}
main() {
  int i, j, n, T, pos;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = j = m = pos = 0; i < n; ++i) {
      scanf("%d", s+i);
      if (s[i] < 0) {
        if (!m++ || s[i] > s[j])
          j = i;
      }
      if (s[i] > 0) pos = 1;
    }
    if (pos < 1) {
      if (m == 1 && n == 1) {
        printf("%d\n", s[j]);
        continue;
      }
      if (m <= 1 && n > 0) {
        puts("0");
        continue;
      }
    }
    if (m > 0 && m%2) s[j] = 1;
    t[0] = 1;
    m = 1;
    for (i = 0; i < n; ++i) {
      if (s[i] < 0) s[i] = -s[i];
      if (s[i]) mul(s[i]);
    }
    printf("%lld", t[m-1]);
    for (i = m-2; i >= 0; --i)
      printf("%09lld", t[i]);
    puts("");
    while(m--) t[m] = 0;
  }
}
