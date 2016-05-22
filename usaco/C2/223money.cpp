/*
ID: s0000151
PROG: money
LANG: C++
*/

#include<stdio.h>
main(){
freopen("money.in","r",stdin);
freopen("money.out","w",stdout);
long v,n,coin,i,j;
long long s[10001];
scanf("%ld %ld",&v,&n);
for(j=1,s[0]=1;j<=n;j++)s[j]&=0;
for(i=0;i<v;i++){
    scanf("%ld",&coin);
    for(j=0;j+coin<=n;j++)s[j+coin]+=s[j];
}
printf("%lld\n",s[n]);
//scanf(" ");
}
