#include<iostream>
#define MAX 1000000
using namespace std;
int notp[MAX],prime[78500];
main(){
long p,i,j,n,num;
long long low,high,s;
notp[0]=notp[1]=1;
for(prime[0]=i=2;i<MAX;i+=2)notp[i]=1;
for(p=1,i=3;i<MAX;i+=2){
    if(notp[i])continue;
    for(j=i*3;j<MAX;j+=i*2)notp[j]=1;
    prime[p++]=i;
}
cin>>n;
while(n--){
    cin>>low>>high;
    for(num=i=0;i<p && prime[i]<=high/prime[i];i++){
        for(s=prime[i];s<=high/prime[i];s*=prime[i]){
            if(s*prime[i]<=high && s*prime[i]>=low)num++;
        }
    }
    cout<<num<<'\n';
}
}
