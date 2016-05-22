#include <stdio.h>

int nprime[65536];

int pow(long long n,int k,int m){
  if(k==0)return 1;
  if(k%2==1)
    return n * pow(n,k-1,m) % m;
  n=pow(n,k/2,m);
  return n * n % m;
}
bool witness(int a,int n){
  int x,y,u,t;
  for(u=n-1,t=0;u%2==0;u/=2,t++);
  x=pow(a,u,n);
  while(t--){
    y=x;
    x=pow(x,2,n);
    if(x==1 && y!=1 && y!=n-1)
      return 1;
  }
  return x!=1;
}
bool prime(long long n){
  if(n-1>=2 && witness(2,n))return 0;
  if(n-1>=3 && witness(3,n))return 0;
  if(n-1>=7 && witness(7,n))return 0;
  if(n-1>=61 && witness(61,n))return 0;
  if(n-1>=24251 && witness(24251,n))return 0;
  //if(n==46856248255981ll)return 0;
  //printf("%lld\n", n);
  return 1;
}

int main(void)
{
  int T, a, b, k, s;
  scanf("%d", &T);
  while(T--){
    scanf("%d%d%d%d", &a, &b, &k, &s);
    unsigned short lasti, j, js, lastis;
    int i;
    for(i=0;i<65536;i++)
      nprime[i]=0;
    lasti = s;
    for(i=a;i<a+s;i++){
      nprime[i-a] = nprime[lasti] + prime(i);
      lasti = i - a;
    }
    j = s;
    int cnt = 0;
    js = 0;
    lastis = 65535;
    for(i=a+s;i<=b;i++){
      int v = prime(i);
      nprime[j] = nprime[lasti] + v;
      if(v && (nprime[js] != nprime[lastis]) &&
          nprime[j] - nprime[lastis] == k)
        ++cnt;
      ++lasti;
      ++j;
      ++js;
      ++lastis;
//      if (v && (nprime[j] - nprime[j - (unsigned short)s] == k))

    }
    printf("%d\n", cnt);
  }
  return 0;
}
