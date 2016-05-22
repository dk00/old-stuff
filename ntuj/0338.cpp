#include<cmath>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
struct pt{
    double s,t;
    int n;
    bool operator<(pt a)const{return t>a.t;}
}s[1001];
bool cmp(pt a,pt b){return a.s<b.s;}
main()
{
    int i,j,n,T,sum,ub;
    double x,y;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%lf %lf %d",&x,&y,&s[i].n);
            if(y>1000)
            {
                i--,n--;
                continue;
            }
            s[i].s=x-sqrt(1000000-y*y);
            s[i].t=x+x-s[i].s;
        }
        sort(s,s+n,cmp);
        priority_queue<pt> h;
        h.push((pt){-10e10,-10e10,0});
        ub=sum=0;
        for(i=0;i<n;i++)
        {
            /*while(!h.empty() && h.top().t<s[i].s)
                sum-=h.top().n,h.pop();
            h.push(s[i]);
            sum+=s[i].n;*/
            for(j=sum=0;j<n;j++)
                if(s[j].s<=s[i].t && s[j].t>=s[i].t)
                    sum+=s[j].n;
            ub>?=sum;
        }
        printf("%d\n",ub);
    }
}
