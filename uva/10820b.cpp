#include<stdio.h>
const int N=1000000;
int p[N+1];
main(){
int i,j,k;
p[1]=1;
for(i=2;i<=N;i++)
    p[i]=i-1;
for(i=2;i<=N;i++){
    for(j=i*2;j<=N;j+=i)
        p[j]-=p[i];
    p[i]=p[i-1]+p[i]*2;
}
while(scanf("%d",&i) && i){
    printf("%d\n",p[i]);
}
}
