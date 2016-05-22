#include<stdio.h>
long long f[51];
main(){
int i,n,k;
f[0]=1,f[1]=2,f[2]=3;
for(i=3;i<51;i++)f[i]=f[i-1]+f[i-2];
scanf("%d",&n);
for(k=1;k<=n;k++){
    scanf("%d",&i);
    printf("Scenario #%d:\n%lld\n\n",k,f[i]);
}
}
