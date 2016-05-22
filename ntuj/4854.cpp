#include<cstdio>
char p1[][99] = {
  ".../\\...",
  "../..\\..",
  "./....\\.",
  "/......\\",
  "\\______/",
}, 
p2[][99] = {
  ".../\\...",
  "../..\\..",
  "./....\\.",
  "/......\\",
  "\\______/",
}, 
p3[][99] = {
  ".../\\...",
  "../..\\..",
  "./....\\.",
  "/......\\",
  "\\______/",
}, 
p0[][99] = {
  "........||........",
  "........||........",
  "........||........",
  "........||........",
  "........||........",
  "........||........",
  "........||........",
  "------------------"
}, tmp[99][99];

int tonum(int v) {
  int sum = 0;
  if ('A' <= v && v <= 'Z') {
    while (v > 0) {
      sum += 250 * (1 + v%2);
      v /= 2;
    }
  }
  return sum;
}
main() {
  int T, C = 1;
  scanf("%d", &T);
  while (T--) {
    int i, j, a, b, c, d;
    for (i = 0; i < 5; ++i)
      for (j = 0; j < 90; ++j)
        p2[i][j] = p3[i][j] = p1[i][j];
    for (i = a = b = 0; i < 8; ++i) {
      scanf("%s", tmp[i]);
      for (j = 0; tmp[i][j]; ++j) {
        if (j < 9) a += tonum(tmp[i][j]);
        else b += tonum(tmp[i][j]);
        if ('A' <= tmp[i][j] && tmp[i][j] <= 'Z') {
          if (j < 9) p2[3][j] = tmp[i][j];
          else p3[3][j-10] = tmp[i][j];
        }
        if (tmp[i][j] == '_') {
          if (j < 9) c = i - 4;
          else d = i - 4;
        }
      }
    }
    printf("Case %d:\n", C++);
    for (i = 0; i < 8; ++i)
      for (j = 0; j < 90; ++j)
        tmp[i][j] = p0[i][j];
    if (a > b) a = 2, b = 0;
    else if (a == b) a = b = 1;
    else a = 0, b = 2;
    if (a == c && b == d) {
      puts("The figure is correct.");
      continue;
    }
    for (i = 0; i < 5; ++i)
      for (j = 0; j < 8; ++j)
        tmp[i+a][j] = p2[i][j];
    for (i = 0; i < 5; ++i)
      for (j = 0; j < 8; ++j)
        tmp[i+b][j+10] = p3[i][j];
    for (i = 0; i < 7; ++i)
      puts(tmp[i]);
  }
}
