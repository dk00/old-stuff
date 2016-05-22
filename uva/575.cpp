#include<stdio.h>
#include<string.h>
main(){
unsigned r,sbin[33];
int i,j;
char s[10000];
for(i=sbin[0]=1;i<32;i++)sbin[i]=sbin[i-1]<<1;
for(i=1;i<32;i++)sbin[i]--;
while(gets(s) && strcmp(s,"0")){
    for(r=0,j=0,i=strlen(s);i>0;i--,j++)while(s[j]-->'0')r+=sbin[i];
    printf("%u\n",r);
}
}
