#include<queue>
#include<cstdio>
using namespace std;
const int N = 9999;
int a[N], t[N];
long long s[N];
struct pt {
  double n;
  int i, t;
  bool operator<(pt a) const {
    if (t != a.t) return t > a.t;
    return n < a.n;
  }
};
main() {
  int i, j, p, v;
  long long l, n;
  while (scanf("%lld %d %d", &n, &p, &v) == 3) {
    s[0] = 1;
    t[0] = 0;
    priority_queue<pt> H;
    for (i = 1, l = 2; l <= n; ++i) {
      j = 0;
      while (!H.empty()) {
        pt x = H.top();
        H.pop();
        j = x.i;
        if (++a[j] <= j)
          H.push((pt){s[j]*1.0*s[a[j]], j, t[j] + t[a[j]]});
        if (x.t < t[i-1])
          continue;
        if (x.t == t[i-1]) {
          if (x.n >= s[i-1])
            s[i-1] = s[j]*s[a[j]-1];
        } else break;
      }
      printf("%lld %lld %d %d\n", s[j], s[a[j]-1], t[j] + t[a[j]-1], t[i-1]);
      if (s[i-1] > l) {
        l = s[i-1];
        if (l >= n) break;
      }
      if (j > 0 && t[j] + t[a[j]-1] < l*p + v) {
        l = 1 + (s[i] = s[j]*s[a[j]-1]);
        t[i] = t[j] + t[a[j]-1];
        printf("%lld %d %lld %d %lld %d %d\n", l, t[i-1], s[j], t[j], s[a[j]], t[a[j]], t[j] + t[a[j]]);
        continue;
      }
      t[i] = l*p + v;
      s[i] = l++;
      a[i] = 1;
      H.push((pt){s[1]*1.0*s[i], i, t[1] + t[i]});
    }
    printf("%d\n", n < 2? 0: t[i-1]);
  }
}

