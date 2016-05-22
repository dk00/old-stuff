#include<cmath>
#include<cstdio>
struct pt
{
    double x,y;
    double operator^(pt a){return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);}
}s[20];
int n,u[20];
double min,now;
double go(int i)
{
    if(now>=min)return min;
    if(i>=n)return(min<?=now);
    if(u[i])return go(i+1);
    double tmp;
    for(int j=i+1;j<n;j++)
        if(!u[j])
        {
            u[j]++;
            tmp=now;
            now+=sqrt(s[i]^s[j]);
            go(i+1);
            now=tmp;
            u[j]--;
        }
    return min;
}
main()
{
    int i,C=1;
    char tmp[1000];
    while(scanf("%d",&n) && (n*=2))
    {
        for(i=0;i<n;i++)
            scanf("%s %lf %lf",tmp,&s[i].x,&s[i].y);
        now=0,min=1e20;
        printf("Case %d: %.2lf\n",C++,go(0));
    }
}
