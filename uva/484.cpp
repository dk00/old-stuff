#include<stdio.h>
#include<stdlib.h>
long i,t[100000],o[100000],n,k;
main(){
for(i=0;scanf("%ld\n",&n)!=EOF;){
    for(k=0;k<i;k++)if(o[k]==n)break;
    if(k>=i){
        t[i]=1;
        o[i++]=n;
    }
    else t[k]++;
}
for(n=0;n<i;n++)printf("%ld %ld\n",o[n],t[n]);
}
