#include<queue>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2009;
struct pt {
  int id, st, ed, c;
  bool operator <(pt a) const {
    if (ed != a.ed) return ed > a.ed;
    return c > a.c;
  }
} s[N];
int a[N], b[N];
bool cmp(pt a, pt b) {
  if (a.st != b.st) return a.st < b.st;
  return a.ed < b.ed;
}
int main() {
  int i, j, k, t, n, m;
  while (scanf("%d %d", &n, &m) == 2) {
    for (i = 0; i < n; ++i) {
      scanf("%d %d", &s[i].st, &s[i].ed);
      a[i] = b[i] = -1;
      s[i].id = i;
      s[i].c = 0;
      s[i].ed += s[i].st - 1;
    }
    sort(s, s+n, cmp);
    priority_queue<pt> H;
    for (i = t = 0; t <= 3000; ++t) {
      while (i < n && t >= s[i].st)
        H.push(s[i++]);
      if (!H.empty() && H.top().ed < t) break;
      vector<pt> tmp;
      for (k = 0; k < m && !H.empty(); ++k) {
        j = H.top().id;
        if (a[j] < 0) {
          a[j] = t;
          tmp.push_back(H.top());
        }
        else b[j] = t;
        H.pop();
      }
      while (tmp.size() > 0) {
        tmp.back().c = 1;
        H.push(tmp.back());
        tmp.pop_back();
      }
    }
    if (!H.empty()) {
      puts("No");
      continue;
    }
    puts("Yes");
    for (i = 0; i < n; ++i)
      printf("%d %d\n", a[i], b[i]);
  }
}
