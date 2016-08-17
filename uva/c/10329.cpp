#include"d:\\a\\tools\\bigint2.h"
#include<cmath>
#include<cstring>
int pn,pr[700],num[700];
char notp[5001];
void factor(int x,char r)
{
    int i,j;
    for(i=0;i<pn && pr[i]<=x;i++)
        for(num[i]+=r*(j=x/pr[i]);j;num[i]+=r*(j/=pr[i]));
}
bigint pow(bigint n,int k)
{
    if(k==0)return 1;
    if(k%2)return n*=pow(n,k-1);
    n=pow(n,k/2);
    return n*=n;
}
bigint res;
main()
{
    int i,j,n,m;
    double sum;
    pn=1,pr[0]=2;
    for(i=3;i<5000;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<5000;j+=i*2)
            notp[j]=1;
        pr[pn++]=i;
    }
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<pn;i++)num[i]=0;
        while(n--)
        {
            scanf("%d %d",&i,&j);
            factor(i,1);
            factor(i-j,-1);
            factor(j,-1);
        }
        while(m--)
        {
            scanf("%d %d",&i,&j);
            factor(i,-1);
            factor(i-j,1);
            factor(j,1);
        }
        for(sum=i=0;i<pn;i++)
        {
            if(num[i]<0)
            {
                puts("0");
                goto exit;
            }
            sum+=num[i]*log10(pr[i]);
        }
        if(sum>101)
        {
            puts("-1");
            goto exit;
        }
        for(res=1,i=0;i<pn;i++)
            res*=pow((bigint)pr[i],num[i]);
        if(strlen(res.tostr())>100)
        {
            puts("-1");
            goto exit;
        }
        puts(res.tostr());
    exit:;
    }
}
