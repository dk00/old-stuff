#include<cstdio>
#include<algorithm>
using namespace std;
const int inf = 26000;
inline int R(int i) {return (26 + i%26)%26;}
inline int Dis(int a, int b) {return min(abs(a-b), 26-abs(a-b));}
char tmp[3000];
main() {
  int i, j, k, l, d;
  while (scanf("%s", tmp) > 0 && tmp[0] != '*') {
    for (i = j = k = 0; tmp[i]; ++i) {
      printf("%d ", j);
      l = tmp[i] -= 'a';
      if (tmp[i] > 13) l -= 26;
      if (j >= 0 && tmp[j]) j = l;
      else if ((d = Dis(j, l)) < abs(l)) {
        k += d;
        if (j < 0) j = (l + 26)%26 - 26;
        else j = (l + 26)%26;
      }
      else {
        j = l;
        k += abs(l);
      }
    }
    printf("%d\n", k);
  }
}
