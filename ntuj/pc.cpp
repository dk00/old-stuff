#include <stdio.h>

int main(void)
{
  int n, m, k;
  while(scanf("%d%d%d", &n, &m, &k)!=EOF) {
    if((n-1)%k!=0) {
      puts("Invalid\n");
      continue;
    }
    int a = (n-1)/k, c = (m-k)/k;
    if(c < a-1 || c > a*(a-1)/2) {
      puts("Invalid\n");
      continue;
    }
    int p[505][505]={};
    for(i=0;i<n;i++) {
      
    }
  }
}
