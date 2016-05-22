#include<stack>
#include<vector>
#include<cstdio>
using namespace std;
const int N = 50005;
vector<int> c[N];
int s[N][2], dg[N];
main() {
  int i, j, k, n;
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; ++i) {
      c[i].clear();
      dg[i] = 0;
      s[i][0] = 0;
      s[i][1] = 1;
    }
    for (i = 0; i < n - 1; ++i) {
      scanf("%d %d", &j, &k);
      --j, --k;
      ++dg[j], ++dg[k];
      c[j].push_back(k);
      c[k].push_back(j);
    }
    stack<int> S;
    for (i = 0; i < n; ++i)
      if (dg[i] == 1) S.push(i);
    while (!S.empty()) {
      i = S.top();
      S.pop();
      for (j = 0; j < c[i].size(); ++j) {
        k = c[i][j];
        if (--dg[k] == 1) S.push(k);
        if (s[i][1] > s[i][0]) s[k][0] += s[i][1];
        else s[k][0] += s[i][0];
        s[k][1] += s[i][0];
      }
      j = s[i][0];
      if (s[i][1] > j) j = s[i][1];
    }
    printf("%d\n", j);
  }
}
