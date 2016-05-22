#include<stdio.h>
main(){
int n,i,j,k,l,p[21][21][21],path[21];
double e[21][21][21],max;
while(scanf("%d",&n)!=EOF){
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j)continue;
            scanf("%lf",&e[1][i][j]);
            p[1][i][j]=i;
        }
        p[1][i][i]=0;
    }
    for(l=2;l<=n;l++){
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                e[l][i][j]=0.0;
                for(k=1;k<=n;k++){
                    if(e[l][i][j]<e[l-1][i][k]*e[1][k][j]){
                        e[l][i][j]=e[l-1][i][k]*e[1][k][j];
                        p[l][i][j]=k;
                    }
                }
            }
            if(e[l][i][i]>1.01)break;
        }
        if(e[l][i][i]>1.01)break;
    }
    if(l>n){
        puts("no arbitrage sequence exists");
        continue;
    }
    path[0]=j=i;
    for(k=1;l>0;l--)path[k++]=j=p[l][i][j];
    printf("%d",path[--k]);
    while(k--)printf(" %d",path[k]);
    puts("");
}
}
