#include<cstdio>
#include<algorithm>
int n,sum,max1,max2,s[15],num[32768];
int go(int ns,int u)
{
    max2>?=ns;
    if(max2>=max1)return max2;
    if(num[u]>=0)
        return num[u];
    num[u]=ns;
    int i,j,k,n1,v[15];
    for(i=n1=0;i<n;i++)
        if(!(u&(1<<i)))
            v[n1++]=i;
    i=v[n1-1],j=v[0],k=v[1];
    if(s[i]+s[j]+s[k]>=20)
    {
        num[u]=go(ns+1,u|(1<<i)|(1<<j)|(1<<k));
        return num[u];
    }
    for(i=n1-1;i>1;i--)
    {
        for(j=i-1;j>0 && s[v[i]]+s[v[j]]>=20;j--);
        if(j+1<i)j++;
        for(;j>0;j--)
        {
            for(k=0;k<j && s[v[i]]+s[v[j]]+s[v[k]]<20;k++);
            if(k<j)
                num[u]>?=go(ns+1,u|(1<<v[i])|(1<<v[j])|(1<<v[k]));
        }
    }
    return num[u];
}
main()
{
    int i,C=1;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        std::sort(s,s+n);
        for(i=sum=0;i<n-n%3;i++)
        {
            s[i]=s[i+n%3];
            sum+=s[i];
        }
        n-=n%3,max1=sum/20,max1<?=(n/3),max2=0;
        for(i=(1<<n)-1;i>=0;i--)num[i]=-1;
        printf("Case %d: %d\n",C++,go(0,0));
    }
}
