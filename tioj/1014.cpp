#include<cstdio>
int n,t[16],s[16][65536];
int abs(int n){return n<0?-n:n;}
int go(int p,int u)
{
    if(s[p][u])return s[p][u];
    s[p][u]=2000000000;
    int i,tmp;
    for(i=0;i<n;i++)
        if(i!=p && (u&(1<<i)))
        {
            tmp=go(i,u&~(1<<p));
            if((tmp+abs(p-i))%t[p])
                tmp+=t[p]-(tmp+abs(p-i))%t[p];
            tmp+=abs(p-i);
            s[p][u]<?=tmp;
        }
    return s[p][u];
}
main()
{
    int i,j;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            scanf("%d",t+i),s[i][1<<i]=i+t[i]-i%t[i];
        j=go(0,(1<<n)-1);
        for(i=1;i<n;i++)
            j<?=go(i,(1<<n)-1);
        printf("%d\n",j);
    }
}
