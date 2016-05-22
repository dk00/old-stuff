#include<map>
#include<cstdio>
#include<string>
using namespace std;
int p[1000000],d[1000000];
int find(int v)
{
    if(p[v]==v)return v;
    return p[v]=find(p[v]);
}
int uni(int a,int b)
{
    a=find(a);
    b=find(b);
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])
        d[a]++;
}
struct ed
{
    int s,t;
    double c;
    bool operator<(ed a)const{return c<a.c;}
}s[1000000];
char tmp0[999],tmp1[999];
main()
{
    int i,n,m,T;
    double sum,max;
    scanf("%d",&T);
    while(T--)
    {
        map<string,int> v;
        scanf("%lf",&max);
        scanf("%d",&n);
        for(i=0;i<n;i++)
            p[i]=i,d[i]=0;
        for(i=0;i<n;i++)
        {
            scanf("%s",tmp0);
            v[tmp0]=i;
        }
        scanf("%d",&m);
        for(i=0;i<m;i++)
        {
            scanf("%s %s %lf",tmp0,tmp1,&s[i].c);
            s[i].s=v[tmp0];
            s[i].t=v[tmp1];
        }
        sort(s,s+m);
        for(sum=i=0;i<m;i++)
        {
            if(find(s[i].s)==find(s[i].t))
                continue;
            sum+=s[i].c;
            uni(s[i].s,s[i].t);
        }
        if(sum<max)
            printf("Need %.1lf miles of cable\n",sum);
        else
            puts("Not enough cable");
    }
}
