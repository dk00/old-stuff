/*
LANG:C++
TASK:tanning
*/
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
struct pt
{
    int a,b;
    bool operator<(pt x)const
    {
        return a<x.a;
    }
}s1[2500],s2[2500];
main()
{
    freopen("tanning.in","r",stdin);
    freopen("tanning.out","w",stdout);
    int i,j,k,n1,n2;
    priority_queue<int> h;
    scanf("%d %d",&n1,&n2);
    for(i=0;i<n1;i++)
        scanf("%d %d",&s1[i].a,&s1[i].b);
    for(i=0;i<n2;i++)
        scanf("%d %d",&s2[i].a,&s2[i].b);
    sort(s1,s1+n1);
    sort(s2,s2+n2);
    while(h.size())h.pop();
    for(i=j=k=0;i<n2;i++)
    {
        while(j<n1 && s2[i].a>=s1[j].a)
            h.push(-s1[j++].b);
        while(h.size() && -h.top()<s2[i].a)h.pop();
        while(s2[i].b-- && h.size() && -h.top()>=s2[i].a)
            h.pop(),k++;
    }
    printf("%d\n",k);
}
