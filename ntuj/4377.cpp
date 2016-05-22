#include <stdio.h>

int main(void)
{
  int rh, rv, sh, sv;
  int n;
  while(scanf("%d%d%d%d",&rh,&rv,&sh,&sv)!=EOF){
  scanf("%d",&n);
  int mc = -1, i;
  for(i=0;i<n;i++){
    int a, b, c, d, e, x, y, z = 0;
    scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
    x = (rh + a - 1) / a;
    if (x < (sh + c - 1) / c)
      x = (sh+c-1)/c;
    y = (rv + b - 1) / b;
    if (y < (sv + d - 1) / d)
      y = (sv + d - 1)/d;
    z = x*y;
    x = (rh + b - 1)/b;
    if (x < (sh + d - 1) / d)
      x = (sh+d-1)/d;
    y = (rv + a - 1)/a;
    if (y < (sv + c - 1)/c)
      y = (sv+c-1)/c;
    if (z > x*y)
      z = x*y;
    if(mc==-1 || z*e < mc)
      mc = z*e;
  }
  printf("%d\n", mc);
  }
}
