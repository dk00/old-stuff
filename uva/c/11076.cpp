#include<cstdio>
long long f[13],t[13],c[14][14];
int n,num[10];
long long go(int k)
{
    int i;
    long long j=f[n-num[k]];
    for(i=0;i<10;i++)
        if(i!=k)
            j/=f[num[i]];
    return j;
}
main()
{
    int i,j;
    long long sum;
    for(i=f[0]=t[0]=1;i<13;i++)f[i]=f[i-1]*i,t[i]=t[i-1]*10;
    for(i=1;i<13;i++)
        for(j=1;j<=i;j++)
            c[i][j]=c[i-1][j-1]+f[i-1]/f[j-1]/f[i-j]*t[i]+c[i-1][j];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<10;i++)
            num[i]=0;
        for(i=0;i<n;i++)
        {
            scanf("%d",&j);
            num[j]++;
        }
        for(i=sum=0;i<10;i++)
            sum+=c[n][num[i]]*i*go(i);;
        printf("%lld\n",sum/10);
    }
}
