#include<cstdio>
int dp[100][100];
int calc(char *,bool);
main()
{
    char s[200];
    while(scanf("%s",s)!=EOF)
        printf("%d\n",calc(s,0));
}
int calc(char *s,bool star)
{
    int i,j,k,n,num[100];
    for(i=n=0;s[i];i++)
    {
        if(s[i]=='+' || s[i]=='*')continue;
        if(s[i]=='(')
            for(j=i+1;s[j]!=')';j++);
        else j=i;
        if(star || s[j+1]!='*')
        {
            if(s[i]=='(')
            {
                char tmp;tmp=s[j],s[j]=0;
                num[n++]=calc(s+i+1,0);
                s[j]=tmp;
                i=j;
            }
            else
                num[n++]=1;
        }
        else
        {
            int cnt=0;
            for(j++;s[j] && (cnt || s[j]!='+');j++)
            {
                if(s[j]=='(')cnt++;
                if(s[j]==')')cnt--;
            }
            char tmp=s[j];
            s[j]=0;
            num[n++]=calc(s+i,1);
            s[j]=tmp;
            i=j;
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
