#include<cstdio>
int n,m;
struct V
{
    int s[25];
    void operator+=(V a){for(int i=0;i<m;i++)s[i]+=a.s[i];}
    void operator-=(V a){for(int i=0;i<m;i++)s[i]-=a.s[i];}
    bool operator>=(V a)
    {
        for(int i=0;i<m;i++)
            if(s[i]<a.s[i])return 0;
        return 1;
    }
}min,now,s[15];
int p[15];
bool go(int d,int i=0)
{
    if(now>=min)return 1;
    if(i>=n ||d==0)return 0;
    now+=s[i];
    if(go(d-1,(p[d]=i)+1))return 1;
    now-=s[i];
    return go(d,i+1);
}
main()
{
    freopen("holstein.in","r",stdin);
    freopen("holstein.out","w",stdout);
    int i,j;
    scanf("%d",&m);
    for(i=0;i<m;i++)
        scanf("%d",&min.s[i]);
    scanf("%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&s[i].s[j]);
    for(i=0;i<=n;i++)
        if(go(i))break;
    printf("%d",i);
    while(i--)
        printf(" %d",p[i+1]+1);
    puts("");
    scanf(" ");
}
/*
PROB:holstein
LANG:C++
*/
