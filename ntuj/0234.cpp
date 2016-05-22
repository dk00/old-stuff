#include<cstdio>
struct pp
{
    int p,n,m;
}s[100008];
main()
{
    int i,j,k,n,m,num,T;
    long long sum;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        m=sum=0;
        while(n--)
        {
            scanf("%d %d %d",&k,&i,&j);
            while(m && num && i<s[m-1].p)
            {
                --m;
                sum+=s[m].p*(num<?s[m].n<?s[m].m);
                num-=(num<?s[m].n<?s[m].m);
            }
            num+=k;
            s[m++]=(pp){j,i,num};
        }
        while(num && m--)
        {
            sum+=s[m].p*(num<?s[m].n);
            num-=(num<?s[m].n);
        }
        printf("%lld\n",sum);
    }
}
