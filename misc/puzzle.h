#include"scrctrl.h"
inline int abs(int n){if(n<0)return -n;return n;}
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
class puzzle
{
public:
    int x,y,pnum,hnum,s[4][4];
    bool get()
    {
        int i,j,k,l;
        for(i=l=0;i<4;i++)
            for(j=0;j<4;j++)
            {
                scanf("%d",&s[i][j]);
                if(s[i][j]==0)
                {
                    x=i,y=j;
                    continue;
                }
                for(k=i*4+j-1;k>=0;k--)
                    if(s[k/4][k%4]>s[i][j])l++;
            }
        return((l+x)&1);
    }
    void show()
    {
        int i,j;
        for(i=0;i<4;i++)
        {
            locate(10+i,10);
            for(j=0;j<4;j++)
            {
                if(s[i][j])
                    myputs("%c ",'A'+s[i][j]-1);
                else
                    myputs("  ");
            }
            locate(14,12);myputs("%3d %10d ",pnum,hnum);
        }
    }
    bool move(int d)
    {
        if(x-dx[d]<0 || x-dx[d]>=4 || y-dy[d]<0 || y-dy[d]>=4)
            return false;
        s[x][y]=s[x-dx[d]][y-dy[d]];
        s[x][y]--;
        pnum-=abs(x-dx[d]-s[x][y]/4)+abs(y-dy[d]-s[x][y]%4);
        hnum^=(s[x][y]<<((x-dx[d])*8+(y-dy[d])*2));
        pnum+=abs(x-s[x][y]/4)+abs(y-s[x][y]%4);
        hnum^=s[x][y]<<(x*8+y*2);
        s[x][y]++;
        s[x-=dx[d]][y-=dy[d]]=0;
        return true;
    }
    int num();
    int calc_init()
    {
        int i,j;
        hnum=pnum=0;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                if(s[i][j])
                {
                    s[i][j]--;
                    pnum+=abs(i-s[i][j]/4)+abs(j-s[i][j]%4);
                    hnum+=s[i][j]<<(i*8+j*2);
                    s[i][j]++;
                }
        return pnum;
    }
};
