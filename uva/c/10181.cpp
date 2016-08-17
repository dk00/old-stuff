#include<cstdio>
inline int abs(int n){if(n<0)return -n;return n;}
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1},rev[]={2,3,0,1};
const char dir[]="DRUL";
class puzzle
{
public:
    int x,y,pnum,hnum,s[4][4];
    inline bool operator==(puzzle a)
    {
        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                if(s[i][j]!=a.s[i][j])
                    return false;
        return true;
    }
    inline bool get()
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
    inline bool move(int d)
    {
        if(x-dx[d]<0 || x-dx[d]>=4 || y-dy[d]<0 || y-dy[d]>=4)
            return false;
        s[x][y]=s[x-dx[d]][y-dy[d]];
        s[x][y]--;
        pnum-=abs(x-dx[d]-s[x][y]/4)+abs(y-dy[d]-s[x][y]%4);
        pnum+=abs(x-s[x][y]/4)+abs(y-s[x][y]%4);
        s[x][y]++;
        s[x-=dx[d]][y-=dy[d]]=0;
        return true;
    }
    int num();
    inline int calc_init()
    {
        int i,j;
        pnum=0;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)
                if(s[i][j])
                {
                    s[i][j]--;
                    pnum+=abs(i-s[i][j]/4)+abs(j-s[i][j]%4);
                    s[i][j]++;
                }
        return pnum;
    }
};
int min,bound,use[1021][107];
char path[1000];
puzzle test,tmp[105];
inline bool dfs(int d)
{
    if(test.pnum==0)
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
    for(int i=0;i<4;i++)
    {
        path[d]=dir[rev[i]];
        if(test.move(i))
        {
            if(dfs(d+1))
                return true;
            test.move(rev[i]);
        }
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
        min=bound=test.calc_init();
        min=bound=45;
        for(;;bound=min)
            if(dfs(0))
                break;
        puts(path);
    }
}
