#include<iostream>
#include<string>
using namespace std;
int main(void){
  cin.sync_with_stdio(false);
  string s;
  int ax,an,zx,zn;
  double a,b,deta=1e-9;
  while(cin>>s){
    ax=0; an=s.size(); zx=0; zn=0;
    for(int i=0;i<s.size();++i){
      if(s[i]=='1')
        ++ax;
      if(s[i]=='0'){
        ++zn;
        int t=i+1;
        if(t==s.size()) t=0;
        if(s[t]=='1')
          zx++;
      }
    }
    a = (double)ax/an;
    b = (double)zx/zn;
    if(a > b+deta){
      cout<<"SHOOT"<<endl;
    }
    else if(b > a+deta)
      cout<<"ROTATE"<<endl;
    else
      cout<<"EQUAL"<<endl;
  }
  return 0;
} 
  
