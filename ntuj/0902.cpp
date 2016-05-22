#include<map>
#include<vector>
#include<cstdio>
using namespace std;
const int N = 1009;
long long s0[N], s1[N];
char path[99999], tmp[99999];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, n, m, M;
    scanf("%d %d %d", &n, &m, &M);
    vector<int> from[256];
    vector<int> to[256];
    for (i = 0; i < n; ++i)
      s0[i] = 1, s1[i] = 0;
    scanf("%s", path);
    while (m--) {
      scanf("%d %d %s", &i, &j, tmp);
      from[tmp[0]].push_back(i);
      to[tmp[0]].push_back(j);
    }
    for (i = 0; path[i]; ++i) {
      const vector<int>& st = from[path[i]];
      const vector<int>& ed = to[path[i]];
      for (j = 0; j < st.size(); ++j) {
        s1[ed[j]] += s0[st[j]];
        s1[ed[j]] %= M;
      }
      for (j = 0; j < n; ++j)
        s0[j] = s1[j], s1[j] = 0;
    }
    for (i = 1; i < n; ++i)
      s0[0] = (s0[0] + s0[i])% M;
    printf("%lld\n", s0[0]);
  }
}
