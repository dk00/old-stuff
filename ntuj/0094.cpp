#include<cstdio>
int s[500001],t[500001],p[500001],len[500001];
main()
{
    int i,j,n;
    long long sum;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        for(sum=i=j=0;i<n;i++)
        {
            while(j && s[i]>=s[t[j-1]])
                p[t[--j]]=i;
            t[j++]=i;
        }
        while(j)
            p[t[--j]]=i;
        len[n]=0;
        for(i=n-1;i>=0;i--)
            len[i]=len[p[i]]+1;
        len[n]=1;
        for(sum=i=j=0;i<n;i++)
        {
            while(j && s[i]>s[t[j-1]])
                p[t[--j]]=i;
            t[j++]=i;
        }
        while(j)
            p[t[--j]]=i;
        for(i=0;i+1<n;i++)
            sum+=len[i+1]-len[p[i]]+1;
        printf("%lld\n",sum);
    }
}
