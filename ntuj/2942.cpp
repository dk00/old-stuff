#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 3012;
struct pt {
  long long st, ed, v;
  bool operator<(pt a) const{
    if (ed != a.ed) return ed < a.ed;
    if (st != a.st) return st < a.st;
    return v < a.v;
  }
} a[N];
long long s[N];
long long find(int m, long long pos) {
  int i, j, k;
  long long l = 0;
  for (i = 0, j = m; i <= j; ) {
    k = (i + j)/2;
    if (a[k].ed > pos) j = k - 1;
    else l = s[k], i = k + 1;
  }
  return l;
}
main() {
  int i, n, C = 0;
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; ++i) {
      scanf("%*s %lld %lld %lld", &a[i].st, &a[i].ed, &a[i].v);
      a[i].ed += a[i].st;
    }
    sort(a, a+n);
    for (i = 0; i < n; ++i)
      s[i] = max((i?s[i-1]:0), find(i-1, a[i].st) + a[i].v);
    if (C++) puts("");
    printf("%lld\n", s[n-1]);
  }
}
