#include<cstdio>
struct pt{int x,y;}p[99];
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int n,m,r0,r[59049],max[59049],t0,t[9][9];
char s[9][9],u[99],best[99];
int calc()
{
    int i,j;
    for(i=j=0;i<m;i++)
        j=j*3+u[i];
    return j;
}
inline int val(int x,int y){return x>=0 && x<n && y>=0 && y<n;}
int gg(int x,int y)
{
    if(t[x][y]==t0)return 0;
    t[x][y]=t0;
    int i,sum=1;
    for(i=0;i<4;i++)
        if(val(x+dx[i],y+dy[i]) && s[x][y]==s[x+dx[i]][y+dy[i]])
            sum+=gg(x+dx[i],y+dy[i]);
    return sum;
}
int sc()
{
    int i,j,g[]={0,0};
    for(i=0;i<m;i++)
        s[p[i].x][p[i].y]=u[i]+'0';
    for(t0++,i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(t[i][j]!=t0)
                g[s[i][j]-'0']>?=gg(i,j);
    return g[0]-g[1];
}
int go(int k,int d)
{
    int z=calc();
    if(r[z]==r0)return max[z];
    if(d>=m)
    {
        r[z]=r0;
        return max[z]=(1-k*2)*sc();
    }
    r[z]=r0,max[z]=-99;
    int i,j;
    for(i=0;i<m;i++)
        if(u[i]==2)
        {
            u[i]=k;
            if((j=-go(!k,d+1))>max[z])
                max[z]=j,best[d]=i;
            u[i]=2;
        }
    return max[z];
}
main()
{
    int i,j,k;
    while(scanf("%d",&n)>0 && n)
    {
        for(r0++,i=k=m=0;i<n;i++)
        {
            scanf("%s",s[i]);
            for(j=0;s[i][j];j++)
                if(s[i][j]=='.')
                    u[m]=2,p[m++]=(pt){i,j};
                else
                    k+=1-(s[i][j]-'0')*2;
        }
        printf("(%d,%d) %d\n",p[best[0]].x,p[best[0]].y,go(k,0));
    }
}
