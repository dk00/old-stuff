#include <stdio.h>

double a[405][405] = {{0}};
double s[405][405] = {{0}};
int main(void)
{
  int i, j, k;
  a[1][1] = 1.0;
  s[1][1] = 0.0;
  for(k=1;k<=400;k++)
    s[1][k+1] = 1.0;
  a[0][0] = 1.0;
  for(k=0;k<=400;k++)
    s[0][k] = 1.0;
  for(i=2;i<=400;i++){
    for(k=0;k<=i-1;k++){
      for(j=0;j<=i-1;j++){
        a[i][k+1] += a[j][k] * s[i-1-j][k] + a[i-1-j][k] * s[j][k]
          + a[j][k] * a[i-1-j][k];
      }
      a[i][k+1] /= i;
    }
    s[i][0] = 0.0;
    for(k=0;k<=400;k++)
      s[i][k+1] = s[i][k] + a[i][k];
  }
  /*
  for(i=1;i<=5;i++, printf("\n"))
    for(j=1;j<=5;j++)
      printf("%.3f ", a[i][j]);
  printf("==\n");
  for(i=1;i<=5;i++, printf("\n"))
    for(j=1;j<=5;j++)
      printf("%.3f ", s[i][j]);*/
  int n;
  scanf("%d", &n);
  double ans = 0.0;
  for(i=0;i<=n;i++){
    ans += a[n-2][i] * (i + 1);
  }
  printf("%.10lf\n", (ans-1)*10.0);
  return 0;
}
