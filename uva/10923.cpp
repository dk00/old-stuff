#include<cstdio>
#include<cstring>
const int dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,1,1,1,0,-1,-1,-1};
struct pt
{
    char x,y;
    void go(int d){x+=dx[d],y+=dy[d];}
}st,_st[10],s[100],_s[10][100];
char map[9][9],_map[10][9][9];
int n,_n[10];
void mem(int v)
{
    _n[v]=n,_st[v]=st;
    for(int i=0;i<n;i++)
        _s[v][i]=s[i];
    for(int i=0;i<9;i++)
        strcpy(_map[v][i],map[i]);
}
void rec(int v)
{
    n=_n[v],st=_st[v];
    for(int i=0;i<n;i++)
        s[i]=_s[v][i];
    for(int i=0;i<9;i++)
        strcpy(map[i],_map[v][i]);
}
char des[100];
int u[9][8];
bool go(int v)
{
    if(!n)return 1;
    if(v<=0)return 0;
    char good;
    int i,j,k;
    for(i=0;i<8;i++)
    {
        mem(v);
        st.go(i);
        if(st.x>=0 && st.x<9 && st.y>=0 && st.y<8 &&
        map[st.x][st.y]!='#')good=1;
        for(j=0;j<72;j++)u[j/8][j%8]=-1;
        for(j=0;good && j<n;j++)
        {
            des[j]=0;
            if(s[j].x<st.x)s[j].x++;
            if(s[j].x>st.x)s[j].x--;
            if(s[j].y<st.y)s[j].y++;
            if(s[j].y>st.y)s[j].y--;
            if(s[j].x==st.x && s[j].y==st.y)good=0;
            if(u[s[j].x][s[j].y]>=0)
            {
                map[s[j].x][s[j].y]='#';
                des[u[s[j].x][s[j].y]]=1;
            }
            u[s[j].x][s[j].y]=j;
            if(map[s[j].x][s[j].y]=='#')des[j]=1;
        }
        if(good)
        {
            for(j=k=0;j<n;j++)
                if(!des[j])s[k++]=s[j];
            n=k;
            good=go(v-1);
        }
        rec(v);
        if(good)return 1;
    }
    return 0;
}
main()
{
    int i,j,T;
    scanf("%d",&T);
    while(T--)
    {
        for(i=n=0;i<9;i++)
        {
            scanf("%s",map[i]);
            for(j=0;j<8;j++)
            {
                if(map[i][j]=='E')
                    s[n++]=(pt){i,j};
                if(map[i][j]=='S')
                    st=(pt){i,j};
            }
            if(map[i][j]!='#')map[i][j]='.';
        }
        for(i=0;i<=9 && !go(i);i++)
            i=i+i-i;
        if(i<=9)printf("I'm the king of the Seven Seas!\n");
        else puts("Oh no! I'm a dead man!");
    }
}
