#include<cstdio>
long long calc(int);
long long p(int n)
{
    if(n<=1)return 1;
    long long sum=0;
    for(int i=1;i<=n;i++)
        sum+=calc(i)*p(n-i);
    return sum;
}
long long s[100],t[100];
long long calc(int n)
{
    if(s[n]>=0)return s[n];
    s[n]=(3*(2*n-3)*calc(n-1)-(n-3)*calc(n-2))/n;
    return s[n];
}
long long calc1(int n)
{
    if(t[n]>=0)return t[n];
    t[n]=0;
    for(int i=1;i<n;i++)
        t[n]+=calc1(i)*calc1(n-i);
    return t[n];
}
main()
{
    int i;
    for(i=0;i<100;i++)s[i]=t[i]=-1;
    s[0]=s[1]=s[2]=1;
    t[0]=t[1]=1;
    while(scanf("%d",&i)==1 && i)
        printf("%lld\n",calc(i)-calc1(i));
}
