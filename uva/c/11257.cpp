#include<cstdio>
long long s[505];
char tmp[505];
main()
{
    int i,j,T;
    long long k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",tmp);
        for(i=0;tmp[i];i++)s[i+1]=0;
        for(i=0;tmp[i];i++)
            for(j=0,k=tmp[i]-'0';tmp[i+j] && k<=2147483647;k=k*10+tmp[i+(++j)]-'0')
                s[i+j+1]>?=s[i]+k;
        printf("%lld\n",s[i]);
    }
}
