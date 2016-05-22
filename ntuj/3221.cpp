#include <stdio.h>
#include <string.h>

int a[100005];
int p[100005], np=0;
int v[100005], nv=0;

int main(void)
{
  int i, j;
  for(i=2;i<=1000;i++){
    if(!a[i]){
      p[np++] = i;
      for(j=i*i;j<=100000;j+=i)
        a[j] = 1;
    }
  }
  for(;i<=100000;i++)
    if(!a[i])
      p[np++] = i;
  int n, m;
  while(scanf("%d%d", &n, &m)!=EOF)
  {
    memset(v, 0, sizeof(v));
    int b[15]={0}, c[15]={0}, d[15]={0}, nb = 0;
    int t = m;
    for(i=0;i<np && p[i] *p[i] <= t; i++){
      if(t%p[i]==0) {
        b[nb] = p[i];
        c[nb] = 0;
        while(t%p[i]==0){
          t/=p[i];
          c[nb] ++;
        }
        ++nb;
      }
    }
    if(t>1){
      b[nb] = t;
      c[nb++] = 1;
    }
    for(i=0;i<nb;i++)
      d[i] = 0;
    nv = 0;
    if(m==1) v[nv++] = 1;
    for(i=1;i<n;i++){
      int tp = i;
      for(j=0;j<nb;j++){
        while(tp % b[j]==0){
          --d[j];
          tp/=b[j];
        }
      }
      tp = n-i;
      for(j=0;j<nb;j++){
        while(tp % b[j]==0){
          ++d[j];
          tp/=b[j];
        }
      }
      for(j=0;j<nb;j++)
        if(d[j] < c[j])
          break;
      if(j==nb) {
        v[nv++] = i+1;
      }
    }
    printf("%d\n", nv);
    for(i=0;i<nv;i++)
      printf("%d%s", v[i], i==nv-1?"":" ");
    printf("\n");
  }
  return 0;
}
