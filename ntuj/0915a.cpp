#include<iostream>
using namespace std;
int main(void){
  long long n,k,c,sum,ans;
  cin>>n;
  for(int count=1;count<=n;++count){
    cin>>k>>c;
    sum=0; ans=0;
    while(sum<k*c){
      sum+=(sum/k)+1;
      ++ans;
    }
    cout<<"Case #"<<count<<": "<<ans<<endl;
  }
  return 0;
}
