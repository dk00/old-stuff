#include<cstdio>
#include<algorithm>
const int inf=2147483647;
int s[1001],c[1001];
main()
{
    int i,j,n,m,t1,t2,t3,T,min,sum;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d %d",&t3,&t2,&t1,&m,&n);
        for(i=sum=0;i<n;i++)
            scanf("%d",&c[i]);
        std::sort(c,c+n);
        if(n)min=c[n-1]*t1;
        else min=0;
        s[n]=0;
        for(i=n-1;i>=0;i--)
        {
            s[i]=inf;
            for(j=i+1;j<=n;j++)
                s[i]<?=s[j]+(((c[j-1]-c[i]+1)/2*t1-(m-(c[i]+c[j-1])/2)*t3-s[j])>?0)+t2;
            if(i)sum=c[i-1]*t1;
            else sum=0;
            min<?=(s[i]+m*t3)>?sum;
        }
        printf("%d\n",min);
    }
}
