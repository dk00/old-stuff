#include<cstdio>
int c(int n,int m)
{
    if(n<m)return 0;
    if(m<=0)return 1;
    return c(n-1,m-1)+c(n-1,m);
}
int go(int n)
{
    if(n<=1)return 1;
    int i,sum=0;
    for(i=0;i<=n-1;i++)
        sum+=c(n-1,i)*go(i)*go(n-i-1);
    return sum;
}
main()
{
    int n;
    while(scanf("%d",&n)==1)
    {
        printf("%d\n",go(n));
    }
}
