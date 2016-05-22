/*
ID: s0000151
PROG: dualpal
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#define DEBUG 0
main(){
if(!DEBUG){freopen("dualpal.in","r",stdin);
freopen("dualpal.out","w",stdout);}
long n,s,base,i,j,k,m=1;
char num1[33],num2[33];
for(scanf("%ld %ld",&n,&s);n--;m=1){
    while(s++ && m){
        for(m=base=2;base<=10 && m;base++){
            for(i=32,k=s;k;i--,k/=base)num1[i]=k%base+'0';
            for(j=0,i++;i<=32;i++,j++)num1[j]=num1[i];
            for(j--,i=0;j>=0;j--,i++)num2[i]=num1[j];
            num1[i]=num2[i]='\0';
            if(!strcmp(num1,num2))m--;
        }
        if(!m)break;
    }
    printf("%ld\n",s);
}
if(DEBUG)scanf(" ");
}
