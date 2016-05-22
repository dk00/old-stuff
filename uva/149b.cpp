#include<cmath>
#include<cstdio>
const double pi=acos(-1),min=pi/18000+1e-6;
struct pt
{
    double x,y;
};
struct Q
{
    int k;
    double a,b;
}q[10000];
double dis(pt a,pt b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double r;
int calc(double x,double y)
{
    int i,j,k;
    double d,an1,an2;
    pt p1,p2;
    d=dis((pt){x,y},(pt){1,0});
    an1=pi-asin((1-x)/d)+asin(r/d);
    d=dis((pt){x,y},(pt){1,1});
    an2=asin((1-x)/d)+asin(r/d);
    q[0]=(Q){2,an1,an2};
    for(i=0,j=1;i<j;i++)
    {
        k=q[i].k,an1=q[i].a,an2=q[i].b;
        if(an2-an1<min)
            continue;
        p1=(pt){k,(k-x)/tan(an1)};
        p2=(pt){k,(k-x)/tan(an2)};
    }
}
main()
{
    int sum;
    double x,y;
    while(scanf("%lf %lf %lf",&x,&y,&r)==3)
    {
        if(x<1e-8 && y<1e-8 && r<1e-8)
            break;
        sum=4;
        sum+=calc(x,y);
        sum+=calc(1-x,y);
        sum+=calc(x,1-y);
        sum+=calc(1-x,1-y);
    }
}
