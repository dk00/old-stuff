#include<stdio.h>
#include<stdlib.h>
long m[1572864],b[21];
main(){
long n,k,i,j;
for(b[0]=i=1;i<21;i++)b[i]=b[i-1]*2;
m[0]=0;
m[1]=m[2]=1;
for(j=3;j<3*b[19];j++)m[j]=(m[j-1]+m[j-2])%b[20];
while(scanf("%ld %ld",&n,&k)!=EOF){
    printf("%ld\n",m[n%(b[k-1]*3)]%b[k]);
}
}
