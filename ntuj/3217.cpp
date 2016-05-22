#include <stdio.h>

double a[100005];
double b[100005], c[100005];

int main(void)
{
  int m, n;
  int k, f=0, i;
  while(scanf("%d%d%d", &m, &n, &k)!=EOF){
    if(f==0) f=1;
    else printf("\n");
    for(i=0;i<k;i++){
      scanf("%lf", &a[i]);
    }
    int st=0;
    b[0] = a[0];
    c[0] = b[0];
    for(i=1;i<m;i++)
      b[i] = b[i-1] + a[i];
    for(i=m;i<k;i++)
      b[i] = b[i-1] + a[i] - a[i-m];
    for(i=1;i<n;i++)
      c[i] = c[i-1] + a[i];
    for(i=n;i<k;i++)
      c[i] = c[i-1] + a[i] - a[i-n];
    for(i=n-1;i<k;i++){
      if(b[i] * n > c[i] * m){
        if(st!=1){
        printf("BUY ON DAY %d\n", i+1);
        st = 1;
        }
      }
      else {
        if(st!=2){
        printf("SELL ON DAY %d\n", i+1);
        st = 2;
        }
      }
    }
  
  }
  return 0;
}
