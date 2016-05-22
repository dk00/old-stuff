/*
4040 0.000000 484.800000 0.161600
4040 0.000000 606.000000 0.202000
4040 0.000000 808.000000 0.269333
4040 0.161600 1212.000000 0.565600
10000 0.269333 1000.000000 0.602667
6030 0.202000 1809.000000 0.805000
Case 1: 0.518489

1234 0.000000 0.000000 0.000000
Case 2: 0.000000   
 */
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 200001;
int n, m, SP;
struct pt {
  int size, c;
  double st, rem;
  bool operator< (pt a) const {
    return done() > a.done();
  }
  double done() const {
    return st + rem*m/SP;
  }
} s[N], t[N];
bool cmp(pt a, pt b) {
  if (a.size != b.size) return a.size < b.size;
  return a.c > b.c;
}
main() {
  int i, j, k, C = 1;
  while (scanf("%d %d %d", &n, &m, &SP) == 3 && n + m + SP) {
    SP *= 100.0;
    for (i = 0; i < n; ++i) {
      scanf("%d.%d %d", &j, &k, &s[i].c);
      s[i].size = j*100 + k;
      s[i].rem = s[i].size * 1.0 * (100 - s[i].c) / 100.0;
    }
    sort(s, s+n, cmp);
    priority_queue<pt> H;
    for (i = 0; i < m; ++i) {
      s[i].st = 0;
      H.push(s[i]);
    }    
    for (i = m; i < n; ++i) {
      pt x = H.top();
      H.pop();
      s[i].st = x.done();
      H.push(s[i]);
    }
    for (k = 0; !H.empty(); ++k) {
      t[k] = H.top();
      pt x = t[k];
      H.pop();
    }
    for (i = 0; i < k; ++i, --m) {
      double ed = t[i].done();
      for (j = i + 1; j < k; ++j) {
        if (ed > t[j].st)
          t[j].rem -= (ed - t[j].st)*SP/m;
        t[j].st = ed;
      }
    }
    m = 1;
    printf("Case %d: %.2lf\n\n",C++, t[i-1].done() + 1e-8);
  }
}
