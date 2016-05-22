#include<cstdio>
int s[10000];
int qfind(int st,int ed,int k)
{
    int p1=st+1,p2=ed,tmp;
    while(1)
    {
        for(;s[p1]<=s[st] && p1<=ed;p1++);
        for(;s[p2]>=s[st] && p2>st;p2--);
        if(p1>=p2)break;
        tmp=s[p1];
        s[p1]=s[p2];
        s[p2]=tmp;
    }
    tmp=s[st];
    s[st]=s[p2];
    s[p2]=tmp;
    if(p2+1==k)
        return s[p2+1];
    if(k<=p2)
        return qfind(st,p2-1,k);
    else
        return qfind(p2+1,ed,k);
}
void qsort(int st,int ed)
{
    if(st>=ed)
        return;
    int p1=st+1,p2=ed,tmp;
    while(1)
    {
        for(;s[p1]<=s[st] && p1<=ed;p1++);
        for(;s[p2]>=s[st] && p2>st;p2--);
        if(p1>=p2)break;
        tmp=s[p1];
        s[p1]=s[p2];
        s[p2]=tmp;
    }
    tmp=s[st];
    s[st]=s[p2];
    s[p2]=tmp;
    qsort(st,p2-1);
    qsort(p2+1,ed);
}
main()
{
    int i,n;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        qsort(0,n-1);
        scanf("%d",&i);
        printf("%d\n",qfind(0,n-1,i));
        puts("");
    }
}
