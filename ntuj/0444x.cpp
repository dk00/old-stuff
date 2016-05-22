#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n,q[5005];
int count(int d){
  int s=0,t[5005];
  vector<int> v;
  vector<int>::iterator a,b;
  for(int i=0;i<n;++i)
    t[i]=q[i];
  if(t[0]==0){
    ++s;
    v.push_back(0);
  }
  for(int i=1;i+d<=n;++i){
    if(i-d+1>0)
      a=lower_bound(v.begin(),v.end(),i-d+1);
    else
      a=v.begin();
    b=upper_bound(v.begin(),v.end(),i-1);
    if((b-a)&1)
      t[i]=1-t[i];
    if(t[i]==0){
      v.push_back(i);
      ++s;
    }
  }
  for(int i=n-d+1;i<n;++i){
    if(i-d+1>0)
      a=lower_bound(v.begin(),v.end(),i-d+1);
    else
      a=v.begin();
    b=upper_bound(v.begin(),v.end(),i-1);
    if((b-a)&1)
      t[i]=1-t[i];
    if(t[i]==0)
      return -1;
  }
  return s;
}
int main(void){
  int a[5005],k,m;
  char t;
  while(cin>>n){
    k=1;
    m=0;
    for(int i=0;i<n;++i){
      cin>>t;
      if(t=='B'){
        q[i]=0;
        ++m;
      }
      else 
        q[i]=1;
    }
    for(int i=1;i<=n;++i)
      a[i]=0;
    for(int i=2;i<=n;++i){
      if(a[i]!=-1){
        a[i]=count(i);
        if(a[i]==-1)
          for(int j=i+i;j<=n;j+=i)
            a[j]=-1;
      }
      if(a[i]>0 && a[i]<m){
        k=i;
        m=a[i];
      }
    }
    cout<<k<<" "<<m<<endl;
  }
  return 0;
}
