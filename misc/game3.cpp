#include<cstdio>
int a,b,u[100000];
int go(int n)
{
    if(u[n])return 0;
    u[n]=1;
    int sum=1;
    sum+=go(n/a);
    sum+=go(n/b);
    return sum;
}
main()
{
    int i,n;
    while(scanf("%d %d %d",&n,&a,&b))
    {
        for(i=0;i<=n;i++)u[i]=0;
        printf("%d\n",go(n));
    }
}
