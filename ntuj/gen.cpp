#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int s[11111];
main() {
  int T = 4;
  printf("%d\n", T);
  srand(time(NULL));
while (T--) {
  int i, j, n = 8, m = 3;
  printf("%d %d\n", n, m);
  for (i = 0; i < n; ++i) {
    printf("%d ", 1 + rand()%n);
    for (j = 0; j < m; ++j)
      printf("%c", 'A' + rand()%m);
    puts("");
  }
  puts("");
}
}
