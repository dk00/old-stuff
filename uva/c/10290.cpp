#include<iostream>
using namespace std;
bool notp[30000001];
long prime[1857859];
main(){
int i,j,p=1,k,f,odd,perfect;
prime[0]=2;
for(i=3;i<30000000;i+=2){
    if(notp[i])continue;
    for(j=i*3;j<30000000;j+=i*2)notp[j]=1;
    prime[p++]=i;
}

long long n,g;
while(cin>>n){
    while(n%2==0)n>>=1;
    for(f=0,i=k=1;i<p && prime[i]<=n/prime[i];i++){
        for(f=0;n%prime[i]==0;f++)n/=prime[i];
        if(f)k*=(f+1);
    }
    if(n>1)k*=2;
    cout<<k<<'\n';
}
}
