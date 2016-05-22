#include<cstdio>
const int r[6][6]={
{0,-1,-1,-1,-1,-1},
{1,2,-1,-1,-1,-1},
{3,4,5,-1,-1,-1},
{6,7,8,9,-1,-1},
{10,11,12,13,14,-1},
{-1,-1,-1,-1,-1,-1}},dx[]={1,1,0},dy[]={0,1,1};
int s[50000],b[20];
bool go(int x,int f=0)
{
    if(!x)return 0;
    int win=0;
    int i,j,d,now,nx,ny;
    if(s[x]>=0 && !f)
        return s[x];
    for(i=0;!win && i<5;i++)
        for(j=0;!win && r[i][j]>=0;j++)
        {
            if(!(x&b[r[i][j]]))
                continue;
            for(d=0;!win && d<3;d++)
            {
                nx=i,ny=j;
                now=x&~b[r[i][j]];
                while(!win)
                {
                    win=!go(now);
                    if(win && f)
                    {
                        while(nx>=i && ny>=j)
                        {
                            printf("%d ",r[nx][ny]+1);
                            nx-=dx[d],ny-=dy[d];
                        }
                        puts("");
                    }
                    nx+=dx[d],ny+=dy[d];
                    if(r[nx][ny]<0 || !(now&b[r[nx][ny]]))
                        break;
                    now&=~b[r[nx][ny]];
                }
            }
        }
    return(s[x]=win);
}
main()
{
    int i,j,k;
    for(i=0;i<20;i++)
        b[i]=1<<i;
    for(i=0;i<32768;i++)
        s[i]=-1;
    while(1)
    {
        for(i=k=0;i<15;i++)
        {
            scanf("%d",&j);
            if(j)k|=b[i];
        }
        if(!go(k,1))
            puts("impossible");
    }
}
