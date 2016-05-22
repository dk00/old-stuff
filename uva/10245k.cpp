#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct pt
{
    double x,y;
    bool operator<(pt a)const{return x<a.x;}
}s[10000],t1[10000],t0[10000];
bool cmp(const pt& a,const pt& b){return a.y<b.y;}
double dis(pt a,pt b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double mini;
double go(int st,int ed)
{
    int i,j,l;
    if(ed-st<8)
    {
        for(i=st;i<=ed;i++)
            for(j=i+1;j<=ed;j++)
                mini<?=dis(s[i],s[j]);
        sort(s+st,s+ed+1,cmp);
        return mini;
    }
    int mid=(st+ed)/2;
    double tx=s[mid].x;
    mini<?=go(st,mid-1);
    mini<?=go(mid,ed);
    merge(s+st,s+mid,s+mid,s+ed+1,t1+st,cmp);
    for(i=st,l=0;i<=ed;i++)
        if((t1[i].x-tx)*(t1[i].x-tx)<mini)
            t0[l++]=t1[i];
    for(i=0;i<l;i++)
        for(j=1;j<=8 && i+j<l;j++)
            mini<?=dis(t0[i],t0[i+j]);
    copy(t1+st,t1+ed+1,s+st);
    return mini;
}
main()
{
    srand(time(NULL));
    int i,j,k,n;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%lf %lf",&s[i].x,&s[i].y);
        mini=1e8;
        for(i=0;i<50;i++)
        {
            j=rand()%n;
            k=rand()%n;
            if(j!=k)mini<?=dis(s[j],s[k]);
        }
        sort(s,s+n);
        mini=sqrt(go(0,n-1));
        if(mini<10000)
            printf("%.4lf\n",mini);
        else
            puts("INFINITY");
    }
}
