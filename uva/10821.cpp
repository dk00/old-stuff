#include<cstdio>
void go(int d,int n,int h)
{
    if(n==1)
    {
        printf(" %d",d);
        return;
    }
    int i;
    for(i=0;1<<(h-1)<n-i;i++);
    printf(" %d",i+d);
    if(i>0)
        go(d,i,(h-1)<?i);
    if(n-i-1>0)
        go(i+d+1,n-i-1,h-1);
}
main()
{
    int n,h,C=1;
    while(scanf("%d %d",&n,&h) && n+h)
    {
        printf("Case %d:",C++);
        if((1<<h)-1<n)
            printf(" Impossible.");
        else
            go(1,n,h);
        puts("");
    }
}
