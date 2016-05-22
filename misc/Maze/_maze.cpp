#include<map>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
volatile int n,x,y,step=0;
map<int,map<int,char> > _s;
char to[128];
void Init()
{
    _s.clear();
    scanf("%d",&n);
    int i,j,k;
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&j,&k);
        _s[j][k]=1;
    }
    x=j,y=k;
    to['D']=1,to['R']=2,to['U']=3,to['L']=4;
}
int Go(char d)
{
    if(d<0 || to[d]==0)
    {
        puts("Illegal move");
        exit(0);
    }
    d=to[d]-1;
    if(step++>15000)
    {
        puts("Move limit excceed");
        exit(0);
    }
    if(!_s[x+dx[d]][y+dy[d]])
        return 0;
    x+=dx[d];
    y+=dy[d];
    return 1;
}
void End(int x)
{
    if(x==n)puts("Correct");
    else puts("Incorrect");
 //   printf("%d moves.\n",step);
    exit(0);
}
