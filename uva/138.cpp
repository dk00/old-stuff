#include<stdio.h>
int k[2][10];
main(){
    int i,j,t,c;
    t=0;
    for(i=10000;i<100000;i++){
        c=0;
        for(j=10000;j<100000;j++){
            if(i*(i+1)==(i+j)*(j-i+1)){
                k[0][t]=i;
                k[1][t]=j;
                c++;
                t++;
            }
            if(i*(i+1)<(i+j)*(j-i+1)){
                c++;
            }
        }
    }
    for(i=0;i<10;i++){
        printf("%d %d\n",k[0][i],k[1][i]);
    }
    scanf(" ");
}
