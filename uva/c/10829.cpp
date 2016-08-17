#include<cstdio>
int n,t[100][100];
char s[2000];
int lcp(int i,int j)
{
    if(i>=n || j>=n || s[i]!=s[j])return 0;
    if(t[i][j]>=0)return t[i][j];
    return(t[i][j]=1+lcp(i+1,j+1));
}
main()
{
    int i,j,k,g,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %s",&g,s);
        for(n=0;s[n];n++);
        for(i=0;s[i];i++)
            for(j=0;s[j];j++)
                t[i][j]=-1;
        for(i=k=0;i<n;i++)
            for(j=i+g+1;j<n;j++)
                k+=(i+lcp(i,j)+g>=j);
        printf("%d\n",k);
    }
}
