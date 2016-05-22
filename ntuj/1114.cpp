#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 10002;
struct pt {
  int x, y, id;
} s[N];
bool cmp(pt a, pt b) {
  a.x -= s[0].x;
  a.y -= s[0].y;
  b.x -= s[0].x;
  b.y -= s[0].y;
  return (a.x*1ll*b.y - a.y*1ll*b.x < 0);
}
main() {
  int i, j, n, m, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (i = j = 0; i < n; ++i) {
      scanf("%d %d", &s[i].x, &s[i].y);
      s[i].id = i;
      if (s[i].x < s[j].x || (s[i].x == s[j].x && s[i].y < s[j].y))
        j = i;
    }
    swap(s[j], s[0]);
    sort(s+1, s+n, cmp);
    for (i = 0; i < m; ++i)
      printf("%d\n", s[i].id + 1);
  }
}
