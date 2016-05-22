#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int cmp(int a,int b){return a>b;}
struct vec
{
    int x,y;
    vec& operator+=(vec a){x+=a.x,y+=a.y;return *this;}
    vec operator+(vec a){return(vec){x+a.x,y+a.y};}
    vec operator-(vec a){return(vec){x-a.x,y-a.y};}
    int operator*(vec a)const{return x*a.y-a.x*y;}
}p[9]={{900,900}};
int ub,n,s[9];
inline int area(int n)
{
    int i,sum=0;
    vec a={0,0},b;
    p[n]=p[0];
    for(i=0;i<n;i++)
        sum+=p[i]*p[i+1];
    if(sum<0)sum*=-1;
    return sum;
}
class hash
{
    const static int N=1000003;
    int s[N],t[N];
    int h(int k)
    {
        return k%N;
    }
public:
    void clear(){memset(s,0,sizeof(s));}
    int& operator[](int k)
    {
        int j=h(++k);
        for(;s[j] && s[j]!=k;j++);
        if(!s[j])t[j]=0;
        s[j]=k;
        return t[j];
    }
    int count(int k)
    {
        int j=h(++k);
        for(;s[j] && s[j]!=k;j++);
        return s[j]==k;
    }
}h;
vector<int> dx[301],dy[301];
int sum,m1,m2;
inline int gen(vec p,int u){sum>?=((p.x<<6)*1800+(p.y<<6)+u);
return((p.x<<6)*1800+(p.y<<6)+u);}
void go(int d,int u)
{
    int i,t,l=-1,t1=area(d);
    sum++;
    if(d==m2)
        h[i=gen(p[d-1],u)]>?=t1;
    if(d==m1 && h.count(t=gen(p[d-1],u^((1<<n)-1))))
        ub>?=t1+h[t];
    if(d>=m1)return;
    for(t=0;t<n;t++)
    {
        if((1<<t)&u)continue;
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
                if(r[i]*a<=0 && r[i]*b>=0 && (p[d]=p0+r[i]).x|1)
                    go(d+1,u|(1<<t));
        }
        vec q[]={{l,0},{0,l},{-l,0},{0,-l}};
        for(i=0;i<4;i++)
            if(q[i]*a<=0 && q[i]*b>=0 && (p[d]=p0+q[i]).x|1)
                go(d+1,u|(1<<t));
    }
}
int sqrt[90001];
main()
{
    int i,j,k;
    for(i=1;i<=300;i++)sqrt[i*i]=i;
    for(i=1;i<=300;i++)
        for(j=i;i*i+j*j<=300*300;j++)
            if(sqrt[i*i+j*j])
                dx[sqrt[i*i+j*j]].push_back(i),dy[sqrt[i*i+j*j]].push_back(j);
    while(scanf("%d",&n)>0 && n)
    {
        m1=n-n/2+1,m2=n/2+1;
        h.clear();
        for(i=0,ub=-2;i<n;i++)
            scanf("%d",s+i);
        sort(s,s+n,cmp);
        go(1,0);
        if(ub<2)ub=-2;
        printf("%d %d\n",ub/2,sum);
        sum=0;
    }
}
