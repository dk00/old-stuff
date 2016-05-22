#include<map>
#include<ctime>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
struct pa
{
    int x,y;
    bool operator<(pa a)const
    {
        if(x!=a.x)return x<a.x;
        return y<a.y;
    }
};
map<int,map<int,char> > u;
vector<pa> s;
int r;
void go(int x,int y)
{
    if(u[x][y])return;
    u[x][y]=1;
    s.push_back((pa){x,y});
    for(int i=0;i<4;i++)
    {
        if(rand()%1000>r)continue;
        go(x+dx[i],y+dy[i]);
    }
}
main(int m,char *a[])
{
    srand(time(NULL));
    int i;
    sscanf(a[1],"%d",&r);
begin:
    u.clear();
    s.clear();
    go(0,0);
    if(s.size()>5000 || s.size()<4500)goto begin;
    printf("%d\n",s.size());
    //sort(s.begin(),s.end());
    for(i=0;i<s.size();i++)
        printf("%d %d\n",s[i].x,s[i].y);
}
