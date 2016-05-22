#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
int cmp(int a,int b){return a>b;}
struct vec
{
    int x,y;
    vec& operator+=(vec a){x+=a.x,y+=a.y;return *this;}
    vec operator+(vec a){vec tmp={x+a.x,y+a.y};return tmp;}
    vec operator-(vec a){vec tmp={x-a.x,y-a.y};return tmp;}
    int operator*(vec a)const{return x*a.y-a.x*y;}
}p[9]={{900,900}};
int n,s[9];
inline int area(int n)
{
    int i,sum=0;
    vec a={0,0};
    p[n]=p[0];
    for(i=0;i<n;i++)
        sum+=p[i]*p[i+1];
    if(sum<0)sum*=-1;
    return sum;
}
map<int,int> h;
vector<int> dx[301],dy[301];
inline int gen(int x,int y,int u){return(x<<17)+(y<<6)+u;}
inline int gen(vec p,int u){return(p.x<<17)+(p.y<<6)+u;}
void go(int d,int u)
{
    int i,l=-1,t;
	int &t0=h[gen(p[d-1],u)],t1=area(d);
	if(t1>t0)t0=t1;
    if(d*2>=n+2)return;
    for(t=0;t<n;t++)
    {
        if((1<<t)&u || l==s[t])continue;
        l=s[t];
        vec p0=p[d-1],a={-1,0},b={0,1};
        if(d>1)a=p0-p[0];
        if(d>1)b=p[d-1]-p[d-2];
        a.x*=-1,a.y*=-1;
        for(int z=0;z<dx[l].size();z++)
        {
            int j=dx[l][z],k=dy[l][z];
            vec r[]={{j,k},{j,-k},{k,-j},{-k,-j},{-j,-k},{-j,k},{-k,j},{k,j}};
            for(i=0;i<8;i++)
                if((p[d]=p0+r[i])*a<=0 && r[i]*b>=0)
                    go(d+1,u|(1<<t));
        }
        vec q[]={{l,0},{0,l},{-l,0},{0,-l}};
        for(i=0;i<4;i++)
            if((p[d]=p0+q[i])*a<=0 && q[i]*b>=0)
                go(d+1,u|(1<<t));
    }
}
int sqrt[90001];
int main()
{
    int i,j,k,ub;
    for(i=1;i<=300;i++)sqrt[i*i]=i;
    for(i=1;i<=300;i++)
        for(j=i;i*i+j*j<=300*300;j++)
            if(sqrt[i*i+j*j])
                dx[sqrt[i*i+j*j]].push_back(i),dy[sqrt[i*i+j*j]].push_back(j);
    while(scanf("%d",&n)>0 && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        sort(s,s+n,cmp);
        go(1,0);
        for(i=0,ub=-2;i<=1800;i++)
            for(j=0;j<=1800;j++)
                for(k=(1<<n)-1;k>0;k--)
                    if(h.count(gen(i,j,k)) && h.count(gen(i,j,k^((1<<n)-1))))
					{
						int t0=h[gen(i,j,k)]+h[gen(i,j,k^((1<<n)-1))];
                        if(t0>ub)ub=t0;
					}
        printf("%d\n",ub/2);
    }
}
