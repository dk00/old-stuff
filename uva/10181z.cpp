#include<cstdio>
#include<cstdlib>
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
class puzzle
{
public:
    int x,y,pnum,s[4][4];
    inline bool operator==(puzzle a)
    {
        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                if(s[i][j]!=a.s[i][j])
                    return false;
        return false;
    }
    inline bool get()
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
    inline bool move(int d)
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
    inline int calc()
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
puzzle test,tmp[1000];
int min,bound,rev[]={2,3,0,1};
char dir[]="ULDR",path[1000];
inline bool dfs(int d)
{
    if(!test.pnum)
    {
        path[d]=0;
        return true;
    }
    if(d+test.pnum>bound)
    {
        if(min==bound)
            min=d+test.pnum;
        if(min>d+test.pnum)
            min=d+test.pnum;
        return false;
    }
    /*for(int i=0;i<d;i++)
        if(test==tmp[i])
            return false;*/
    tmp[d]=test;
    bool found;
    for(int i=0;i<4;i++)
        if(test.move(i))
        {
            path[d]=dir[i];
            found=dfs(d+1);
            test.move(rev[i]);
            if(found)
                return true;
        }
    return false;
}
main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        if(!test.get())
        {
            puts("This puzzle is not solvable.");
            continue;
        }
        test.calc();
        for(min=bound=45;;bound=min)
            if(dfs(0))
                break;
        puts(path);
    }
}
