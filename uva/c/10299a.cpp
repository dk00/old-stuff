#include<cstdio>
bool notp[31628];
int p[3401];
main()
{
    int i,j,n;
    p[0]=2;
    for(n=1,i=3;i<=31627;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<31627;j+=i*2)
            notp[j]=1;
        p[n++]=i;
    }
    while(scanf("%d",&n) && n)
    {
        for(i=0,j=n;p[i]*p[i]<=n && p[i]<=31267;i++)
        {
            if(n%p[i]==0)
                j=j/p[i]*(p[i]-1);
            while(n%p[i]==0)n/=p[i];
        }
        if(n>1 && j!=n)j=j/n*(n-1);
        if(j==n)j--;
        printf("%d\n",j);
    }
}
