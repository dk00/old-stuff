#include<cstdio>
const int dx[]={1,2,1,2,-1,-2,-1,-2},dy[]={2,1,-2,-1,2,1,-2,-1};
int n,m,s1[4][16][16],s2[4][16][16];
bool map[16][16];
struct pt
{
    int x,y;
    bool operator()()
    {return(x>=0 && x<n && y>=0 && y<m && !map[x][y]);}
    bool operator+=(int d)
    {x+=dx[d],y+=dy[d];}
}q[2007];
void clear(int s[16][16])
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            map[i][j]=0,s[i][j]=-1;
}
void go(int sx,int sy,int s[16][16])
{
    pt now;
    int i,j,k;
    q[0]=(pt){sx,sy};
    s[sx][sy]=0,map[sx][sy]=1;
    for(i=0,j=1;i<j;i++)
        for(k=0;k<8;k++)
        {
            now=q[i],now+=k;
            if(now())
            {
                q[j++]=now;
                map[now.x][now.y]=1;
                s[now.x][now.y]=s[q[i].x][q[i].y]+1;
            }
        }
}
main()
{
    int i,j,k,l,p,min,sum,x[5],y[5];
    char tmp[1000];
    while(scanf("%s",tmp)==1)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<5;i++)
            scanf("%d %d",&x[i],&y[i]);
        for(i=0;i<4;i++)
        {
            clear(s1[i]);
            go(x[i]-1,y[i]-1,s1[i]);
            clear(s2[i]);
            map[x[4]-1][y[4]-1]=1;
            go(x[i]-1,y[i]-1,s2[i]);
        }
        for(i=0,min=20000;i<n;i++)
            for(j=0;j<m;j++)
                for(k=0;k<4;k++)
                {
                    for(l=sum=0;l<4;l++)
                    {
                        p=((l==k)?s2[l][i][j]:s1[l][i][j]);
                        if(p>=0)sum+=p;
                        else break;
                    }
                    if(l>=4)min<?=sum;
                }
        puts(tmp);
        if(min<20000)
            printf("Minimum time required is %d minutes.\n",min);
        else puts("Meeting is impossible.");
    }
}
