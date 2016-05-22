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
int n;
char u[128];
void go(set<q> s[128],int v)
{
    if(u[v])return;
    u[v]=1;
    int i;
    set<q>::iterator j,k;
    for(i=1;i<(1<<n);i++)
        if((v&i)==i &&(v^i))
        {
            go(s,i),go(s,v^i);
            for(j=s[i^v].begin();j!=s[i^v].end();j++)
                for(k=s[i].begin();k!=s[i].end();k++)
                {
                    s[v].insert((*j)+(*k));
                    s[v].insert((*j)-(*k));
                    s[v].insert((*j)*(*k));
                    if(k->a)s[v].insert((*j)/(*k));
                }
        }
}
main()
{
    int i,C=1,num[7];
    set<q> s[128];
    set<q>::iterator p;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",num+i);
        for(i=0;i<(1<<n);i++)
            u[i]=0,s[i].clear();
        for(i=0;i<n;i++)
            u[1<<i]=1,s[1<<i].insert((q){num[i],1});
        go(s,(1<<n)-1);
        printf("Case %d: %d\n",C++,s[(1<<n)-1].size());
    }
}
