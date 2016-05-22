#include<stdio.h>
bool notp[1000000];
int prime[120053];
main(){
freopen("test!.out","w",stdout);
int i,j,p=0,n,r,t;
prime[p++]=2;
for(i=3;i<1000000;i++){
    if(notp[i])continue;
    for(j=i*3;j<1000000;j+=i*2)notp[j]=1;
    prime[p++]=i;
}
printf("%d\n",p);
scanf("%d",&n);
for(i=0;i<p;i++){
    for(t=1,r=n/prime[i];r>1;r/=prime[i])t+=r;
    printf("%d^%d\n",prime[i],t);
}
}
