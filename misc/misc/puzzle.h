const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
class puzzle
{
public:
    int x,y,pnum;
    char s[4][4];
    bool operator==(puzzle a)
    {
        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                if(s[i][j]!=a.s[i][j])
                    return false;
        return false;
    }
    bool get()
    {
        int i,j,k,l=0;
        for(i=0;i<4;i++)
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
#ifdef SCRCTRL_H
    void show()
    {
        int i,j;
        for(i=0;i<4;i++)
        {
            locate(10+i,10);
            for(j=0;j<4;j++)
            {
                if(s[i][j])
                    myputs("%c ",s[i][j]-1+'A');
                else
                    myputs("%c ",' ');
            }
        }
        locate(14,12);myputs("rem=%3d",pnum);
    }
#endif
    bool move(int d)
    {
        if(x-dx[d]<0 || x-dx[d]>=4 || y-dy[d]<0 || y-dy[d]>=4)
            return false;
        s[x-dx[d]][y-dy[d]]--;
        s[x][y]=s[x-dx[d]][y-dy[d]];
        pnum+=abs(x-s[x][y]/4)+abs(y-s[x][y]%4);
        x-=dx[d],y-=dy[d];
        pnum-=abs(x-s[x][y]/4)+abs(y-s[x][y]%4);
        s[x+dx[d]][y+dy[d]]++;
        s[x][y]=0;
        return true;
    }
    int calc()
    {
        int i,j;
        pnum=0;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
            {
                if(s[i][j])
                {
                    s[i][j]--;
                    pnum+=abs(i-s[i][j]/4)+abs(j-s[i][j]%4);
                    s[i][j]++;
                }
            }
        return pnum;
    }
};
