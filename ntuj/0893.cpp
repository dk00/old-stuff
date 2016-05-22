#include<cstdio>
const int N = 13;
long long F[13];
int un, u[N];
void gen(int n, long long k, int s[]) {
  k += F[9] / F[10 - n];
  int i, j;
  for (++un, i = 0; i < n; ++i) {
    for (j = 0; u[j] == un || k > F[9-i]/F[10-n]; ++j)
      if (u[j] != un)
        k -= F[9-i]/F[10-n];
    s[i] = j;
    u[j] = un;
  }
}
char tmp[99999], id[99999];
main() {
  int T;
  F[0] = 1;
  for (int i = 1; i < N; ++i)
    F[i] = F[i-1] * i;
  scanf("%d", &T);
  while (T--) {
    int i, n, s[90];
    long long k;

    for (i = 'a'; i <= 'z'; ++i)
      id[i] = -1;
    scanf("%s %lld", tmp, &k);
    for (i = n = 0; tmp[i]; ++i)
      if (id[tmp[i]] < 0)
        id[tmp[i]] = n++;
    if (n > 0) gen(n, k, s);
    for (i = 0; tmp[i]; ++i)
      tmp[i] = '0' + s[id[tmp[i]]];
    puts(tmp);
  }
}
