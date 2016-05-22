#include<stdio.h>
#define MAX 32000
int notp[MAX+1]={0};
long prime[3500],q;
int isp(long n){
    for(q=0;prime[q]<=n/prime[q];q++)if(n%prime[q]==0)return 0;
    return 1;
}
main(){
long n,i,j,p,c,r;
p=notp[(prime[0]=2)-1]=1;
for(i=4;i<=MAX;i+=2)notp[i]=1;
for(i=3;i<=MAX;i+=2){
    if(!notp[i] && (prime[p++]=i))
        for(j=i*3;j<=MAX;j+=i*2)notp[j]=1;
}
while(scanf("%ld",&n) && (c=n)){
    if(n==1){puts("0");continue;}
    for(r=n,i=0;n>1 && prime[i]<=n && i<p;i++){
        if(n%prime[i]==0)c-=c/prime[i];
        while(n%prime[i]==0)n/=prime[i];
    }
    if(c==r)c-=1;
    else if(n>1)c-=c/n;
    printf("%ld\n",c);
}
}
