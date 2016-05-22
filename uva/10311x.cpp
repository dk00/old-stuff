#include<stdio.h>
const int max=10010;
bool notp[max+2];
int p,prime[13000];
bool inline isp(int n)
{
    if(n<10000)
        return !notp[n];
    for(int i=0;prime[i]<n/prime[i] && i<p;i++)
        if(n%prime[i]==0)
            return false;
    return true;
}
main()
{
    int i,j,k,n;
    prime[0]=2;
    notp[1]=true;
    for(i=3;i<max;i++,i++)
    {
        if(!notp[i])
            for(prime[p++]=i,j=3*i;j<max;j+=i*2)
                notp[j]=true;
    }
    while(scanf("%d",&n)!=EOF)
    {
        if(n<5)
        {
            printf("%d is not the sum of two primes!\n",n);
            continue;
        }
        if(n%2)
        {
            if(isp(n-2))
                printf("%d is the sum of 2 and %d.\n",n,n-2);
            else
                printf("%d is not the sum of two primes!\n",n);
            continue;
        }
        n/=2;
        k=n;
        while((!isp(n*2-k) || k==n) && k>=3)
            for(k--;!isp(k) && k>=3;k--);
        if(k>=3)
            printf("%d is the sum of %d and %d.\n",n*2,k,n*2-k);
        else
            printf("%d is not the sum of two primes!\n",n*2);
    }
}
