/*C(n) = 2n! / (n+1)!  / n!
1.37e791    C(n+1) = C(n) * (2n+1) * (2n+2) / (n+2)
*/
#define MAXD 80
#include<stdio.h>
long long R=100000;
main(){
R*=R/10;
char l[100];
long long c[301][91];
int d[301],i,j,n;
c[1][90]=1;d[1]=90;
for(i=2;i<=300;i++){
/*    printf("%d %d\n",i,d[i-1]);
    gets(l);*/
    //for(j=0;j<=90;j++)c[i][j]=0;
    for(j=90;j>=d[i-1];j--)
        c[i][j]=c[i-1][j]*(2*i-1)*(2*i);
    for(j=d[i-1];j<90;j++){
        c[i][j+1]+=(c[i][j]%(i+1))*R;
        c[i][j]/=(i+1);
    }
    c[i][90]/=(i+1);
    for(j=90;j>d[i-1];j--){
        if(c[i][j]>=R){
            c[i][j-1]+=c[i][j]/R;
            c[i][j]%=R;
        }
    }
    d[i]=d[i-1];
    if(c[i][d[i]]>=R){
        c[i][d[i]-1]=c[i][d[i]]/R;
        c[i][d[i]--]%=R;
    }
}
while(scanf("%d",&n)){
    if(!n)break;
    printf("%lld",c[n][d[n]]);
    for(i=d[n]+1;i<=90;i++)
        printf("%09lld",c[n][i]);
    printf("\n");
}
}
