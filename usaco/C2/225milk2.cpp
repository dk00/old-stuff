/*
ID: s0000151
PROG: milk2
LANG: C++
*/

#include<stdio.h>
main(){
freopen("milk2.in","r",stdin);
freopen("milk2.out","w",stdout);
long n1,i,max1=0,max2=0,start,end,n2,s1=999999,e1=0;
short int s[1000001];
for(i=1;i<1000001;i++)s[i]&=0;
scanf("%ld",&n1);
for(i=0;i<n1;i++){
    scanf("%ld %ld",&start,&end);
    s[start]++;s[end]--;
    s1<?=start;e1>?=end;
}
for(i=s1+1;i<=e1;i++)s[i]+=s[i-1];
for(i=s1,n1=0,n2=0;i<e1;){
    for(n1=0;s[i] && i<e1;n1++,i++);
    max1>?=n1;
    for(n2=0;!s[i] && i<e1;n2++,i++);
    max2>?=n2;
}
printf("%ld %ld\n",max1,max2);
//scanf(" ");
}
