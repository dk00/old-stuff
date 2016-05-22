#include<cstdio>
#include<algorithm>
using namespace std;
const int N=201;
struct pt{
    int x,y;
    pt operator-(pt a)const{
        return (pt){x-a.x,y-a.y};
    }
    bool operator!=(pt a)const{return x!=a.x || y!=a.y;}
    bool operator<(pt a)const{
        if(x!=a.x)return x<a.x;
        return y<a.y;
    }
}s[N],t[N*N];
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
pt make(pt a,pt b)
{
    pt c=a-b;
    if(c.x<0)c.x*=-1,c.y*=-1;
    if(!c.x)return (pt){0,1};
    if(!c.y)return (pt){1,0};
    int d=gcd(c.x,c.y);
    c.x/=d,c.y/=d;
    return c;
}
main()
{
    int i,j,n,m;
    while(scanf("%d",&n)>0 && n)
    {
        for(i=m=0;i<n;i++)
        {
            scanf("%d %d",&s[i].x,&s[i].y);
            for(j=0;j<i;j++)
                if(s[i]!=s[j])
                    t[m++]=make(s[j],s[i]);
        }
        sort(t,t+m);
        for(i=j=0;i<m;i++)
            if(!i || t[i]!=t[i-1])j++;
        printf("%d\n",j);
    }
}
