#include <stdio.h>

int a[100005];
int main(void)
{
  int n, i;
  while(scanf("%d", &n)!=EOF){
    for(i=1;i<=n;i++)
      a[i] = i;
    for(i=2;i<n;i++)
    {
      a[i] = 1;
      a[1] = i;
      int j = i;
      while(j>1){
        a[j] = a[j/2];
        a[j/2] = 1;
        j/=2;
      }
    }
    a[n] = 1;
    a[1] = n;
    for(i=1;i<=n;i++)
      printf("%d%s", a[i], i==n?"":" ");
    printf("\n");
  }
  return 0;
}
