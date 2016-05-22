#include<queue>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 101;
struct pt {
  int pos, val;
};
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, n, m;
    scanf("%d %d", &n, &m);
    queue<pt> Q;
    vector<int> s;
    pt a;
    for (i = 0; i < n; ++i) {
      scanf("%d", &a.val);
      a.pos = i;
      Q.push(a);
      s.push_back(a.val);
    }
    sort(s.begin(), s.end());
    i = 1;
    while (1) {
      a = Q.front();
      Q.pop();
      if (a.val != s.back()) {
        Q.push(a);
        continue;
      }
      if (a.pos == m) break;
      s.pop_back();
      ++i;
    }
    printf("%d\n", i);
  }
}
