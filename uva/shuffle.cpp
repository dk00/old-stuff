#include<cstdio>
#include<algorithm>
using namespace std;
int s[100000];
main()
{
    int i,n;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)s[i]=i;
        random_shuffle(s,s+n);
        for(i=0;i<n;i++)
            printf("%d ",s[i]);
        puts("");
    }
}
