#include<cstdio>
using namespace std;
int M;
const int N = 100001;
char tmp[N];
long long s[N];
unsigned p[N], u[N];
main() {
  int n, M, T, un = 0, st, ub;
  scanf("%d", &T);
  while (T--) {
    long long i, j, l;
    scanf("%s %d" , tmp, &M);
    for (n = 0; tmp[n]; ++n);
    s[n] = 0;
    u[0] = un + 1;
    p[0] = n;
    for (++un, i = n - 1, j = 1, ub = 0; i >= 0; --i, j = j * 10 % M) {      
      s[i] = (s[i+1] + (tmp[i] - '0') * j) % M;
      if (u[s[i]] == un && p[s[i]] - i > ub) {
        ub = p[s[i]] - i;
        st = i;
      }
      if (u[s[i]] == un) continue;
      u[s[i]] = un;
      p[s[i]] = i;
    }
    tmp[st+ub] = '\0';
    puts(tmp + st);
  }
}
