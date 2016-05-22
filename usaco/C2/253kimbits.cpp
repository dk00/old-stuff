/*
ID: s0000151
PROG: kimbits
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
main(){
if(!DEBUG){freopen("kimbits.in","r",stdin);
freopen("kimbits.out","w",stdout);}
long n,l,s,i,c[32][32];
for(i=0;i<32;i++)c[i][0]=c[0][i]=1;
for(i=1;i<32;i++){
    for(s=i+1;s<32;s++)c[i][s-i]=c[i-1][s-i]+c[i][s-i-1];
}
for(i=1;i<32;i++){
    for(s=i+1;s<32;s++)c[i][s-i]+=c[i][s-i-1];
}
char bit[33]="00000000000000000000000000000000";
scanf("%ld %ld %ld",&n,&l,&s);
for(bit[n]='\0';l-->0 && s>0;){
    for(i=l;s>=c[l][i-l];i++)s-=c[l][i-l];
    bit[n-i]='1';
}
puts(bit);
if(DEBUG)scanf(" ");
}
