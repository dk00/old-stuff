#include<map>
#include<string>
#include<cstdio>
const int N = 1002;
using namespace std;
map<string, int> H;
int g[N], p[N], d[N], c[N];
int Read() {
  char tmp[99];
  scanf("%s", tmp);
  int i;
  if (!H.count(tmp)) {
    i = H[tmp] = H.size() - 1;
    g[i] = i;
    p[i] = i;
    d[i] = 0;
    c[i] = 0;
  }
  i = H[tmp];
  return i;
}
int find(int v) {
  if (v == p[v]) return v;
  return find(p[v]);
}
int dep(int v) {
  if (v == p[v]) return c[v];
  return c[v]^dep(p[v]);
}
void uni(int a, int b) {
  a = find(a), b = find(b);
  if (a == b) return;
  if (d[a] < d[b]) p[a] = b;
  else p[b] = a;
  if (d[a] == d[b]) ++d[a];
}
main() {
  int T, C = 1;
  scanf("%d", &T);
  while (T--) {
    int i, j, k = 1, n, m;
    H.clear();
    scanf("%d %d", &n, &m);
    while (n--) {
      i = Read();
      j = Read();
      uni(i, j);
    }
    for (i = 0; i < H.size(); ++i)
      g[i] = find(i);
    while (m--) {
      i = Read();
      j = Read();
      i = g[i], j = g[j];
      if (i == j) k = 0;
      if (find(i) == find(j)) {
        if(dep(i) == dep(j)) k = 0;
        continue;
      }
      c[find(j)] = 1^dep(i)^dep(j);
      uni(i, j);
    }
    printf("Case %d: %s\n", C++, k?"YES":"NO");
  }
}
