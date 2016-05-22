#include"maze.h"
#include<map>
using namespace std;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
const char dz[]="DRUL";
map<int,map<int,char> > s;
int go(int x,int y)
{
    int i,sum=1;
    for(i=0;i<4;i++)
    {
        if(s[x+dx[i]][y+dy[i]])continue;
        if((s[x+dx[i]][y+dy[i]]=2*Go(dz[i])-1)>0)
        {
            sum+=go(x+dx[i],y+dy[i]);
            Go(dz[i^2]);
        }
    }
    return sum;
}
main()
{
    Init();
    s[0][0]=1;
    End(go(0,0));
}
