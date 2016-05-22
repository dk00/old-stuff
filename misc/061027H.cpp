#include<cstdio>
#include<algorithm>
int s[10000],u[10000];
int abs(int n){if(n<0)return -n;return n;}
int sum(int st,int ed)
{
    if(st>ed)return 0;
    if(st)return u[ed]-u[st-1];
    return u[ed];
}
int go(int st,int ed)
{
    int i,j,k,min=2147483647,max=-2147483647;
    for(i=j=st;i<=ed;i++)
    {
        if(i+1<=ed && s[i]==s[i+1])continue;
        k=abs(sum(st,i-1)-sum(i+1,ed));
        if(k<min ||(k==min && sum(st,i-1)>max))
            j=i,min=k,max=sum(st,i-1);
    }
    printf("%d",s[j]);
    if(st<j || j<ed)
    {
        putchar('(');
        if(st<j)
            go(st,j-1);
        if(st<j && j<ed)
            putchar(',');
        if(j<ed)
            go(j+1,ed);
        putchar(')');
    }
}
main()
{
    int i,j,n,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        std::sort(s,s+n);
        u[0]=s[0];
        for(i=1;i<n;i++)
            u[i]=u[i-1]+s[i];
        printf("Case #%d: ",C++);
        go(0,n-1);
        puts("");
    }
}


