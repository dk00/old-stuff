#include<cstdio>
inline int go(int n,int i)
{
    if(i<0)return n;
    int x;
    if(n<0)
    {
        x=go(n+(1<<i),i-1);
        putchar('-');
    }
    else
    {
        x=go(n-(1<<i),i-1);
        putchar('+');
    }
    return x;
}
main()
{
    int i,n;
    while(scanf("%d",&n)==1)
    {
        for(i=0;(1<<i)<=n;i++);
        printf("%d\n",i);
        if(go(n,i-1)!=0)putchar('!');
        puts("");
    }
}
