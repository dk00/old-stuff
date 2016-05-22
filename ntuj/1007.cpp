#include<set>
#include<queue>
#include<cstdio>
using namespace std;
const int inf = 2147483647;
struct Set {
  set<int> a;
  set<int, greater<int>, allocator<int> > b;
  void insert(int x) {
    a.insert(x);
    b.insert(x);
  }
  void insert(input_iterator begin, input_iterator end) {
    a.insert(begin, end);
    b.insert(begin, end);
  }
  int size() const {
    return a.size();
  }
  int diff(int x) {
    set<int>::iterator p = a.lower_bound();
    int j = abs(x-*p), k;
    p = b.lower_bound();
    k = abs(x-*p);
    return min(j, k);
  }
};
struct pt {
  Set *s;
  bool operator<(pt a)const {
    return *(s->a.begin()) < *(a.s->a.begin());
  }
  int min() {
    return *(s->a.begin());
  }
  void pop() {
    s->a.erase(s->a.begin());
    set<int>::iterator p = s->b.end();
    s->b.erase(--p);
    return s->a.size();
  }
};
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i) {
      best[i] = inf;
      dg[i] = 0;
    }
    for (i = 1; i < n; ++i) {
      scanf("%d", p+i);
      ++dg[p[i]];
    }
    queue<int> Q;
    for (i = m; i < n; ++i) {      
      s[i] = new Set;
      scanf("%d", &j);
      s[i].insert(j);
      --dg[p[i]];
      c[p[i]].push_back(i);
      if (!dg[p[i]]) Q.push(p[i]);
    }
    while (!Q.empty()) {
      i = Q.top();
      Q.pop();
      for (j = 0, k = c[i][0]; j < c[i].size(); ++j)
        if (s[c[i][j]].size() > s[k]) k = c[i][j];
      for (j = 0; j < c[i].size(); ++j)
        if (c[i][j] != k)
          H.insert((pt){s[c[i][j]]});
      vector<int> tmp;
      while (!H.empty()) {
        pt a = H.top();
        H.pop();
        tmp.push_back(a.min());
        best[i] = min(best[i], s[i].diff(a.min()));
        if (a.pop()) H.insert(a);
      }
      s[i] = s[k];
      if (tmp.size() > 0) s[i].insert(tmp[0]);
      for (j = 1; j < tmp.size(); ++j) {
        if (tmp[j] - tmp[j-1] < best[i])
          best[i] = tmp[j] - tmp[j-1];
        s[i].insert(tmp[j]);
      }
      for (j = 0; j < c[i].size(); ++j)
        if (c[i][j] != k) delete s[c[i][j]];
      --dg[p[i]];
      c[p[i]].push_back(i);
      if (!dg[p[i]]) Q.push(p[i]);      
    }
    for (i = 0; i < m; ++i)
      printf("%d", best[i]);    
  }
}
