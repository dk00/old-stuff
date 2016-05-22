#include<cstdio>
long long max,s[50],c[100][100],path[50];
long long C(long long n,long long  k)
{
    if(n<1)return 0;
    if(k>3)max>?=n;
    if(k==1)return n;
    if(k==2)
    {
        if(n%2)return (n+1)/2*n;
        return n/2*(n+1);
    }
    if(k==3)
    {
        int i;
        long long s[]={n+2,n+1,n};
        for(i=0;s[i]%2;i++);s[i]/=2;
        for(i=0;s[i]%3;i++);s[i]/=3;
        return s[0]*s[1]*s[2];
    }
    if(c[n][k])return c[n][k];
    c[n][k]=C(n-1,k)+C(n,k-1);
    return c[n][k];
}
long long go(int n,int i,int d=0)
{
    long long sum;
    if(n<=0)
    {
        int num=1,last=path[0];
        for(i=sum=1;i<d;i++)
        {
            if(path[i]==last)num++;
            else
            {
                sum*=C(s[last],num);
                last=path[i],num=1;
            }
        }
        sum*=C(s[last],num);
        return sum;
    }
    for(sum=0;i>0;i--)
    {
        path[d]=i;
        sum+=go(n-i,i<?(n-i),d+1);
    }
    return sum;
}
main()
{
    int i,j;
    s[0]=s[1]=1;
    for(i=2;i<=30;i++)
        s[i]=go(i,i-1);
    while(scanf("%d",&i) && i)
    {
        if(i==1)puts("1");
        else printf("%lld\n",s[i]*2);
    }
}
