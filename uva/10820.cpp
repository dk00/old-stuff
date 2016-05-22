#include<stdio.h>
#define MAX 50000
int notp[MAX+1];
long long t[MAX+1];
main(){
long i,j,p;
for(i=4;i<=MAX;i++,i++)notp[i]=1;
for(i=3;i<=MAX;i++,i++)
   if(!notp[i])
       for(j=i*3;j<=MAX;j+=i*2)notp[j]=1;
for(t[1]=1,i=2;i<=MAX;i++){
    for(p=i,j=2;j*j<=i;j++)
        if(i%j==0){
            if(!notp[j])p-=p/j;
            if(!notp[i/j] && j*j!=i)p-=p/(i/j);
        }
    t[i]=(p-(p==i))*2+t[i-1];
}
while(scanf("%d",&i) && i)printf("%lld\n",t[i]);
}
