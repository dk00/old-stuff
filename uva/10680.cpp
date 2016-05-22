#include<stdio.h>
int notp[1000001],prime[78498],lcm[78498],fac[78498];
main(){
int i,j,p,n;
prime[0]=2;
for(p=1,i=3;i<1000000;i++,i++){
    if(notp[i])continue;
    for(j=i*3;j<1000000;j+=i*2)notp[j]=1;
    prime[p++]=i;
}
while(scanf("%d",&n)){

}
}
