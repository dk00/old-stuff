#include<cstdio>
main()
{
    for(i=3,m=0;i<31622;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<31622;j+=i*2)
            notp[j]=1;
        p[m++]=i;
    }
    while(scanf("%d",&n) && n>0)
    {
        for(k=n;k%2==0;k/=2);
        if(k==1)
        {
            printf("%d = %d + ... + %d\n",n,n,n);
            continue;
        }
        for(i=0;p[i]*p[i]<=k;i++)
            if(k%p[i]==0)break;
        if(k%p[i]==0)
        {
            printf("%d = %d + ... + %d\n",n,n/p[i]-
        }
    }
}
