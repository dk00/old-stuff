#include<cstdio>
const int N=50001;
int b[N],a[N],h[N];
main()
{
    int i,l,n,m,T;
    double j,k,t,sum;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(sum=k=i=0;i<n;i++)
        {
            scanf("%d %d %d %d",b+i,h+i,a+i,&l);
            a[i]*=l;
            sum+=a[i]*h[i];
            k>?=b[i]+h[i];
        }
        scanf("%d",&m);
        if(m>sum)
        {
            puts("OVERFLOW");
            continue;
        }
        for(j=0;j+1e-3<k;)
        {
            t=(j+k)/2;
            for(sum=i=0;i<n;i++)
                if(t>b[i])
                {
                    if(t-b[i]<h[i])
                        sum+=a[i]*(t-b[i]);
                    else
                        sum+=a[i]*h[i];
                }
            if(sum<m)j=t;
            else k=t;
        }
        t=(j+k)/2;
        printf("%.2lf\n",t);
    }
}
