#include<cstdio>
#include<algorithm>
using namespace std;
int inv(long long b,long long a)
{
    b%=a;
    long long c,p,q,r,x0=1,y0=0,x1=0,y1=1;
    while(1){
        p=x0*a+y0*b;
        q=x1*a+y1*b;
        r=p/q;
        if(p==r*q)break;
        x0-=r*x1;
        y0-=r*y1;
        swap(x0,x1);
        swap(y0,y1);
    }
    return (y1%a+a)%a;
}
int crt_merge(long long r0,int p0,long long r1,int p1)
{
    r0%=p0,r1%=p1;
    long long x=inv(p0,p1),r;
    int p=p0*p1;
    x=x*(r1-r0)%p1;
    p=p0*p1;
    r=(r0+x*p0)%p;
    return (r+p)%p;
}
int crt_solve(int n,int r[],int p[])
{
    int i,R=r[0],P=p[0];
    for(i=1;i<n;i++){
        R=crt_merge(R,P,r[i],p[i]);
        P*=p[i];
    }
    return R;
}

main()
{
    int i,n,k,r[99],p[99];
    while(scanf("%d",&n)==1){
        scanf("%d",&k);
        for(i=0;i<n;i++)
            scanf("%d",p+i),r[i]=k%p[i];
        printf("%d\n",crt_solve(n,r,p));
    }
}
