/*C(n) = 2n! / (n+1)!  / n!
1.37e791    C(n+1) = C(n) * (2n+1) * (2n+2) / (n+2)
2.05e597
*/
#define MAXD 50
#define MAX 1000
#include<stdio.h>
long long R=1000000;
main(){
R*=R;
long long c[MAX+1][MAXD+1];
long d[MAX+1],i,j,n;
c[1][MAXD]=1;d[1]=MAXD;
for(i=2;i<=MAX;i++){
    for(j=MAXD;j>=d[i-1];j--)
        c[i][j]=c[i-1][j]*(2*i-1)*(2*i);
    for(j=d[i-1];j<MAXD;j++){
        c[i][j+1]+=(c[i][j]%((i+1)*i))*R;
        c[i][j]/=(i+1)*i;
    }
    c[i][MAXD]/=(i+1)*i;
    for(j=MAXD;j>d[i-1];j--){
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
while(scanf("%ld",&n)!=EOF){
    printf("%I64d",c[n][d[n]]);
    for(i=d[n]+1;i<=MAXD;i++)
        printf("%012I64d",c[n][i]);
    printf("\n");
}
}
