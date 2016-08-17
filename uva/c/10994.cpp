#include<cstdio>
main()
{
    long long i,j,n,m,num[]={0,1,3,6,10,15,21,28,36,45};
    while(scanf("%lld %lld",&n,&m) && n>=0 && m>=0)
    {
        if(n>0)n--;
        for(i=10,j=0;i>0 && i<12147483647ll;i*=10)
            j+=45*(m/i)+num[m%i/(i/10)]-45*(n/i)-num[n%i/(i/10)];
        printf("%lld\n",j);
    }
}
