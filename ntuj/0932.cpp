#include<set>
#include<vector>
#include<cstdio>
const int N = 100000;
using namespace std;
vector<int> c[N];
set<long long> H;
main() {
  while (scanf("%d", &n) == 1) {
    H.clear();
    for (i = 0; i < n; ++i)
      c[i].clear();
    for (i = 0; i < n; ++i) {
      scanf("%d %d", &j, &k);
      --j, --k;
      if (H.count(j*1ll*n+k)) continue;
      H.insert(j*1ll*n+k)
      c[j].push_back(k);
      c[k].push_back(j);
    }

  }
}
