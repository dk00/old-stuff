#include<cstdio>
#include<cstdlib>
int calc(int n,int k)
{
    if(n<=k)return 0;
    return 1+calc(n-k,k*2);
}
int num,bound,next,path[1000],s[10000];
bool dfs(int d)
{
    if(path[d-1]==num)
        return 1;
    int k=d+s[num/path[d-1]+(num%path[d-1]>0)];
    if(k>bound)
    {
        if(k<next)next=k;
        return 0;
    }
    int i,j;
    for(i=d-1;i>=0;i--)
        for(j=d-1;j>=i;j--)
        {
            k=path[i]+path[j];
            if(k<=num && k>path[d-1])
            {
                path[d]=k;
                if(dfs(d+1))return 1;
            }
        }
    return 0;
}
main()
{
    int i;
    for(i=1;i<10000;i++)s[i]=calc(i,1);
    while(scanf("%d",&num) && num)
    {
        path[0]=1;
        next=1+s[num-1];
        while(1)
        {
            bound=next,next=100;
            if(dfs(1))break;
        }
        printf("1");
        for(i=1;path[i-1]!=num;i++)
            printf(" %d",path[i]);
        puts("");
    }
}
