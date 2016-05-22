#include<cstdio>
const int dx[] = {1, 1, 1, 1, -1, -1, -1, -1},
      dy[] = {1, 1, -1, -1, 1, 1, -1, -1},
      dz[] = {1, -1, 1, -1, 1, -1, 1, -1};
main() {
  int i, j, k, x, y, z, n, min[8], max[8];
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; ++i) {
      scanf("%d %d %d", &x, &y, &z);
      for (j = 0; j < 8; ++j) {
        k = x*dx[j] + y*dy[j] + z*dz[j];
        if (!i || k < min[j]) min[j] = k;
        if (!i || k > max[j]) max[j] = k;
      }
    }
    for (j = k = 0; j < 8; ++j)
      if (max[j] - min[j] > k) k = max[j] - min[j];
    printf("%d\n", k);
  }
}
