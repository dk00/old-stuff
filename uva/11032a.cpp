#include<cstdio>
int sum,max,s[100];
void go(int n,int w,int i)
{
    if(w>sum-w)return;
    if(!n)
    {
        max>?=w;
        return;
    }
    for(;i>=0;i--)
        go(n-1,w+s[i],i-1);
}
main()
{
    int i,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",&s[i]);
            sum+=s[i];
        }
        max=0,go(n/2,0,n-1);
        if(n%2)go(n/2+1,0,n-1);
        printf("%d %d\n",max,sum-max);
    }
}
