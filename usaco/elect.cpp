/*
TASK:elect
LANG:C++
*/
#include<cstdio>
#include<algorithm>
using namespace std;
struct tri
{
    int a,b,c;
    bool operator<(tri x)const{return a>x.a;}
}s[50001];
main()
{
    freopen("elect.in","r",stdin);
    freopen("elect.out","w",stdout);
    int i,j,k,n;
    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&s[i].a,&s[i].b);
        s[i].c=i;
    }
    sort(s,s+n);
    for(i=j=0;i<k;i++)
        if(s[i].b>s[j].b)j=i;
    printf("%d\n",s[j].c+1);
}
