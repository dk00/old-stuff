#include<stack>
#include<cstdio>
using namespace std;
const int N = 2012;
int s[N][N];
struct pt {
  int x, y;
};
main() {
  int T, C = 1;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, l, a, n, m;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i) {
      scanf("%d %d", &k, &a);
      for (j = 0; k--;) {
        scanf("%d", &l);
        a = 1 - a;
        while (l--) s[i][j++] = a;
      }
    }
    for (j = 0; j < m; ++j) s[n][j] = 0;
    for (j = a = 0; j < m; ++j) {
      stack<pt> H;
      for (i = 0; i <= n; ++i) {
        if (j && s[i][j]) s[i][j] += s[i][j-1];
        l = i;
        while (!H.empty() && s[i][j] < H.top().y) {
          k = (i - H.top().x)*H.top().y;
          l = H.top().x;
          if (k > a) a = k;
          H.pop();
        }
        if (s[i][j] > 0) H.push((pt){l, s[i][j]});
      }
    }
    printf("Case %d: %d\n", C++, a);
  }
}
