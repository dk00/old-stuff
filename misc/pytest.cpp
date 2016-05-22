#include<cstdio>
int cn;
int s[6]={0,0,5,0,5,0};
int dfs(int n)
{
    if(n>=6)
        return 1;
    if(s[n]==cn)
        return dfs(n+1);
    int sum=0;
    for(int i=0;i<cn;i++)
        if(n==0 || s[n-1]==cn || s[n-1]!=i)
        {
            s[n]=i;
            sum+=dfs(n+1);
        }
    return sum;
}
main()
{
    while(scanf("%d",&cn)!=EOF)
        printf("%d\n",dfs(0));
}
