#include<cstdio>
int s[2009];
int go(int st,int n)
{
    int a=0;
    if(n>2)a+=go(st,n/2)+go(st+n/2,n/2);
    a+=s[st]^s[st+n/2];
    s[st]|=s[st+n/2];
    return a;
}
main()
{
    int i,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        n=(1<<n);
        for(i=0;i<n;i++)s[i]=1;
        while(m--)
            scanf("%d",&i),s[i-1]=0;
        printf("%d\n",go(0,n));
    }
}
