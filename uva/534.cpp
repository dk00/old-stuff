#include<cmath>
#include<cstdio>
#include<algorithm>
int p[999],d[999],x[999],y[999];
struct ed{
    int s,t,l;
    bool operator<(ed a)const{return l<a.l;}
}s[50000];
int find(int v)
{
    if(v==p[v])return v;
    return p[v]=find(p[v]);
}
void uni(int a,int b)
{
    a=find(a),b=find(b);
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])d[a]++;
}
main()
{
    int i,j,n,m,C=1;
    while(scanf("%d",&n)==1 && n)
    {
        for(i=0;i<n;i++)
            scanf("%d %d",x+i,y+i),p[i]=i,d[i]=0;
        for(i=m=0;i<n;i++)
            for(j=i+1;j<n;j++)
                s[m++]=(ed){i,j,(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])};
        std::sort(s,s+m);
        for(i=0;find(0)!=find(1);i++)
            uni(s[i].s,s[i].t);
        printf("Scenario #%d\nFrog Distance = %.3lf\n\n",C++,n?sqrt(s[i-1].l):0.00);
    }
}
