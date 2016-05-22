#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;

int ans[11][11][11];

int ns = 0;
set<int> s[11];
int sol = 0;

int r[20][2];
const long long p1 = 107, p2 = 1000000007;

int draw(int r[][2], int lev)
{
  int w = 5, h = 5;
  int i, j, k;
  for(i=0;i<lev;i++)
    printf("(%d,%d)", r[i][0], r[i][1]);
  printf("\n");
  int g[10][10]={0}, mX=r[0][0], mY=r[0][1];
  for(i=0;i<lev;i++){
    if(mX > r[i][0]) mX = r[i][0];
    if(mY > r[i][1]) mY = r[i][1];
  }
  for(i=0;i<lev;i++)
    g[r[i][0]-mX][r[i][1]-mY] = 1;
  for(i=0;i<w;i++, printf("\n"))
    for(j=0;j<h;j++)
      printf("%c", g[i][j]?'O':'.');
  printf("===============\n");
  
}

int gethash(int t[][2], int n)
{
  int i, j, ret = 0, mX=t[0][0], mY=t[0][1];
  for(i=0;i<n;i++)
    for(j=i+1;j<n;j++){
      if(t[i][0] > t[j][0] || t[i][0] == t[j][0] && t[i][1] > t[j][1]) {
        int w = t[i][0];t[i][0] = t[j][0];t[j][0] = w;
        w = t[i][1];t[i][1] = t[j][1];t[j][1] = w;
      }
    }
  for(i=0;i<n;i++) {
    if(mX > t[i][0]) mX = t[i][0];
    if(mY > t[i][1]) mY = t[i][1];
  }
  for(i=0;i<n;i++)
  {
    ret = (int)((
        (ret * p1 + t[i][0] -mX+1)% p2 * p1
        + t[i][1]-mY+1) % p2);
  }
  return ret;
}

int fx[4]={1, 0, -1, 0}, fy[4]={0, 1, 0, -1};

void rotate(int t[][2], int n){
  for(int i=0;i<n;i++)
  {
    int w = t[i][0];
    t[i][0] = t[i][1];
    t[i][1] = -w;
  }
  //draw(t, n);
  //printf("h=%d\n", gethash(t, n));
}
void mirror(int t[][2], int n){
  for(int i=0;i<n;i++)
    t[i][1] = -t[i][1];
  //draw(t, n);
  //printf("h=%d\n", gethash(t, n));
}
int N;
bool within_size(int r[][2], int lev, int w, int h){
        int ax = r[0][0], bx = r[0][0], ay = r[0][1], by = r[0][1], ii;
        for(ii=0;ii<lev;ii++){
          if(ax < r[ii][0]) ax = r[ii][0];
          if(bx > r[ii][0]) bx = r[ii][0];
          if(ay < r[ii][1]) ay = r[ii][1];
          if(by > r[ii][1]) by = r[ii][1];
        }
        if(ax - bx + 1 <= w && ay - by + 1 <= h ||
            ax - bx + 1 <=h && ay - by + 1 <= w)
          return true;
        return false;
}

void dfs(int lev, int w, int h)
{
  int i, j, k, t[20][2];
  for(i=0;i<lev;i++)
    t[i][0] = r[i][0], t[i][1] = r[i][1];
  int hh, h0;
  hh = gethash(t, lev);
  h0 = hh;
  for(i=0;i<3;i++){
    if(s[lev].find(hh) != s[lev].end()) return;
    rotate(t, lev);
    hh = gethash(t, lev);
  }
  if(s[lev].find(hh) != s[lev].end()) return;
  mirror(t, lev);
  hh = gethash(t, lev);
  for(i=0;i<3;i++){
    if(s[lev].find(hh) != s[lev].end()) return;
    rotate(t, lev);
    hh = gethash(t, lev);
  }
  if(s[lev].find(hh) != s[lev].end()) return;
  s[lev].insert(h0);
  if(lev == N && within_size(t, lev, w, h))
    ++sol;
  //printf("OK\n");
  //draw(r, lev);

  if(lev==N) return;
  for(i=0;i<lev;i++){
    for(j=0;j<4;j++){
      int xx = r[i][0] + fx[j], yy = r[i][1] + fy[j];
      //printf("i=%d j=%d, (%d, %d)->(%d, %d)\n", i, j, r[i][0], r[i][1], xx, yy);
      for(k=0;k<lev;k++)
        if(xx == r[k][0] && yy==r[k][1])
          break;
      if(k==lev){
        r[lev][0] = xx;
        r[lev][1] = yy;
        
          dfs(lev+1, w, h);
      }
    }
  }
  return;
}

int go(int n, int w, int h) {
  r[0][0] = 0;
  r[0][1] = 0;
  N = n;
  for(int i=1;i<=n;i++)
    s[i].clear();
  sol = 0;
  dfs(1, w, h);
  return sol;
}

int main(void)
{
  int n, w, h;
  memset(ans, -1, sizeof(ans));
  while(scanf("%d%d%d", &n, &w, &h)!=EOF)
  {
    if(ans[n][w][h] == -1) {
      ans[n][w][h] = go(n, w, h);
      ans[n][h][w] = ans[n][w][h];
    }
    printf("%d\n", ans[n][w][h]);
  }
  return 0;
}
