#include<cstdio>
#include<algorithm>
using namespace std;
int s[1000000];
main()
{
    int i,k,n;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        scanf("%d",&k);
        nth_element(s,s+k-1,s+n);
        printf("%d\n",s[k-1]);
    }
}
