#include<cstdio>
int n,s[1024][1024];
void addy(int x,int y,int st,int ed,int k)
{
    if(st>ed)
        return;
    int mid=(st+ed)/2;
    if(y<mid)
    {
        addy(x,y,st,mid-1,k);
        return;
    }
    s[x][mid]+=k;
    addy(x,y,mid+1,ed,k);
}
void addx(int x,int y,int st,int ed,int k)
{
    if(st>ed)
        return;
    int mid=(st+ed)/2;
    if(x<mid)
    {
        addx(x,y,st,mid-1,k);
        return;
    }
    addy(mid,y,0,n-1,k);
    addx(x,y,mid+1,ed,k);
}
int sumy(int x,int y,int st,int ed)
{
    if(st>ed)
        return 0;
    int mid=(st+ed)/2;
    if(y<=mid)
        return s[x][mid]+sumy(x,y,st,mid-1);
    return sumy(x,y,mid+1,ed);
}
int sumx(int x,int y,int st,int ed)
{
    if(st>ed)
        return 0;
    int mid=(st+ed)/2;
    if(x<=mid)
        return sumy(mid,y,0,n-1)+sumx(x,y,st,mid-1);
    return sumx(x,y,mid+1,ed);
}
main()
{
    int k,m,x1,x2,y1,y2;
    scanf("0 %d",&n);
    while(scanf("%d",&m) && m!=3)
    {
        if(m==1)
        {
            scanf("%d %d %d",&x1,&y1,&k);
            addx(x1,y1,0,n-1,k);
        }
        else
        {
            scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            k=sumx(x1,y1,0,n-1);
            if(x2+1<n)k-=sumx(x2+1,y1,0,n-1);
            if(y2+1<n)k-=sumx(x1,y2+1,0,n-1);
            if(x2+1<n && y2+1<n)k+=sumx(x2+1,y2+1,0,n-1);
            printf("%d\n",k);
        }
    }
}
