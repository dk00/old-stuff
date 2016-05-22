#include<set>
#include<cstdio>
using namespace std;
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
struct q
{
    int a,b;
    bool operator()()const
    {return a!=0;}
    bool operator<(q x)const
    {
        return (*this-x).a<0;
    }
    q operator+(q x)const
    {
        int d=gcd(b,x.b);
        q tmp;
        tmp.a=a*x.b/d+x.a*b/d;
        tmp.b=b*x.b/d;
        d=gcd(tmp.a,tmp.b);
        tmp.a/=d,tmp.b/=d;
        if(tmp.b<0)tmp.b*=-1,tmp.a*=-1;
        return tmp;
    }
    q operator-(q x)const
    {
        int d=gcd(b,x.b);
        q tmp;
        tmp.a=a*x.b/d-x.a*b/d;
        tmp.b=b*x.b/d;
        d=gcd(tmp.a,tmp.b);
        tmp.a/=d,tmp.b/=d;
        if(tmp.b<0)tmp.b*=-1,tmp.a*=-1;
        return tmp;
    }
    q operator*(q x)const
    {
        q tmp;
        tmp.a=a*x.a;
        tmp.b=b*x.b;
        int d=gcd(tmp.a,tmp.b);
        tmp.a/=d,tmp.b/=d;
        if(tmp.b<0)tmp.b*=-1,tmp.a*=-1;
        return tmp;
    }
    q operator/(q x)const
    {
        q tmp;
        tmp.a=a*x.b;
        tmp.b=b*x.a;
        int d=gcd(tmp.a,tmp.b);
        tmp.a/=d,tmp.b/=d;
        if(tmp.b<0)tmp.b*=-1,tmp.a*=-1;
        return tmp;
    }
};
char u[7][7],p[7];
int n,num[7],h[7];

int go(set<q> s[7][7],int st,int ed)
{
    if(u[st][ed])return s[st][ed].size();
    u[st][ed]=1;
    if(st==ed)
    {
        s[st][ed].insert((q){num[st],1});
        return 1;
    }
    set<q>::iterator a,b;
    int i;
    for(i=st;i<ed;i++)
    {
        go(s,st,i);
        go(s,i+1,ed);
        a=s[st][i].begin();
        for(;a!=s[st][i].end();a++)
            for(b=s[i+1][ed].begin();b!=s[i+1][ed].end();b++)
            {
                s[st][ed].insert((*a)+(*b));
                s[st][ed].insert((*a)-(*b));
                s[st][ed].insert((*a)*(*b));
                if(b->a!=0)s[st][ed].insert((*a)/(*b));
            }
    }
    return s[st][ed].size();
}
void start(set<q> &all,set<q> s[7][7])
{
    int i,j;

    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
            u[i][j]=0,s[i][j].clear();
    go(s,0,n-1);
    //printf("%d\n",s[0][n-1].size());
    set<q>::iterator a;
    a=s[0][n-1].begin();
    for(;a!=s[0][n-1].end();a++)
        all.insert(*a);
}
void go(set<q> &all,set<q> s[7][7],int v)
{
    if(v>=n)
    {
        start(all,s);
        return;
    }
    for(int i=0;i<n;i++)
        if(p[i]==0)
        {
            p[i]++;
            num[v]=h[i];
            go(all,s,v+1);
            p[i]--;
        }
}
main()
{
    set<q> s[7][7],all;
    int i,j;
    q a,b;
    a=(q){1,2};
    b=(q){2,1};
   // printf("%d %d\n",(a-b).a,(a-b).b);
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",h+i);
        all.clear();
        go(all,s,0);
        printf("%d\n",all.size());
        set<q>::iterator a=all.begin();
        //for(;a!=all.end();a++)
        //    printf("%d/%d\n",a->a,a->b);
    }
}
