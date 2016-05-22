#include<cstdio>

main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j;
    char tmp[128];
    scanf("%s", tmp);
    for (i = 0; tmp[i]; ++i);
    for (j = 1; j <= i; ++j)
      if (tmp[i - j] == '8') printf("big");
      else break;
    if (j == 1) printf("bang");
    puts("");
  }
}
