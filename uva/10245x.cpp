#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001;
const double inf=100000000.0;
struct pt{
    double x,y;
    bool operator<(pt a)const{return x<a.x;}
}s[N],t[N];
inline double dis(pt a,pt b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double go(int st,int ed)
{
    if(ed-st<1)
        return inf;
    int i,j,k,m=(st+ed)/2;
    double mini=go(st,m)<?go(m+1,ed);
    for(i=k=st,j=m+1;k<=ed;)
        if(j>ed || (i<=m && s[i].y<=s[j].y))
            t[k++]=s[i++];
        else
            t[k++]=s[j++];
    copy(t+st,t+ed+1,s+st);
    for(i=st;i<=ed;i++)
        for(j=i+1;j<=ed && s[j].y-s[i].y<mini;j++)
            mini<?=dis(s[i],s[j]);
    return mini;
}
main()
{
    int i,n;
    while(scanf("%d",&n)==1 && n){
        for(i=0;i<n;i++)
            scanf("%lf %lf",&s[i].x,&s[i].y);
        sort(s,s+n);
        double d=go(0,n-1);
        if(d<inf)
            printf("%.4lf\n",sqrt(d));
        else
            puts("INFINITY");
    }
}
