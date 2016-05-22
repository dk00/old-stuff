#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 109004;
int t[N], p[N];
struct pt {
  int x, y, id;
  bool operator<(pt a) const {
    return x < a.x;
  }
} s[N];
int go(int i, int j, pt a) {
  int k, r;
  while (i <= j) {
    k = (i + j)/2;
    if (k < 1 || (a.x > s[t[k-1]].x & a.y > s[t[k-1]].y))
      r = k, i = k + 1;
    else j = k - 1;
  }
  return r;
}
main() {
  int i, j, k, n;
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; ++i)
      s[i].id = i + 1, scanf("%d %d", &s[i].x, &s[i].y);
    sort(s, s+n);
    for (i = k = 0; i < n; ++i) {
      j = go(0, k, s[i]);
      if (j == k || s[i].y < s[t[j]].y) t[j] = i;
      if (j > 0) p[i] = t[j-1];
      else p[i] = -1;
      if (j == k) ++k;
    }
    printf("%d\n", k);
    for (j = k-1; j > 0; --j)
      t[j-1] = p[t[j]];
    for (i = 0; i < k-1; ++i)
      printf("%d ", s[t[i]].id);
    printf("%d\n", s[t[i]].id);
  }
}
