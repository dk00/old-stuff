#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
struct pt
{
    double x,y;
    bool operator<(pt a)const{return x<a.x;}
}s[10000],t1[10000],t0[10000];
bool cmp(const pt& a,const pt& b){return b<a;}
double dis(pt a,pt b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double go(int st,int ed)
{
    double mini=1e4;
    int i,j,l;
    if(1)
    {
        for(i=st;i<=ed;i++)
            for(j=i+1;j<=ed;j++)
                mini<?=dis(s[i],s[j]);
        sort(s+st,s+ed+1,cmp);
        return mini;
    }
    int mid=(st+ed)/2;
    go(st,mid-1);
    go(mid+1,ed);
    merge(s+st,s+mid,s+mid+1,s+ed+1,t1+st);
    for(i=st,l=0;i<=ed;i++)
        if(abs(t1[i].y-s[mid].y)<mini)
            t0[l++]=t1[i];
    for(i=0;i<l;i++)
    {
        mini<?=dis(s[mid],t0[i]);
        for(j=1;j<8 && i+j<l;j++)
            mini<?=dis(t0[i],t0[j]);
    }
    copy(t1+st,t1+ed+1,s+st);
    return mini;
}
main()
{
    int i,j,n;
    double mini;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%lf %lf",&s[i].x,&s[i].y);
        sort(s,s+n);
        mini=go(0,n-1);
        if(mini<10000)
            printf("%.4lf\n",mini);
        else
            puts("INFINITY");
    }
}
