#include<cstdio>
#include<algorithm>
bool notp[5000000];
int p[350000];
struct Pair
{
    int a;
    long long b;
    bool operator<(Pair x)const{return a<x.a;}
}s[750000];
main()
{
    int i,j,n,m;
    long long k;
    p[0]=2;
    for(m=1,i=3;i<5000000;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;i<2500 && j<5000000;j+=i*2)notp[j]=1;
        p[m++]=i;
    }
    for(n=0,i=1;i<m;i++)
        for(j=p[i]*2,k=3-p[i];j<=10000000;j*=2)
        {
            s[n++]=(Pair){j,k};
            k+=j/p[i]*(p[i]+1)*2-j*2;
        }
    std::sort(s,s+n);
    for(i=1;i<n;i++)
        s[i].b+=s[i-1].b;
    while(scanf("%d",&i) && i)
    {
        for(j=0,k=n-1;j<=k;)
        {
            m=(j+k)/2;
            if(s[m].a<=i &&(m==n-1 || i<s[m+1].a))break;
            if(s[m].a<=i)j=m+1;
            else k=m-1;
        }
        printf("%d %lld\n",i,s[m].b);
    }
}
