#include<cstdio>
#include<cstring>
using namespace std;
const int N = 1000007;
int m, sib[N], ch[N], back[N];
char a[N], text[N], *s[10001];
void add(int v, char c) {
  int i, j;
  for (i = ch[v]; i; i = sib[i])
    if (a[i] == c) return;
  j = m++;
  sib[j] = ch[v];
  ch[v] = j;
  a[j] = c;
}

main() {
  int i, n, m;
  while (scanf("%d", &n) == 1 && n) {
    for (i = j = 0; i < n; ++i) {
      text[j] = 0;
      scanf("%s", s[i] = text + ++j);
      j += strlen(s[i]);
      add(0, s[i][0]);
    }
  }
}

