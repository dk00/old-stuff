#include<cstdio>
struct pt
{
    double x,y;
    pt operator-(pt a){return(pt){x-a.x,y-a.y};}
    double operator*(pt a){return x*a.y-a.x*y;}
    bool on(pt a,pt b)
    {
        return((a.x<?b.x)<=x && x<=(a.x>?b.x)
        &&(a.y<?b.y)<=y && y<=(a.y>?b.y));
    }
};
struct stick
{
    int u;
    double x1,y1,x2,y2;
    char ins(stick a)
    {
        pt p1=(pt){x1,y1},p2=(pt){x2,y2},
        p3=(pt){a.x1,a.y1},p4=(pt){a.x2,a.y2};
        double d1=(p3-p1)*(p4-p1),d2=(p3-p2)*(p4-p2),
            d3=(p1-p3)*(p2-p3),d4=(p1-p4)*(p2-p4);
        if(d1*d2<0 && d3*d4<0)return 1;
        if(d1==0 && p1.on(p3,p4))return 1;
        if(d2==0 && p2.on(p3,p4))return 1;
        if(d3==0 && p3.on(p1,p2))return 1;
        if(d4==0 && p4.on(p1,p2))return 1;
        return 0;
    }
}s[10001],p;
char u[10000];
main()
{
    int i,j,t,n,m;
    while(scanf("%d",&n) && n)
    {
        for(t=1,m=0;t<=n;t++)
        {
            scanf("%lf %lf %lf %lf",&p.x1,&p.y1,&p.x2,&p.y2);
            p.u=t;
            for(i=0;i<m;i++)
                if(p.ins(s[i]))u[i]=0;
                else u[i]=1;
            for(i=j=0;i<m;i++)
                if(u[i])s[j++]=s[i];
            s[(m=j)++]=p;
        }
        printf("Top sticks:");
        for(i=0;i<m-1;i++)
            printf(" %d,",s[i].u);
        printf(" %d.\n",s[i].u);
    }
}
