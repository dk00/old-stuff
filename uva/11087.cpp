#include<cstdio>
#include<algorithm>
int s[100001],t[100001],u[501];
main()
{
    int i,j,k,n,T,C=1;
    long long num;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        for(i=0;i<k;i++)
            u[i]=0;
        for(i=num=0;i<n;i++)
            scanf("%d",&s[i]);
        std::sort(s,s+n);
        s[n]=s[n-1]+1;
        t[0]=s[0];
        for(i=j=1;i<n;)
        {
            if(s[i]==t[j-1])
            {
                if((s[i]*2)%k==0)num++;
                while(s[i]==t[j-1])i++;
            }
            else t[j++]=s[i++];
        }
        for(i=0;i<j;i++)
        {
            t[i]%=k;
            if(t[i]<0)t[i]+=k;
        }
        while(j--)
        {
            num+=u[(k-t[j])%k];
            u[t[j]]++;
        }
        printf("Case %d: %lld\n",C++,num);
    }
}
