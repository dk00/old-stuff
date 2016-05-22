#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
char tmp[222];
main() {
  int i, j, k, n;
  vector<int> s, t, d;
  while (scanf("%d", &n) == 1 && n) {
    for (i = k = 0; i < n; ++i) {
      scanf("%s", tmp);
      for (j = 0; tmp[j]; ++j)
        k += 1 - tmp[j] + '0';
    }
    k *= 360000/n/n;
    s.push_back(k);
    t.push_back(k);
  }
  sort(t.begin(), t.end());
  for (i = 0; i + 1 < t.size(); ++i) 
    d.push_back(t[i+1] - t[i]);
  sort(d.begin(), d.end());
  k = d.size() >= 4? d[d.size() - 4]: d[0];
  for (i = j = 0; i < 5; ++i, ++j) {
    for (; j < t.size(); ++j)
      if (j + 1 >= t.size() || t[j+1] - t[j] >= k) break;
    t[i] = t[j];
  }
  for (i = 0; i < s.size(); ++i) {
    for (j = 0; j < 4 && s[i] > t[j]; ++j);
    printf("%d\n", j + 1);
  }
}
