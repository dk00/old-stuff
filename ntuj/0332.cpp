#include<cstdio>
const int N=1000000;
char notp[N+1];
int n,m,pn,p[79000],f[9];
long long go(int d,int m)
{
    if(!d)return m;
    return go(d-1,-m/f[d-1])+go(d-1,m);
}
long long go(long long x,int d,int i)
{
    long long sum=go(d,m);
    if(x>1 && x*p[i]<=n)
        sum+=go(x*p[i],d,i),i++;
    for(;x*p[i]<=n && i<pn;i++)
    {
        f[d]=p[i];
        sum+=go(x*p[i],d+1,i);
    }
    return sum;
}
main()
{
    int i,j;
    p[0]=2,pn=1;
    for(i=3;i<N;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*2;j<=N;j+=i)
            notp[j]=1;
        p[pn++]=i;
    }
    while(scanf("%d %d",&n,&m)==2)
    {
        if(n>m)
            m+=n,n=m-n,m-=n;
        printf("%lld\n",go(1,0,0));
    }
}
