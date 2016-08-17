#include<cstdio>
const int D=1000000007;
int pow(long long n,int k)
{
    if(!k)return 1;
    if(k%2)
        return n*pow(n,k-1)%D;
    n=pow(n,k/2);
    return n*n%D;
}
char notp[40001];
int pn,pr[10000],v[40001],c[40001],d[40001],p[40001],q[40001];
main()
{
    int i,j,n,m,T;
    long long k;
    pr[0]=2;
    for(i=3,pn=1;i<=40000;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<=40000;j+=i*2)
            notp[j]=1;
        pr[pn++]=i;
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<=n;i++)v[i]=1,d[i]=0,p[i]=0;
        for(i=0;i<pn;i++)c[i]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            p[i]=j,d[j]++;
        }
        for(i=1,j=0;i<=n;i++)
            if(d[i]==0)
                q[j++]=i;
        for(i=0;i<j;i++)
        {
            v[p[q[i]]]+=v[q[i]];
            if(!--d[p[q[i]]])
                q[j++]=p[q[i]];
        }
        for(i=1;i<=n;i++)
            for(j=0;v[i]>1 && j<pn;j++)
                while(v[i]%pr[j]==0)
                {
                    c[j]--;
                    v[i]/=pr[j];
                }
        for(j=0;pr[j]<=n && j<pn;j++)
            for(i=n/pr[j];i>0;i/=pr[j])
                c[j]+=i;
        for(i=0,k=1;i<pn;i++)
            (k*=pow(pr[i],c[i]))%=D;
        printf("%lld\n",k);
    }
}
