#include<stdio.h>
const int inf=2000000000;
int w,p,q,min,max,sum,find,s[51];
void calc(int);
void dfs(int,int,int);
main()
{
    int i,j,k,n;
    while(1)
    {
        scanf("%d %d",&n,&w);
        for(i=1;i<=50;i++)
            s[i]=0;
        min=inf,max=0;
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",&k);
            if(min>k)
                min=k;
            if(max<k)
                max=k;
            sum+=k;
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
    if(sum==0)
    {
        find=a;
        return;
    }
    int i,b=(sum+w-1)/w;
    if(a+b>p)
    {
        if(a+b<q)
            q=a+b;
        return;
    }
    for(i=max;s[i]==0;i--);
    s[i]--;
    sum-=i;
    if(w-i<min)
        calc(a+1);
    else
        dfs(a,i,i);
    sum+=i;
    s[i]++;
}
void dfs(int a,int n,int i)
{
    if(i<w-n)
        i=w-n;
    for(;i>=min && s[i]==0;i--);
    if(i<min)
    {
        calc(a+1);
        return;
    }
    if(w-n<=max && s[w-n]>0)
    {
        s[w-n]--;
        sum-=w-n;
        calc(a+1);
        sum+=w-n;
        s[w-n]++;
        return;
    }
    for(;i>=min && find==0;i--)
        if(s[i]>0)
        {
            s[i]--;
            sum-=i;
            dfs(a,n+i,i);
            sum+=i;
            s[i]++;
        }
}
