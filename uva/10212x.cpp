#include<stdio.h>
#define MAX 20000000
bool notp[MAX+1]={0};
long prime[1270608];
main(){
long p,i,j,f[10],n,m,k;
p=notp[(prime[0]=2)-1]=1;
for(i=4;i<=MAX;i+=2)notp[i]=1;
for(i=3;i<=MAX;i+=2){
    if(!notp[i] && (prime[p++]=i))
        for(j=i*3;j<=MAX;j+=i*2)notp[j]=1;
}
while(scanf("%ld %ld",&n,&m)!=EOF){
    m=n-m;
    for(i=0;i<10;i++)f[i]=0;
    for(i=0;prime[i]<=n && i<1270607;i++){
        for(k=n;k;f[prime[i]%10]+=(k/=prime[i]));
    }
    for(i=0;prime[i]<=m && i<1270607;i++){
        for(k=m;k;f[prime[i]%10]-=(k/=prime[i]));
    }
    f[2]-=f[5];
    f[2]%=4;f[3]%=4;f[7]%=4;f[9]%=2;
    for(n=1;f[2]>0;f[2]--)n=(n*2)%10;
    while(f[3]-->0)n=(n*3)%10;
    while(f[7]-->0)n=(n*7)%10;
    while(f[9]-->0)n=(n*9)%10;
    printf("%ld\n",n);
}
}
