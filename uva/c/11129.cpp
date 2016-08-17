#include<cstdio>
int s[10001],t[10001];
void go(int st,int ed)
{
    if(st>=ed)
        return;
    int i,k=st+(ed-st)/2;
    for(i=1;i+st<=ed;i++,i++)
    {
        t[k+1+i/2]=s[st+i];
        if(i+1<=ed)
            t[st+i/2]=s[st+i+1];
    }
    t[k]=s[st];
    for(i=st;i<=ed;i++)
        s[i]=t[i];
    go(st,k-1);
    go(k+1,ed);
}
main()
{
    int i,n;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            s[i]=i;
        go(0,n-1);
        printf("%d:",n);
        for(i=0;i<n;i++)
            printf(" %d",s[i]);
        puts("");
    }
}
