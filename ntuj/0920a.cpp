#include<cstdio>
void Split(const char s[], int x, char a[], char b[]) {
  int i, n0 = 0, n1 = 0;
  for (i = 0; s[i]; ++i)
    if ((1<<i)&x) a[n0++] = s[i];
    else b[n1++]= s[i];
  a[n0] = b[n1] = 0;
}
int Len(const char s[]) {
  int i, j, n;
  for (n = 0; s[n]; ++n);
  for (i = 1; s[i]; ++i) {
    if (n%i) continue;
    for (j = i; s[j]; ++j)
      if (s[j] != s[j%i]) break;
    if (!s[j]) break;
  }
  return i;
}
char tmp[20], s1[20], s0[20];
main() {
  int T, n, i, j;
  scanf("%d", &T);
  while (T--) {
    scanf("%s", tmp);
    for (n = 0; tmp[n]; ++n);
    for (i = (1 << n) - 1; i > 0; --i) {
      Split(tmp, i, s0, s1);
      j = Len(s0) + Len(s1);
      if (j < n) n = j;
    }
    printf("%d\n", n);
  }
}
