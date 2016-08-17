#include<cstdio>
long long n;
int m,s[1000];
inline long long gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
long long go(long long num,int i,int r)
{
    long long sum=0,tmp;
    if(!num)
    {
        for(i=0;i<m;i++)
            sum+=go(s[i],i+1,-r);
        return sum;
    }
    sum=r*n/num;
    for(;i<m;i++)
    {
        tmp=num*s[i]/gcd(num,s[i]);
        if(tmp>n)
            continue;
        sum+=go(tmp,i+1,-r);
    }
    return sum;
}
main()
{
    int i,j;
    while(scanf("%lld %d",&n,&m)!=EOF){
        for(i=0;i<m;i++)
            scanf("%d",&s[i]);
        printf("%lld\n",n-go(0,0,-1));
    }
}
