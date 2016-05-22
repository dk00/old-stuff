/*
ID: s0000151
PROG: palsquare
LANG: C++
*/

#include<stdio.h>
#include<string.h>
#define DEBUG 0
main(){
if(!DEBUG){freopen("palsquare.in","r",stdin);
freopen("palsquare.out","w",stdout);}
long base,i,j,n,k;
char num[17],num1[17],num2[17],ch[20]={"0123456789ABCDEFGHI"};
scanf("%ld",&base);
for(k=1;k<=300;k++){
    n=k;
    for(j=16;n;j--){
        num[j]=ch[n%base];
        n/=base;
    }
    for(i=0,j++;j<17;i++,j++)num[i]=num[j];
    num[i]='\0';
    n=k*k;
    for(j=16;n;j--){
        num1[j]=ch[n%base];
        n/=base;
    }
    for(i=0,j++;j<17;i++,j++)num1[i]=num1[j];
        num1[i]=num2[i]='\0';
    for(j=0;j<i;j++)num2[i-j-1]=num1[j];
    if(!strcmp(num1,num2))
        printf("%s %s\n",num,num1);
}
if(DEBUG)scanf(" ");
}
