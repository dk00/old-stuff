#include<cstdio>
main()
{
    int i,j,k,n,C=1;
    long long sum;
    while(scanf("%d",&n) && n)
    {
        for(i=2,sum=0;i<n/i;i++)
        {
            j=n/i,k=n/(i+1)+1;
            sum+=1ll*i*(j-1)+(i-1ll)*(j+k)*(j-k+1)/2;
        }
        if(i==n/i)
            sum+=i*(i-1);
        printf("Case %d: %lld\n",C++,sum);
    }
}
