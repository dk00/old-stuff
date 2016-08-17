#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 105;
int p[N];
double sum, s[N];
bool test(int d, int i, double w) {
  if (w >= sum - w) return false;
  if (w*1.02 >= sum - w) {
    printf("%d", p[0]+1);
    for (i = 1; i < d; ++i)
      printf(" %d", p[i]+1);
    puts("");
    return true;
  }
  if (i < 0) return false;
  p[d] = s[i];
  if (test(d+1, i-1, w+s[i])) return true;
  return test(d, i-1, w);
}
main() {
  int i, n;
  while (scanf("%d", &n) == 1 && n) {
    for (sum = i = 0; i < n; ++i)
      scanf("%lf", s+i), sum += s[i];
    sort(s, s + i);
    test(0, n - i, 0);
  }
}
