#include<set>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int n, m;
set<long long> H;
long long s[377777];
long long Gen(int a, int b) {
  long long i, j = 0;
  for (i = 1ll << b; i > 0; i >>= 1){
    j *= 10;
    if (i&a) j += 7;
    else j += 4;
  }
  return j;
}
inline int Count(long long a) {
  int i, j, k, l;
  for (i = 0, j = m - 1; i <= j;) {
    k = (i + j)/2;
    if (s[k] > a) j = k - 1;
    else l = k, i = k + 1;
  }
  return l;
}
void go(long long v, int i) {
  if (i >= n || v > 1000000000000ll || H.count(v)) return;
  s[m++] = v;
  H.insert(v);
  for (;s[i] <= 1000000000000ll/v + 1 &&  i < n; ++i)
    go(v*s[i], i);
}
main() {
  int T;
  long long i, j, k;
  for (k = m = 0; k < 12; ++k)
    for (i = 0; i < 2<<k; ++i) {
      j = Gen(i, k);
      s[m++] = j;
    }
  n = m;
  go(1, 0);
  sort(s, s+m);
  for (i = j = 1; i < m; ++i)
    if (s[i] != s[j-1]) s[j++] = s[i];
  m = j;
  s[0] = -1;
  scanf("%d", &T);
  while (T--) {
    scanf("%lld %lld", &i, &j);
    printf("%d\n", Count(j) - Count(i-1));
  }
}
