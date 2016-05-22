#include<cstdio>
int to[27], u[27], num[27], un;
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    char tmp[27];
    int i, j, k, a = 0;
    scanf("%s", tmp);
    for (i = 0; i < 26; ++i)
      num[i] = 0, to[tmp[i] - 'A'] = i;
    for (++un, i = 0; i < 26; ++i) {
      for (j = i, k = 0; u[j] != un; j = to[j], ++k)
        u[j] = un;
      if (k > 0 && k%2 == 0) {
        if (num[k]^=1) ++a;
        else --a;
      }
    }
    if (a) puts("No");
    else puts("Yes");
  }
}
