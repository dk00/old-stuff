#include<cstdio>
#include<cstdlib>
const short ns=20;
int edge;
short pl,num[2],tri[9],to[11][11],
    move[][2]={{0,-1},{0,-1},{0,2},{1,-1},{1,2},{2,3},{3,-1},{1,5},{3,7},
    {4,-1},{4,5},{5,6},{6,7},{7,8},{8,-1},{4,-1},{6,-1},{8,-1}};
int tb1[262144];
void init()
{
    for(int i=0;i<9;i++)tri[i]=0;
    pl=edge=num[0]=num[1]=0;
}
char make(short x)
{
    short a=move[x][0],b=move[x][1];
    edge|=(1<<x);
    if(++tri[a]==3)num[pl]++;
    if(b>=0 && ++tri[b]==3)num[pl]++;
    if(tri[a]==3 ||(b>=0 && tri[b]==3))pl=!pl;
    pl=!pl;
}
int _edge[ns];
short _pl[ns],_num[ns][2],_tri[ns][9];
void store(short d)
{
    _pl[d]=pl,_edge[d]=edge;
    _num[d][0]=num[0],_num[d][1]=num[1];
    for(int i=0;i<9;i++)
        _tri[d][i]=tri[i];
}
void recover(short d)
{
    pl=_pl[d],edge=_edge[d];
    num[0]=_num[d][0],num[1]=_num[d][1];
    for(int i=0;i<9;i++)
        tri[i]=_tri[d][i];
}
short go(short d,short a,short b)
{
    if(d>=18)
        return num[pl]-num[!pl];
    if(18-num[0]-num[1]+d==18)return 18-num[!pl];
    short tmp,pre=a;
    for(int i=0;i<18;i++)
    {
        if(edge&(1<<i))continue;
        store(d);make(i);
        if(pl==_pl[d])tmp=go(d+1,a,b);
        else tmp=-go(d+1,-b,-a);
        a>?=tmp;
        //if(a>0)return a;
        if(a>=b)return b;
        recover(d);
    }
    return a;
}
main()
{
    int i,n,T,C=1,j,k;
    to[1][2]=1,to[1][3]=2,to[2][3]=3,to[2][4]=4,to[2][5]=5,to[3][5]=6,
    to[3][6]=7,to[4][5]=8,to[5][6]=9,to[4][7]=10,to[4][8]=11,
    to[5][8]=12,to[5][9]=13,to[6][9]=14,to[6][10]=15,
    to[7][8]=16,to[8][9]=17,to[9][10]=18;
    scanf("%d",&T);
    while(T--)
    {
        init();
        scanf("%d",&n);
        for(k=0;k<n;k++)
        {
            scanf("%d %d",&i,&j);
            make(to[i][j]-1);
        }
        printf("Game %d: ",C++);
        if((go(n,-1,1)>0)^pl)puts("A wins.");
        else puts("B wins.");

    }
}
