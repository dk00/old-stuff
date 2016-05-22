#include<cstdio>
main()
{
    int k,T;
    long long i,j,n,m;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld %d",&n,&k);
        n--;
        for(i=j=1;i*(k-1)<=n;i*=(k-1),j*=k);
        for(m=1;n>0;i/=(k-1),j/=k)
            if(n>=i)m+=j*(n/i),n%=i;
        printf("%lld\n",m);
    }
}
