#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;

char a[105][105];
char z[105][105];
int s[105][105];
int n;

char r[50][50][5040];
class XD{
  public:
  int x, y, t;
  XD(int xx, int yy, int tt):x(xx), y(yy), t(tt){}
};
queue<XD> que;
const int cyc = 5040;

int fx[5]={0, 1, 0, -1, 0};
int fy[5]={0, 0, 1, 0, -1};

int check(int x, int y, int t){
  int v = t % cyc;
  if(x<0 || x>=n || y<0 || y>=n) return -1;
  int ch = 0;
  if(s[x][y] != 0 && (t % (2*s[x][y]) >= s[x][y])) ch = 1;
  ch ^= (a[x][y]=='.');
  if(ch){
    if(x==n-1 && y==n-1) return t; //success
    if(!r[x][y][v]){
      r[x][y][v] = 1;
      que.push(XD(x, y, t));
    }
  }
  return -1;
}

int main(void)
{
  int i, j, f=0;
  while(scanf("%d",&n)!=EOF)
  {
    if(!f) f=1;
    else printf("\n");
    for(i=0;i<n;i++)
      scanf("%s",a[i]);
    for(i=0;i<n;i++)
      scanf("%s",z[i]);
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        s[i][j] = z[i][j] - '0';
    memset(r, 0, sizeof(r));
    while(!que.empty()) que.pop();
    que.push(XD(0, 0, 0));
    int mnt = -1;
    while(!que.empty()){
      XD st = que.front();
      que.pop();
      for(i=0;i<5;i++){
        mnt = check(st.x +fx[i], st.y+fy[i], st.t+1);
        if(mnt != -1)
          break;
      }
      if(mnt!=-1)
        break;
    }
    if(mnt != -1) 
      printf("%d\n", mnt);
    else
      printf("NO\n");
  }
  return 0;
}
