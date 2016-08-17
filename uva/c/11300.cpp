#include<cstdio>
#include<algorithm>
using namespace std;
long long s[1000001];
main()
{
    int i,n;
    unsigned long long sum;
    while(scanf("%d",&n)==1)
    {
        for(i=sum=0;i<n;i++)
        {
            scanf("%lld",s+i);
            sum+=s[i];
        }
        sum/=n;
        for(i=0;i<n;i++)
            s[i]-=sum;
        s[0]=0;
        for(i=2;i<n;i++)
            s[i]+=s[i-1];
        nth_element(s,s+n/2,s+n);
        for(i=sum=0;i<n;i++)
            if(s[i]>s[n/2])
                sum+=s[i]-s[n/2];
            else
                sum+=s[n/2]-s[i];
        printf("%llu\n",sum);
    }
}
