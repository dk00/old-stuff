#include<iostream>
#define INF 2000000000
using namespace std;
int main(void){
  cin.sync_with_stdio(false);
  int n,m,u,d,ans,x;
  while(cin>>n>>m){
    ans = INF;
    for(int i=0;i<m;++i){
      cin>>u>>d;
      x = d*n/(u+d);
      if((u+d)*x <= d*n)
        ++x;
      if(x>=n) x=n;
      if((u+d)*x-d*n < ans)
        ans = (u+d)*x-d*n;
    }
    cout<<ans<<endl;  
  }
}
