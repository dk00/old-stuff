#include<stdio.h>
#define max 1001
int notp[max],prime[300];
main(){
int i,j,p,n;
prime[0]=2;
for(p=1,i=3;i<max;i++,i++){
    if(notp[i])continue;
    for(j=i*3;j<max;j+=i*2)notp[j]=1;
    prime[p++]=i;
}
while(scanf("%d",&n) && n){
    printf("%d: ",n);
    for(i=j=0;n>1 && prime[i]<=n/prime[i] && i<p;i++){
        if(n%prime[i]==0)j++;
        while(n%prime[i]==0)n/=prime[i];
    }
    if(n>1)j++;
    printf("%d\n",j);
}
}
