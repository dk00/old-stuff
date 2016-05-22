#include<cmath>
#include<cstdio>
main()
{
    int i,n,T;
    double sum;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n),sum=0;
        for(i=2;i<=n;i++)
            sum+=log10(i);
        printf("%.0lf\n",floor(sum)+1);
    }
}
