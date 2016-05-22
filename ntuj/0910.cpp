#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 70;
struct pt {
  int h, w;
  bool operator<(pt a)const {
    if (h != a.h) return h > a.h;
    return w > a.w;
  }
} s[N];
char u[N];
int n, n0, n1, sum_w[N];
bool go(int w0, int w1, int w2, int i) {
  while (!u[i] && i < n) ++i;
  if (i >= n) return true;
  if (i < n0) {
    if ((w0 -= s[i].w) < 0) return false;
    return go(w0, w1, w2, i+1);
  }
  if (w0 >= s[i].w && go(w0 - s[i].w, w1, w2, i+1))
    return true;
  if (w1 >= s[i].w && go(w0, w1 - s[i].w, w2, i+1))
    return true;
  return (i > n1 && w2 >= s[i].w && go(w0, w1, w2 - s[i].w, i+1));
}
bool Test(int Max) {
  int i, j, k, h, w;
  for (i = 1; i < n; ++i)
    for (j = i + 1; j < n; ++j) {
      h = s[0].h + s[i].h + s[j].h;
      w = Max / h;
      for (k = 0; k < n; ++k) u[k] = 1;
      n0 = i, n1 = j;
      u[0] = u[i] = u[j] = 0;
      if (w < s[0].w || w < s[i].w || w < s[j].w) continue;
      if (go(w-s[0].w, w-s[i].w, w-s[j].w, 1)) {
        return true;
      }
    }
  return false;
}
main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int i, j, k, a;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
      scanf("%d %d", &s[i].h, &s[i].w);
      sum_w[i] += (i?sum_w[i-1]:0) + s[i].w;
    }
    i = (sum_w[n-1] + 2)/3*s[n-1].h*3;
    j = sum_w[n-3]*s[0].h*3;
    while (i <= j) {
      k = (i + j)/2;
      if (Test(k)) a = k, j = k - 1;
      else i = k + 1;
    }
    printf("%d\n", a);
  }
}
