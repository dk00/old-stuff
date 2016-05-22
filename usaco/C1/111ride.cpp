/*
ID: s0000151
PROG: ride
LANG: C++
*/

#include<stdio.h>
#include <stdlib.h>
main(){
long n1,n2;
char c;
freopen("ride.in","r",stdin);
freopen("ride.out","w",stdout);
scanf("%c",&c);
for(n1=1;c!='\n';scanf("%c",&c))n1*=(c-'A'+1);
scanf("%c",&c);
for(n2=1;c!='\n';scanf("%c",&c))n2*=(c-'A'+1);
if(n1%47==n2%47)printf("GO\n");
else printf("STAY\n");
//exit(0);
}
