#include<cstdio>
#include<algorithm>
const long long Max=1000000000001ll;
int n,pn;
long long s[5000001],pr[200000];
char notp[1000001];
void go(long long x,int i)
{
   // printf("%I64d ",x);
    s[n++]=x;
    if(x<=Max/pr[i])go(x*pr[i],i);
    while(++i<pn && x<=Max/pr[i])go(x*pr[i],i);
}
int find(long long x)
{
    int i,j,k;
    for(i=0,j=n-1;i<=j;)
    {
        k=(i+j)/2;
        if((!k || x>s[k-1])&& x<=s[k])
            return k+(s[k]==x);
        if(x>s[k])i=k+1;
        else j=k-1;
    }
}
main()
{
    long long i,j;
    pr[0]=2;
    for(i=3,pn=1;i<1000000;i++,i++)
    {
        if(notp[i])continue;
        if(i<1000)for(j=i*i;j<1000000;j+=i*2)
            notp[j]=1;
        pr[pn++]=i*i;
    }
    go(1,0);
    std::sort(s,s+n);
    while(scanf("%lld",&i)==1 && i)
        printf("%lld\n",i-find(i));
}
