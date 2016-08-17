#include<set>
#include<cstdio>
using namespace std;
struct data
{
    int a,b;
    bool operator<(data d)const{return a<d.a ||(a==d.a && b<d.b);}
};
multiset<data> s;
main()
{
    int i,j,n,t,C;
    multiset<data>::iterator now,last;
    scanf("%d",&t);
    for(C=1;C<=t;C++)
    {
        scanf("%d",&n);
        s.clear();
        s.insert((data){-1,1000000001});
        s.insert((data){1000000001,-1});
        if(C>1)puts("");
        printf("Case #%d:\n",C);
        while(n--)
        {
            scanf("%d %d",&i,&j);
            while(1)
            {
                last=s.upper_bound((data){i,j});
                if(j>(now=last--)->b)
                    break;
                s.erase(*now);
            }
            if(j<last->b ||(i==last->a && j==last->b))
                s.insert((data){i,j});
            printf("%d\n",s.size()-2);
        }
    }
}
