/*
ID: s0000151
PROG: kimbits
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
#define min(a,b) (a)<(b)?(a):(b)
main(){
if(!DEBUG){freopen("kimbits.in","r",stdin);
freopen("kimbits.out","w",stdout);}
long long c[32][32],i,l,n,s;
char bit[33]={"00000000000000000000000000000000"},*t=bit;
for(i=0;i<32;i++)c[i][0]=c[i][i]=1;
for(i=2;i<32;i++){
    for(s=1;s<i;s++)c[i][s]=c[i-1][s]+c[i-1][s-1];
}
for(i=1;i<32;i++){
    for(s=1;s<=i;s++)c[i][s]+=c[i][s-1];
}
scanf("%lld %lld %lld",&n,&l,&s);
for(bit[n--]='\0';n>=0;n--,l--,t=&t[1]){
    for(;s<=c[n][min(l,n)] && n>0;n--,t=&t[1]);
    if(s<=c[n][min(l,n)])break;
    s-=c[n][min(l,n)];
    t[0]='1';
}
puts(bit);
if(DEBUG)scanf(" ");
}
