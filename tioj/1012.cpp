#include<cstdio>
int n,m,tn,s[10],t[10];
void ins(int p,int x)
{
    for(int j=tn;j>p;j--)
        t[j]=t[j-1];
    t[p]=x;
    tn++;
}
void del(int j)
{
    for(;j<tn;j++)
        t[j]=t[j+1];
    tn--;
}
char go(int d,int f)
{
    if(f>=n)return 1;
    int i;
    if(d<=n)
    {
        for(i=0;i<=m && i<=tn;i++)
        {
            ins(i,d);
            if(go(d+1,f))return 1;
            del(i);
        }
    }
    for(i=0;i<=m && i<=tn;i++)
        if(t[i]==s[f])
        {
            del(i);
            if(go(d,f+1))return 1;
            ins(i,s[f]);
        }
    return 0;
}
main()
{
    int i;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        if(go(1,0))puts("yes");
        else puts("no");
    }
}
