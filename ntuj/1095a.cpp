#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1600;
int un, u[N][N];
struct pt {
  int x, y, x0, y0;
  bool operator<(pt a)const {
    if (x != a.x) return x < a.x;
    return y < a.y;
  }
} s[N];
main() {
  int i, j, k, a, n;
  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; ++i)
      scanf("%d %d", &s[i].x, &s[i].y);
    sort(s, s+n);
    map<int, int> H;
    for (i = 0; i < n; ++i)
      H[s[i].x] = H.size() - 1;
    for (i = 0; i < n; ++i)
      s[i].x0 = H[s[i].x];
    for (i = 0; i < n; ++i)
      swap(s[i].x, s[i].y);
    sort(s, s+n);
    H.clear();
    for(i = 0; i < n; ++i)
      H[s[i].x] = H.size() - 1;
    for (i = 0; i < n; ++i) {
      s[i].y0 = H[s[i].x];
      u[s[i].x0][s[i].y0] = 1;
    }
    for (++un, i = a = 0; i < n; ++i)
      for (j = i + 1; j < n; ++j) {
        k = abs((s[i].x-s[j].x)*(s[i].y-s[j].y));
        if (k > a && u[s[i].x0][s[j].y0] == un && u[s[j].x0][s[i].y0] == un)
          a = k;
      }
    printf("%d\n", a);
  }
}
