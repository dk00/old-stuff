#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
struct word {
  int l, d, v;
  bool operator<(const word& x)const {
    return d < x.d;
  }
} t[1001];
word go(char s[]) {
  word r = {0, 0, 0};
  for (int i = 0; s[i]; ++i) {
    ++r.l;
    if (s[i] == '(')++r.v;
    else --r.v;
    if (r.v < r.d) r.d = -r.v;
  }
  return r;
}
const int N = 20001;
int _s[N], _s0[N], _u[N];
int *s = _s+N/2, *s0 = _s0+N/2, *u = _u + N/2;
char tmp[N];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, n = 0, len = 0;
    vector<int> p, q;
    p.push_back(0);
    s[0] = 0;
    scanf("%d", &k);
    while (k--) {
      scanf("%s", tmp);
      word x = go(tmp);
      if (x.d > 0) {
        t[n++] = x;
        continue;
      }
      if (x.d == 0 && x.v ==0) {
        len += x.v;
        continue;
      };
      q = p;
      for (i = 0; i < q.size(); ++i) {
        if (u[q[i] + x.v] != T+1 || s[q[i]] + x.l > s0[q[i] + x.v]) {
          s0[q[i] + x.v] = s[q[i]] + x.l;
          u[q[i] + x.v] = T+1;
          p.push_back(q[i] + x.v);
        }
      }
      for (i = 0; i < p.size(); ++i)
        s[p[i]] = s0[p[i]];
    }
    sort(t, t+n);
    for (j = 0; j < n; ++j) {
      q = p;
      word x = t[j];
      for (i = 0; i < q.size(); ++i) {
        if (q[i] < x.d) continue;
        if (u[q[i] + x.v] != T+1 || s[q[i]] + x.l > s0[q[i] + x.v]) {
          s0[q[i] + x.v] = s[q[i]] + x.l;
          u[q[i] + x.v] = T+1;
          p.push_back(q[i] + x.v);
        }
      }
      for (i = 0; i < p.size(); ++i)
        s[p[i]] = s0[p[i]];      
    }
    printf("%d\n", s[0] + len);
  }
}
