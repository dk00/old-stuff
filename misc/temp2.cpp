#include<stdio.h>
int p,q,w,min,max,sum,find,stop,s[101];
void calc(int);
void dfs(int,int,int);
main()
{
    int i,k,n;
    while(1)
    {
        scanf("%d %d",&n,&w);
        if(n==0 && w==0)
            break;
        for(i=1;i<=50;i++)
            s[i]=0;
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",&k);
            s[k]++;
            if(min>k)
                min=k;
            if(max<k)
                max=k;
            sum+=k;
        }
        p=n,q=0;
        for(;;p=q,q=stop=0)
        {
            calc(0);
            printf("test %d\n",p);
            if(q==0)
                break;
        }
        printf("%d\n",p);
    }
}
void calc(int a)
{
    int i,j,b,tmp;
    for(tmp=0,i=min,b=0;i<=max;i++)
        for(j=0;j<s[i];j++)
        {
            if(tmp+i>w)
                tmp=0,b++;
            tmp+=i;
        }
    b++;
    if(a+b<p)
    {
        if(a+b>q)
            q=a+b;
        stop=1;
        return;
    }
    if(sum==0)
        return;
    for(i=max;s[i]<=0;i--);
    s[i]--;
    sum-=i;
    if(s[i]==w || sum==0)
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
    for(;i>=min && find==0 && stop==0;i--)
        if(s[i]>0)
        {
            s[i]--;
            sum-=i;
            dfs(a,n-i,i);
            sum+=i;
            s[i]++;
        }
}
