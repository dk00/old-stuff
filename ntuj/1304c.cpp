#include<cstdio>
using namespace std;
const int M = 9999;
int m, p, v, un, u[M];
long long s[M];
struct pt {
  long long n;
  int t;
}t[M*2];
inline long long Div(long long q, long long d) {
  return (q + d - 1)/d;
}
inline int Sqrt(long long n) {
  int i, j;
  for (i = 25, j = 0; i >= 0; --i) {
    j |= 1 << i;
    if (j > n/j) j ^= 1 << i;
  }
  if (j < Div(n, j)) ++j;
  return j;
}
int dep = 0;
int Least(long long n) {
  for (int i = m - 1; i >= 0; --i)
    if (t[i].n <= n) return t[i].t;
}
void Update(long long n, int k) {
  int i;
  for (i = m - 1; i >= 0; --i)
    if (k == t[i].t) {
      if (n >= t[i].n)
        t[i].n = n;
      return;
    }
  for (i = m - 1; i >= 0; --i) {  
    if (k < t[i].t) t[i+1] = t[i];
    else break;
  }
  ++m;
  t[i+1] = (pt){n, k};
}
long long go(long long n) {
  if (n < M && u[n] == un) return s[n];
  ++dep;
  int i;
  long long j, k = n*p + v, last;
  if (n < M) 
    u[n] = un, s[n] = k;
  last = 0;
  for (i = Sqrt(n); i >= 2; --i) {
    j = go(i);
    if (j + Least(Div(n, i)) >= k) continue;
    j += last = go(Div(n, i));
    if (dep == 1) printf("%d %d %lld\n", i, Div(n, i), j);
    if (j < k) k = j;
  }
  if (n < M) s[n] = k;
  Update(n, k);
  --dep;
  return k;
}
main() {
  long long n;
  while (scanf("%lld %d %d", &n, &p, &v) == 3) {
    m = 0;
    u[1] = ++un;
    s[1] = 0;
    Update(1, 0);
    printf("%d %d\n", m, go(n));
    for (int i = 0; i < m; ++i)
      printf("%lld %d\n", t[i].n, t[i].t);
  }
}
/*
1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7
0 3 4 5         8

 */

