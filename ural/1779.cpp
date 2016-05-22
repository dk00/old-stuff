#include <stdio.h>

int a[205][205];

int main(void)
{
  int n;
  scanf("%d", &n);
  int e = 0, i, j;
  for(i=1;i<=n;i++){
    for(j=i+1;j<=n-i+1;j++)
      a[i][j] = 1, ++e;
  }
  printf("%d\n", e);
  for(i=1;i<=n;i++){
    for(j=i+1;j<=n-i+1;j++)
      if(a[i][j])
        printf("%d %d\n", i, j);
  }

  return 0;
}
