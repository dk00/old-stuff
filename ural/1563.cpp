#include<set>
#include<string>
#include<cstdio>
using namespace std;
int main() {
  int i, n;
  char tmp[99];
  while (scanf("%d", &n) == 1) {
    set<string> H;
    gets(tmp);
    i = 0;
    while (n--) {
      gets(tmp);
      if (H.count(tmp)) {
        ++i;
        continue;
      }
      H.insert(tmp);
    }
    printf("%d\n", i);
  }
}
