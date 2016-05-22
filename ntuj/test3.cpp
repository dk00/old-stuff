#include<cstdio>
const int N = 1111111, M = 65536;
char buf[M];
inline int getInt() {
  static char *end = buf + M, *p = end;
  if (p+20 >= end) {
    register int i;
    for (i = 0; p+i < end; ++i)
      buf[i] = *(p+i);
    fread(buf+i, sizeof(buf[0]), M-i, stdin);
    p = buf;
  }
  register int j = 0;
  register char *i;
  for (i = p; *i != '\n'; ++i)
    ((j *= 10) += *i) -= '0';
  p = ++i;
  return j;
}
int main() {
  int n = getInt();
  printf("%d\n", n);
  while (n--)
    printf("%d ", getInt());
  puts("");
}
