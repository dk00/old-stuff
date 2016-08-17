#include<stdio.h>
int dp[30001];
main(){
dp[0]=1;
int i,j,k,m,s,n,A,C=1;
while(scanf("%d",&n)!=EOF){
    printf("Case #%d:",C++);
    for(A=1,m=k=i=0;i<n;i++){
        scanf("%d",&s);
        printf(" %d",s);
        if(dp[s] || s<=m)A=0;
        if(!A)continue;
        k+=(m=s);
        for(j=k;A && j>=s;j--)
            if(dp[j-s])dp[j]=1;
    }
    while(k--)dp[k+1]=0;
    printf("\nThis is%san A-sequence.\n",A?" ":" not ");
}
}
