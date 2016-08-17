#include<set>
#include<string>
#include<cstdio>
using namespace std;
long long gcd(long long a,long long b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
struct Q
{
    long long a,b,u;
    void operator()(){int d=gcd(a,b);a/=d,b/=d;}
    Q operator*(Q x)
    {
        Q z=*this;u=1;
        int d=gcd(z.a,x.b);
        z.a/=d,x.b/=d;
        d=gcd(z.b,x.a);
        z.b/=d,x.a/=d;z.u=1,z();
        z.a*=x.a,z.b*=x.b;
        return z;
    }
}c[100][100];
struct name
{
    char s[25];
    int u;
    bool operator<(name o)const
    {
        for(int i=0;s[i] && o.s[i];i++)
            if(s[i]!=o.s[i])return s[i]<o.s[i];
        return 0;
    }
};
int n;
main()
{
    int i,j,k;
    char tmp[10];
    name a,b;
    set<name> S;
    Q l;
    S.clear();
    while(scanf("%s",tmp) && tmp[0]!='.')
    {
        if(tmp[0]=='!')
        {
            scanf("%d %s = %d %s",&i,a.s,&j,b.s);
            if(S.count(a)==0)a.u=n++,S.insert(a);
            else a.u=S.find(a)->u;
            if(S.count(b)==0)b.u=n++,S.insert(b);
            else b.u=S.find(b)->u;
            c[a.u][b.u]=(Q){i,j,1};c[b.u][a.u]=(Q){j,i,1};
            c[a.u][b.u](),c[b.u][a.u]();
            c[a.u][a.u]=c[b.u][b.u]=(Q){1,1,1};
            c[a.u][a.u](),c[b.u][b.u]();
        }
        if(tmp[0]=='?')
        {
            for(k=0;k<n;k++)
                for(i=0;i<n;i++)
                    for(j=0;j<n;j++)
                        if(c[i][k].u && c[k][j].u)
                            c[i][j]=c[i][k]*c[k][j];
            scanf("%s = %s",a.s,b.s);
            a.u=S.find(a)->u;
            b.u=S.find(b)->u;
            if((l=c[a.u][b.u]).u)
                printf("%lld %s = %lld %s\n",l.a,a.s,l.b,b.s);
            else
                printf("? %s = ? %s\n",a.s,b.s);
        }
    }
}
