#include<cstdio>
int s[201],dp[201][10001];
void go(int n,int j)
{
    if(n==0)
        return;
    if(j>=s[n-1] && dp[n-1][j-s[n-1]])
    {
        go(n-1,j-s[n-1]);
        puts("starboard");
    }
    else
    {
        go(n-1,j);
        puts("port");
    }
}
main()
{
    int i,j,n,m,t,max,sum;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&m);
        m*=100;
        for(n=sum=0;scanf("%d",&s[n]) &&(sum+=s[n])&& s[n] && sum<=m*2;n++)
            for(j=0;j<=m;j++)
                dp[n+1][j]=0;
        while(s[n] && scanf("%d",&s[n]));
        dp[0][0]=1;
        for(i=sum=0;i<n;i++)
        {
            sum+=s[i];
            for(j=0;j<=m;j++)
                if((j-s[i]>=0 && dp[i][j-s[i]]) || (dp[i][j] && sum-j<=m))
                    dp[i+1][j]=1,max=i+1;
        }
        printf("%d\n",max);
        for(j=0;dp[max][j]==0;j++);
        go(max,j);
        puts("");
    }
}
