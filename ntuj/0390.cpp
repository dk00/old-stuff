#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001,inf=2000000000;
int c[N],s[N];
main()
{
    int i,j,k,l,a,b,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n,&a,&b);
        for(i=0;i<n;i++)
            scanf("%d",c+i),s[i]=inf;
        sort(c,c+n);
        for(i=j=k=n-1;i>=0;i--)
        {
            while(j>i && c[j]>=c[i]+a)j--;
            while(k>i && c[k]>c[i]+b)k--;
            for(l=j+1;l<=k;l++)
                if(a<=c[l]-c[i] && c[l]-c[i]<=b)
                    s[i]<?=c[i]-s[l];
            if(s[i]>=inf)s[i]=c[i];
        }
        for(i=0,k=-inf;i<n;i++)
            if(a<=c[i] && c[i]<=b)
                k>?=s[i];
        if(k<=-inf)k=0;
        printf("%d\n",k);
    }
}
