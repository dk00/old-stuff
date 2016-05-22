#include<cstdio>
#include<cstring>
char tmp[999999];
inline int gcd(int a, int b) {
  while ((a%=b)&&(b%=a));
  return a + b;
}
main() {
  int T;
  scanf("%d", &T);
  gets(tmp);
  while (T--) {
    const char *p;
    int i, j, n, s[200];
    gets(tmp);
    p = strtok(tmp, " ");
    for (j = n = 0; p; ++n) {
      sscanf(p, "%d", s+n);
      for (i = 0; i < n; ++i)
        if (gcd(s[i], s[n]) > j)
          j = gcd(s[i], s[n]);
      p = strtok(NULL, " ");
    }
    printf("%d\n", j);
  }
}
