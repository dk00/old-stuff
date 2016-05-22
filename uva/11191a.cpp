#include<cstdio>
int pr[]={2,3,5,7,11,13,17,19,23,29};
int conv(long long x)
{
    int i,res=0;
    for(i=0;i<10;i++)
        while(x%pr[i]==0)
            x/=pr[i],res^=(1<<i);
    if(x<0)res^=(1<<i);
    return res;
}
long long s[2048];
main()
{
    int i,j,n,T;
    long long a,b,zero;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<2048;i++)s[i]=0;
        scanf("%d",&n);
        for(i=zero=0;i<n;i++)
        {
            scanf("%lld",&a);
            if(a)s[conv(a)]++;
            else zero++;
        }
        a=zero*(n-zero)+zero*(zero-1)/2;
        b=zero*(n-zero)*(n-zero-1)/2
        +zero*(zero-1)*(n-zero)/2
        +zero*(zero-1)*(zero-2)/6;
        for(i=0;i<2048;i++)
        {
            a+=s[i]*(s[i]-1)/2;
            if(i)b+=s[0]*s[i]*(s[i]-1)/2;
            else b+=s[0]*(s[0]-1)*(s[0]-2)/6;
            for(j=i+1;j<2048;j++)
                if(j<(i^j))
                    b+=s[i]*s[j]*s[i^j];
        }
        printf("%lld %lld\n",a,b);
    }
}
