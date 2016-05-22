#include<stdio.h>
int p[11][11];
void order(int m,int n){
    if(m==n)printf("A%d",m+1);
    else{
        printf("(");
        order(m,p[m][n]-1);
        printf(" x ");
        order(p[m][n],n);
        printf(")");
    }
}
main(){
int n,i,j,k,Case=1;
long mul[11][11],d[11],min,tmp;
while(scanf("%d",&n)){
    if(!n)break;
    for(i=1;i<=n;i++){
        scanf("%ld %ld",&d[i-1],&d[i]);
        mul[i-1][i-1]=0;
        for(j=0;j<=i-1;j++)mul[i][j]=0;
    }
    for(i=1;i<n;i++){
        for(j=0;j+i<n;j++){
            mul[j][i+j]=65536*32767;
            for(k=j+1;k<=i+j;k++){
                tmp=d[j]*d[k]*d[i+j+1]+mul[j][k-1]+mul[k][i+j];
                if(tmp<mul[j][i+j]){
                    p[j][i+j]=k;
                    mul[j][i+j]=tmp;
                }
            }
        }
    }
    printf("Case %d: ",Case++);
    order(0,n-1);
    printf("\n");
}
}
