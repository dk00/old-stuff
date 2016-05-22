#include<vector>
#include<cstdio>
struct node {
  int n, chg, l, r;
};
vector<node> s[N];
void ins(vector<node>& a, int num, int t) {
  int i, j;
  node tmp;
  tmp.l = tmp.r = tmp.n = 0 = tmp.chg = 0;
  for (i = 29, j = 0; i >= 0; --i) {
    if (t&(1<<i))
      a[t].n += num;
    int& next = (t&(1<<i))? a[j].r: a[j].l;
    if (!next) {
      next = a.size();
      a.push_back(tmp);
    }
    j = next;
  }
  a[j].n += num;
}
void ins(vector<node>& a, vector<node>& b, int v, int& u) {
  if (!v) return;
  node tmp;
  tmp.l = tmp.r = tmp.n = tmp.chg = 0;
  if (!u) {
    u = a.size();
    a.push_back(tmp);
  }
  if (u < 0) u = 0;
  a[u].n += b[v].n;
  //XXX a[u].chg += b[v].chg;
  ins(a, b, b[v].l, a[u].l);
  ins(a, b, b[v].r, s[u].r);
}
void go(vector<node>& a) {
}
void cross(vector<node>& a, vector<node>& b) {
  if (a.size() > b.size())
    a.swap(b);
  ins(a, b, -1);
}
main() {
  while (scanf("%d %d", &n, &m) == 2) {
    for (i = 1; i < n; ++i) {
      scanf("%d %d %d", p+i, &j, c+i);
      --p[i];
      ins(s[i], j, 0);
      ++dg[p[i]];
    }
    vector<int> Q;
    for (i = 0; i < n; ++i)
      Q.push_back(i);
    while (Q.size()) {
      i = Q.back(), Q.pop_back();
      go(i);
      if (i) {
        cross(s[i], s[p[i]]);
        if (!--dg[p[i]])
          Q.push_back(p[i]);
      }
    }
  }
}
