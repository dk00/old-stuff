/*
s(n) = s(n-1)*2 + s(n-2) + s(n-3)
       (1 || 4)
*/
#include"bigintA03.h"
bigint s[1000];
char c[10000];
main(){
s[0]=2,s[1]=5,s[2]=13;
int i;
for(i=3;i<1000;i++)
    (((s[i]+=s[i-1])+=s[i-1])+=s[i-2])+=s[i-3];
while(scanf("%d",&i)!=EOF)puts(s[i-1].tostring(c));
}
