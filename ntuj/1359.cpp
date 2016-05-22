#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1111;
struct pt {
  int x, y;
  bool operator<(const pt& a)const {
    if (x != a.x) return x > a.x;
    return y < a.y;
  }
} s[N];
int cmp(int a, int b) {
  if (s[a].y != s[b].y)
    return s[a].y > s[b].y;
  return s[a].x < s[b].x;
}
int t[N], u[N];
main() {
  char tmp[9];
  int i, j, n, T, sum0, sum1;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %s", &n, tmp);
    for (sum0 = sum1 = i = j = 0; i < n; ++i) {
      scanf("%d %d", &s[i].x, &s[i].y);
      if (s[i].x > s[j].x || (s[i].x == s[j].x && s[i].y < s[j].y))
        j = i;
      t[i] = i;
      u[i&~1] = 1;
      sum0 += s[i].x;
    }
    if (tmp[0] == 'P')
      s[j] = s[--n];
    sort(s, s+n);
    sort(t, t+n, cmp);
    for (i = 0; i < n; ++i) {
      for (j = t[i]; j >= 0 && !u[j]; --j);
      if (j < 0) continue;
      u[j] = 0;
      sum0 -= s[t[i]].x;
      sum1 += s[t[i]].y;      
    }
    printf("%d %d\n", sum0, sum1);
  }
}
