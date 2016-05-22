#include<cstdio>
int s[1005][1005];
char t[10000];
main()
{
    int i,j,n,T;
    scanf("%d%c",&T,t);
    while(T--)
    {
        t[0]='$',gets(t+1);
        for(n=0;t[n];n++)
            s[n][0]=s[0][n]=0;
        for(i=0;i<=n+1;i++)
            s[i][n]=0;
        for(i=1;t[i];i++)
        {
            for(j=n-1;j>0;j--)
                if(t[i]==t[j])
                    s[i][j]=s[i-1][j+1]+1;
                else
                    s[i][j]=s[i-1][j]>?s[i][j+1];
        }
        printf("%d\n",s[n-1][1]);
    }
}
