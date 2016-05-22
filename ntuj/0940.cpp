#include<cstdio>
#include<algorithm>
using namespace std;
void go(long long a, int& x, int& y) {
  long long i, j, k;
  for (i = 0, j = 1500000001; i <= j;) {
    k = (i + j + 1) / 2;
    if (k*(k + 1)/2 >= a) j = k - 1;
    else {
      x = k;
      i = k + 1;
    }
  }
  y = a - (x*1ll*(x + 1))/2;
}
int main() {
  int x0, y0, x1, y1, dx, dy;
  long long a, b;
  while (scanf("%lld %lld", &a, &b) == 2 && a + b) {
    if (a > b) swap(a, b);
    go(a, x0, y0);
    go(b, x1, y1);
    dx = x1 - x0;
    dy = min(abs(y0-y1), abs(x0-y0-x1+y1));
    if (y0 <= y1 && y1 <= y0 + dx)
      dy = 0;
    printf("%d\n", dx + dy);
  }
}
