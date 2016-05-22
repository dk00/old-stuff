/*
ID: s0000151
PROG: fact4
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
main(){
if(!DEBUG){freopen("fact4.in","r",stdin);
freopen("fact4.out","w",stdout);}
long fact,n,i;
scanf("%ld",&n);
for(i=1,fact=1;i<=n;i++){
    fact*=i;
    while(fact%10==0)fact/=10;
    fact%=100000;
}
while(fact%10==0)fact/=10;
printf("%ld\n",fact%10);
if(DEBUG)scanf(" ");
}
