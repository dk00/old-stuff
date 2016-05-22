#include<stdio.h>
double c[50001];
long n,k,i;
main(){
c[1]=1;
c[2]=0.5;
for(i=3;i<=50001;i++)
    c[i]=c[i-1]*(i*2-3)/(i*2-2);
scanf("%ld",&k);
for(;k>0;k--){
    scanf("%ld",&n);
    printf("%.4lf\n",1-c[n/2]);
}
}
