#include<cstdio>
#include<algorithm>
using namespace std;
const int inf = 26000;
inline int R(int i) {return (26 + i%26)%26;}
char tmp[3000];
int s[2][26][26];
main() {
  int i, j, k, c, d;
  while (scanf("%s", tmp) > 0 && tmp[0] != '*') {
    for (i = 0; i < 26; ++i)
      for (j = 0; j < 26; ++j)
        s[0][i][j] = i + j;
    for (k = 0; tmp[k]; ++k) {
      tmp[k] -= 'a';
      for (i = 0; i < 26; ++i)
        for (j = 0; j < 26; ++j)
          s[1-k%2][i][j] = inf;      
      for (i = 0; i < 26; ++i)
        for (j = 0; j < 26; ++j) {
          d = R(tmp[k]-i+j);
          c = s[k%2][i][j] + d;
          if (c < s[1-k%2][min(i+d, 25)][j])
            s[1-k%2][min(i+d, 25)][j] = c;
          d = R(i-j-tmp[k]);
          c = s[k%2][i][j] + d;
          if (c < s[1-k%2][i][min(j+d, 25)])
            s[1-k%2][i][min(j+d, 25)] = c;
        }
      for (i = 25; i >= 0; --i)
        for (j = 25; j >= 0; --j)
          s[1-k%2][i][j] = min(s[1-k%2][i][j],
              min(i<25?s[1-k%2][i+1][j]:inf, j<25?s[1-k%2][i][j+1]:inf));
    }
    printf("%d\n", s[k%2][0][0]);
  }
}
