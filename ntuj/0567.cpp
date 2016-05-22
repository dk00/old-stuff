#include<cstdio>
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
    static int n,p[N];
    int r[N];
public:
    static void init(int);
    /*num(){}
    num(int a)
    {
        for(int i=0;i<n;i++)
            r[i]=a%p[i];
    }
    num& operator*=(num a)
    {
        for(int i=0;i<n;i++)
            (r[i]*=a.r[i])%=p[i];
        return *this;
    }
    num operator~()
    {
        num ret=*this;
        for(int i=0;i<n;i++)
            ret.r[i]=inv(ret.r[i],p[i]);
        return ret;
    }*/
};
void num::init(int m)
{
    int i;
    for(n=0,i=2;i*i<=m;i++){
        if(m%i)continue;
        m/=p[n]=i;
        while(m>1)m/=i,p[n]*=i;
        n++;
    }
}
main()
{
    int n,m;
    while(scanf("%d %d",&n,&m)==2){
        num::init(m);

    }
}


