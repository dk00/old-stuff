#include <stdio.h>

long long F[70], SF[70], D[70], SD[70], T[70];
int mI;

long long go(long long k){
  int i;
  if(k<0) return 0LL;
  if(k==1) return 1LL;
  else if(k==0) return 0LL;

  for(i=0;i<mI;i++)
    if(SF[i] > k)
      break;
  long long ret = SD[i-1];
  k -= SF[i-1];
  if(k>0) {--k, ++ret;}
  ret += go(k) + k;
  return ret;
}

long long findans(long long n)
{
  int i;
  long long ret = 0;
  for(i=0;i<mI;i++)
    if(T[i] > n)
      break;
  n -= T[i-1];
  ret += SD[i-1] + n/i;
  long long k = n/i;
  if(k>0) --k;
  ret += go(k);
  long long rf = SF[i-1]+n/i+1;
  int m = (int)(n % (long long)i);
  for(int j = i; j>1 && m>0; j--, --m){
    if(rf >= F[j+1]){
      rf -= F[j+1];
      ++ret;
    }
  }
  return ret;
}

int main(void)
{
  long long n;
  int i;
  F[0] = 0;
  F[1] = 1;
  SF[0] = 0;
  SF[1] = 1;
  for(i=2;i<70 && F[i-1]>0;++i) {
    F[i] = F[i-1] + F[i-2];
    SF[i] = SF[i-1] + F[i];
  }
  D[0] = 0;
  D[1] = 1;
  SD[0] = 0;
  SD[1] = 1;
  for(i=2;i<70 && D[i-1]>0;i++){
    D[i] = F[i] + SD[i-2];
    SD[i] = SD[i-1] + D[i];
  }
  T[0] = 0;
  T[1] = 1;
  for(i=2;i<70 && T[i-1]>0;i++){
    T[i] = T[i-1] + F[i] * i;
  }
  mI = i-1;
  /*fprintf(stderr, "mI=%d\n", mI);
  for(i=0;i<mI;i++)
    fprintf(stderr,"i=%d, F=%lld, SF=%lld, D=%lld, SD=%lld, T=%lld\n", 
        i,
        F[i], SF[i], D[i], SD[i], T[i]);*/

  while(scanf("%lld",&n)!=EOF)
  {
    long long ans = findans(n);
    printf("%lld\n", ans);
  }
  return 0;
}
