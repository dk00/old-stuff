#include<set>
#include<cstdio>
using namespace std;
int add[30005],get[30005];
struct pair1
{
    int a,b;
    bool operator<(pair1 x)const{return(a<x.a ||(a==x.a && b<x.b));}
};
main()
{
    int i,j,n,m,T;
    pair1 x;
    multiset<pair1> s;
    multiset<pair1>::iterator ptr;
    scanf("%d",&T);
    while(T--)
    {
        s.clear();
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%d",add+i);
        for(i=0;i<m;i++)
            scanf("%d",get+i);
        ptr=s.begin();
        for(i=j=0;i<n && j<m;i++)
        {
            if(i && add[i]<ptr->a)ptr--;
            x=(pair1){add[i],i};
            s.insert(x);
            if(!i)ptr=s.begin();
            for(;j<m && i+1==get[j];j++,ptr++)
                printf("%d\n",ptr->a);
        }
        if(T)puts("");
    }
}
