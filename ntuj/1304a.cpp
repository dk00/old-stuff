#include<cstdio>
const int M = 99999;
int p, v, un, u[M];
long long s[M];
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
long long go(long long n);
long long Cost(long long n, int d) {
  return Div(n, d)*p + v + go(d);
}
int count, divide;
long long go(long long n) {
  if (n < M && u[n] == un)
    return s[n];
  ++count;
  int j, m;
  long long i, k, d, min;
  m = Sqrt(n);
  j = Sqrt(m);
  d = 1;
  min = Cost(n, 1);
  for (i = 2; i < n && i < m + j; i += j) {
    if (i >= n) break;
    k = go(Div(n, i)) + go(i) + v;
    if (k < min) min = k, d = i;
  }
  for (i = d - 2*j < 1? 1: d - 2*j; i < n && i <= d + 2*j; i = Div(n, Div(n, i) - 1)) {
    k = Cost(n, i);
    if (k < min) min = k, d = i;
  }
  divide = n / d;
  if (n < M) u[n] = un;
  if (n < M) s[n] = min;
  return min;
}
main() {
  long long n;
  while (scanf("%lld %d %d", &n, &p, &v) == 3) {
    u[1] = ++un;
    s[1] = 0;
    count = 0;
    printf("%d ", go(n));
    printf("%d\n", divide);

  }
}
/*
 n : a
 ap + v
 ceil(n/a) :

 a*a <= n
 b*b > n
 
 C(n, ) <= n

 C(n, a) = ap + v + C(n/a, )
 C(n, b) = bp + v + C(n/b, )
 bp > ap
 n/b < n/a
 C(n/a, ) - C(n/b, ) <= b - a <= bp - ap

 x < y

 C(n, x) = xp + v + C(n/x, )
 C(n, y) = yp + v + C(n/y, )

 C(n, x) <= C(n, y) 

 xp + v + C(n/x, ) <= yp + v + C(n/y, )

 C(n/x, ) - C(n/y, ) <= (y - x)p


 */

