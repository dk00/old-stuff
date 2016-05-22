#include<queue>
#include<cstdio>
using namespace std;
int n,m,h,s[100][100];
struct pt{
    int x,y;
    pt operator+(pt a){return(pt){x+a.x,y+a.y};}
    char in(){return(x>=0 && x<n && y>=0 && y<m);}
};
const pt d[]={{1,0},{0,1},{-1,0},{0,-1}};
char go(queue<pt>& q)
{
    if(q.empty())return 0;
    pt a=q.front();
    q.pop();
    int i;
    if(++s[a.x][a.y]>h)
    {
        for(i=0;i<4;i++)
            if((a+d[i]).in())
                q.push(a+d[i]);
        s[a.x][a.y]-=4;
    }
    return 1;
}
main()
{
    int i,j,k,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&k,&h);
        for(i=0;i<n;i++)
        {
            char tmp[101];
            scanf("%s",tmp);
            for(j=0;j<m;j++)
                s[i][j]=tmp[j]-'0';
        }
        while(k--)
        {
            scanf("%d %d",&i,&j);
            queue<pt> q;
            q.push((pt){i-1,j-1});
            while(go(q));
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
                printf("%d",s[i][j]);
            puts("");
        }
    }
}
