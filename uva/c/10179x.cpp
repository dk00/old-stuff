#include<stdio.h>
#define MAX 32000
int notp[MAX+1]={0};
long prime[3500],q;
int isp(long n){
   for(q=0;prime[q]<=n/prime[q];q++)if(n%prime[q]==0)return 0;
   return 1;
}
main(){
long n,i,j,p,c;
p=notp[(prime[0]=2)-1]=1;
for(i=4;i<=MAX;i+=2)notp[i]=1;
for(i=3;i<=MAX;i+=2){
   if(!notp[i] && (prime[p++]=i))
       for(j=i*3;j<=MAX;j+=i*2)notp[j]=1;
}
while(scanf("%ld",&n) && (c=n)){
   for(i=2;i*i<=n;i++){
       if(n%i==0){
           if(!notp[i])c-=c/i;
           if(i!=n/i && isp(n/i))c-=c/(n/i);
       }
   }
   if(n==1)puts("1");
   else printf("%ld\n",c-(n==c));
}
}
