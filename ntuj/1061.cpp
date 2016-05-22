#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int D = 20, N = 1<<D;
int s[N], t[N];
int BitMod(int x, int s[]) {
  int i, n;
  s[0] = x;
  for (i = n = 1; i < N; i *= 2)
    if (i&~x) s[n++] = x |= i;
  return n;
}
int BitQuery(int x, int s[]) {
  int i, n;
  s[0] = x;
  for (i = n = 1; i <= x; i *= 2)
    if (i&~x) s[n++] = x -= i;
  return n;
}
int Add(int x) {
  int i, k, m, sum, r = 0;
  m = BitQuery(x, key);
  for (k = sum = 0; k < m; ++k)
    sum += t[key[k]];
  if (sum == 0) r = 1;
  m = BitMod(x, key);
  for (k = 0; k < m; ++k)
    ++t[key[k]];
  return r;
}
int Sub(int x) {
  int i, k, m, sum, r = 0;
  m = BitQuery(x, key);
  for (k = sum = 0; k < m; ++k)
    sum += t[key[k]];
  if (sum == 1) r = -1;
  m = BitMod(x, key);
  for (k = 0; k < m; ++k)
    --t[key[k]];
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, a, n, m, sum, key[99];
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
      scanf("%d", s+i), t[i] = s[i];
    sort(t, t+n);
    map<int, int> H;
    for (i = 0; i < n; ++i)
      if (!i || t[i] != t[i-1])
        H[t[i]] = H.size() - 1;
    for (i = 0; i < n; ++i)
      s[i] = H[s[i]];
    for (i = 0; i < N; ++i)
      t[i] = 0;
    for (i = 1, j = a = 0; i*2 < n; ++i) {
      j += Sub(s[i*2-1]);
      j += Sub(s[i*2-2]);
      j += Add(s[i]);
      j += Add(s[i]);
      if (j == 0) a = i;
    }
    printf("%d\n", a);
  }
}
