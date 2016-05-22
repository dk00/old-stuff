#include<cmath>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
int cmp(int a,int b){return a>b;}
struct vec
{
    int x,y;
    vec& operator+=(vec a){x+=a.x,y+=a.y;}
    int operator*(vec a)const{return x*a.y-a.x*y;}
}p[9];
int n,ub,u[9],s[9];
inline int area(int n)
{
    int i,sum=0;
    vec a={0,0},b;
    for(i=0;i<n;i++)
    {
        b=a;
        b+=p[i];
        sum+=a*b;
        a=b;
    }
    if(sum<0)sum*=-1;
    return sum;
}
vector<int> l0[301],l1[301];
int test(int m)
{
    vec a={0,0};
    int i,j;
    for(i=0;i<m;i++)
        a+=p[i];
    for(i=j=0;i<n;i++)
        if(!u[i])j+=s[i];
    return a.x*a.x+a.y*a.y>j*j;
}
inline double h(int d)
{
    int i,l;
    vec a={0,0};
    for(i=0;i<n;i++)
        if(!u[i])l+=s[i];
    for(i=0;i<d;i++)a+=p[i];
    double x=sqrt(p[i].x*p[i].x+p[i].y*p[i].y);

    return ub+1;
}
void go(int d,int l,int c)
{
    int i;
    if(d>=n)
    {
        vec a={0,0};
        for(i=0;i<d;i++)a+=p[i];
        if(!a.x && !a.y)ub>?=area(d);
    }
    else if(!l)
    {
/**/    if(test(d))return;
//**/    if(h(d)<=ub)return;
        int pre=-1;
        if(!d)
            u[0]=1,go(d,s[0],c),u[0]=0;
        else for(i=1;i<n;i++)
            if(!u[i] && pre!=s[i])
                u[i]=1,go(d,pre=s[i],c),u[i]=0;
    }
    else
    {
        vec a={0,0},b={0,0};
        for(i=0;i<d;i++)a+=p[i];
        a.x*=-1,a.y*=-1;
/**/    if(a*p[0]>0)return;
        if(d)b=p[d-1];
        else a=(vec){1,1},b=(vec){0,1};
        vec q[]={{l,0},{0,l},{-l,0},{0,-l}};
        for(int z=0;z<l0[l].size();z++)
        {
            int j=l0[l][z],k=l1[l][z];
            vec r[]={{j,k},{j,-k},{k,-j},{-k,-j},{-j,-k},{-j,k},{-k,j},{k,j}};
            for(i=0;i<8;i++)
                if((p[d]=r[i])*a<=0 && r[i]*b>=0)
                    go(d+1,0,c);
        }
        for(i=0;i<4;i++)
            if((p[d]=q[i])*a<=0 && q[i]*b>=0)
                go(d+1,0,c);
    }
}
int sqrt[90001];
main()
{
    int i,j;
    for(i=1;i<=300;i++)sqrt[i*i]=i;
    for(i=1;i<=300;i++)
        for(j=i;i*i+j*j<=300*300;j++)
            if(sqrt[i*i+j*j])
                l0[sqrt[i*i+j*j]].push_back(i),l1[sqrt[i*i+j*j]].push_back(j);
    while(scanf("%d",&n)>0 && n)
    {
        for(i=ub=0;i<n;i++)
            u[i]=0,scanf("%d",s+i);
        sort(s,s+n);
        go(0,0,0);
        if(ub)printf("%d\n",ub/2);
        else puts("-1");
    }
}
