#include <stdio.h>

int e[20005][3];

int main(void)
{
  int T, m, n, i, j;
  scanf("%d", &T);
  while(T--){
    int d[505] = {0};
    scanf("%d%d", &n, &m);
    for(i=0;i<m;i++){
      scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
      if(e[i][2] < 0){
        int t=e[i][0];e[i][0]=e[i][1];e[i][1]=t;
      }
    }
    int update = 1;
    for(i=0;i<n && update==1; ++i){
      update = 0;
      for(j=0;j<m;j++)
      {
        if(d[e[j][0]] > d[e[j][1]] + e[j][2]) {
          d[e[j][0]] = d[e[j][1]] + e[j][2];
          update = 1;
        }
      }
    }
    if (update == 1){
      printf("NO\n");
    } else
      printf("YES\n");
  }
  return 0;
}
