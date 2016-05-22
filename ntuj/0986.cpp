#include <stdio.h>
#include <string.h>

int a[250][250];
int main(void)
{
  int n, t, cs=0, i, j;
  while(scanf("%d%d",&n,&t)!=EOF && n>0){
    ++cs;
    memset(a,0,sizeof(a));
    int cnt=0;
    for(i=1;i<=n;i++)
      a[i][i] = 1;
    int ii;
    for(ii=0;ii<t;ii++){
      int x, y;
      scanf("%d%d",&x, &y);
      if(a[y][x] ==1){
        ++cnt;
      }else{
        a[x][y] = 1;

        for(i=1;i<=n;i++)
          for(j=1;j<=n;j++)
            if(a[i][x] && a[y][j])
              a[i][j] = 1;
      }
    }
    printf("%d. %d\n", cs, cnt);
  }
  return 0;
}
