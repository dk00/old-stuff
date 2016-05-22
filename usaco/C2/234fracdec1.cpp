/*
ID: s0000151
PROG: fracdec
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
long dec[100000];
main(){
if(!DEBUG){freopen("fracdec.in","r",stdin);
freopen("fracdec.out","w",stdout);}
long n,d,i,j,c;
scanf("%ld %ld",&n,&d);
if(n==d){
    printf("1.0\n");
    return 0;
}
printf("%ld.",n/d);
for(dec[0]=n%d,i=1;;i++){
    dec[i]=(dec[i-1]*10)%d;
    for(j=0;j<i && dec[i]!=dec[j];j++);
    if(j<i)break;
}
for(n=0,c=2;n<j;n++,c++)printf("%ld",(dec[n]*10)/d);
if(dec[j]==0){
    puts("");
    return 0;
}
for(printf("("),n=j,c+=2;n<i;n++,c++){
    if(c>=76){
        puts("");
        c=0;
    }
    printf("%ld",(dec[n]*10)/d);
}
puts(")");
if(DEBUG)scanf(" ");
}
