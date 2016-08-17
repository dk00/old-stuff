#include<map>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
int num[100004], s[100004];
char conv[256], tmp[190];
main() {  
  int i, j, k, n, m, st, ed, T, C = 1;
  scanf("%d", &T);
  gets(tmp);
  for (i = 0; i < 256; ++i)
    conv[i] = ' ';
  for (i = 'a'; i <= 'z'; ++i)
    conv[i] = i;
  while (T--) {
    map<string, int> H;
    for (n = 0; ; ) {
      gets(tmp);
      if (!strcmp(tmp, "END")) break;
      for (i = 0; tmp[i]; ++i)
        tmp[i] = conv[tmp[i]];
      char *p = strtok(tmp, " ");
      for (; p; ++n) {
        if (H.count(p) == 0) H[p] = H.size() - 1;
        s[n] = H[p];
        p = strtok(NULL, " ");
      }
    }    
    for (m = H.size(), i = 0; i < m; ++i) num[i] = 0;
    st = 0, ed = n;
    for (i = j = k = 0; i < n; ++i) {
      while (j < n && k < m)
        if (!num[s[j++]]++) ++k;
      if (k == m) {
        if (j - i < ed - st)
          ed = j, st = i;
        else if (j - i == ed - st && i < st)
          ed = j, st = i;
      }
      if (!--num[s[i]]) --k;
    }
    printf("Document %d: %d %d\n", C++, st+1, ed);
  }
}
