#include<stdio.h>
long long p[50001],pn[50001],t[50001];
main(){
t[1]=1;
int i,j;
for(i=2;i<=50000;i++){
    pn[i]=pn[i-1];
    t[i]=t[i-1];
    if(p[i]){
        t[i]+=(pn[i]-p[i]+1)*2;
        continue;
    }
    pn[i]++;
    t[i]+=(i-1)*2;
    for(j=i*2;j<=50000;j+=i)p[j]++;
}
while(scanf("%d",&i) && i)printf("%I64d\n",t[i]);
}
