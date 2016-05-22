#include<set>
#include<cstdio>
char notp[31625];
int sum(int i)
{
    if(i)return i%10+sum(i/10);
    return 0;
}
int pn,p[3662],x[3662];
int go(int n,int i)
{
    if(n==1)return 0;
    while(i<pn && n%p[i])i++;
    if(i<pn)return x[i]+go(n/p[i],i);
    return sum(n);
}
char isp(int n)
{
    for(int i=0;i<pn && p[i]*p[i]<=n;i++)
        if(n%p[i]==0)return 0;
    return 1;
}
main()
{
    int i,j,n;
    p[0]=2,x[0]=2,pn=1;
    for(i=3;i<31622;i++,i++)
    {
        notp[i+1]=1;
        if(notp[i])continue;
        for(j=i*i;j<31622;j+=i*2)
            notp[j]=1;
        x[pn]=sum(i);
        p[pn++]=i;
    }
    while(scanf("%d",&n) && n)
    {
        while(isp(++n) || go(n,0)!=sum(n));
        printf("%d\n",n);
    }
}
