#include<stdio.h>
long long sn[25],math[25][151];
long long gcd(long long a,long long b)
{while((a%=b) && (b%=a));return a+b;}
long long dfs(int n,int x)
{
    if(n==1)
        return(1<=x && x<=6);
    for(int i=1;i<=6;i++)
        math[n][x]+=dfs(n-1,x-i);
    return math[n][x];
}
main()
{
    int i,j,k,n,x;
    sn[0]=math[0][0]=1;
    for(i=1;i<25;i++)
        sn[i]=sn[i-1]*6;
    while(1)
    {
        scanf("%d %d",&n,&x);
        if(n==0 && x==0)
            break;
        if(n*6<x)
        {
            puts("0");
            continue;
        }
        if(n>=x)
        {
            puts("1");
            continue;
        }
        for(i=0,k=n;k<=x;k++)
            i+=dfs(n,k);
        j=sn[n];
        k=gcd(i,j);
        i/=k,j/=k;
        printf("%d",i);
        if(j>i)
            printf("/%d",j);
        puts("");
    }
}
