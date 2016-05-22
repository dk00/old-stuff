#include<cstdio>
const long long D = 10000000000ll;
int n;
char tmp[9999];
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, m;
    long long r = 0;
    scanf("%d", &m);
    scanf("%s", tmp);
    for (i = 0; tmp[i]; ++i) 
      r = ((r*10) + tmp[i] - '0') % m;
    printf("%lld\n", r);
  }
}
