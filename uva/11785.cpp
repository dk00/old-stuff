#include<cstdio>
const int N = 1025;
int deg[N];
int Dis(int a,int b){
  int k = 0;
  while(a>0 || b>0){
    k += (a^b)&1;
    a >>= 1;
    b >>= 1;
  }
  return k;
}

main(){
  int i,j,k,n,m,dim,hyper;
  while (scanf("%d %d",&n,&m)==2 && n+m){
    hyper = 1;
    for (i = n,dim = 0;i > 1;i >>= 1,++dim)
      if (i>1 && i%2 != 0)
        hyper = 0;
    if (m*2 != n*dim) hyper = 0;
    for (i = 0;i < n;++i)
      deg[i] = 0;
    while (m--) {
      scanf("%d %d",&j,&k);
      if (Dis(j,k)!=1)
        hyper = 0;
      if (j < 0 || j >= n) hyper = 0;
      else ++deg[j];
      if (k < 0 || k >= n) hyper = 0;
      else ++deg[k];
    }
    for (i = 0;i < n;++i)
      if (deg[i] != dim) hyper = 0;
    puts(hyper?"YES":"NO");
  }
}
