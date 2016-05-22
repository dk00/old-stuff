#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
      dg[i] = 0, c[i].clear();
    while (m--) {
      scanf("%d %d", &i, &j);
      --i, --j;
      c[i].push_back(j);
      ++dg[j];
    }
    queue<int> Q;
    for (i = 0; i < n; ++i)
      s[i] = 1, if (dg[i] == 0) Q.push(i);
    sum = 0;
    while (!Q.empty()) {
      i = Q.front();
      Q.pop();
      for (j = 0; j < c[i].size(); ++j) {
        if (!--dg[c[i][j]])
          Q.push(c[i][j]);
        s[c[i][j]] += s[i];
      }        

      
    }
  }
}
