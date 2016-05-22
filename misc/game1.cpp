#include<cstdio>
int dp[2][2000];
int dfs(int n,int p)
{
    if(n<=1)
        return -1;
    if(dp[p][n])
        return dp[p][n];
    dp[p][n]=-1;
    if(p)
    {
        for(int i=2;i<7;i++)
            if(dfs(n-i,!p)<0)
            {
                dp[p][n]=i;
                break;
            }
    }
    else
        for(int i=2;i<7;i++)
            if(dfs(n-i,!p)<0)
            {
                dp[p][n]=i;
                break;
            }
    return dp[p][n];
}
main()
{
    int n;
    while(scanf("%d",&n) && n)
        printf("%d\n",dfs(n,0));
}
