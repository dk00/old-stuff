/*
ID: s0000151
PROG: contact
LANG: C++
*/

#include<stdio.h>
main(){
freopen("contact.in","r",stdin);
freopen("contact.out","w",stdout);
const long B[13]={0,(1<<1)-1,(1<<2)-1,(1<<3)-1,(1<<4)-1,(1<<5)-1,
(1<<6)-1,(1<<7)-1,(1<<8)-1,(1<<9)-1,(1<<10)-1,(1<<11)-1,(1<<12)-1};
long a,b,n,k=0,i,j,sum[13][5000];
char c;
scanf("%ld %ld %ld%c",&a,&b,&n,&c);
for(i=a;i<=b;i++){
    for(j=0;j<5000;j++)sum[i][j]&=0;
}
for(i=0;i<a;i++){
    scanf("%c",&c);
    k=k<<1+c-'0';
}
for(i=a;i<=b;i++){
    scanf("%c",&c);
    k=k<<1+c-'0';
    for(j=a;j<=i;j++)
        sum[j][k&B[j]]++;
}
while(scanf("%c",&c)!=EOF){
    if(c=='\n')continue;
    k=k<<1+c-'0';
    for(i=a;i<=b;i++){
        sum[i][k&B[i]]++;
    }
}
scanf(" ");
}
