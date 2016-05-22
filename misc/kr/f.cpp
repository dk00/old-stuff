#include <stdio.h>
#include <string.h>

int main(void)
{
  int T, n, w, i, x, y;
  scanf("%d", &T);
  while(T--){
    scanf("%d%d", &n, &w);
    int a[2005];
    for(i=0;i<w;i++)
      a[i] = 0;
    while(n--){
      scanf("%d%d", &x, &y);
      int que[2005], qb = 0, qe = 0;
      for(i=0;i<x-1;i++){
        while(qe > qb && a[que[qe-1]] <= a[i]) --qe;
        que[qe++] = i;
      }
      int bestpos = -1, besth = 0;
      for(;i<w;i++){
        while(qe > qb && a[que[qe-1]] <= a[i]) --qe;
        que[qe++] = i;
        while(que[qb] <= i-x) ++qb;
        if(bestpos == -1 || a[besth] > a[que[qb]]) {
          bestpos = i;
          besth = que[qb];
        }
      }
      int yy = y + a[besth];
      for(i=bestpos-(x-1); i <= bestpos; i++)
        a[i] = yy;
    }
    int mx = 0;
    for(i=0;i<w;i++)
      if(mx < a[i]) mx = a[i];
    printf("%d\n", mx);
  }
  return 0;
}
