#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
map<int,int> p,sum;
int tmp;
int find(int v)
{
    if(!p[v])return p[v]=v;
    if(v==p[v])
    {
        tmp=0;
        return v;
    }
    p[v]=find(p[v]);
    tmp+=sum[v];
    sum[v]=tmp;
    return p[v];
}
int val(int v)
{
    if(p[v]==v)return 0;
    return sum[v]+val(p[v]);
}
int uni(int a,int b,int x)
{
    find(a);
    find(b);
    int y=val(a)-val(b);
    a=find(a);
    b=find(b);
    if(a==b)return y;
    p[a]=b;
    sum[a]=x-y;
    return x;
}
main()
{
    int i,j,k,m;
    while(scanf("%d",&m)==1)
    {
        p.clear();
        sum.clear();
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            if(i>j)swap(i,j);
            j++;
            if(uni(i,j,k)!=k)
                printf("Bug Detected %d\n",val(i)-val(j));
            else
                puts("Accept");
        }
    }
}
