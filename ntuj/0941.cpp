#include<cstdio>
#include<algorithm>
using namespace std;
struct pt {
  int x, y;
  bool operator<(pt a)const {
    if (x != a.x) return x < a.x;
    return y < a.y;
  }
}s[2011];
main() {
  int i, n, sum;
  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; ++i)
      scanf("%d %d", &s[i].x, &s[i].y);
    sum = 4*n;
    sort(s, s + n);
    for (i = 1; i < n; ++i)
      if (s[i].x == s[i-1].x && s[i].y == s[i-1].y + 1)
        sum -= 2;
    for (i = 0; i < n; ++i)
      swap(s[i].x, s[i].y);
    sort(s, s + n);
    for (i = 1; i < n; ++i)
      if (s[i].x == s[i-1].x && s[i].y == s[i-1].y + 1)
        sum -= 2;
    printf("%d\n", sum);
  }
}
