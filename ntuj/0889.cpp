#include<cmath>
#include<cstdio>
char s[2010], a[2010], b[2010];
void carry(char s[], int n) {
  while (n-->1) {
    s[n-1] += s[n]/10;
    s[n] %= 10;
  }
}
void cmp(char s[], int n, char a[], int m, int i) {

}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i;
    double c;
    scanf("%s", s + 1);
    for (n = 0; s[n]; ++n)
      s[n] = (s[n] - '0')*8;
    s[0] = 0;
    ++s[n+1];
    carry(s, n);
    m = (n + 1)/2;
    for (i = 0; i < m; ++i) {
      for (j = 1; j < 10; ++j)
        if (cmp(s, n, a, m, i)) break;
      a[i] = j - 1;
    }
  }
}
