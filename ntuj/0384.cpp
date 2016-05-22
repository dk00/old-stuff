#include<cstdio>
#include<algorithm>
using namespace std;
struct pt
{
    int x,y;
    int operator*(pt a)const{return x*a.y-y*a.x;}
}s[9999];
int uy,ly,u[9999],l[9999],num[9999];
int a(int n,pt s[])
{
    int i,sum;
    for(i=sum=0;i<n;i++)
        sum+=s[i]*s[i+1];
    if(sum<0)return -sum;
    return sum;
}
int go(int i,pt p)
{
    pt s[]={{u[i],uy},{l[i],ly},{l[i+1],ly},{u[i+1],uy},{u[i],uy}},t[4];
    int sum=a(4,s);
    t[0]=t[4]=p;
    for(i=0;i<4;i++)
    {
        t[1]=s[i],t[2]=s[i+1];
        sum-=a(3,t);
    }
    return sum>=0;
}
main()
{
    pt p;
    int i,j,n,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        scanf("%d %d %d %d",u,&uy,u+n+1,&ly);
        num[0]=0,l[0]=u[0],l[n+1]=u[n+1];
        for(i=1;i<=n;i++)
            num[i]=0,scanf("%d %d",u+i,l+i);
        sort(u,u+n);
        sort(l,l+n);
        while(m--)
        {
            scanf("%d %d",&p.x,&p.y);
            for(i=0;i<=n;i++)
                if(go(i,p))
                {
                    num[i]++;
                    break;
                }
        }
        for(i=0;i<=n;i++)
            printf("%d:%d\n",i,num[i]);
        puts("");
    }
}
