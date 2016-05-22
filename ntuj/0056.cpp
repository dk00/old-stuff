#include<cstdio>
#include<algorithm>
using namespace std;
int s[1000000];
main()
{
    int i,k,n;
    while(scanf("%d %d",&n,&k)==2)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        sort(s,s+n);
        for(i=0;i<k-1;i++)
            printf("%d ",s[i]);
        printf("%d\n",s[i]);
    }
}
