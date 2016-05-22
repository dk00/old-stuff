int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
const int rownum[6]={5,0,-5,-5,0,5},remnum[5]={0,100,50,20,1};
inline int abs(int a){return a<0?-a:a;}
struct pt
{
    int x,y,d;
}_q[2][100],*q1,*q2,*tmp;
int ptcmp(const void *a,const void *b)
{
    return ((pt *)a)->d-((pt *)b)->d;
}
class P
{
    void expd(int,int);
    void go();
public:
    int score,ball,num,expnum,s[6][6],p1,p2,pn;
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
        printf("score = %d\n",score);
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
    expd(x,y);
    go();
}
void P::expd(int x,int y)
{
    expnum++,num--;
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
        f3=expnum;
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
        f3=expnum-f3;
        if(f2>0 && f1+f2+f3>=3)
        {
            ball++;
            f3-=3-f1-f2;
            f1=f2=0;
        }
        ball+=f3/3;
        f3%=3,f1=f2,f2=f3;
        p1=p2,p2=0;
        tmp=q1,q1=q2,q2=tmp;
    }
    ball+=expnum/6;
    expnum%=6;
}
int P::calc()
{
    if(num==0)return(score=-ball);
    int i,j,ravg,cavg,rsum[6],csum[6];
    score=0;
    for(i=0;i<6;i++)
        for(j=rsum[i]=0;j<6;j++)
            rsum[i]+=s[i][j];
    for(i=0;i<6;i++)
        for(j=csum[i]=0;j<6;j++)
            csum[i]+=s[j][i];
    for(i=ravg=cavg=0;i<6;i++)
    {
        rsum[i]+=rownum[i],csum[i]+=rownum[i];
        ravg+=rsum[i],cavg+=csum[i];
    }
    ravg/=6,cavg/=6;
    for(i=0;i<6;i++)
        score+=abs(rsum[i]-ravg)+abs(csum[i]-cavg);
    return(score+=(100-ball)*30);
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
