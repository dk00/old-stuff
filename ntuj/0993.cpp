#include<set>
#include<string>
#include<cstdio>
#include<cstring>
using namespace std;
const int N = 10005, M = 11;
string s[N][M];
char tmp[99];
main() {
  int i, j, k, n, m, a;
  while (scanf("%d %d", &n, &m) == 2) {
    gets(tmp);
    set<string> H[10];
    for (i = 0; i < n; ++i) {
      gets(tmp);
      char *p = strtok(tmp, ",");
      for (j = 0; j < m; ++j) {
        s[i][j] = p;
        p = strtok(NULL, ",");
      }
    }
    for (j = 0, a = 1; a && j < m; ++j)
      for (k = j+1; a && k < m; ++k) {
        set<string> H;
        for (i = 0; a && i < n; ++i) {
          string t = s[i][j] + "," + s[i][k];
          if (H.count(t)) a = 0;
          H.insert(t);
        }
      }
    puts(a?"YES":"NO");
  }
}
