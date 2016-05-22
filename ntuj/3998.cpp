#include <cstdio>
#include <vector>
using namespace std;

vector<int> p;
vector<int> q;
unsigned char a[10000001];
vector<int> sol;

int main(void)
{
  int T;
  int i, j, k;
  for(i=2;i<=1000;i++){
    if(!a[i]){
      p.push_back(i);
      for(j=i*i;j<=100000;j+=i)
        a[j] = 1;
    }
  }
  for(;i<=100000;i++)
    if(!a[i])
      p.push_back(i);
  printf("%d\n", p.size());
  int c = 2;
  int M = 10000000, HIGH = 2000000000;
  int r = 1;
  q.push_back(p[0]);
  for(i=100001;i<=2000000000;i+=M, ++c){
    for(j=0;p[j]<=44722;j++)
      for(k=((i+p[j]-1)/p[j]*p[j]-i);k<M;k+=p[j]) {
        a[k] = c;
      }
    for(j=0;j<M && i+j<=HIGH;j++)
      if(a[j]!=c) {
        p.push_back(j+i);
      }
    while(r < p.size()-1) {
      if(p[r] - p[r-1] < 40 || p[r+1] - p[r] < 40)
        q.push_back(p[r]);
      ++r;
    }
    printf("i=%d, size=%d; %d\n", i, p.size(), q.size());
  }
  /*
  for(;i<=2000000000;i+=2){
    if(i%100000==1) printf("%d , size=%d\n", i, p.size());
    for(j=1;p[j]<=44722;j++)
      if(i%p[j]==0) break;
    if(p[j]>44722)
      p.push_back(i);
  }
  printf("%d\n", p.size());*/

  scanf("%d", &T);
  while(T--){
    
  }
  return 0;
}
