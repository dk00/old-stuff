#include<cstdio>
int pr[]={2,3,5,7,11,13,17,19,23,29};
int conv(int x)
{
    int i,res=0;
    for(i=0;i<10;i++)
        while(x%pr[i]==0)
            x/=pr[i],res^=(1<<i);
    if(x<0)res^=(1<<i);
    return res;
}
int s[2048];
main()
{
    int i,j,k,n,T;
    long long a,b,zero;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        for
        printf("%I64d %I64d\n",a,b);
    }
}
