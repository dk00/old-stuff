#include<map>
#include<cstdio>
const int N = 100005, dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
struct pt {
  int x, y, z;
} s[N];
inline void go(int& a, int b, int d) {
  if (s[b].x*dx[d] + s[b].y*dy[d] > s[a].x*dx[d] + s[a].y*dy[d])
    a = b;
}
main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int i, j, k, n, m, sum, D[4], A, B, C;
    scanf("%d", &n);
    for (i = D[0] = D[1] = D[2] = D[3] = 0; i < n; ++i) {
      scanf("%d %d %d", &s[i].x, &s[i].y, &s[i].z);
      if (s[i].x > s[D[0]].x) D[0] = i;
      if (s[i].x < s[D[1]].x) D[1] = i;
      if (s[i].y > s[D[2]].y) D[2] = i;
      if (s[i].y < s[D[3]].y) D[3] = i;
    }
    scanf("%d", &m);
    sum = 0;
    while (m--) {
      scanf("%d %d %d", &i, &j, &k);
      A = i;
      if (n < 99) {
        for (B = i; B < n; B += j)
          go(A, B, k);
        sum += s[A].z;
        continue;
      }
      C = i + (n-i-1)/j*j;
      go(A, C, k);
      for (int l = 0; l < 4; ++l)
        if (i <= D[l] && C >= D[l]) {
          B = i + (D[l]-i)/j*j;
          go(A, B, k);
          if (B + j < n) go(A, B + j, k);
        }
      sum += s[A].z;
    }
    printf("%d\n", sum);
  }
}
