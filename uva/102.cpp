/* @JUDGE_ID:  58589NF  102  c  "Ecological Bin Packing"*/
#include<stdio.h>
#include<string.h>
int main(){
long b[3][3],min,sum;
char out[4]="GCB";
while(scanf("%ld %ld %ld %ld %ld %ld %ld %ld %ld",&b[0][0],&b[0][2],
&b[0][1],&b[1][0],&b[1][2],&b[1][1],&b[2][0],&b[2][2],&b[2][1])!=EOF){
    min=b[2][0]+b[2][1]+b[1][0]+b[1][2]+b[0][1]+b[0][2];
    sum=b[0][0]+b[0][2]+b[0][1]+b[1][0]+b[1][2]+b[1][1]+
    b[2][0]+b[2][2]+b[2][1];
    if(sum-b[0][2]-b[1][0]-b[2][1]<=min){
        min=sum-b[0][2]-b[1][0]-b[2][1];
        strcpy(out,"GBC");
    }
    if(sum-b[0][1]-b[1][2]-b[2][0]<=min){
        min=sum-b[0][1]-b[1][2]-b[2][0];
        strcpy(out,"CGB");
    }
    if(sum-b[0][1]-b[1][0]-b[2][2]<=min){
        min=sum-b[0][1]-b[1][0]-b[2][2];
        strcpy(out,"CBG");
    }
    if(sum-b[0][0]-b[1][2]-b[2][1]<=min){
        min=sum-b[0][0]-b[1][2]-b[2][1];
        strcpy(out,"BGC");
    }
    if(sum-b[0][0]-b[1][1]-b[2][2]<=min){
        min=sum-b[0][0]-b[1][1]-b[2][2];
        strcpy(out,"BCG");
    }
    printf("%s %ld\n",out,min);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
