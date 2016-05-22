#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=999;
int gcd(int a,int b)
{
    if(!a || !b)return 1;
    a=a<0?-a:a;
    b=b<0?-b:b;
    while((a%=b)&&(b%=a));
    return a+b;
}
struct px
{
    int a,b;
    bool operator<(px x)const
    {
        if(a!=x.a)return a<x.a;
        return b<x.b;
    }
};
struct pt{
    double d;
    int h;
    bool operator<(pt a)const
    {
        if(d!=a.d)return d<a.d;
        return h<a.h;
    }
};
struct tree{
    int x,y,z;
    px operator-(tree a)
    {
        int dx=x-a.x,dy=y-a.y,d=gcd(dx,dy);
        dx/=d,dy/=d;
        return (px){dx,dy};
    }
    pt operator^(tree a){
        return (pt){sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y)),z-a.z};
    }
}s[N];
int go(vector<pt>& s)
{
    sort(s.begin(),s.end());
    int i,j,k;
    for(i=k=1,j=0;i<s.size();i++)
        if(s[i].h*s[j].d>s[j].h*s[i].d)
            k++,j=i;
    return k;
}
main()
{
    int i,j,k,x,y,z,t,ub,n,m;
    while(scanf("%d %d",&n,&m)==2 && n){
        for(i=0;i<n;i++)
            for(j=0;j<m;j++){
                scanf("%d",&k);
                if(k)s[t++]=(tree){i+1,j+1,k};
            }
        for(i=0,ub=-1;i<t;i++){
            map<px,vector<pt> > H;
            for(j=0;j<t;j++)
                if(i!=j)H[s[i]-s[j]].push_back(s[j]^s[i]);
            map<px,vector<pt> >::iterator ptr=H.begin();
            for(j=0;ptr!=H.end();ptr++){
                vector<pt>& s=ptr->second;
                j+=go(s);
            }
            if(j>ub)
                ub=j,x=s[i].x,y=s[i].y;
            if(j==ub)x=y=0;
        }
        printf("%d %d %d\n",x,y,ub);             
    }
}

