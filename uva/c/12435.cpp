#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2222, M0 = 2459477, M1 = 2460421, M2 = 2459383;
struct pt {
  int x, y;
} s[N];
inline int dis(pt a, pt b) {
  return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
int un, h0[M0], h1[M1], h2[M2];
inline bool testset(int v) {
  int v0 = v%M0, v1 = v%M1, v2 = v%M2;
  if (h0[v0] == un || h1[v1] == un || h2[v2] == un) return false;
  h0[v0] = h1[v1] = h2[v2] = un;
  return true;
}
main() {
  int i, j, k, n, m, T, C = 1;
  scanf("%d", &T);
  while (T--) {
    vector<int> H;
    scanf("%d", &n);
    ++un;
    for (i = m = 0; i < n; ++i) {
      scanf("%d %d", &s[i].x, &s[i].y);
      for (j = 0; j < i; ++j) {
        k = dis(s[i], s[j]);
        if (testset(k)) ++m;
      }
    }
    printf("Case %d: %d\n", C++, m+1);
  }
}
