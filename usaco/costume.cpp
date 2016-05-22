/*
TASK:costume
LANG:C++
*/
#include<cstdio>
#include<algorithm>
using namespace std;
int s[20001];
main()
{
    freopen("costume.in","r",stdin);
    freopen("costume.out","w",stdout);
    int i,j,n,m,sum;
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%d",s+i);
    sort(s,s+i);
    for(i=sum=0,j=n-1;i<=j;i++)
    {
        while(i<j && s[i]+s[j]>m)j--;
        sum+=j-i;
    }
    printf("%d\n",sum);
}
