#include<cstdio>
int m,pn,pr[200000];
char notp[1000001];
inline long long pow(long long n,int k)
{
    if(k==0)return 1;
    if(k%2)return n*pow(n,k-1)%m;
    n=pow(n,k/2);
    return 1ll*n*n%m;
}
main()
{
    int i,j,k,n,res;
    pn=1,pr[0]=2;
    for(i=3;i<=1000000;i++,i++)
    {
        if(notp[i])continue;
        if(i<=1000)for(j=i*i;j<=1000000;j+=i*2)
            notp[j]=1;
        pr[pn++]=i;
    }
    while(scanf("%d %d",&n,&m)==2 && n+m)
    {
        if(n>=m)
        {
            puts("0");
            continue;
        }
        for(i=0,res=1;res && i<pn && pr[i]<=n;i++)
        {
            for(j=k=n/pr[i];k>1;j+=(k/=pr[i]));
            res=(res*pow(pr[i],j))%m;
        }
        printf("%d\n",res);
    }
}
