#include<cstdio>
char go(int n,int p)
{
    if(n%p<n)return go(n%p,p);
    if(n<=1)return n;
    if(n%2)
    {
        if(n%4==3 && p%4==3)
            return -go(p,n);
        return go(p,n);
    }
    if(p%8==1 || p%8==7)
        return go(n/2,p);
    return -go(n/2,p);
}
main()
{
    int n,p;
    while(scanf("%d %d",&n,&p) && n>=0)
        if(go(n,p)!=-1)puts("Yes");
        else puts("No");
}
