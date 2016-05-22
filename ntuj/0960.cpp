#include<cstdio>
const int N = 800000;
long long rec[N];
long long one(int n) {
  long long tmp = -1;
  long long& R = (n < N)?rec[n]:tmp;
  if (R > 0) return rec[n];
  if (n < 1) return 0;
  if (n % 2) return R = 2*one(n/2) + n/2 + 1;
  return R = one(n/2) + one(n/2-1) + n/2;
}
main() {
  int i, j, C = 1;
  while(scanf("%d %d", &i, &j) == 2 && i+j) {
    printf("Case %d: %lld\n", C++, one(j) - one(i-1));
  }
}
