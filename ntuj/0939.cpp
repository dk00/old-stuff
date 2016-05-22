#include<cstdio>
int c[3];
char o[256], tmp[900000];
main() {
  int i, j, T, min;
  for (i = 'A'; i <= 'Z'; ++i) o[i] = 0;
  for (i = 'a'; i <= 'z'; ++i) o[i] = 1;
  for (i = '0'; i <= '9'; ++i) o[i] = 2;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", tmp);
    min = 99999999;
    for (i = j = 0; tmp[i]; ++i) {
      while (tmp[j] && (!c[0] || !c[1] || !c[2]))
        ++c[o[tmp[j++]]];
      if (c[0] && c[1] && c[2] && j - i >= 6 && j - i < min)
        min = j - i;
      --c[o[tmp[i]]];
    }
    if (min >= 99999999) min = 0;
    printf("%d\n", min);
  }
}
