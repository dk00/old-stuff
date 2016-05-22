
#include<iostream>
#define SIZE 100005
using namespace std;
int main(void){
  cin.sync_with_stdio(false);
  int t;
  int n,l,c[SIZE];

  char q[SIZE];
  for(cin>>t;t>0;--t)}{
    cin>>n>>l;
    for(int i=0;i<n;++i){
      cin>>q[i];
    }
    c[0] = q[0] - '0';
    for(int i=1;i<n;++i)
      c[i] = c[i-1] + q[i]-'0';
    for(int i=0;i<n;++i){
    }
  }
  return 0;
}
