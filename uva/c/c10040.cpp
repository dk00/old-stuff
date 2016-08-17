#include<cstdio>
char s[10000],u[10000];
main()
{
    int i,j,k,l,n;
    while(scanf("%d %s",&n,s))
    {
        for(i=(1<<n)-1;i>=0;i--)u[i]=0;
        for(l=0;s[l];l++);
        for(i=j=0;i<n-1;i++)
            j=j*2+s[i]-'0',s[l++]=s[i];
        s[l]=0;
        l=n=1<<n;
        for(;s[i];i++,l--)
        {
            j=j*2%n+s[i]-'0';
            if(u[j]++)break;
        }
        if(l || s[i])puts("fail");
        else puts("correct");
    }
}
