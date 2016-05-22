/* @JUDGE_ID:  58589NF  446  C++ */
/*Kibbles `n' Bits `n' Bits `n' Bits*/
#include<stdio.h>
main(){
long n,bin,dec,i;
char hex1[4],hex2[4],el;
scanf("%ld\n");
for(;n>0;n--){
    scanf("%s %c %s\n",hex1,&el,hex2);
    dec=0;
    for(i=0;i<=3;i++){
        if(hex1[i]>='0' && hex1[i]<='9')
            dec+=hex1[i]-'0';
        else
            dec+=hex1[i]-'A'+10;
        dec << 4;
    }
    printf("0");
    for(i=11,bin=dec;i>=0;i--) printf("%d",bin & (1<<i));
    
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
