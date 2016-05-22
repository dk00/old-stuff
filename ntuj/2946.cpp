#include <stdio.h>
#include <string.h>

int a[1000005];
short c[1000005];
int d[1000005];
int p[1000005];
int r[1000005], np=0;

int main(void)
{
  int n_min, n_max, i, j, k, f=0;
  for(i=2;i<=1000;i++){
    if(!r[i]){
      p[np++] = i;
      for(j=i*i;j<=1000000;j+=i)
        r[j] = 1;
    }
  }
  for(;i<=1000000;i++)
    if(!r[i])
      p[np++] = i;
  while(scanf("%d%d", &n_min, &n_max)!=EOF)
  {
    if(f) printf("\n");
    else f = 1;
    memset(a, 0, sizeof(a));
    memset(c, 0, sizeof(c));
    memset(d, 0, sizeof(d));
    if(n_min % 2 == 0) ++n_min;
    if(n_min<0) n_min = n_max;
    for(i=0;(i+n_min>=0) && i+n_min<=n_max;i++)
      d[i] = i+n_min;
    for(j=1;j<np;j++){
      k = n_min - 1 - (n_min - 1) % p[j] + p[j];
      while(k <= n_max && k >= 0){
        if((k-1)%(p[j]-1))
          a[k - n_min] = 1;
        ++c[k - n_min];
        d[k - n_min] /= p[j];
        if(d[k - n_min] % p[j]==0)
          a[k - n_min] = 1;
        k += p[j];
      }
    }
    int cnt = 0;
    for(i=0;(i+n_min>=0) && i+n_min <= n_max;i+=2){
      if(a[i]==0 && (c[i] >= 3 || (c[i]>=2 && d[i]>1))){
        if(d[i]>1){
          if((i+n_min-1)%(d[i]-1)==0){
            ++cnt;
            printf("%d\n", i+n_min);
          }
        }else{
          ++cnt;
          printf("%d\n", i+n_min);
        }
      }
    }
    if(!cnt) printf("none\n");
  }
  return 0;
}
