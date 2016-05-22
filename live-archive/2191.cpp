#include<cstdio>
int n,s[200100];
int add(int i,int j,int st=0,int ed=n)
{
    int mid=(st+ed)/2;
    if(i<=mid)s[mid]+=j;
    if(i>mid)add(i,j,mid+1,ed);
    if(i<mid)add(i,j,st,mid-1);
}
int sum(int i,int st=0,int ed=n)
{
    if(st==ed)return s[st];
    int mid=(st+ed)/2;
    if(i>mid) return s[mid]+sum(i,mid+1,ed);
    if(i==mid)return s[mid];
    return sum(i,st,mid-1);
}
main()
{
    int i,j,C=0;
    char tmp[100];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<=n;i++)s[i]=0;
        for(i=1;i<=n;i++)
        {
            scanf("%d",&j);
            add(i,j);
        }
        if(C++)puts("");
        printf("Case %d:\n",C);
        while(scanf("%s",tmp) && tmp[0]!='E')
        {
            scanf("%d %d",&i,&j);
            if(tmp[0]=='M')
                printf("%d\n",sum(j)-sum(i-1));
            else add(i,j-sum(i)+sum(i-1));
        }
    }
}
