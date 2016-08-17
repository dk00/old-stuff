#include<set>
#include<cstdio>
using namespace std;
struct p1
{
    int a,b;
    bool operator<(p1 x)const
    {
        return(a<x.a ||(a==x.a && b<x.b));
    }
};
main()
{
    set<p1> s;
    scanf("%d",&T);
    while(T--)
    {
        s.clear();
        s.insert((p1){-1,1000000001});
        s.insert((p1){1000000001,-1});
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d %d",&i,&j);
            p1 tmp=(p1){i,j};
            p1 *pre=s.upper_bound(tmp)-1;
            set<p1>::iterator st=s.upper_bound(tmp),ed;
            if((pre->a<i && pre->b<=j)||(pre->a<=i && pre->b<j))
            {
                printf("%d\n",s.size()-2);
                continue;
            }
            if(st->a==i && st->b==j)
            {
                s.insert(tmp);
                printf("%d\n",s.size()-2);
                continue;
            }
            for(ed=st;ed->b>=j;ed++);
            s.erase(st,ed);
            s.insert(tmp);
            printf("%d\n",s.size()-2);
        }
    }
}
