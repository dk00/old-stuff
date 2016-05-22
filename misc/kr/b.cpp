#include <stdio.h>
#include <string.h>

int n, m;
char a[100][100];
int r[55][55];
int dx[4]={0, 1, 0, -1}, dy[4]={-1, 0, 1, 0};
int que[2550][2]={0};
int go(int x, int y, char c){
  memset(r, -1, sizeof(r));
  int qb = 0, qe = 0;
  int sx, sy, ret=0,i;
  que[qe][0] = x;
  que[qe++][1] = y;
  r[x][y] = 0;
  while(qb < qe)
  {
    x = que[qb][0], y = que[qb][1];
    ++qb;
    if(r[x][y] >= 3) break;
    for(i=0;i<4;i++){
      sx = x+dx[i], sy = y+dy[i];
      while(sx >=0 && sx < m && sy >= 0 && sy < n) {
        if(a[sx][sy] == '.') {
          if(r[sx][sy] == -1){
            r[sx][sy] = r[x][y] + 1;
            que[qe][0] = sx;
            que[qe++][1] = sy;
          }
        }else{
          if(r[sx][sy] == -1) {
            if(a[sx][sy] == c) ++ret;
            r[sx][sy] = r[x][y]+1;
          }
          break;
        }
        sx += dx[i];
        sy += dy[i];
      }
    }
  }
  return ret;
}

int main(void)
{
  int T, i, j;
  scanf("%d", &T);
  while(T--){
    scanf("%d%d", &m, &n);
    for(i=0;i<m;i++)
      scanf("%s", a[i]);
    int cnt = 0;
    for(i=0;i<m;i++)
      for(j=0;j<n;j++){
        if(a[i][j] != '.')
          cnt += go(i, j, a[i][j]);
      }
    printf("%d\n", cnt/2);
  }
  return 0;
}
