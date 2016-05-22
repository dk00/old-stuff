/*
ID: s0000151
PROG: fracdec
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#define DEBUG 0
long dec[100000];
char decc[100000];
main(){
if(!DEBUG){freopen("fracdec.in","r",stdin);
freopen("fracdec.out","w",stdout);}
long n,d,i,j,c;
scanf("%ld %ld",&n,&d);
if(n==d){printf("1.0\n");return 0;}
sprintf(decc,"%ld.",n/d);
printf("%s",decc);
for(c=strlen(decc),dec[n%=d]=i=1;;i++){
    decc[i]=(n*=10)/d+'0';
    if(dec[n%d]>0)break;
    else dec[n%=d]=i+1;
}
for(j=1;j<dec[n%d];j++,c++)printf("%c",decc[j]);
if(n%d==0){puts("");return 0;}
for(printf("("),n=dec[n%d],c++;n<=i;n++,c++){
    if(c>=76){puts("");c=0;}
    printf("%c",decc[n]);
}
puts(")");
if(DEBUG)scanf(" ");
}
