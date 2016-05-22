#include<cstdio>
char tmp[99999];
main() {
  int i, j, k, C=1;
  while (scanf("%s", tmp) && tmp[0] != '-') {
    for (i = j = k = 0; tmp[i]; ++i) {
      if (tmp[i] == '}') {
        if (j <= 0) ++k, j = 1;
        else --j;
      }
      else ++j;
    }
    k += j/2;
    printf("%d. %d\n",C++, k);

  }
}

