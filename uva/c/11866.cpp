#include<cstdio>
inline long long C3(int n) {
  return n*(n + 1)*(n + 2)/6;
}
inline long long S(int n) {
  return n*(n + 1ll)/2;
  
}
main() {
  int i, j, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &i, &j);
    printf("%lld\n", C3(j) - S(j/2 - i + 1) - S((j-1)/2 - i + 1));
  }
}
