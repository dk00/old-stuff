#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
typedef unsigned long long Int;
Int gcd(Int a, Int b) {
  while ((a%=b) && (b%=a));
  return a + b;
}
const int M = 10000;
bool notp[M+5];
int pn, p[M/3];
void Init() {
  srand(time(NULL));
  pn = 1, p[0] = 2;
  int i, j;  
  for (i = 3; i < M; i += 2) {
    notp[i+1] = true;
    if (notp[i]) continue;
    for (j = i*3; j < M; j += i*2) notp[j] = true;
    p[pn++] = i;
  }
}
inline Int Rand() {
  return rand()*(1ll<<48)+rand()*(1ll<<32)+rand()*(1ll<<16)+rand();
}
inline Int mul (Int a, Int b, Int m) {
  Int i, res=0;
  for (i = 1; i <= b; i *= 2, (a *= 2)%= m)
    if (b&i) (res += a) %= m;
  return res;
}
inline Int pow(Int n,Int k,Int m){
  if (k == 0) return 1;
  if (k % 2 == 1)
    return mul(n, pow(n, k-1, m), m);
  n = pow(n, k/2, m);
  return mul(n, n, m);
}
bool witness(Int a, Int n){
  Int x, y, u, t;
  for(u =n-1, t = 0; u%2 == 0; u/=2, ++t);
  x = pow(a, u, n);
  while(t--){
    y = x;
    x = pow(x, 2, n);
    if (x == 1 && y != 1 && y != n - 1)
      return 1;
  }
  return x != 1;
}
inline bool Prime(Int n) {
  if (n-1 >= 2 && witness(2, n)) return 0;
  if (n-1 >= 3 && witness(3, n)) return 0;
  if (n-1 >= 5 && witness(5, n)) return 0;
  if (n-1 >= 179 && witness(179, n)) return 0;
  if (n-1 >= 9137 && witness(9137, n)) return 0;
  if (n-1 >= 28087 && witness(28087, n)) return 0;
  return 1;
}
int Count, Lim;
Int rho(Int N) {
  while (1) {
    Int x, y, g = 1, c = Rand()%N;
    x = y = Rand()%N;
    while (g == 1) {
      x = (mul(x, x, N) + c)%N;
      y = (mul(y, y, N) + c)%N;
      y = (mul(y, y, N) + c)%N;
      g = gcd(abs(x-y), N);
    }
    if (g != N) return g;
  }
}

int Factor(Int N, Int s[]) {
  int i, n;
  for (i = n = 0; i < 100 && p[i] < N; ++i) {
    while (N % p[i] == 0) {
      N /= p[i];
      s[n++] = p[i];
    }
  }
  if (N <= 1) return n;
  s[n++] = N;
  for (i = n - 1; i < n; ) {
    while (i < n && Prime(s[i])) ++i;
    if (i >= n) break;
    s[i] /=(s[n] = rho(s[n-1]));
    ++n;
  }
  return n;
}
main() {
  Init();
  int i, j, n, T = 99999;
  scanf("%d", &T);
  while (T--) {
    Int x, s[66];
    scanf("%lld", &x);
    printf("%lld = ", x);
    n = Factor(x, s);
    std::sort(s, s+n);
    for (i = 0; i < n; i += j) {
      if (i > 0) printf(" * ");
      printf("%lld", s[i]);
      for (j = 1; i + j < n && s[i] == s[i+j]; ++j);
      if (j > 1)
        printf("^%d", j);
    }
    puts("");
  }
}
