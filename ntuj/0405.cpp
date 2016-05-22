#include<map>
#include<cstdio>
#include<string>
using namespace std;
const int N=128,M=128,dx[]={0,1,0,1},dy[]={0,0,1,1};
char s[9][N+1][N+1];
map<string,int> h;
int go(int x,int y,int n)
{
    if(!n)
        return 1;
    int i,j,d=(1<<(n-1)),sum=1;
    for(i=j=0;i<4;i++)
    {
        sum+=go(x+d*dx[i],y+d*dy[i],n-1);
        if(i && s[n-1][x+d*dx[i]][y+d*dy[i]]!=
        s[n-1][x+d*dx[i-1]][y+d*dy[i-1]])j=1;
    }
    if(s[n-1][x][y]!=3 && !j)
    {
        s[n][x][y]=s[n-1][x][y];
        return 1;
    }
    s[n][x][y]=3;
    return sum;
}
string t[9][N][N];
int gos(int x,int y,int n)
{
    if(s[n][x][y]!=3)return 1;
    int i,nx,ny,sum=1,d=(1<<(n-1));
    string &cur=t[n][x][y];
    cur="";
    for(i=0;i<4;i++)
    {
        nx=x+d*dx[i];
        ny=y+d*dy[i];
        if(s[n-1][nx][ny]!=3)
            sum++,cur+=(s[n-1][nx][ny]+'0');
        else
            sum+=gos(nx,ny,n-1),cur+="("+t[n-1][nx][ny]+")";
    }
    if(h[cur])sum=0;
    else h[cur]=1;
    return sum;
}
main()
{
    int i,j,n,m;
    while(~scanf("%d %d",&n,&m) && n+m)
    {
        h.clear();
        for(int k=0;k<9;k++)
        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                s[k][i][j]=0;
        for(i=0;i<n;i++)
        {
            scanf("%s",s[0][i]);
            for(j=0;j<m;j++)
                s[0][i][j]-='0';
        }
        for(i=0;(1<<i)<n || (1<<i)<m;i++);
        j=go(0,0,i);
        printf("%d %d\n",j,gos(0,0,i));
    }
}
