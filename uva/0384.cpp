#include<cstdio>
#include<algorithm>
using namespace std;
struct pt
{
    double x,y;
    double operator*(pt a)const{return x*a.y-y*a.x;}
};
int a(int n,pt s[])
{
    for(i=sum=0;i<n;i++)
        sum+=s[i]*s[i+1];
    if(sum<0)return -sum;
    return sum;
}
int go(int i,pt a)
{
    pt s[]={{u[i],uy},{l[i],ly},{l[i+1],ly},{u[i+1],u[y]},{u[i],uy}},t[4];
    int sum=a(s,4);
    t[0]=t[4]=a;
    for(i=0;i<4;i++)
    {
        t[1]=s[i],t[2]=s[i+1];
        sum-=a(s,3);
    }
    return sum>=0;
}
main()
{
    pt p;
    while(scanf("%d %d %d %d %d %d",&n,&m,u,&uy,u+n+1,&ly)==6)
    {
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
                    num[i]++;
        }
        for(i=0;i<=n;i++)
            printf("%d:%d\n",i,s[i]);
        puts("");
    }
}
