#include<cstdio>
#include<cstdlib>
long long s[50000];
main()
{
    int i,j,n,sum,T,C=0;
    char tmp[100];
    long long bit;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<=45000;i++)s[i]=0;
        s[0]=1,sum=0;
        scanf("%d",&n);
        bit=(1ll<<(n/2));
        if(n%2)bit|=(1ll<<(n/2+1));
        while(n--)
        {
            scanf("%d",&j);
            sum+=j;
            for(i=sum;i>=j;i--)
                s[i]|=(s[i-j]<<1);
        }
        for(i=sum/2;i>=0;i--)
            if(s[i]&bit)break;
        if(C++)puts("");
        printf("%d %d\n",i,sum-i);
    }
}
