int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
inline int abs(int a){return a<0?-a:a;}
struct pt
{
    int x,y,d;
}_q[2][1000],*q1,*q2,*tmp;
int ptcmp(const void *a,const void *b)
{
    return ((pt *)a)->d-((pt *)b)->d;
}
class P
{
    void expd(int,int);
    void go();
public:
    int score,p1,p2,pn,num,expnum;
    char ball,s[6][6];
    pt path[20];
    void add(int,int);
    int calc();
    int remain();
    bool operator<(P t)
    {
        return score<t.score;
    }
    void get()
    {
        int i,j;
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
            {
                scanf("%d",&s[i][j]);
                if(s[i][j])num++;
            }
    }
    void set(){pn=p1=p2=num=score=ball=expnum=0;}
    void print()
    {
        printf("score = %d\n",ball);
        if(num>0)
            return;
        for(int i=0;i<pn;i++)
            printf("%d %d\n",path[i].x+1,path[i].y+1);
    }
};
void P::add(int x,int y)
{
    ball--;
    path[pn++]=(pt){x,y,0};
    if(s[x][y]<4)
    {
        s[x][y]++;
        return;
    }
    q1=_q[0],q2=_q[1],p1=p2=0;
    expnum=0;
    expd(x,y);
    go();
}
void P::expd(int x,int y)
{
    expnum++,num--;
    s[x][y]=0;
    for(int i=0;i<4;i++)
        q2[p2++]=(pt){x+dx[i],y+dy[i],i};
}
void P::go()
{
    int i,x,y,d,f1,f2,f3;
    tmp=q1,q1=q2,q2=tmp;
    p1=p2,p2=0;
    f1=f2=f3=0;
    while(p1>0 && num>0)
    {
        for(i=0;i<p1;i++)
        {
            x=q1[i].x,y=q1[i].y,d=q1[i].d;
            if(x<0 || x>=6 || y<0 || y>=6)
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
    ball+=expnum/3;
}
int c_tmp[4][6][6];
int P::calc()
{
    if(num==0)return(score=-ball);
    static const int anum[5][6]={
    //  0    1  2p   2   3   4
    {    0,  0,  0,  0,  0,  0},
    {10000,250,150,100, 60, 40},
    { 7500,150,100, 60, 40, 25},
    { 5000,100, 60, 40, 25, 15},
    { 2500, 60, 40, 25, 15, 10}},
    snum[]={0,-1,-2,-5,-10};
    int i,j,k,lx,ly,x,y,count,sum,ne;
    for(int k=0;k<4;k++)
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
                c_tmp[i][j][k]=0;
    for(i=0;i<6;i++)
    {
        for(lx=0;lx<6 && s[lx][i]==0;lx++);
        for(ly=0;ly<6 && s[i][ly]==0;ly++);
        for(j=lx+1;j<6;j++)
            if(s[j][i])
            {
                c_tmp[lx][i][0]=s[j][i];
                c_tmp[j][i][1]=x[lx][i];
                lx=j;
            }
        for(j=ly+1;j<6;j++)
            if(s[i][j])
            {
                c_tmp[i][ly][2]=s[i][j];
                c_tmp[i][j][3]=s[i][ly];
                ly=j;
            }
    }
    for(i=score=0;i<6;i++)
        for(j=0;j<6;j++)
            if(s[i][j])
            {
                ne=c_tmp[i][j];
                count=0;
                if(ne[0])count++;
                if(ne[1])count++;
                if(ne[2])count++;
                if(ne[3])count++;
                if(count>2)count++;
                else if(count==1);
                else if(!(ne[0] && ne[1]) || !(ne[2] && ne[3]))
                    count++;
                sum=anum[s[i][j]][count]-
                (snum[ne[0]]+snum[ne[1]]+snum[ne[2]]+snum[ne[3]]);
                if(snum>0)
                    score+=sum;
            }
    return score;
}
int P::remain()
{
    int i,j,sum=0;
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
            sum+=remnum[s[i][j]];
    return sum;
}
class Heap
{
public:
    int n;
    P s[10000],tmp;
    void insert(P);
    P exmin();
};
void Heap::insert(P t)
{
    s[n]=t;
    for(int i=n++;i>1 && s[i]<s[i/2];i/=2)
        tmp=s[i],s[i]=s[i/2],s[i/2]=tmp;
}
P Heap::exmin()
{
    s[0]=s[1];
    s[1]=s[--n];
    for(int i=1;i*2+1<n;)
    {
        if((i*2+2>=n || s[i*2+1]<s[i*2+2]) && s[i*2+1]<s[i])
        {
            tmp=s[i],s[i]=s[i*2+1],s[i*2+1]=tmp;
            i=i*2+1;
        }
        else if(i*2+2<n && s[i*2+2]<s[i])
        {
            tmp=s[i],s[i]=s[i*2+2],s[i*2+2]=tmp;
            i=i*2+2;
        }
        else return s[0];
    }
}
