#include <stdio.h>
#include <string.h>
using namespace std;

int a[16][16];
int b[16][16];
int c[16][16];
int edg[105][2];
int deg[16];


int main(void) {
  int n, i, j, k;
  char p[10], q[10];
  while(scanf("%d",&n)!=EOF) {
    memset(a,0,sizeof(a));
    memset(deg, 0, sizeof(deg));
    for(i=0;i<n;i++) {
      scanf("%s%s",p, q);
      edg[i][0] = p[0]-'L';
      edg[i][1] = q[0]-'L';
      a[p[0]-'L'][q[0]-'L']=1;
      a[q[0]-'L'][p[0]-'L']=1;
      deg[p[0]-'L']++;
      deg[q[0]-'L']++;
    }
    int bb[17]={0};
    bb[0] = 1;
    int N = 15;
    int minans = 16;
    int cnt=1;
    while(bb[15] == 0) {
      int que[16], qb=0, qe=0;
      int dis[16];
      int u[16];
      for(i=0;i<N;i++)
        if(bb[i] && deg[i] == 0) {
          int j=0;
          while(bb[j]) bb[j++] = 0;
          bb[j]=1;
          break;
        }
      if(i<N) continue;
      for(i=0;i<N;i++){
        u[i] = dis[i] = 0;
        if(bb[i]){
          que[qe++] = i;
          u[i] = 1;
        }
      }
      memset(b, 0, sizeof(b));
      int flag = 0;
      while(qb < qe) {
        int x = que[qb];
        for(i=0;i<N;i++)
          if((!u[i]) && a[x][i]){
            b[x][i] = 1;
            u[i] = 1;
            que[qe++] = i;
            dis[i] = dis[x]+1;
          }else if(a[x][i] && dis[i]==0 && dis[x]==0){
            flag = 1;
            break;
          }
        ++qb;
      }
      for(i=0;i<N;i++)
        if((!u[i]) && deg[i]>0)
          break;
      ++cnt;
      if(i==N && !flag){
        int mx=0;
        for(i=0;i<N;i++)
          if(u[i] && deg[i]>0 && dis[i]>mx)
            mx = dis[i];
        if(mx == 1){
          for(i=0;i<N;i++)
            printf("%d",bb[i]);
          printf("\n");
        }
        if(mx < minans){
          for(i=0;i<N;i++)
            for(j=0;j<N;j++)
              c[i][j] = b[i][j];
          minans = mx;
        }
      }
      i=0;
      while(bb[i]) bb[i++] = 0;
      bb[i]=1;
    }
    for(k=0;k<N;k++)
      for(i=0;i<N;i++)
        for(j=0;j<N;j++)
          if(c[i][k] && c[k][j])
            c[i][j] = 1;
    printf("%d\n", minans-1);
    for(i=0;i<n;i++){
      if(c[edg[i][0]][edg[i][1]])
        printf("%c %c\n", edg[i][0]+'L', edg[i][1]+'L');
      else
        printf("%c %c\n", edg[i][1]+'L', edg[i][0]+'L');
    }
  }
  return 0;
}
