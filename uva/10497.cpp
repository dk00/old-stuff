#include<stdio.h>
#define N 810
#define D 125
main(){
long long put[N+1][D+1],D1=10000000;
D1=D1*100000000;
int i,j,d[N+1];
d[1]=D;d[2]=D;d[0]=D;
put[1][D]=0;put[2][D]=1;put[0][D]=1;
for(i=3;i<=N;i++){
    for(j=d[i-1];j<d[i-2];j++)
        put[i][j]=put[i-1][j];
    for(j=d[i-2];j<=D;j++)
        put[i][j]=put[i-1][j]+put[i-2][j];
    d[i]=d[i-1];
    for(j=D;j>d[i];j--){
        if(put[i][j]>=D1){
            put[i][j-1]+=put[i][j]/D1;
            put[i][j]%=D1;
        }
    }
    if(put[i][d[i]]>=D1){
        put[i][d[i]-1]=put[i][d[i]]/D1;
        put[i][d[i]--]%=D1;
    }
    for(j=d[i];j<=D;j++)
        put[i][j]*=(i-1);
    for(j=D;j>d[i];j--){
        if(put[i][j]>=D1){
            put[i][j-1]+=put[i][j]/D1;
            put[i][j]%=D1;
        }
    }
    if(put[i][d[i]]>=D1){
        put[i][d[i]-1]=put[i][d[i]]/D1;
        put[i][d[i]--]%=D1;
    }
}
while(scanf("%d",&i)){
    if(i<0)break;
    printf("%lld",put[i][d[i]]);
    for(j=d[i]+1;j<=D;j++)
        printf("%015lld",put[i][j]);
    printf("\n");
}
}
