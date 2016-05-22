#include"bigint1a.h"
bigint s[505],p[505];
main()
{
    int i,j,k,n,T,C=1;
    s[0]=1;s[1]=0;
    for(i=2;i<502;i+=2)
    {
        s[i]=0;
        for(j=1;i-j>0;j++)
            s[i]+=s[j-1]*s[i-j-1];
    }
    p[0]=1;
    for(i=0;i<500;i+=2)
        for(j=2;i+j<=500;j+=2)
            p[i+j]+=p[i]*s[j];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("Case %d: %s\n",C++,p[n].tostr());
    }
}
