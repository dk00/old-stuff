#include<cstdio>
int dx[]={1,0,-1,0},dy[]={0,1,0,-1},bad[]={0,50,20,5,1},
od[6][6]=
{{5,4,3,3,4,5},
{4,2,1,1,2,4},
{3,1,0,0,1,3},
{3,1,0,0,1,3},
{4,2,1,1,2,4},
{5,4,3,3,4,5}
};
struct pt
{
    int x,y,d;
}_q[2][1000],*q1=_q[0],*q2=_q[1],*tmp,path[200],list[36];
class P
{
    void expd(int,int);
    void go();
public:
    int s[6][6],path[20],pn,p1,p2,num,cnt,fcnt,score;
    int add(int,int);
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
        p1=p2=pn=cnt=fcnt=num=0;
        int i,j;
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
            {
                scanf("%d",&s[i][j]);
                if(s[i][j])
                    num++;
            }
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
}test,best,tp[200];
int P::add(int a,int b)
{
    cnt--;
    if(s[a][b]<=3)
    {
        s[a][b]++;
        return -1;
    }
    s[a][b]=0;
    expd(a,b);
    fcnt=0;
    go();
    int i,j,tmpnum=0;
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
            tmpnum+=bad[s[i][j]];
    return tmpnum;
}
void P::expd(int a,int b)
{
    num--,fcnt++;
    s[a][b]=0;
    for(int i=0;i<4;i++)
        q2[p2++]=(pt){a+dx[i],b+dy[i],i};
}
void P::go()
{
    int i,x,y,d,f1,f2,f3,cnt2=0;
    p1=p2,p2=f1=f2=f3=0;
    tmp=q1,q1=q2,q2=tmp;
    while(p1>0 && num>0)
    {
        fcnt=0;
        for(i=0;i<p1 && num>0;i++)
        {
            x=q1[i].x,y=q1[i].y,d=q1[i].d;
            if(x<0 || x>5 || y<0 || y>5)
                continue;
            if(s[x][y]==0)
                q2[p2++]=(pt){x+dx[d],y+dy[d],d};
            else if(s[x][y]<4)
                s[x][y]++;
            else
                cnt2++,expd(x,y);
        }
        f3=fcnt;
        if(f1>0 && f2>0 && f3>0)
        {
            cnt+=(f1+f2+f3)/3;
            f3=(f1+f2+f3)%3;
            f1=f2=0;
        }
        f1=f2,f2=f3;
        p1=p2,p2=0;
        tmp=q1,q1=q2,q2=tmp;
    }
    cnt+=cnt2/6;
}
class Heap
{
    P s[100000];
    void up();
    void down();
public:
    int n;
    P exmin()
    {
        s[0]=s[1];
        s[1]=s[--n];
        down();
        return s[0];
    }
    void insert(P t)
    {
        s[n++]=t;
        up();
    }
}heap;
void Heap::up()
{
    int i;
    P tmp;
    for(i=n;i>1 && s[i].score<s[i/2].score;i/=2)
        tmp=s[i/2],s[i/2]=s[i],s[i]=tmp;
}
void Heap::down()
{
    int i;
    P tmp;
    for(i=0;i*2+1<n;)
    {
        if(i*2+2>=n || s[i*2+1].score<s[i*2+2].score)
            if(s[i].score>s[i*2+1].score)
                tmp=s[i],s[i]=s[i*2+1],s[i*2+1]=tmp;
            else
                break;
        else if(s[i].score>s[i*2+2].score)
            tmp=s[i],s[i]=s[i*2+2],s[i*2+2]=tmp;
        else
            break;
    }
}
int clear,snum,limit,rem[20][36];
int dfs(int n,int x)
{
    if(x>=36)
        return 2000;
    int i,j,min=2147483647,tmpr;
    if(n==1)
    {
        for(x=0;x<36;x++)
        {
            i=list[x].x,j=list[x].y;
            if(tp[1].s[i][j]==4)
            {
                path[0]=(pt){i,j,0};
                tp[0]=tp[1];
                tmpr=tp[0].add(i,j);
                tp[0].path[tp[0].pn++]=x;
                if(!tmpr)
                    tmpr=-tp[0].cnt;
                if(tmpr<min)
                    min=tmpr;
                if(tmpr<0 && tp[0].cnt>best.cnt)
                    best=tp[0];
            }
        }
        return min;
    }
    for(;x<36;x++)
    {
        i=list[x].x,j=list[x].y;
        if(tp[n].s[i][j] && tp[n].s[i][j]<4)
        {
            tp[n-1]=tp[n],tp[n-1].add(i,j);
            tp[n-1].path[tp[n-1].pn++]=x;
            path[n-1]=(pt){i,j,0};
            tmpr=dfs(n-1,x);
            if(tmpr<min)
                min=tmpr;
        }
    }
    return min;
}
void branch(P root)
{
    if(root.pn>8)
        return;
    int i,j,k,x,y,now;
    static const int bound=5;
    P leaf;
    for(i=0;i<36;i++)
    {
        x=list[i].x,y=list[i].y;
        if(root.s[x][y])
        {
            leaf=root;
            leaf.add(x,y);
            tp[bound]=leaf;
            leaf.path[leaf.pn++]=i;
            leaf.score=2000000;
            for(k=1;k<=bound;k++)
            {
                clear=0;
                tp[k]=leaf;
                now=dfs(k,0);
                if(now<leaf.score)
                    leaf.score=now;
            }
            heap.insert(leaf);
        }
    }
}
main()
{
    int i,j,k,n;
    for(k=n=0;k<5;k++)
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
                if(od[i][j]==k)
                    list[n++]=(pt){i,j,0};
    while(1)
    {
        heap.n=1;
        best.cnt=-1000;
        test.get();
        snum=clear=0;
        branch(test);
        while(heap.n<1000 && heap.n>1 && best.cnt<1)
            branch(heap.exmin());
        printf("+%d\n",best.cnt+best.pn);
        for(i=0;i<best.pn;i++)
            printf("%d %d\n",list[best.path[i]].x+1,list[best.path[i]].y+1);
    }
}
