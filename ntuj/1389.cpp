#include<queue>
#include<cstdio>
using namespace std;
const int N = 111, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, inf = 100000000;
struct pt {
  int x, y, z;
};
int l, h, w, d[N/10][N][N], s[11111];
char map[N/10][N][N];
inline bool valid(int x, int y, int z) {
  return (x >= 0 && x < l && y >= 0 && y < h && z >= 0 && z < w
      && map[x][y][z] != 'X');
}
main() {
  int i, j, k, n, t, x, y, z, nx, ny, nz, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d %d %d %d", &l, &h, &w, &n, &t);
    queue<pt> Q;
    for (i = 0; i < l; ++i)
      for (j = 0; j < h; ++j) {
        scanf("%s", map[i][j]);
        for (k = 0; k < w; ++k) {
          d[i][j][k] = inf;
          if (map[i][j][k] == 'S')
            Q.push((pt){i, j, k});
        }
      }
    for (i = 0; i <= t; ++i)
      s[i] = 0;
    d[Q.front().x][Q.front().y][Q.front().z] = 0;
    while (!Q.empty()) {
      x = Q.front().x, y = Q.front().y, z = Q.front().z;
      Q.pop();
      for (i= 0; i < 4; ++i) {
        nx = x;
        ny = y + dx[i];
        nz = z + dy[i];
#define UPDATE if (valid(nx, ny, nz) && d[x][y][z] + 1 < d[nx][ny][nz]) {\
          d[nx][ny][nz] = d[x][y][z] + 1;\
          Q.push((pt){nx, ny, nz});\
        }
        UPDATE
      }
      if (map[x][y][z] == 'U') {
        nx = x + 1, ny = y, nz = z;
        UPDATE
      }
      if (map[x][y][z] == 'D') {
        nx = x - 1, ny = y, nz = z;
        UPDATE
      }
    }
    while (n--) {
      scanf("%d %d %d %d", &x, &y, &z, &k);
      --x, --y, --z;
      for (i = t, j = d[x][y][z]*3; i >= j; --i)
        if (s[i-j] + k > s[i])
          s[i] = s[i-j] + k;
    }
    for (i = j = 0; i <= t; ++i)
      if (s[i] > s[j]) j = i;
    printf("%d\n", s[j]);
  }
}
