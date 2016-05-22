#include<cstdio>
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
struct pt
{
    int x,y,d;
}_q[2][1000],*q1=_q[0],*q2=_q[1],*tmp,path[200];
class P
{
    void expd(int,int);
    void go();
public:
    int s[6][6],p1,p2;
    void add(int,int);
    bool clear()
    {
        int i,j;
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
                if(s[i][j])
                    return false;
        return true;
    }
    void get()
    {
        p1=p2=0;
        int i,j;
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
                scanf("%d",&s[i][j]);
    }
    void print()
    {
        int i,j;
        for(i=0;i<6;i++)
        {
            for(j=0;j<6;j++)
                printf(" %d",s[i][j]);
            puts("");
        }
    }
}test,tp[20];
void P::add(int a,int b)
{
    if(s[a][b]<=3)
        s[a][b]++;
    else
    {
        s[a][b]=0;
        expd(a,b);
        go();
    }
}
void P::expd(int a,int b)
{
    s[a][b]=0;
    for(int i=0;i<4;i++)
        q2[p2++]=(pt){a+dx[i],b+dy[i],i};
}
void P::go()
{
    int i,x,y,d;
    p1=p2,p2=0;
    tmp=q1,q1=q2,q2=tmp;
    while(p1>0)
    {
        for(i=0;i<p1;i++)
        {
            x=q1[i].x,y=q1[i].y,d=q1[i].d;
            if(x<0 || x>5 || y<0 || y>5)
                continue;
            if(s[x][y]==0)
                q2[p2++]=(pt){x+dx[d],y+dy[d],d};
            else if(s[x][y]<4)
                s[x][y]++;
            else
                expd(x,y);
        }
        p1=p2,p2=0;
        tmp=q1,q1=q2,q2=tmp;
    }
}
int clear,snum;
char ttmp[100];
void dfs(int n,int x,int y)
{
    snum++;
    int i,j;
    if(y>=6)x++,y=0;
    if(x>=6)
        return;
    /*printf("%d %d\n",path[n+1].x,path[n+1].y);
    tp[n].print();
    gets(ttmp);*/
    if(n==1)
    {
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
                if(tp[1].s[i][j]==4)
                {
                    path[0]=(pt){i,j,0};
                    tp[0]=tp[1],tp[0].add(i,j);
                    if(tp[0].clear())
                    {
                        clear=1;
                        puts("clear");
                        return;
                    }
                }
        return;
    }
    for(j=y;j<6;j++)
        if(tp[n].s[x][j] && tp[n].s[x][j]<4)
        {
            tp[n-1]=tp[n],tp[n-1].add(x,j);
            path[n-1]=(pt){x,j,0};
            dfs(n-1,x,j);
            if(clear)
                return;
        }
    for(i=x+1;i<6;i++)
        for(j=y+1;j<6;j++)
            if(tp[n].s[i][j] && tp[n].s[i][j]<4)
            {
                tp[n-1]=tp[n],tp[n-1].add(i,j);
                path[n-1]=(pt){i,j,0};
                dfs(n-1,i,j);
                if(clear)
                    return;
            }
}
main()
{
    int i,n;
    while(1)
    {
        test.get();
        scanf("%d",&n);
        snum=clear=0;
        for(i=1;i<=n;i++)
        {
            tp[i]=test,dfs(i,0,0);
            if(clear)
                break;
        }
        printf("%d\n",snum);
        if(clear)
            while(i--)
                printf("%d %d\n",path[i].x+1,path[i].y+1);
        else
            puts("...");
    }
}
