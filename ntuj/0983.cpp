#include<cstdio>
main() {
  int n, C = 1;
  while (scanf("%d", &n) == 1 && n) {
    printf("%d. %s %d\n", C++, (n%2)?"odd":"even", (3*n+1)/2*3/9);
  }
}
