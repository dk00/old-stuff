#include<cstdio>
#include<algorithm>
struct num
{
    char sy;
    int l,o,r,d;
    bool operator<(num x)const
    {
        return(d>x.d ||(d==x.d && o<x.o));
    }
}s[10001];
int u;
void go(num &x)
{
    x.o=u++;
    if(x.l>=0)
    {
        s[x.l].d=x.d+1;
        go(s[x.l]);
    }
    if(x.r>=0)
    {
        s[x.r].d=x.d+1;
        go(s[x.r]);
    }
}
char tmp[10001];
int st[10001];
main()
{
    int i,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",tmp);
        for(n=i=u=0;tmp[n];n++)
        {
            s[n].sy=tmp[n];
            if(tmp[n]<='Z')
            {
                s[n].l=st[--i];
                s[n].r=st[--i];
            }
            else s[n].l=s[n].r=-1;
            st[i++]=n;
        }
        s[n-1].d=0;
        go(s[n-1]);
        std::sort(s,s+n);
        for(i=0;i<n;i++)
            putchar(s[i].sy);
        puts("");
    }
}
