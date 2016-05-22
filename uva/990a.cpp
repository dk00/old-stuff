#include <stdio.h>
int dp[31][1001],num[31][1001],depth[31],cost[31],gold[31],path[30];
main(){
    int n,m,w,i,j,first=1;
    while(scanf("%d %d",&m,&w)!=EOF){
        scanf("%d",&n);
        for(i=1;i<=n;i++){
            scanf("%d %d",&depth[i],&gold[i]);
            cost[i]=3*w*depth[i];
        }
        for(i=0;i<=m;i++)
            dp[0][i]=0;
        for(i=1;i<=n;i++){
            dp[i][0]=0;
            for(j=1;j<=m;j++)
                if(j-cost[i]<0)
                    dp[i][j]=dp[i-1][j];
                else
                    dp[i][j]=(dp[i-1][j])>?(dp[i-1][j-cost[i]]+gold[i]);
        }
        if(first) first=0;
        else      puts("");
        printf("%d\n",dp[n][m]);
        for(i=0,j=n;dp[j][m]!=0;j--)
            if(dp[j-1][m]!=dp[j][m]){
                path[i++]=j;
                m-=cost[j];
            }
        printf("%d\n",i);
        for(i--;i>=0;i--)
            printf("%d %d\n",depth[path[i]],gold[path[i]]);
    }
}
