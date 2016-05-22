#include<set>
#include<string>
#include<cstdio>
using namespace std;
main()
{
    int i,j,k,n;
    multiset<string> s;
    char tmp1[100],tmp2[100];
    while(scanf("%d",&n)==1)
    {
        s.clear();
        n=1<<n;
        for(i=k=0;i<n;i++)
        {
            scanf("%s %s",tmp1,tmp2);
            s.insert((string)tmp2);
            j=s.count((string)tmp2);
            if(j>k)k=j;
        }
        for(i=-1;n>=k;i++,n/=2);
        printf("%d\n",i);
    }
}
