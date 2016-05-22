#include<set>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
void go(vector<int>& s) {
  vector<int> t = s;
  for (int i = 0; i < s.size(); ++i)
    s[i] = abs(t[i] - t[(i+1)%s.size()]);
}
main() {
  int i, j, n, T;
  scanf("%d", &T);
  while (T--) {
    vector<int> s;
    set<vector<int> > H;    
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d", &j);
      s.push_back(j);
    }
    while (H.count(s) == 0) {
      H.insert(s);
      go(s);
    }
    for (i = 0; i < s.size(); ++i)
      if (s[i] != 0) break;
    if (i < s.size()) puts("LOOP");
    else puts("ZERO");
  }
}
