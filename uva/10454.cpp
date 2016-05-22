#include<cstdio>
int dp[100][100];
int calc(char* s)
{
    int i,j,k,n,num[100];
    for(i=n=0;s[i];i++)
    {
        if(s[i]=='(')
        {
            for(j=i+1;s[j]!=')';j++);
            s[j]=0;
            num[n++]=calc(s+i+1);
            i=j;
        }
        if(s[i]>='0' && s[i]<='9')
        {
            if(s[i+1]!='*')
                num[n++]=1;
            else
            {
                for(j=i+3;s[j]=='*';j++);
                s[j]=0;
                num[n++]=calc(s+i);
                i=j;
            }
        }
    }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            dp[i][j]=0;
    for(i=0;i<n;i++)
        dp[i][i]=num[i];
    for(k=1;k<n;k++)
        for(i=0;i+k<n;i++)
            for(j=i;j<i+k;j++)
                dp[i][i+k]+=dp[i][j]*dp[j+1][i+k];
    return dp[0][n-1];
}
main()
{
    char s[200];
    while(scanf("%s",s)!=EOF)
        printf("%d\n",calc(s));
}
