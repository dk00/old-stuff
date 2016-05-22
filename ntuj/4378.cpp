#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 100005;
struct pt {
  int pos, v;
  bool operator <(pt a) const {
    if (v != a.v) return v < a.v;
    return pos < a.pos;
  }
} s[N];
int u[N];
main() {
  int i, n;
  long long sum;
  while (scanf("%d", &n) == 1) {
    for (i = sum = 0; i < n; ++i) {
      u[i] = 1;
      scanf("%d", &s[i].v);
      s[i].pos = i;
      sum += s[i].v;
    }
    if (sum % 2) {
      puts("No");
      continue;
    }
    sum /= 2;
    sort(s, s+n);
    for (i = n-1; sum > 0 && i >= 0; --i) {
      if (sum >= s[i].v) {
        sum -= s[i].v;
        u[s[i].pos] = -1;
      }
    }
    if (sum != 0) {
      puts("No");
      continue;
    }
    puts("Yes");
    for (i = 0; i < n-1; ++i)
      printf("%d ", u[i]);
    printf("%d\n", u[i]);
  }
}
