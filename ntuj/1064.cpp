#include<iostream>
#include<algorithm>
#define MAX 1000000
using namespace std;
int main(void){
  int t,n,a[5005],b[5005],ma,mb,mf,bg,ed,na,nb,ans;
  for(cin>>t;t>0;--t){
    cin>>n;
    for(int i=0;i<n;++i)
      cin>>a[i]>>b[i];
    ans=MAX; bg=0; ed=MAX;
    while(ed>=bg){
      int tnow = (ed+bg)/2;
      int now = tnow+1;
      bool y=1;
      //check
      ma=0; mb=0; mf=0; na=0; nb=0;
      for(int i=0;i<n;++i){
        na+=a[i];
        nb+=b[i];

        if(na>now){
          if(na-now>min(ma,mf)){
            y=0;
            break;
          }
          else{
            ma -= (na-now);
            mf -= (na-now);
            na = now;
            mb = min(mb,mf);
          }
        }

        if(nb>now){
          if(nb-now>min(mb,mf)){
            y=0;
            break;
          }
          else{
            mb -= (nb-now);
            mf -= (nb-now);
            nb = now;
            ma = min(ma,mf);
          }
        }
        if(mf < na+nb)
          ++mf;
        if(ma<na)
          ++ma;
        if(mb<nb)
          ++mb;
      }
      if(y && tnow<ans) 
        ans=tnow;
      if(y)
        ed = tnow-1;
      else
        bg = tnow+1;

    }
    cout<<ans<<endl;
  }
  return 0;
}
