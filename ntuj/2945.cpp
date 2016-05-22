#include <stdio.h>
#include <stdlib.h>

int seg[4000005];

void init(int x, int L, int R, int k){
  if(L>R) return;
  if(L==R) seg[x] = k;
  else {
    seg[x] = k;
    init(x*2, L, (L+R)/2, k);
    init(x*2+1, (L+R)/2+1, R, k);
  }
}

int insert(int x, int L, int R, int s)
{
  if(L==R){
    seg[x] -= s;
    return L;
  }else{
    int M = (L+R)/2, ret;
    if(seg[x*2] >= s)
      ret = insert(x*2, L, M, s);
    else
      ret = insert(x*2+1, M+1, R, s);
    seg[x] = (seg[x*2] > seg[x*2+1])? seg[x*2]: seg[x*2+1];
    return ret;
  }
}

int main(void)
{
  int k, n, f = 0;
  while(scanf("%d", &k)!=EOF)
  {
    scanf("%d", &n);
    if(f) printf("\n");
    else f = 1;
    init(1, 1, n, k);
    char z[100];
    int t = n, r, s, ms = 0, v = 0, x;
    while(t > 0){
      scanf("%s", z);
      if(z[0]=='b'){
        scanf("%d%d", &r, &s);
      }else{
        s = atoi(z);
        r = 1;
      }
      while(r>0){
        x = insert(1, 1, n, s);
        v += s;
        if(ms < x) ms = x;
        --t;
        --r;
      }
    }
    printf("%d %d\n", ms, ms * k - v);
  }
}
