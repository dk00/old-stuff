#include<cstdio>
int m;
int pow(int n,int k)
{
    if(k==0)return 1;
    if(k%2)return 1ll*n*pow(n,k-1)%m;
    n=pow(n,k/2);
    return 1ll*n*n%m;
}
int C(int n,int k)
{
    if(k>n-k)k=n-k;
    int x=1;
    for(i=0;i<k;i++)
}
int calc(int n,int k,int p)
{
    if(k==0)return 1%m;
    if(k==1)return n%m;
    if(n-p*(k-1)>=k)return 0;
    return C(n-p*(k-1),k);
}
main()
{
    while(scanf("%d %d %d %d",&k,&p,&n,m)==4 && k+p+n+m)
    {
        for(i=sum=0;(p+1)*(i-1)+1<=n;i++)
            sum=(1ll*pow(k,n)*calc(n,i,p)%m+sum)%m;
        printf("%d\n",sum);
    }
}
