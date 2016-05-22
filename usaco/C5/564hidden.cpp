/*
ID: s0000151
PROG: hidden
LANG: C++
*/
#include<stdio.h>
main(){
freopen("hidden.in","r",stdin);
freopen("hidden.out","w",stdout);
int i,j,k,l;
char s[100001];
scanf("%d",&l);
for(i=0;scanf("%s",s+i)-EOF;i+=72);
for(i=1,k=0;i<l;){
    for(j=0;j<l && s[(i+j)%l]==s[(k+j)%l];j++);
    if(s[(i+j)%l]<s[(k+j)%l])k=i++;
    else i+=++j;
}
printf("%d\n",k);
}
