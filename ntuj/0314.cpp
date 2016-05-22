#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct pt
{
    double x,y;
};
const pt nil={1e9,1e9};
double dis(pt a,pt b)
{
    return sqrt(abs(a.x-b.x)*abs(a.x-b.x)+abs(a.y-b.y)*abs(a.y-b.y));
}
struct line
{
    int x1,y1,x2,y2;
    double a,b;
    bool ve;
    line(){}
    void get(int p,int q,int r,int s)
    {
        x1=p,y1=q,x2=r,y2=s;
        if(x1==x2){ve=1;return;}
        ve=0;
        a=(y2-y1)/(double)(x2-x1);
        b=y1-a*x1;
    }
    bool in(pt p)
    {
        if(ve)return x1==p.x;
        return(abs(p.y-p.x*a-b)<1e-6 && abs(abs(x2-x1)-abs(p.x-x2)-abs(p.x-x1))<1e-6 &&
        abs(abs(y2-y1)-abs(p.y-y1)-abs(p.y-y2))<1e-6);
    }
    double len(pt p){return dis((pt){x1,y2},p);}
    pt operator+(line l)
    {
        if(ve)
        {
            if(l.ve)return nil;
            pt p;
            p.x=x1;
            p.y=p.x*l.a+l.b;
            return p;
        }
        if(a==l.a)return nil;
        pt p;
        p.x=(l.b-b)/(a-l.a);
        p.y=p.x*a+b;
        return p;
    }
}s[199];
main()
{
    int i,j,n,a,b,c,d,sum,C=1;
    vector<double> t[199];
    while(scanf("%d",&n)==1 && n)
    {
        for(i=0;i<n;i++)
        {
            scanf("%d %d %d %d",&a,&b,&c,&d);
            s[i].get(a,b,c,d);
            t[i].clear();
            t[i].push_back(-25.0);
            t[i].push_back(dis((pt){a,b},(pt){c,d})+25.0);
        }
        for(i=0;i<n;i++)
            for(j=0;j<i;j++)
            {
                pt tmp=s[i]+s[j];
                if(s[i].in(tmp) && s[j].in(tmp))
                    t[i].push_back(s[i].len(tmp)),
                    t[j].push_back(s[j].len(tmp));
            }
        for(i=sum=0;i<n;i++)
        {
            sort(t[i].begin(),t[i].end());
            for(j=1;j<t[i].size();j++)
                sum+=floor((t[i][j]-t[i][j-1])/50);
        }
        printf("Map %d\nTrees = %d\n",C++,sum);
    }
}
