#include<map>
#include<string>
#include<cstdio>
using namespace std;
const int N = 2222;
struct pt {
  int x, y, z;
} s[N];
int type[N], count[N], bind[N];
bool test(int a, int b) {
  return (!count[a] || bind[a] == b) && (!count[b] || bind[b] == a);
}
void link(int a, int b) {
  bind[a] = b;
  bind[b] = a;
  ++count[a];
  ++count[b];
}
void unlink(int a, int b) {
  --count[a];
  --count[b];
}
int ins(int a, int b) {
  if (!test(s[a].x, s[b].x))
    return 0;
  if (type[a]) {
    if (!test(s[a].z,s[b].z))
      return 0;
    link(s[a].x, s[b].x);
    link(s[a].z, s[b].z);
    return 1;
  }
  
}
int rm(int a, int b) {
  unlink(s[a].x, s[b].x);
  if (type[a]) {
    unlink(s[a].x, s[b].z);
    return;
  }
}
map<string, int> H;
int getval(int flag) {
  char tmp[9];
  scanf("%s", tmp + flag);
  if (flag) tmp[0] = '.';
  if (!H.count(tmp))
    H[tmp] = H.count() - 1;
  return H[tmp];
}
main() {
  int i, j, k, l, len, n0, n1;
  while (scanf("%d %d", &n0, &n1) == 2) {
    H.clear();
    for (i = 0; i < n0 + n1; ++i) {
      s[i].x = getval(i < n0);
      scanf("%*s");
      s[i].y = getval(i >= n0);
      s[i].z = getval(i >= n0);
      if (s[i].x == s[i].z)
        k = s[i].y, s[i].y = s[i].z, s[i].z = k;
      type[i] = ((s[i].x == s[i].y)<<1)|(s[i].y == s[i].z);
    }
    for (i = 0; i < H.size(); ++i) {
      count[i] = 0;
      bind[i] = -1;
    }
    for (len = 0, i = 1 - n0; i < n0; ++i)
      for (l = j = i > 0? i: 0; j < n0 && n0 + i + j < n1; ++j) {
        k = n0 + i + j;
        if (type[j] != type[k]) break;
        while (l < j && !ins(j, k))
          rm(l, k-j+l), ++l;
        if (!ins(s[j], s[k])) break;
        if (j - l + 1 > len) len = j - l + 1;
      }
    printf("%d\n", len);
  }
}
