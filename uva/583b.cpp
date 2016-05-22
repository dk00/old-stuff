#include<stdio.h>
bool notp[50000];
int prime[5000];
main(){
int i,j,k,n,f,p=0;
    prime[p++]=2;
    for(i=3;i<50000;i++,i++){
        if(notp[i])continue;
        for(j=i*3;j<50000;j+=i*2)notp[j]=1;
        prime[p++]=i;
    }
    while(scanf("%d",&n) && n){
        printf("%d=",n);
        if(n<0){
            n=-n;
            f=0;
            printf(" -1");
        }
        else f=1;
        for(i=0;n>1 && i<p && prime[i]<=n/prime[i];i++){
            while(
        }
    }
}
