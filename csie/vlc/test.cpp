#include<vector>
#include<cstdio>
using namespace std;
main() {
  int i, j;
  vector<int> t;
  printf("%d\n", t.size());
  t.resize(6);
  t[5] = 8;
  printf("%d\n", t.size());
  for (i = 0; i < t.size(); ++i)
    printf("%d ", t[i]);
  puts("");
  t.resize(4);
  printf("%d\n", t.size());
  for (i = 0; i < t.size(); ++i)
    printf("%d ", t[i]);
  puts("");
  t.resize(8);
  printf("%d\n", t.size());
  for (i = 0; i < t.size(); ++i)
    printf("%d ", t[i]);
  puts("");  
}
