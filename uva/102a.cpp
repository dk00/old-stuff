/* @JUDGE_ID:  58589NF  102  c  "Ecological Bin Packing"*/
#include<stdio.h>
#include<string.h>
int main(){
long b[3],c[3],g[3],min=0,sum=0,i,j,k;
char out[4]="GCB";
while(scanf("%ld %ld %ld %ld %ld %ld %ld %ld %ld",&b[0],&g[0],
&c[0],&b[1],&g[1],&c[1],&b[2],&g[2],&c[2])!=EOF){
    for(i=0,sum=0;i<3;i++)
        sum+=(b[i]+c[i]+g[i]);
    min=sum;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            for(k=0;k<3;k++){
                if(i!=j && i!=k && j!=k &&
                (sum-b[i]-c[j]-g[k])<min){
                    min=sum-b[i]-c[j]-g[k];
                    out[i]='B';out[j]='C';out[k]='G';
                }
            }
        }
    }
    out[3]='\0';
    printf("%s %ld\n",out,min);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
