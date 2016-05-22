#include<cstdio>
long long s[99];
main()
{
    int i,T;
    s[0]=s[1]=1,s[2]=5;
    for(i=3;i<=40;i++)
        s[i]=s[i-1]+4*s[i-2]+2*s[i-3];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&i);
        printf("%lld\n",s[i]);
    }
}
