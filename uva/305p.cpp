#include<stdio.h>
main(){
long s[14]={0,2,7,5,30,169,441,1872,7632,1740,93313,
459901,1358657,2504881},k;
while(1){
    scanf("%ld",&k);
    if(k==0) break;
    printf("%ld\n",s[k]);
}
}
