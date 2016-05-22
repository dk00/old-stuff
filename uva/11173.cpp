#include<cstdio>
int go(int n,int i)
{
    if(!n)return 0;
    if(i&n)
        return n+go(n/2,(~i)&(n-1));
    return go(n/2,i);
}
main()
{
    int i,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&i);
        printf("%d\n",go(1<<n,i));
    }
}
