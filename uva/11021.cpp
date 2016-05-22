#include<cmath>
#include<cstdio>
int n;
double p[1001];
double go(int k,int m)
{
    if(k==0)return 1.0;
    if(m==0)return 0.0;
    if(k>1)
        return pow(go(1,m),(double)k);
    if(m==1) return p[0];
    double x,p0,s=0;
    x=1,p0=go(1,m-1);
    for(int i=0;i<n;i++,x*=p0)
        s+=x*p[i];
    return s;
}
main()
{
    int i,j,k,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&k,&m);
        for(i=0;i<n;i++)
            scanf("%lf",&p[i]);
        printf("Case #%d: %.7lf\n",C++,go(k,m));
    }
}
