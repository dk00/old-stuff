#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1005;
struct pt {
  int x, y;
  long long z;
  bool operator<(pt a) const {
    if (x != a.x) return x < a.x;
    if (y != a.y) return y < a.y;
    return z < a.z;
  }
  bool operator==(pt a) const {
    return x == a.x && y == a.y && z == a.z;
  }  
} s[N], H[N*(N-1)/2];
inline int gcd(int a, int b) {
  if (!a || !b) return a+b;
  while ((a%=b)&&(b%=a));
  return a+b;
}
inline pt Line(pt a, pt b) {
  pt c;
  c.y = a.x - b.x;
  c.x = b.y - a.y;
  c.z = gcd(c.x, c.y);
  c.x /= c.z;
  c.y /= c.z;
  if (c.x < 0) c.x *= -1, c.y *= -1;
  c.z = a.x*1ll*c.x + a.y*1ll*c.y;
  return c;
}
main() {
  int i, j, k, n, m;
  map<int, int> sq;
  for (i = 0; i < N; ++i)
    sq[i*(i-1)/2] = i;
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; ++i)
      scanf("%d %d", &s[i].x, &s[i].y);
    for (i = m = 0; i < n; ++i)
      for (j = 0; j < i; ++j)
        H[m++] = Line(s[i], s[j]);
    sort(H, H+m);
    for (i = k = 0; i < m; i += j) {
      for (j = 1; i+j < m && H[i] == H[i+j]; ++j);
      if (j > k) k = j;
    }
    printf("%d\n", sq[k]);
  }
}
