#include<cstdio>
char dx[]={1,0,-1,0},dy[]={0,1,0,-1},bx[4],by[4];
int m;
char map[31][31];
char out(char x,char y){return(x<=0 || x>=m || y<=0 || y>=m);}
struct pt
{
    char x,y,u[4],v;
    char go(char d)
    {
        char i,nx=x+dx[d],ny=y+dy[d];
        for(i=0;!out(nx,ny) && !map[nx][ny];i++,nx+=dx[d],ny+=dy[d]);
        if(map[nx][ny])return -1;
        nx=x+dx[d],ny=y+dy[d];
        for(i=1;!out(nx,ny);i++,nx+=dx[d],ny+=dy[d])
            map[nx][ny]=1;
        return i;
    }
    void clear(char d)
    {
        char i,nx=x+dx[d],ny=y+dy[d];
        for(i=0;!out(nx,ny);i++,nx+=dx[d],ny+=dy[d])
            map[nx][ny]=0;
    }
}s[99];
void test(pt &a,pt &b)
{
    if(a.x==b.x)
    {
        if(a.y<b.y)a.u[1]=b.u[3]=0;
        else b.u[1]=a.u[3]=0;
    }
    if(a.y==b.y)
    {
        if(a.x<b.x)a.u[0]=b.u[2]=0;
        else b.u[0]=a.u[2]=0;
    }
    if(a.x<b.x)
    {
        if(a.y<b.y)
            a.u[0]&=~2,a.u[1]&=~2,
            b.u[2]&=~2,b.u[3]&=~2;
        if(a.y>b.y)
            a.u[0]&=~2,a.u[3]&=~2,
            b.u[1]&=~2,b.u[2]&=~2;
    }
    if(a.x>b.x)
    {
        if(a.y>b.y)
            a.u[2]&=~2,a.u[3]&=~2,
            b.u[0]&=~2,b.u[1]&=~2;
        if(a.y<b.y)
            a.u[1]&=~2,a.u[2]&=~2,
            b.u[0]&=~2,b.u[3]&=~2;
    }
}
int n,next,min;
char ans[99];
int base[99];
char go(int i,int d)
{
    if(d>min)
    {
        next<?=d;
        return 0;
    }
    if(i>=n)return 1;
    if(ans[i])return go(i+1,d);
    char j,k;
    for(j=0;j<4;j++)
    {
        k=s[i].go(j);
        if(k>=0)
        {
            ans[i]=j+1;
            if(go(i+1,d+k-base[i]))
                return 1;
            ans[i]=0;
            s[i].clear(j);
        }
    }
    return 0;
}
char str[][6]={"","right","up","left","down"};
main()
{
    int i,j,k,tmp,sum;
    while(scanf("%d %d",&m,&n)==2)
    {
        for(i=0;i<m;i++)
            for(j=0;j<m;j++)
                map[i][j]=0;
        bx[0]=by[1]=m;
        for(i=0;i<n;i++)
        {
            scanf("%d %d",&s[i].x,&s[i].y);
            map[s[i].x][s[i].y]=1;
            for(k=0;k<4;k++)
            {
                s[i].u[k]=3;
                j=s[i].go(k);
                if(j>=0)s[i].clear(k);
                else continue;
                tmp=s[i].go(s[i].v);
                if(tmp>=0)s[i].clear(s[i].v);
                else tmp=20000;
                if(j>=0 && j<tmp)
                    s[i].v=k;
            }
        }
        for(i=0;i<n;i++)
            for(j=0;j<i;j++)
                test(s[i],s[j]);
        for(i=j=sum=0;i<n;i++)
        {
            k=s[i].v;
            if(s[i].u[k]==3)
            {
                j+=dx[k]*(bx[k]-s[i].x)+dy[k]*(by[k]-s[i].y);
                ans[i]=k+1;
            }
            base[i]=20000;
            for(k=0;k<4;k++)
            {
                tmp=s[i].go(k);
                if(tmp>=0)
                {
                    base[i]<?=tmp;
                    s[i].clear(k);
                }
            }
            if(!ans[i])sum+=base[i];
        }
        next=sum;
        while(1)
        {
            min=next,next=2000000000;
            if(go(0,sum))break;
        }
        printf("%d\n",j+min);
        for(i=0;i<n;i++)
            puts(str[ans[i]]);
    }
}
