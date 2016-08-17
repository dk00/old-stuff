#include<stdio.h>
#define MAX 1000001
int dprime[MAX]={0};
int pr[MAX]={0};
main(){
long i,j,k,n;
long prime[100000],isP,p;
prime[p=0]=2;prime[++p]=3;
pr[2]=pr[3]=1;
for(i=5;i<=MAX;i+=2){
    for(j=1,isP=1;prime[j]*prime[j]<=i;j++){
        if(i%prime[j]==0){
            isP=0;
            break;
        }
    }
    if(isP){
        prime[++p]=i;
        pr[i]=1;
    }
}
for(i=0;i<=p;i++){
    for(n=prime[i],k=n%10;n/=10;k+=n%10);
    if(pr[k])dprime[prime[i]]=1;
}
for(i=j=0;i<=MAX;i++){
    if(dprime[i])j++;
    dprime[i]=j;
}
scanf("%ld",&n);
while(n-- && scanf("%ld %ld",&i,&j))
    printf("%d\n",dprime[j]-dprime[i-1]);
}
