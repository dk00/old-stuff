#include<cstdio>
#include<algorithm>
using namespace std;
main()
{
    int i,m,n;
    double j,k,l;
    while(scanf("%d",&n) && n)
    {
        l=-1;
        for(i=1;i<=n;i++)
        {
            scanf("%lf %lf",&j,&k);
            if(j>k)swap(j,k);
            if(min(j,k/4)>l)
                l=min(j,k/4),m=i;
            if(j/2>l)
                l=j/2,m=i;
        }
        printf("%d\n",m);
    }
}
