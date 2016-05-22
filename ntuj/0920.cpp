#include<cstdio>
main() {
  int T, n, i;
  char tmp[20];
  scanf("%d", &T);
  gets(tmp);
  while (T--) {
    gets(tmp);
    for (n = i = 0; tmp[n]; ++n)
      i |= (tmp[n] - '0' + 1);
    printf ("%d\n", (i&1) + !!(i&2));
  }
}
