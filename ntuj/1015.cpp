#include<cstdio>
#include<string>
#include<cstring>
main() {
  int a, b, C = 1;
  char tmp[99];
  while (scanf("%d %s %d", &a, tmp, &b) == 3 && strcmp(tmp, "E")) {
    printf("Case %d: ", C++);
    if (a < b && !strcmp(tmp, "<")) puts("true");
    else if (a == b && !strcmp(tmp, "==")) puts("true");
    else if (a != b && !strcmp(tmp, "!=")) puts("true");
    else if (a > b && !strcmp(tmp, ">")) puts("true");
    else if (a <= b && !strcmp(tmp, "<=")) puts("true");
    else if (a >= b && !strcmp(tmp, ">=")) puts("true");
    else puts("false");
  }
}
