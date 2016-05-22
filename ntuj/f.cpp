#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define M 60
using namespace std;
double per(int* x, int n){
  double ret=1;
  for(int i=2,j=1;i<=n;++i){
    ret*=i;
    if(x[i-1]==x[i-2]){
      ++j;
      ret/=j;
    }
    else
      j=1;
  }
  return ret;
}
int main(void){
  double p[M],ans;
  int t,n,m,q,now[M];
  cin>>t;
  for(int C=1;C<=t;++C){
    cin>>m;
    for(int i=0;i<m;++i)
      cin>>p[i];
    cout<<"Test Case #"<<C<<":"<<endl;
    cin>>q;
    for(int j=0;j<q;++j){
      ans=1;
      cin>>n;
      for(int i=0;i<n;++i){
        cin>>now[i];
        --now[i];
      }
      for(int i=0;i<n;++i)
        ans*=p[now[i]];
      sort(now,now+n);
      ans*=per(now, n);
      double x=log(ans)/log(10);
      printf("%.5lf x 10^%.0lf\n",pow(10, x-floor(x)), floor(x));
    }

  }
  return 0;
}
