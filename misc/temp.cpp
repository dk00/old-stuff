#include<stdio.h>
main()
{
    while(1)
    {
        scanf("%d %d",&n,&w);
        if(n==0 && w==0)
            break;
        for(i=1;i<=50;i++)
            s[i]=0;
        min=0,max=inf;
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",&k);
            sum+=k;
            if(min>k)
                min=k;
            if(max<k)
                max=k;
            s[k]++;
        }
        p=(sum+w-1)/w;
        q=inf;
        for(find=0;find==0;p=q,q=inf)
            calc(0);
        printf("%d\n",find);
    }
}
void calc(int a)
{
    int i,b=(sum+w-1)/w;
    if(a+b>p)
    {
        if(a+b<q)
            q=a+b;
        return;
    }
    if(sum==0)
    {
        find=a;
        return;
    }
    for(i=max;s[i]<0;i--);
    s[i]--;
    sum-=i;
    if(s[i]==w)
        calc(a+1);
    else
        dfs(a,w-i,i);
    sum+=i;
    s[i]++;
}
void dfs(int a,int n,int i)
{
    if(n<i)
        i=n;
    for(;i>=min && s[i]==0;i--);
    if(i<min)
    {
        calc(a+1);
        return;
    }
    if(i==n)
    {
        s[i]--;
        sum-=i;
        calc(a+1);
        sum+=i;
        s[i]++;
        return;
    }
    for(;i>=min && find==0;i--)
        if(s[i]>0)
        {
            s[i]--;
            sum-=i;
            dfs(a,n-i,i);
            sum+=i;
            s[i]++;
        }
}
