int pl,step;
int bh,bw;
int dx[1000],dy[1000];
char map[15][15],mark[15][15];
int level=5;
short sc1[][5]={{0,1,3,5,5},{0,1,7,10,17},{0,1,7,11,19},{0,1,7,9,19}},
      sc2[][5]={{0,1,4,7,7},{0,1,4,7,7},{0,1,6,9,15},{0,1,6,9,15},
                {0,2,10,20,33};
struct S
{
    int x,y;
}list[225];
int __tmp;
inline void swap(int &a,int &b){__tmp=a,a=b,b=__tmp;}
/*
state:
    step
    map[15][15]
    adj[15][15]
    mark[15][15]
    
    list[225]
    ln,v[255][2]
    oln[255]
    ov[255]
*/
