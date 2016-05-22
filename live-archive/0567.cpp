#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int inv(long long r,long long m)
{
    r%=m;
    long long a,b,q,x0=1,y0=0,x1=0,y1=1;
    while(1){
        a=x0*r+y0*m;
        b=x1*r+y1*m;
        q=a/b;
        if(a==b*q)break;
        x0-=q*x1;
        y0-=q*y1;
        swap(x0,x1);
        swap(y0,y1);
    }
    return (x1%a+a)%a;
}
class num{
    const static int N=30;
    static int n,m,p[N];
    int r,c[N];
public:
    static void init(int);
    num(){}
    num(int a)
    {
        for(int i=0;i<n;i++)
            for(c[i]=0;a%p[i]==0;a/=p[i],c[i]++);
        r=a%m;
    }
    num& operator*=(num a)
    {
        r=1ll*r*a.r%m;
        for(int i=0;i<n;i++)
            c[i]+=a.c[i];
        return *this;
    }
    num& operator/=(num a)
    {
        r=1ll*r*inv(a.r,m)%m;
        for(int i=0;i<n;i++)
            c[i]-=a.c[i];
        return *this;
    }
};
int num::n,num::m,num::p[N];
void num::init(int M)
{
    m=M;
    int i;
    for(n=0,i=2;i*i<=m;i++){
        if(m%i)continue;
        p[n++]=i;
        while(m>1)m/=i;
    }
}
const int N=300001;
int s[N],c[N];
main()
{
    int i,n,m;
    while(scanf("%d %d",&n,&m)==2){
        num::init(m);
        memset(c,0,sizeof(c));
        num a=1;
        for(i=2;i<=n;i++){
            a*=i;
            scanf("%d",s+i);
            a/=++c[s[i]];
        }
        sort(s,s+n);
    }
}
