#include<stdio.h>
#define MAX 2703664
#define P 1650
int fact[MAX+1],notp[P],prime[260];
main(){
int i,j,p=1,n,f,stt,end,mid,C=1;
prime[0]=2;
for(i=3;i<P;i++,i++){
    if(notp[i])continue;
    for(j=i*3;j<P;j+=i*2)notp[j]=1;
    prime[p++]=i;
}
for(i=0;i<=MAX;i++)fact[i]=1;
for(i=0;i<p;i++)
    for(j=2;j<=MAX/prime[i];j++)
        fact[j*prime[i]]=fact[j]+1;
for(i=3;i<=MAX;i++)fact[i]+=fact[i-1];
while(scanf("%d",&n) && n>=0){
    printf("Case %d: ",C++);
    if(!n){
        puts("0!");
        continue;
    }
    for(stt=2,end=MAX,mid=MAX/2;stt<end;mid=(stt+end)/2){
        if(fact[mid]==n)break;
        else if(fact[mid]>n)end=mid-1;
        else stt=mid+1;
    }
    if(fact[mid]==n)printf("%d!\n",mid);
    else puts("Not possible.");
}
}
