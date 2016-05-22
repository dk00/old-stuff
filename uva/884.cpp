/* @JUDGE_ID:  58589NF  884  C++  "Factorial Factors"*/
#include<stdio.h>
#include<stdlib.h>
int main(){
long n,*fa=(long *)malloc(sizeof(long)*1000001),i;
int prime[168],isP,p,j;
prime[p=0]=2;prime[++p]=3;
for(i=5;i<=1000;i+=2){
    for(j=1,isP=1;prime[j]*prime[j]<=i;j++){
        if(i%prime[j]==0){
            isP=0;
            break;
        }
    }
    if(isP) prime[++p]=i;
}
for(i=2;i<=1000000;i++)fa[i]=1;
for(j=0;j<=167;j++){
    for(i=2;i<=1000000/prime[j];i++)
        fa[i*prime[j]]=fa[i]+1;
}
for(i=3;i<=1000000;i++)fa[i]+=fa[i-1];
while(scanf("%ld",&n)!=EOF) printf("%ld\n",fa[n]);
return 0;
}
/*@END_OF_SOURCE_CODE*/
