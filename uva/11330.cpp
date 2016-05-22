#include<cstdio>
int s[10001],t[10001];
main()
{
    int i,j,k,n,sum,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%d %d",&j,&k);
            s[i]=k-1,t[j-1]=i;
        }
        for(j=0;j<n;j++)
            s[j]=t[s[j]];
        for(j=0;j<n;j++)t[j]=0;
        for(i=j=sum=0;i<n;i++)
        {
            if(t[i])continue;
            t[i]=1;
            for(k=s[i];k!=i;k=s[k],sum++)
                t[k]=1;
        }
        printf("%d\n",sum);
    }
}
