#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 1000001, M = 26;
struct dict {
  int id;
  string w;
  bool operator<(dict a) const {
    if (w.length() != a.w.length())
      return w.length() < a.w.length();
    if (w != a.w) return w < a.w;
    return id < a.id;
  }
} d[N];
int nNode;
struct node {
  int id;
  int back, ch[M];
  vector<int> H;
} s[N];
void Init(int v) {
  s[v].H.clear();
  s[v].id = -1;
  s[v].back = 0;
  for (int i = 0; i < M; ++i)
    s[v].ch[i] = -1;
}
inline void ins(int v, char c) {
  c -= 'a';
  if (s[v].ch[c] >= 0)
    return;
  Init(nNode);
  s[v].ch[c] = nNode++;
}
inline int next(int v, char c) {
  c -= 'a';
  while (v > 0 && s[v].ch[c] < 0) v = s[v].back;
  if (s[v].ch[c] >= 0) v = s[v].ch[c];
  return v;
}
char tmp[1200000];
string w[N];
int same[N], u[N], q[2][N], v[2][N];
vector<int> ans[N];
void merge(vector<int>& a, const vector<int>& b) {
  vector<int> c = a;
  int i;
  for (i = 0; i < b.size(); ++i)
    c.push_back(b[i]);
  sort(c.begin(), c.end());
  a.clear();
  for (i = 0; a.size() < 10 && i < c.size(); ++i)
    if (a.size() < 1 || c[i] != a.back()) a.push_back(c[i]); 
}
main() {
  int i, j, k, n, m;
  while (scanf("%d", &m) == 1) {
    for (i = 0; i < m; ++i) {
      scanf("%s", tmp);
      d[i].w = tmp;
      d[i].id = i;
    }
    sort(d, d+m);
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%s", tmp);
      w[i] = tmp;
      u[i] = 0;
      same[i] = i;
      ans[i].clear();
    }
    Init(0), nNode = 1;
    int n0, n1, *s0 = q[0], *s1 = q[1], *v0 = v[0], *v1 = v[1];
    for (i = n0 = 0; i < n; ++i) {
      char c = w[i][0];
      ins(0, c);
      v0[n0] = s[0].ch[c-'a'];
      s0[n0++] = i;
    }
    for (j = 1; n0 > 0; ++j) {
      n1 = 0;
      for (k = 0; k < n0; ++k) {
        char c = w[s0[k]][j];
        if (!c) {
          if (s[v0[k]].id < 0)
            s[v0[k]].id = s0[k];
          else same[s0[k]] = s[v0[k]].id;
          continue;
        }
        ins(v0[k], c);
        v1[n1] = s[v0[k]].ch[c-'a'];
        s[v1[n1]].back = next(s[v0[k]].back, c);
        s1[n1++] = s0[k];
      }
      swap(n0, n1);
      swap(v0, v1);
      swap(s0, s1);
    }
    int un = 1;
    for (k = 0; k < m; ++k, ++un) {
      const char *w = d[k].w.c_str();
      for (i = j = 0; w[i]; ++i) {
        j = next(j, w[i]);
        if (u[j] != un && s[j].H.size() < 10) {
          s[j].H.push_back(k);
          u[j] = un;
        }
      }
    }
    for (i = nNode; i > 0; --i) {
      if (s[i].back > 0) merge(s[s[i].back].H, s[i].H);
      if (s[i].id >= 0) ans[s[i].id] = s[i].H;
    }
    for (i = 0; i < n; ++i) {
      j = same[i];
      if (ans[j].size() < 1) {
        puts("-1");
        continue;
      }
      printf("%d", d[ans[j][0]].id+1);
      for (k = 1; k < ans[j].size(); ++k)
        printf(" %d", d[ans[j][k]].id+1);
      puts("");
    }
  }
}
