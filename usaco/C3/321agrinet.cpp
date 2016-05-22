/*
ID: s0000151
PROG: agrinet
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
main(){
if(!DEBUG){freopen("agrinet.in","r",stdin);
freopen("agrinet.out","w",stdout);}
long n,i,j,dis[101][101],to[101],sum,min,k;
for(scanf("%ld",&n),sum=i=0;i<n;i++){
    for(j=0;j<n;j++)scanf("%ld",&dis[i][j]);
    to[i]=dis[0][i];
}
for(k=n-1;k--;){
    for(min=0;!to[min];min++);
    while(++i<n)if(to[i] && to[i]<to[min])min=i;
    sum+=to[min];
    for(i=0;i<n;i++)to[i]<?=dis[i][min];
}
printf("%ld\n",sum);
if(DEBUG)scanf(" ");
}
