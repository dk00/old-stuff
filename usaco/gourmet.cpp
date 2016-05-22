#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
struct pt
{
    int x,y;
    bool operator<(pt a)const
    {
        if(x!=b.x)return x<b.x;
        return y<b.y;
    }
};
struct px
{
    int x,y;
    px(){};
    px(pt a){x=a.x,y=a.y;}
    bool operator<(px b)
    {
        if(y!=b.y)return y
    }
};
main()
{
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%d %d",&s[i].x,&s[i].y);
    for(i=0;i<m;i++)
        scanf("%d %d",&t[i].x,&t[i].y);
    sort(s,s+n);
    sort(t,t+m);
    
}
