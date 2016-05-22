#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int a[16][16];
int deg[16]={0};
int dp[65536] = {0};
int from[65536] = {0};

int main(void)
{
  int n, i, j;
  while(scanf("%d",&n)!=EOF)
  {
    memset(a, 0, sizeof(a));
    memset(deg, 0, sizeof(deg));
    int p[16], pn=0;
    int edg[105][2];
    char xx[3], yy[3];
    vector<int> inds;
    for(i=0;i<n;i++){
      scanf("%s%s",xx,yy);
      int x=xx[0]-'L', y = yy[0]-'L';
      edg[i][0]=x;
      edg[i][1]=y;
      a[x][y] = 1;
      a[y][x] = 1;
      if(deg[x]++==0) p[pn++] = x;
      if(deg[y]++==0) p[pn++] = y;
    }
    int bb[16]={0};
    int bcnt = 1;
    bb[0] = 1;
    while(bb[pn]==0){
      int cc[16], cn=0;
      for(i=0;i<pn;i++){
        if(bb[i])
          cc[cn++] = p[i];
      }
      for(i=0;i<cn;i++){
        for(j=i+1;j<cn;j++)
          if(a[cc[i]][cc[j]])
            goto NEXT_ROUND;
      }
      inds.push_back(bcnt);
NEXT_ROUND:
      i=0;
      while(bb[i]) bb[i++]=0;
      bb[i]=1;
      ++bcnt;
    }
    memset(dp,0,sizeof(dp));
    dp[0] = 0;
    from[0] = -1;
    int INF = 20;
    /*for(i=0;i<inds.size();i++)
      printf("%d ", inds[i]);
    printf("\n");*/
    for(i=1;i<(1<<pn);i++){
      dp[i] = INF;
      for(j=0;j<inds.size();j++){
        if(inds[j]&(~i)) continue;
        if(dp[i] > dp[i^inds[j]]+1) {
          dp[i] = dp[i^inds[j]]+1;
          from[i] = inds[j];
        }
      }
    }
    int x = (1<<pn)-1;
    int ans = dp[x], lay;
    printf("%d\n", ans-2);
    lay = ans;
    int m[16]={0};
    while(x>0){
//      printf("from[%d]=%d\n", x, from[x]);
      for(i=0;i<pn;i++)
        if((1<<i)&from[x]){
//          printf("p[i]=%d\n", p[i]);
          m[p[i]] = lay;
        }
      x ^= from[x];
      lay--;
    }
    for(i=0;i<n;i++)
    {
//      printf("l1 %d l2 %d\n", m[edg[i][0]], m[edg[i][1]]);
      if(m[edg[i][0]] > m[edg[i][1]]) {
        printf("%c %c\n", edg[i][0]+'L', edg[i][1]+'L');
      }else
        printf("%c %c\n", edg[i][1]+'L', edg[i][0]+'L');
    }
  }
  return 0;
}
